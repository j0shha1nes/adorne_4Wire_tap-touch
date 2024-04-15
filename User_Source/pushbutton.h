
/*----------------------------------------------------------------------------
 *    ADORNE GEN 2 SOFTAP TRUE UNIVERSAL DIMMER
 *----------------------------------------------------------------------------
 *    File Name:     pushbutton.h
 *    Description:   Header file to include when using pushbutton.c
 *----------------------------------------------------------------------------
 *    Notes:
 *    1. 
 *----------------------------------------------------------------------------
 *    This code is the property of P&S Division of Legrand Corporation.
 *    Copyright (c) 2012-2014 Legrand Corp. All rights reserved.
 *---------------------------------------------------------------------------*/

/*----------------------------------------------------------------------------
 *    Public Function Prototypes
 *---------------------------------------------------------------------------*/     
void init_pb_status(void);
void read_pushbutton(uint8_t pb);
#if(SofTap == 0)
  void init_ct_status(void);
#endif