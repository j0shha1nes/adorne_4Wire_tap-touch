
/*----------------------------------------------------------------------------
 *    ADORNE SOFTAP 4-WIRE DIMMER
 *----------------------------------------------------------------------------
 *    File Name:     user_main.c
 *    Description:   Main Program File for sofTap 4-Wire Dimmer 
 *    Target:        Cypress CY8C4124LQI-443
 *    Environment:   PSoC Creator  3.1 SP3 (3.1.0.2288)
 *    Author:        Josh Haines
 *    Specification: Document #TBD
 *----------------------------------------------------------------------------
 *    Revisions:
 *    1.00  Initial revision JPH 10/20/2014
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/
#define _MAIN_C   // for global variable declarations in user_main.h

#include <user_main.h>
#include <pushbutton.h>
#include <dimming_ctrl.h>
#include <project.h>
#include <CY8C4124.h>

  
/*----------------------------------------------------------------------------
 *  Private Functions
 *---------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------
 *  Public Interface
 *---------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------
 *  user_main() 
 *---------------------------------------------------------------------------*/ 
int main(void)
{
    Test_Write(0);
    
    
    read_data_flash();
    
    init_dimmer_status();
    init_pb_status();
    
    CyGlobalIntEnable;
    
    #if(SofTap == 0)
    // captouch status
    init_ct_status();               // Init CapSense pushbutton status reg
    CapSense_1_Start();	            // Start the CapSense component    
    CapSense_1_InitializeAllBaselines();  //Loads the CapSense Baseline array with initial values by scanning
    #endif    //  CapSense Initialization
    
    while (FOREVER)
    {   
        #if(Wdog_Enable)
        SERVICE_WDT();       // strobe WDog - confirms no endless loop, action timer & interrupts running
        #endif
        Test_Write(~Test_ReadDataReg());
        PWM_CURRENT = Dimming_ReadCompare();
        
        #if(OvrldEndurance == 0)
    // Gotobed calculation and set flag
        if (SECOND_CNTR >= gotobed_interval && !DMR_Status.min_cal_adjust && !DMR_Status.max_cal_adjust)
        {
            DMR_Status.goto_bed = SET;
            GOTO_BED_INTERVAL = (gotobed_totaltime*gotobed_scalefactor)/((PWM_MIN-PWM_TARGET)/PWM_CHG); 
            //scaled so that is always takes about 25s to 'go to bed'
            SECOND_CNTR = 0;
        }
        #endif
    
    //Determine positve versus negative half cycle
        if (Zero_Cross_GetCompare() == 0) 
        {
            TMR_Status.pos_half = CLEAR;
            TMR_Status.neg_half = SET;
        }
        else 
        {
            TMR_Status.pos_half = SET;
            TMR_Status.neg_half = CLEAR;
        }
        

    //Collect Current Sense Data
        if (TMR_Status.pwmtick && I_Sense_Read() == HIGH && TMR_Status.neg_half) 
        {
            if (++I_SENSE_CNT > max_current_sense) I_SENSE_CNT = max_current_sense;
        }

    // Poll buttons and take the appropriate actions
        if (PB_INTERVAL_TICK >= pushbutton_interval)
        {
            
        #if(SofTap == 0)
            // captouch status
            CapTouch_Scan();      
        #endif
            
            read_pushbutton(PB_MAIN);
            read_pushbutton(PB_UP);
            read_pushbutton(PB_DOWN);
            
            button_response();
            
            PB_INTERVAL_TICK = 0;
        }  
        
        #if(OvrldEndurance == 0)
    // EEPROM Write if requested; checked and performed once per second
        if (DMR_Status.store_status && TMR_Status.second)
        {
            NON_VOL_A[PWM_Max_High] = (PWM_MAX>>8); 
            NON_VOL_A[PWM_Max_Low] = PWM_MAX & 0xFF; 
            NON_VOL_A[PWM_Min_High] = (PWM_MIN>>8); 
            NON_VOL_A[PWM_Min_Low] = PWM_MIN & 0xFF; 
            NON_VOL_A[PWM_Trgt_High] = (PWM_TARGET>>8); 
            NON_VOL_A[PWM_Trgt_Low] = PWM_TARGET & 0xFF;
            // store key so that future cal updates
            // won't be overwritten after power cycle   
            NON_VOL_A[Cal_Key] = cal_key_value;
            write_data_flash();
            DMR_Status.store_status = CLEAR;
        }
        #endif
        
    // Drive Display to current value; also manages the dimming component
        if (TICK_CNT_Display >= PWM_display_interval) 
        {
            TICK_CNT_Display = 0;
            if ((DMR_Status.on || DMR_Status.fade_off || DMR_Status.fade_on) && !DMR_Status.throwrelay) 
            {
                user_interface(UI_VAL);
                LED_Main_Write(0xFF);
                LED_Plus_Write(0);
                LED_Minus_Write(0);
            }
            else 
            {
                user_interface(0);
                LED_Main_Write(0);
                LED_Plus_Write(0xFF);
                LED_Minus_Write(0xFF);
            }
        }
        if (TICK_CNT_Display >= PWM_display_on_off) LED_Main_Write(0xFF);
        if (TICK_CNT_Display >= PWM_display_bargraph) user_interface(0);
        if (TICK_CNT_Display >= PWM_display_plusminus)
        {
            LED_Plus_Write(0xFF);
            LED_Minus_Write(0xFF);
        }
        
    // Perform 100mS increment tasks
        if (TICK_CNT_100mS >= pwm_100mS_count)
        {
        TICK_CNT_100mS = 0;
        TMR_Status.gp_100mS_tick = SET;
        gp_100mS_timer();
        }
        
    // Reset timer flags
        TMR_Status.pwmtick = CLEAR;         //TMR_Status.pwmtick set in the PWM interrupt
        TMR_Status.second = CLEAR;          //clear the second flag
        
        
        CySysPmSleep();
    }
}
 //end of user_main()


