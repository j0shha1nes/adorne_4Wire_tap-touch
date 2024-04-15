/*----------------------------------------------------------------------------
 *    ADORNE GEN 2 SOFTAP TRUE UNIVERSAL DIMMER
 *----------------------------------------------------------------------------
 *    File Name:     user_main.c
 *    Description:   Main Program File for Gen. 2 sofTap 4-Wire Dimmer 
 *    Target:        Renesas R5F10268
 *    Environment:   IAR EWB for RL78 Version 1.40.1
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
#define _INTERRUPTS_C   // for global variable declarations in user_main.h

#include <interrupts.h>
#include <user_main.h>
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
 *  Interrupts - Listed in order of Priority where 1 is the highest priority
 *  1. zero_cross - this interrupt is serviced every rising edge of the comparator output.  
 *  ISR_PERIOD: 1/60cycles = 16.6667mS
 *  ISR_DURATION: 7µ - 10µS in duration
 *
 *  2. pwm_timer - this interrupt's sole purpose is to output a pseudo-analog value to the 
 *  constant current source that in turn varies the current through the LED front end of an 
 *  opto coupler.  The duty cycle of this PWM timer are controlled by the PWM_MIN and
 *  PWM_MAX values which can vary from 1% (PWM_lower_max_limit) to 54.5% (PWM_upper_min_limit).
 *  ISR_PERIOD: 1mS
 *  ISR_DURATION: 2µ - 3µS in duration
 *
 *  3.  Relay_Offset_timer - this general purpose timer interupts program flow every 50µS.  This
 *  function performs two important tasks.  First, it implements a precise offset from the zero 
 *  cross interrupt with which to fire the relay such that the relay contacts will close on or 
 *  close to a zero cross.  Second, the Relay_Offset_timer isr provides an opportunity to dim
 *  the display intensity at a (1/(PWM_display_interval*50µ))= 200Hz rate.  
 *  ISR_PERIOD: 50µS
 *  ISR_DURATION: 1µ - 6µS in duration
 *
 *---------------------------------------------------------------------------*/ 

/*********************************************************************************************************************************************/
void zero_cross(void) 
{
    Zero_Cross_ClearInterrupt(Zero_Cross_INTR);
    ZC_ISR_Disable();
    
    TICK_CNT = 0;
    
//    //test the oscilator frequency using the zero cross interrupt
//    if(ZC_TEST >= zc_test_min && ZC_TEST <= zc_test_max) MCU_OSC_ACC = 0;
//    else MCU_OSC_ACC++;
//    ZC_TEST = 0;
//    
//    if (MCU_OSC_ACC > 10) 
//    {
//        Relay_Offset_Sleep();
//    }
    
    if (DMR_Status.throwrelay) 
    {
        TMR_Status.zc_tick = SET;
    }
    
    #if(OvrldEndurance == 0)
    if (!DMR_Status.goto_bed && !DMR_Status.mincalibration && !DMR_Status.maxcalibration) 
    {
        UI_VAL = (user_interface_levels-((Dimming_ReadCompare()-PWM_MAX)/(PWM_CHG*translation_factor)))-1;
    }
    
    
    //Current Sensing Tasks
    if (I_SENSE_CNT >= i_presence_threshold_hi)                                   //current threshold must be exceeded in order to accumulate
    {
        I_SENSE_ACC += 2;                                                           //accumulate if not aleady at the threshold
        if (I_SENSE_ACC > i_sense_threshold) I_SENSE_ACC = i_sense_threshold;       //manage the overflow
    }
    else 
    {
        if (I_SENSE_CNT == 0) 
        {
            if (I_SENSE_ACC > 1) I_SENSE_ACC--;
            if (I_SENSE_ACC <= 1) I_SENSE_ACC = 0;                                //current not preset for at least part of c
        }
    }
    
    //One Second Timer made from zero cross counting
    if(++ZC_CNTR >= one_second_interval) 
    {
        TMR_Status.second = SET;
        
        if(PB_Status[PB_MAIN].held_on && DMR_Status.on) 
        {
            ++SECOND_CNTR;
        }
        else SECOND_CNTR = 0;
        
        //Enter Calibraton Mode - Maximum Cal
        if(PWM_TARGET <= PWM_MAX && PB_Status[PB_UP].held_on && !DMR_Status.maxcalibration)
        {
            if (++PWM_CAL_CNT >= PWM_cal_count_limit) 
            {
                DMR_Status.maxcalibration = SET;
                PWM_CAL_CNT = PWM_cal_count_limit;
            }                
        }
        
        //Enter Calibraton Mode - Minimum Cal
        if(PWM_TARGET >= PWM_MIN && PB_Status[PB_DOWN].held_on && !DMR_Status.mincalibration)
        {
            if (++PWM_CAL_CNT >= PWM_cal_count_limit) 
            {
                DMR_Status.mincalibration = SET;
                PWM_CAL_CNT = PWM_cal_count_limit;
            }
        }
        
        ZC_CNTR = 0;
    }
    
    //wait for the button release to set the calibration flag and reset the count
    if(DMR_Status.maxcalibration && !PB_Status[PB_UP].held_on && !DMR_Status.max_cal_adjust)
    {
        PWM_CAL_CNT = 0;
        DMR_Status.max_cal_adjust = SET;
    }
    
        //wait for the button release to set the calibration flag and reset the count
    if(DMR_Status.mincalibration && !PB_Status[PB_DOWN].held_on  && !DMR_Status.min_cal_adjust)
    {
        PWM_CAL_CNT = 0;
        DMR_Status.min_cal_adjust = SET;
    }
    #endif
    
    I_SENSE_CNT = 0;  

}   //End of Zero Cross ISR
/*********************************************************************************************************************************************/

