
/*----------------------------------------------------------------------------
 *    ADORNE 4-WIRE SOFTAP DIMMER
 *----------------------------------------------------------------------------
 *    File Name: CY8C4124.c
 *    Description: Implements EEPROM read/write functions for Cypress MCU, CY8C4124.
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2013 - 2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/   
#include <CY8C4124.h>
#include <user_main.h>

// Must declare EEprom segment as constant
const uint8 CYCODE EEprom[]=
{ 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};

void init_data_flash(void)
{
   uint8_t i;

   // initialize RAM buffer
   for (i=0;i<A_SIZE;i++) 
   {
      NON_VOL_A[i] = 0xff;
   }
}


void write_data_flash(void)
{
        Relay_Cal_Bytes_Write(&NON_VOL_A[0],&EEprom[0],8u);
}

void read_data_flash(void)
{
uint8 i;
    for(i=0;i<A_SIZE;i++)
    {
        NON_VOL_A[i] = *(volatile uint8_t *) &EEprom[i];  
        //2016-03-15: needed *(volatile uint8_t *) conditioner when optimizing
    }
}

