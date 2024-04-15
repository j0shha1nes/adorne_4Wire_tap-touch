/*----------------------------------------------------------------------------
 *    ADORNE GEN 2 SOFTAP TRUE UNIVERSAL DIMMER
 *----------------------------------------------------------------------------
 *    File Name:     dimming_ctrl.c
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
#define _DIMMING_C   // for global variable declarations in user_main.h

#include <CY8C4124.h>
#include <user_main.h>
#include <project.h>

  
/*----------------------------------------------------------------------------
 *  Private Functions
 *---------------------------------------------------------------------------*/ 

/*----------------------------------------------------------------------------
 *  Public Interface
 *---------------------------------------------------------------------------*/ 

   
/*****************************************************************************
   Function button_response is run every time the tick counter reaches 
   pushbutton_interval.  For example, tick counter is increments 10 times, and 
   when it reaches this threshold, the buttons are read and action taken based
   on this update.
*****************************************************************************/
void button_response(void)
{
    #if(OvrldEndurance == 0)
    //DOUBLE TAP - Main On/Off Button
    if (TMR_Status.single_tap && PB_Status[PB_MAIN].switched_off)
    { 
        PWM_TARGET = PWM_MAX;
        if (DMR_Status.fade_off)
        {
            DMR_Status.fade_off = CLEAR;
            DMR_Status.fade_on = SET;  //Double Tap
            DMR_Status.on = SET;        
        }
    }

    //DOUBLE TAP - Plus OR Down Button
    if (TMR_Status.single_tap && (PB_Status[PB_UP].switched_off || PB_Status[PB_DOWN].switched_off))
    { 
        PWM_TARGET = PWM_MAX;
    }
    #endif
        
    // MAIN button 'turn on' command
    if (PB_Status[PB_MAIN].switched_off && DMR_Status.off && !DMR_Status.fade_off && !DMR_Status.fade_on && !DMR_Status.maxcalibration && !DMR_Status.mincalibration && !TMR_Status.single_tap)
    {
        DMR_Status.off = CLEAR;
        DMR_Status.throwrelay = SET;  //main button; off
        DMR_Status.fade_on = SET;  //main button; turn on
        #if(OvrldEndurance == 0)
        TMR_Status.single_tap = SET;
        #endif
    }
      
    // MAIN button 'turn off' command
    if (PB_Status[PB_MAIN].switched_off && DMR_Status.on && !DMR_Status.fade_off && !DMR_Status.fade_on && !DMR_Status.goto_bed && !DMR_Status.maxcalibration && !DMR_Status.mincalibration && !TMR_Status.single_tap)
    {
        DMR_Status.on = CLEAR;
        DMR_Status.fade_off = SET;
        #if(OvrldEndurance == 0)
        TMR_Status.single_tap = SET;
        #endif
    }
    
    #if(OvrldEndurance == 0)
    //'dimmer increase' from UP BUTTON press
    if (PB_Status[PB_UP].switched_off && DMR_Status.on && !DMR_Status.fade_off && !DMR_Status.fade_on && !TMR_Status.single_tap)
    {
        if(PWM_TARGET >= (PWM_MAX + PWM_CHG)) PWM_TARGET = Dimming_ReadCompare()-PWM_CHG;
        else PWM_TARGET = PWM_MAX;
          
        Dimming_WriteCompare(PWM_TARGET);
        if (!DMR_Status.maxcalibration) DMR_Status.store_status = SET;
    }
      
    //'dimmer decrease' from DOWN BUTTON press
    if (PB_Status[PB_DOWN].switched_off && DMR_Status.on && !DMR_Status.fade_off && !DMR_Status.fade_on)
    {
        if(PWM_TARGET <= (PWM_MIN - PWM_CHG)) PWM_TARGET = Dimming_ReadCompare()+PWM_CHG;
        else PWM_TARGET = PWM_MIN;
      
        Dimming_WriteCompare(PWM_TARGET);
        if (!DMR_Status.mincalibration) DMR_Status.store_status = SET;
    }
      
    //'turn on' from UP BUTTON press
    if (PB_Status[PB_UP].switched_off && DMR_Status.off && !DMR_Status.fade_off && !DMR_Status.fade_on)
    {
        DMR_Status.on = SET;
        DMR_Status.off = CLEAR;
        DMR_Status.throwrelay = SET;  //up button
        DMR_Status.fade_on = SET;
        DMR_Status.fade_off = CLEAR;
        TMR_Status.single_tap = SET;
    }
      
    //'turn on' from DOWN BUTTON press
    if (PB_Status[PB_DOWN].switched_off && DMR_Status.off && !DMR_Status.fade_off && !DMR_Status.fade_on)
    {
        DMR_Status.on = SET;
        DMR_Status.off = CLEAR;
        DMR_Status.throwrelay = SET;   //down button
        DMR_Status.fade_on = SET;
        DMR_Status.fade_off = CLEAR;
        TMR_Status.single_tap = SET;
    }
      
    //'dimmer decrease' from DOWN BUTTON hold
    if (PB_Status[PB_DOWN].held_on && DMR_Status.on)
    {
        if (TMR_Status.gp_100mS_tick) 
        {
            ++DMR_ADJ_CNT;
            TMR_Status.gp_100mS_tick = CLEAR;
            if (DMR_ADJ_CNT >= dimmer_adjust_interval)
            {
                if (DMR_ADJ_CNT % autorepeat == 0)
                {
                    if(PWM_TARGET <= (PWM_MIN - PWM_CHG)) PWM_TARGET = Dimming_ReadCompare()+PWM_CHG;
                    else PWM_TARGET = PWM_MIN;
              
                    Dimming_WriteCompare(PWM_TARGET);
                } 
            }
        }
    }
    else if (!PB_Status[PB_UP].held_on  && !DMR_Status.goto_bed) DMR_ADJ_CNT = 0;
      
    //'dimmer increase' from UP BUTTON hold
    if (PB_Status[PB_UP].held_on && DMR_Status.on)
    {
        if (TMR_Status.gp_100mS_tick) 
        {
            ++DMR_ADJ_CNT;
            TMR_Status.gp_100mS_tick = CLEAR;
            if (DMR_ADJ_CNT >= dimmer_adjust_interval)
            {
                if (DMR_ADJ_CNT % autorepeat == 0)
                {
                    if(PWM_TARGET >= (PWM_MAX + PWM_CHG)) PWM_TARGET = Dimming_ReadCompare()-PWM_CHG;
                    else PWM_TARGET = PWM_MAX;
              
                    Dimming_WriteCompare(PWM_TARGET);
                } 
            }
        }
    }
    else if (!PB_Status[PB_DOWN].held_on && !DMR_Status.goto_bed) DMR_ADJ_CNT = 0;
      
    // GOTO_BED
    if (DMR_Status.goto_bed && PB_Status[PB_MAIN].held_off)
        {  
            if (TMR_Status.gp_100mS_tick)
            {
                ++DMR_ADJ_CNT;
                TMR_Status.gp_100mS_tick = CLEAR;
                if (DMR_ADJ_CNT >= GOTO_BED_INTERVAL)
                {
                    Dimming_WriteCompare(Dimming_ReadCompare()+PWM_CHG);
                    DMR_ADJ_CNT = 0;
                    if (Dimming_ReadCompare() >= PWM_MIN) 
                    {
                        DMR_Status.off = SET;
                        Dimming_WriteCompare(PWM_MIN);
                        DMR_Status.on = CLEAR;
                    
                        #if(OvrldEndurance == 0)
                        DMR_Status.throwrelay = SET;  //gotobed off
                        #endif
                      
                        DMR_Status.goto_bed = CLEAR;
                        I_SENSE_ACC = 0;
                    }
                }
            }
        }
    else if (!PB_Status[PB_UP].held_on && !PB_Status[PB_DOWN].held_on) DMR_ADJ_CNT = 0;
    #endif
    
    //turn on or turn off transitions using fades
    if ((DMR_Status.fade_off || DMR_Status.fade_on) && !TMR_Status.single_tap)
    {  
        // 03-20-15: fade interval=4, pushbutton_interval=10; 
        // so every 4*10*1.1mS this will fall through
        if (++FADE_CNT >= fade_interval)            
        {                                                                        
        FADE_CNT = 0;
        if (DMR_Status.fade_on)
            {
                DMR_Status.on = SET;
                #if(OvrldEndurance == 0)
                Dimming_WriteCompare(Dimming_ReadCompare()-PWM_CHG);
                if (Dimming_ReadCompare() <= PWM_TARGET) 
                {
                    DMR_Status.fade_on = CLEAR;
                    Dimming_WriteCompare(PWM_TARGET);                                           // Always fade_on to the PWM_TARGET
                }
                #else
                DMR_Status.fade_on = CLEAR;
                #endif
            }
        if (DMR_Status.fade_off)
            {
                #if(OvrldEndurance == 0)
                Dimming_WriteCompare(Dimming_ReadCompare()+PWM_CHG);
                if (Dimming_ReadCompare() >= PWM_MIN) 
                {
                    Dimming_WriteCompare(PWM_MIN);
                    DMR_Status.fade_off = CLEAR;
                    DMR_Status.off = SET;
                    if (I_SENSE_ACC > i_sense_off) 
                    {
                        DMR_Status.throwrelay = SET;  //fade off end
                        I_SENSE_ACC = 0;
                    }
                }
                #else
                DMR_Status.off = SET;
                DMR_Status.fade_off = CLEAR;
                DMR_Status.throwrelay = SET;
                #endif
            }
        }
    }
    else FADE_CNT = 0;
    
    #if(OvrldEndurance == 0)
    //turn OFF dimmer due to zero current measured by current sensor
    if (I_SENSE_ACC == i_sense_off && DMR_Status.on && !DMR_Status.fade_on) 
    {
        DMR_Status.fade_off = CLEAR;
        DMR_Status.off = SET;
        Dimming_WriteCompare(PWM_MIN);
        DMR_Status.on = CLEAR;
    }
      
    //turn ON dimmer due to presence current measured by current sensor
    if (I_SENSE_ACC >= i_sense_threshold && DMR_Status.off  && !DMR_Status.fade_off) 
    {
        DMR_Status.off = CLEAR;
        DMR_Status.fade_on = SET;
        DMR_Status.on = SET;
        Dimming_WriteCompare(PWM_MIN);
    }
    

    //Exit calibration mode by pressing either the plus or minus button
    if ((DMR_Status.min_cal_adjust || DMR_Status.max_cal_adjust) && (PB_Status[PB_UP].switched_off || PB_Status[PB_DOWN].switched_off)) 
    {
        DMR_Status.mincalibration = CLEAR;
        DMR_Status.maxcalibration = CLEAR;
        DMR_Status.min_cal_adjust = CLEAR;
        DMR_Status.max_cal_adjust = CLEAR;
        DMR_Status.flash = CLEAR;
        DMR_Status.store_status = SET;
        
        if (PWM_MAX >= PWM_MIN - desired_dim_levels) 
        {
            PWM_MIN = PWM_MAX + desired_dim_levels;
            PWM_TARGET = PWM_MAX;
        }  
        
        if ((PWM_MIN - PWM_MAX)%desired_dim_levels != 0) 
        { 
            PWM_MIN -= (PWM_MIN - PWM_MAX)%desired_dim_levels;
        }
        
        PWM_CHG = ((PWM_MIN-PWM_MAX)/desired_dim_levels);
        
    }

      //Adjust PWM_MAX in CALIBRATION MODE
    if (DMR_Status.max_cal_adjust && PB_Status[PB_MAIN].switched_off)
    {
        if (Dimming_ReadCapture() >= (PWM_lower_max_limit+PWM_max_cal_chg_fine) && Dimming_ReadCapture() <= PWM_upper_min_limit)
        {
            if (Dimming_ReadCapture() < PWM_max_fine_mode)
            {
                Dimming_WriteCompare(Dimming_ReadCapture()-PWM_max_cal_chg_fine);
                PWM_MAX = Dimming_ReadCapture();
            }
            else
            {
                Dimming_WriteCompare(Dimming_ReadCapture()-PWM_max_cal_chg);
                PWM_MAX = Dimming_ReadCapture();
            }
        }
        else if (Dimming_ReadCapture() >=  PWM_lower_max_limit && Dimming_ReadCapture() < (PWM_lower_max_limit+PWM_max_cal_chg_fine)) 
        {
            Dimming_WriteCompare(PWM_upper_min_limit-PWM_max_cal_chg);  //reset to the boundary of the MINIMUM setting to
            PWM_MAX = Dimming_ReadCapture();
        }
         
    }

      //Adjust PWM_MIN in CALIBRATION MODE
    if (DMR_Status.min_cal_adjust && PB_Status[PB_MAIN].switched_off)
    {
        if (Dimming_ReadCapture() >= (PWM_lower_max_limit+(2*PWM_max_cal_chg)) && Dimming_ReadCapture() <= PWM_upper_min_limit)
        {
            Dimming_WriteCompare(Dimming_ReadCapture()-PWM_min_cal_chg);
            PWM_MIN = Dimming_ReadCapture();
        }
        else if (Dimming_ReadCapture() >= (PWM_lower_max_limit+desired_dim_levels) && Dimming_ReadCapture() < PWM_lower_max_limit+(2*PWM_max_cal_chg)) 
        {
            Dimming_WriteCompare(PWM_upper_min_limit);  //reset to the boundary of the MAXIMUM setting to 
            PWM_MIN = Dimming_ReadCapture();
        }
      
    }
    #endif
// Added this code to eliminate the possible bug where two button presses 1s apart inadvertantly
// allows SECOND_CNTR to be incremented to the gotobed_interval allowing the gotobed sequence to 
// start
  if (PB_Status[PB_MAIN].held_off && DMR_Status.on) SECOND_CNTR = 0;

}  //End of BUTTON RESPONSE Routine