/*********************************************************************************************************************************************/
void pwm_timer(void)
{
    Dimming_ClearInterrupt(Dimming_INTR_MASK_TC);   
    
    if (TMR_Status.single_tap)
    {
        if (++TICK_DBL_TAP >= double_tap_interval)
        {
            TICK_DBL_TAP = 0;
            TMR_Status.single_tap = CLEAR;
        }
    }
    
    TMR_Status.pwmtick = SET;

}  //End of the PWM Timer ISR

/*********************************************************************************************************************************************/
void Relay_Offset_timer(void) 
{
    Relay_Offset_ClearInterrupt(Relay_Offset_INTR_MASK_TC);
    
    TICK_CNT_100mS++;
    ZC_TEST++;
        
    PB_INTERVAL_TICK++;             // marks every 10mS for pushbutton measurement
    //re-enable zero cross interrupt after acceptable number of PWM counts
    if (++TICK_CNT >= full_cycle_count) ZC_ISR_Enable();
    
    //Attenuate the display to dim the bright LED's to some value
    TICK_CNT_Display++;
    
    if (TMR_Status.zc_tick && DMR_Status.throwrelay && !TMR_Status.ovldend_bug)
    {
        ++RELAY_CNT;
        if (DMR_Status.single_pole && RELAY_CNT >= relay_delay_1p && RELAY_CNT < Relay_coil_active && !TMR_Status.ovldend_bug) 
        {
            if (RELAY_CNT >= relay_delay_1p) 
            {
                Relay_3W_Write(0xFF);
                DMR_Status.coilactive = SET;
            }
        }
        else if (DMR_Status.three_way && RELAY_CNT >= relay_delay_3w && RELAY_CNT < Relay_coil_active && !TMR_Status.ovldend_bug)
        {
            if (RELAY_CNT >= relay_delay_3w) 
            {
                Relay_1P_Write(0xFF);
                DMR_Status.coilactive = SET;
            }
        }
        
        if (RELAY_CNT >= Relay_coil_active)
        {
            if (DMR_Status.single_pole)
            {
                DMR_Status.three_way = SET;
                DMR_Status.single_pole = CLEAR;
            }
            else
            {
                DMR_Status.three_way = CLEAR;
                DMR_Status.single_pole = SET;
            }
            RELAY_CNT = 0;
            #if(OvrldEndurance == 1)
            TMR_Status.ovldend_bug = SET;
            #endif
            DMR_Status.coilactive = CLEAR;
            DMR_Status.throwrelay = CLEAR;
            TMR_Status.zc_tick = CLEAR;
            Relay_3W_Write(0);
            Relay_1P_Write(0);
            I_SENSE_ACC = 0;                // reset the current sense accumlation
            if (DMR_Status.fade_on) I_SENSE_ACC = i_sense_threshold;
        }
    }
}
/*********************************************************************************************************************************************/
// end of interrupts.c
