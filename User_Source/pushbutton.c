
/*----------------------------------------------------------------------------
 *    ADORNE GEN 2 SOFTAP TRUE UNIVERSAL DIMMER
 *----------------------------------------------------------------------------
 *    File Name:     pushbutton.c
 *    Description:   Pushbutton functions
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2012-2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/
#include "user_main.h"
#include "project.h"
#include "CY8C4124.h"
  
/*----------------------------------------------------------------------------
 *    Public Functions
 *---------------------------------------------------------------------------*/     
/*----------------------------------------------------------------------------
 *    init_pb_status() - clears global pushbutton status structures
 *---------------------------------------------------------------------------*/      
void init_pb_status(void)
{
   PB_Status[PB_MAIN].switched_on = 0;
   PB_Status[PB_MAIN].held_on = 0;
   PB_Status[PB_MAIN].switched_off = 0;
   PB_Status[PB_MAIN].held_off = 1;
   PB_Status[PB_UP].switched_on = 0;
   PB_Status[PB_UP].held_on = 0;
   PB_Status[PB_UP].switched_off = 0;
   PB_Status[PB_UP].held_off = 1;
   PB_Status[PB_DOWN].switched_on = 0;
   PB_Status[PB_DOWN].held_on = 0;
   PB_Status[PB_DOWN].switched_off = 0;
   PB_Status[PB_DOWN].held_off = 1;
}

#if(SofTap == 0)
/*----------------------------------------------------------------------------
 *    init_ct_status() - initializes CapTouch status register
 *---------------------------------------------------------------------------*/      
void init_ct_status(void)
{
  CT_Status.ON_SWCPS = 1;           // init On/Off key to Not Active
  CT_Status.UP_SWCPS = 1;           // init Up key to Not Active
  CT_Status.DN_SWCPS = 1;           // init Down key to Not Active
}
#endif

/*----------------------------------------------------------------------------
 *    read_pushbutton() - reads and debounces pushbutton, 
 *       updates global status 
 *---------------------------------------------------------------------------*/
void read_pushbutton(uint8_t pb)
{
   static uint8_t active_count[3] = {0,0,0};
   static uint8_t inactive_count[3] = {0,0,0};
   uint8_t pushbutton;   
   uint8_t pb_switched_on;
   uint8_t pb_held_down;
   uint8_t pb_switched_off;
   uint8_t pb_held_open;
   
   // read present switch position, and determine previous state, 
#if(SofTap == 1)

   switch (pb)
   { 
      case PB_MAIN:
         pushbutton = SW_Main_Read();  
         break;  
      case PB_UP:
         pushbutton = SW_Plus_Read(); 
         break;
      case PB_DOWN:
         pushbutton = SW_Minus_Read(); 
         break;  
   } 
#else
   switch (pb)
   { 
      case PB_MAIN:
         pushbutton = CT_Status.ON_SWCPS;
         break;  
      case PB_UP:
         pushbutton = CT_Status.UP_SWCPS;
         break;
      case PB_DOWN:
         pushbutton = CT_Status.DN_SWCPS;
         break;  
   }      
#endif




   // had problem debugging bit variables, led to awkward coding style 
   if(PB_Status[pb].switched_on) pb_switched_on = 1;
   else pb_switched_on = 0;
   if(PB_Status[pb].held_on) pb_held_down = 1;
   else pb_held_down = 0;
   if(PB_Status[pb].switched_off) pb_switched_off = 1;
   else pb_switched_off = 0;
   if(PB_Status[pb].held_off) pb_held_open = 1;
   else pb_held_open = 0;
    
   // implement debounce, and update global status 
   if (pushbutton == SW_PRESSED)  
   // active low pushbutton is pressed
   {
      active_count[pb] += 1;
      inactive_count[pb] = 0;
      //require successive pushbutton active readings to debounce
      if (active_count[pb] >= pb_debounce_press)
      {
      // switch press debounce complete
         // update status byte
         if (pb_held_down == TRUE) return; // no change, still held down 
         else  if (pb_switched_on == TRUE) // change state to pb_held_down
         {
            PB_Status[pb].switched_on = CLEAR;
            PB_Status[pb].held_on = SET;
         }
         else  // change state to pb_switched_on
         {
            PB_Status[pb].switched_on = SET;
            PB_Status[pb].switched_off = CLEAR;   
            PB_Status[pb].held_off = CLEAR;   
         }
         active_count[pb] = pb_debounce_press;   // prevent wrapping             
      }
      // debounce complete  
   } 
   // switch press processing complete  
   
   else                 
   // pushbutton is released
   {
      inactive_count[pb] += 1;
      active_count[pb] = 0;
      //require successive pushbutton inactive readings to debounce
      if (inactive_count[pb] >= pb_debounce_release)
      {
      // switch released debounce complete
         // update status byte
         if (pb_held_open == TRUE) return;   // no change, still held open 
         else  if (pb_switched_off == TRUE)  // change state to pb_held_open
         {
            PB_Status[pb].switched_off = CLEAR;
            PB_Status[pb].held_off = SET;
         }
         else  // change state to pb_switched_off
         {
            PB_Status[pb].switched_off = SET;
            PB_Status[pb].switched_on = CLEAR;   
            PB_Status[pb].held_on = CLEAR;   
         }
         inactive_count[pb] = pb_debounce_release;    // prevent wrapping
      }
      // debounce complete
   } 
   // switch release processing complete  
}

