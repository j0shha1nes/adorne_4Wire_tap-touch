
/*----------------------------------------------------------------------------
 *    ADORNE GEN 2 SOFTAP TRUE UNIVERSAL DIMMER
 *----------------------------------------------------------------------------
 *    File Name: CY8C4124.h
 *    Description: Maps platform independent macros to RL78G12 hardware.
 *       Provides interface for data flash functions in RL78G12.c.
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/               


// header files for tool-provided peripheral drivers
#include <project.h>
           

/*----------------------------------------------------------------------------
 *  Macros and Constants
 *---------------------------------------------------------------------------*/   

// Digital input pins
#define ON_SW           SW_Main_Read()          // On/off switch  
#define DN_SW           SW_Minus_Read()         // Down switch      
#define UP_SW           SW_Plus_Read()          // Up switch       
#define I_SENSE         I_Sense_Read()          // Analog comparator output

//Digital ouptut pins
//#define LED_1_on()      LED_1_Write(0)          // Turn LED_1 on


/* WDT counter configuration */
#define WDT_COUNT0_MATCH    (0x02u)     // Wdog Prescaler of 2 => LFCLK (32khz)/2 = 16khz
#define WDT_COUNT1_MATCH    (0x4000u)   // Wdog Timeout = 16384*(1/16khz) = 1.024 seconds

#define SERVICE_WDT()       CySysWdtUnlock(); \
                            CySysWdtResetCounters(CY_SYS_WDT_COUNTER1_RESET); \
                            CySysWdtLock()
                                                              
// data flash                              
#define nonvol_t           pfdl_u08 // platform independent type
#define pfdl_u08           uint8_t   // platform independent type
#define A_SIZE             8

                              
// interrupts and low power modes                              
#define DISABLE_INTERRUPTS()  __disable_interrupt()
#define ENABLE_INTERRUPTS()   __enable_interrupt()
#define ENTER_LOW_POWER()     __halt()
                                    
/*----------------------------------------------------------------------------
 *  Global Variables
 *---------------------------------------------------------------------------*/ 
extern uint8_t volatile NON_VOL_A[A_SIZE];
//extern pfdl_u08    NON_VOL_A[B_SIZE];

/*----------------------------------------------------------------------------
 *  Public Function Prototypes
 *---------------------------------------------------------------------------*/ 
void init_data_flash(void);
void write_data_flash(void);
void read_data_flash(void);
