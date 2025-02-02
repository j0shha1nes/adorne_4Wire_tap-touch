/*******************************************************************************
* File Name: Relay_Cal_PM.c
* Version 2.0
*
* Description:
*  This file contains the setup, control, and status commands to support
*  the component operations in the low power mode.
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Relay_Cal.h"

static Relay_Cal_BACKUP_STRUCT Relay_Cal_backup;


/*******************************************************************************
* Function Name: Relay_Cal_SaveConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to save here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Relay_Cal_Sleep
********************************************************************************
*
* Summary:
*  Stops the component operation and saves the user configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_Sleep(void)
{
    if(0u != (Relay_Cal_BLOCK_CONTROL_REG & Relay_Cal_MASK))
    {
        Relay_Cal_backup.enableState = 1u;
    }
    else
    {
        Relay_Cal_backup.enableState = 0u;
    }

    Relay_Cal_Stop();
    Relay_Cal_SaveConfig();
}


/*******************************************************************************
* Function Name: Relay_Cal_RestoreConfig
********************************************************************************
*
* Summary:
*  All configuration registers are retention. Nothing to restore here.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Relay_Cal_Wakeup
********************************************************************************
*
* Summary:
*  Restores the user configuration and restores the enable state.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_Wakeup(void)
{
    Relay_Cal_RestoreConfig();

    if(0u != Relay_Cal_backup.enableState)
    {
        Relay_Cal_Enable();
    }
}


/* [] END OF FILE */
