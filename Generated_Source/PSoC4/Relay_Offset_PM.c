/*******************************************************************************
* File Name: Relay_Offset_PM.c
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

#include "Relay_Offset.h"

static Relay_Offset_BACKUP_STRUCT Relay_Offset_backup;


/*******************************************************************************
* Function Name: Relay_Offset_SaveConfig
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
void Relay_Offset_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Relay_Offset_Sleep
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
void Relay_Offset_Sleep(void)
{
    if(0u != (Relay_Offset_BLOCK_CONTROL_REG & Relay_Offset_MASK))
    {
        Relay_Offset_backup.enableState = 1u;
    }
    else
    {
        Relay_Offset_backup.enableState = 0u;
    }

    Relay_Offset_Stop();
    Relay_Offset_SaveConfig();
}


/*******************************************************************************
* Function Name: Relay_Offset_RestoreConfig
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
void Relay_Offset_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Relay_Offset_Wakeup
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
void Relay_Offset_Wakeup(void)
{
    Relay_Offset_RestoreConfig();

    if(0u != Relay_Offset_backup.enableState)
    {
        Relay_Offset_Enable();
    }
}


/* [] END OF FILE */
