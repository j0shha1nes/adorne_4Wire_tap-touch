/*******************************************************************************
* File Name: Opto_PWM.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the Opamp (Analog Buffer)
*  Component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Opto_PWM.h"

uint8 Opto_PWM_initVar = 0u; /* Defines if component was initialized */
static uint32 Opto_PWM_internalPower = 0u; /* Defines component Power value */


/*******************************************************************************
* Function Name: Opto_PWM_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opto_PWM_Init(void)
{
    Opto_PWM_internalPower = Opto_PWM_POWER;
    Opto_PWM_CTB_CTRL_REG = Opto_PWM_DEFAULT_CTB_CTRL;
    Opto_PWM_OA_RES_CTRL_REG = Opto_PWM_DEFAULT_OA_RES_CTRL;
    Opto_PWM_OA_COMP_TRIM_REG = Opto_PWM_DEFAULT_OA_COMP_TRIM_REG;
}


/*******************************************************************************
* Function Name: Opto_PWM_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opto_PWM_Enable(void)
{
    Opto_PWM_OA_RES_CTRL_REG |= Opto_PWM_internalPower | \
                                        Opto_PWM_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: Opto_PWM_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables power 
*  to the block. The first time the routine is executed, the Power level, Mode, 
*  and Output mode are set. When called to restart the Opamp following a Stop() call, 
*  the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opto_PWM_initVar: Used to check the initial configuration, modified
*  when this function is called for the first time.
*
*******************************************************************************/
void Opto_PWM_Start(void)
{
    if( 0u == Opto_PWM_initVar)
    {
        Opto_PWM_Init();
        Opto_PWM_initVar = 1u;
    }
    Opto_PWM_Enable();
}


/*******************************************************************************
* Function Name: Opto_PWM_Stop
********************************************************************************
*
* Summary:
*  Turn off the Opamp block.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Opto_PWM_Stop(void)
{
    Opto_PWM_OA_RES_CTRL_REG &= ((uint32)~(Opto_PWM_OA_PWR_MODE_MASK | \
                                                   Opto_PWM_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: Opto_PWM_SetPower
********************************************************************************
*
* Summary:
*  Sets the Opamp to one of the three power levels.
*
* Parameters:
*  power: power levels.
*   Opto_PWM_LOW_POWER - Lowest active power
*   Opto_PWM_MED_POWER - Medium power
*   Opto_PWM_HIGH_POWER - Highest active power
*
* Return:
*  None
*
**********************************************************************************/
void Opto_PWM_SetPower(uint32 power)
{
    uint32 tmp;
    
    Opto_PWM_internalPower = Opto_PWM_GET_OA_PWR_MODE(power);
    tmp = Opto_PWM_OA_RES_CTRL_REG & \
           (uint32)~Opto_PWM_OA_PWR_MODE_MASK;
    Opto_PWM_OA_RES_CTRL_REG = tmp | Opto_PWM_internalPower;
}


/*******************************************************************************
* Function Name: Opto_PWM_PumpControl
********************************************************************************
*
* Summary:
*  Allows the user to turn the Opamp's boost pump on or off. By Default the Start() 
*  function turns on the pump. Use this API to turn it off. The boost must be 
*  turned on when the supply is less than 2.7 volts and off if the supply is more 
*  than 4 volts.
*
* Parameters:
*  onOff: Control the pump.
*   Opto_PWM_PUMP_OFF - Turn off the pump
*   Opto_PWM_PUMP_ON - Turn on the pump
*
* Return:
*  None
*
**********************************************************************************/
void Opto_PWM_PumpControl(uint32 onOff)
{
    
    if(0u != onOff)
    {
        Opto_PWM_OA_RES_CTRL |= Opto_PWM_OA_PUMP_EN;    
    }
    else
    {
        Opto_PWM_OA_RES_CTRL &= (uint32)~Opto_PWM_OA_PUMP_EN;
    }
}


/* [] END OF FILE */