/*----------------------------------------------------------------------------
 *  Initialize Dimmer
 *---------------------------------------------------------------------------*/ 
void init_dimmer_status(void)
{
    if (NON_VOL_A[Cal_Key] != cal_key_value)
    // calibration not valid, load eeprom with defaults  
    {
        NON_VOL_A[PWM_Max_High] = (PWM_max_default>>8); 
        NON_VOL_A[PWM_Max_Low] = PWM_max_default & 0xFF; 
        NON_VOL_A[PWM_Min_High] = (PWM_min_default>>8); 
        NON_VOL_A[PWM_Min_Low] = PWM_min_default & 0xFF; 
        NON_VOL_A[PWM_Trgt_High] = (PWM_min_default>>8); 
        NON_VOL_A[PWM_Trgt_Low] = PWM_min_default & 0xFF;
        //NON_VOL_A[I_Thresh_Saved] = I_THRESH_DEF;
        // store key so that future cal updates
        // won't be overwritten after power cycle   
        NON_VOL_A[Cal_Key] = cal_key_value;
        write_data_flash();
    }  

    // load ram with cal values from eeprom
    PWM_MIN = (uint16_t)(NON_VOL_A[PWM_Min_High]<<8);
    PWM_MIN += (uint16_t)NON_VOL_A[PWM_Min_Low];
    PWM_MAX = (uint16_t)(NON_VOL_A[PWM_Max_High]<<8);
    PWM_MAX += (uint16_t)NON_VOL_A[PWM_Max_Low];
    PWM_TARGET = (uint16_t)(NON_VOL_A[PWM_Trgt_High]<<8);
    PWM_TARGET += (uint16_t)NON_VOL_A[PWM_Trgt_Low];

    //Calculate the amount of up and down incremental change based on the min and max stored values
    PWM_CHG = ((PWM_MIN-PWM_MAX)/desired_dim_levels);
    
    
    
    DMR_Status.on = CLEAR;
    DMR_Status.off = SET;
    DMR_Status.fade_on = CLEAR;
    DMR_Status.fade_off = CLEAR;
    DMR_Status.goto_bed = CLEAR;
    DMR_Status.single_pole = SET;
    DMR_Status.three_way = CLEAR;
    DMR_Status.store_status = CLEAR;
    DMR_Status.mincalibration = CLEAR;
    DMR_Status.maxcalibration = CLEAR;
    TMR_Status.single_tap = CLEAR;
    
    ZC_ISR_Start();                 // Enable, Set Priority and Start the ZC ISR
    Zero_Cross_Start();             // Setup and Enable the Analog Comparator
    
    #if(OvrldEndurance == 0)
    PWM_ISR_Start();                // PWM Interupt Service Routine
    Dimming_Start();                // PWM Timer; 1000 counts * 1uS source = 1mS Timer
    Opto_PWM_Start();               // Constant Current Control OpAmp
    #endif
    
    Relay_Fire_ISR_Start();         // Relay first ISR timer is used to zero cross closes for the relay 
    Relay_Offset_Start();           // 50µS Timer
    
    /*
    2016-09-22: there appears to be a hang-up issue where at Rocom, on the test fixture, when
    the unit is changed from 1P to 3W, the unit appears to dim beyond the boundaries established
    by PWM_MIN and PWM_MAX and consequently, while fading on (when it comes into range, the bargraph 
    increases from min to max, thus fade_on) none of the other buttons work because it is in an 
    endless loop.
    Change 1: A change was made to the default values in the "Dimming" pwm timer block in the 
    schematic where the default compare value is changed to PWM_min_default (545); the original 
    was 250, which is not a conducive value to the prescribed values allowed
    Change 2: Immediately following this description is a PWM Write command that initializes 
    the starting point of the PWM value at any given POR
    */
    Dimming_WriteCompare(PWM_MIN);
    
    #ifdef Wdog_Enable
    // Enable Watchdog
    /* WDT is clocked by LFCLK which for the CY84125 is the 32kHz ILO */
    /* Note: ILO accuracy is +/- 60% over voltage & temperature range */
    /* The WDT counters should be cleared by calling the CySysWdtResetCounters() */
    /* Set WDT counter 0 to generate interrupt on match */
    /* Cntr 0 = 0x7FFF (32767 * 1/32000) = 1 second & Cntr 1 = 0x08 gives 8 second Wdog window */

    /* Update from Carl Finke - 08182015
    Cntr0 is a prescaler when Cntr0 & Cntr1 are cascaded
    Cntr0 = 2 then 32khz = 16khz and Cntr1 = 65535 then 4(5) second Timeout
    */
    /* NOTE: Wdog can only be checked w/o emulator - appears to just hangup & does not respond if
            Wdog trips.  Verify using programmed part.
    */

    // Set Cntr0 as Free Running - No action on match for cntr 0
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER0, CY_SYS_WDT_MODE_NONE);
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER0, WDT_COUNT0_MATCH);
    CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER0, 1u);
    
    /* Enable WDT counters 0 and 1 cascade */
    CySysWdtWriteCascade(CY_SYS_WDT_CASCADE_01);
    
    /* Set WDT counter 1 to generate reset on match */
    CySysWdtWriteMode(CY_SYS_WDT_COUNTER1, CY_SYS_WDT_MODE_RESET);
    CySysWdtWriteMatch(CY_SYS_WDT_COUNTER1, WDT_COUNT1_MATCH);
    CySysWdtWriteClearOnMatch(CY_SYS_WDT_COUNTER1, 1u);

    /* Enable WDT counters 0 and 1 */
    CySysWdtEnable(CY_SYS_WDT_COUNTER0_MASK | CY_SYS_WDT_COUNTER1_MASK);

    /* Lock WDT registers and try to disable WDT counters 0 and 1 */
    /* If not commented out, the counters can not be reset & Reset occurs */
    CySysWdtLock();
    //End of WatchDog Initialization & Setup
    #endif
}

