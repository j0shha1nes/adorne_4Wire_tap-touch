
/*----------------------------------------------------------------------------
 *    ADORNE SOFTAP 4-WIRE DIMMER
 *----------------------------------------------------------------------------
 *    File Name: interrupts.h
 *    Description: Compilation options, global variables, constants, enums, 
 *       typedefs, and prototypes for public functions in interrupts.c.  
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/   
//#include "RL78G12.h"    // maps pltform independent macros to RL78 G12 hardware

/*----------------------------------------------------------------------------
 *  Function Prototypes
 *---------------------------------------------------------------------------*/ 
void gp_100mS_timer(void); //this is a general purpose timer set to 1S period
void zero_cross(void);
void pwm_timer(void);
void Relay_Offset_timer(void);

