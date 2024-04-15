/*----------------------------------------------------------------------------
 *    ADORNE SOFTAP 4-WIRE DIMMER
 *----------------------------------------------------------------------------
 *    File Name: dimming.h
 *    Description: Compilation options, global variables, constants, enums, 
 *       typedefs, and prototypes for public functions in user_main.c.  
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/   
//#include "RL78G12.h"    // maps pltform independent macros to RL78 G12 hardware
#include <CY8C4124.h>

/*----------------------------------------------------------------------------
 *  Function Prototypes
 *---------------------------------------------------------------------------*/ 
void button_response(void);      //this routine uses the button presses 
                                //to effect the pwm, LED's and 

void sensor_response(void);

void user_interface(uint8_t);