/*----------------------------------------------------------------------------
 *  General Purpose 100mS
 *---------------------------------------------------------------------------*/
void gp_100mS_timer(void)  //called from the PWM Timer
{ 
    if (DMR_Status.goto_bed || DMR_Status.maxcalibration || DMR_Status.mincalibration)
    {    
        if (++FLASH_CNT >= flash_threshold)
        {
            DMR_Status.flash = ~DMR_Status.flash;
            FLASH_CNT = 0;
        }
    
        if (DMR_Status.flash) UI_VAL = (user_interface_levels-((Dimming_ReadCompare()-PWM_MAX)/(PWM_CHG*translation_factor)))-2;
        else UI_VAL = (user_interface_levels-((Dimming_ReadCompare()-PWM_MAX)/(PWM_CHG*translation_factor)))-1;
    }

    if (TMR_Status.ovldend_bug) 
    {
        ++Nuisance_Trigger;  
        DMR_Status.coilactive = CLEAR;
        DMR_Status.throwrelay = CLEAR;
        TMR_Status.zc_tick = CLEAR;
        Relay_3W_Write(0);
        Relay_1P_Write(0);
    }
    else Nuisance_Trigger = 0;
    
    if (Nuisance_Trigger >= dead_zone) 
    {
        TMR_Status.ovldend_bug = CLEAR;
    }

}


#if(SofTap == 0)
    
//    captouch status
/*----------------------------------------------------------------------------
 * CapTouch_Scan() - use Renesas Capacitive Touch routines for keyscan
 * PadCnt determines which Pad is currently being scanned
 * Both Single & Multiple key detection is used
 * Returned code sets key bit in CT_Status register
 *---------------------------------------------------------------------------*/ 
void CapTouch_Scan(void)
{
//     PSoC
            /* Update all baselines */
        CapSense_1_UpdateEnabledBaselines();      //Check the CapSense array - update baselines
        
   		/* Start scanning all enabled sensors */
    	CapSense_1_ScanEnabledWidgets();
    
        /* Wait for scanning to complete */
		while(CapSense_1_IsBusy() != 0) {}			/* Loop until condition true */
        // ON/OFF Key check
        if ( CapSense_1_CheckIsWidgetActive(CapSense_1_SENSOR_MAIN__BTN)  == 1)
        {
       		CT_Status.ON_SWCPS = 0;    // Key Pressed
            //LED_Status_Write(0);    //Toggle Status LED on MCU board
       	}else{
        	CT_Status.ON_SWCPS = 1;    // Key Released
            //LED_Status_Write(1);    //Toggle Status LED on MCU board
        }
        
        // DOWN Key check
        if ( (CapSense_1_CheckIsWidgetActive(CapSense_1_SENSOR_PLUS__BTN) == 1) ) 
        {
            CT_Status.UP_SWCPS = 0;    // Key Pressed
	    }else{
		    CT_Status.UP_SWCPS = 1;    // Key Released
        }
        
        // UP Key check
        if ( (CapSense_1_CheckIsWidgetActive(CapSense_1_SENSOR_MINUS__BTN) == 1) ) 
        {
            CT_Status.DN_SWCPS = 0;    // Key Pressed
	    }else{
		    CT_Status.DN_SWCPS = 1;    // Key Released
        }
               
} 
#endif