/*****************************************************************************
Function Description:

*****************************************************************************/
#if(SofTap == 1)
    
void user_interface(uint8_t UI_VAL)
{
  
  switch (UI_VAL)
  {
    case 0:  //OFF
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
    
    case 1:

        LED_LO_Write(0);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
      
    case 2:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
      
      
    case 3:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
      
      
    case 4:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
      
      
    case 5:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
        
    
    case 6:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0xFF);
        
    break;
        
    
    case 7:  //FULL-ON
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
    
    }
}

#else

void user_interface(uint8_t UI_VAL)
{
  
  switch (UI_VAL)
  {
    case 0:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0xFF);
        
    break;
    
    case 1:

        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0xFF);
        LED_Hi_Write(0);
               
    break;
      
    case 2:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0xFF);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
      
      
    case 3:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0xFF);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
      
      
    case 4:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0xFF);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
      
      
    case 5:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0xFF);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
        
    
    case 6:
      
        LED_LO_Write(0xFF);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
        
    
    case 7:
      
        LED_LO_Write(0);
        LED_1_Write(0);
        LED_2_Write(0);
        LED_3_Write(0);
        LED_4_Write(0);
        LED_5_Write(0);
        LED_Hi_Write(0);
        
    break;
    
    }
}
    
#endif
