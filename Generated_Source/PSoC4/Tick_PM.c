/*******************************************************************************
* File Name: Tick_PM.c
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

#include "Tick.h"

static Tick_BACKUP_STRUCT Tick_backup;


/*******************************************************************************
* Function Name: Tick_SaveConfig
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
void Tick_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Tick_Sleep
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
void Tick_Sleep(void)
{
    if(0u != (Tick_BLOCK_CONTROL_REG & Tick_MASK))
    {
        Tick_backup.enableState = 1u;
    }
    else
    {
        Tick_backup.enableState = 0u;
    }

    Tick_Stop();
    Tick_SaveConfig();
}


/*******************************************************************************
* Function Name: Tick_RestoreConfig
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
void Tick_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Tick_Wakeup
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
void Tick_Wakeup(void)
{
    Tick_RestoreConfig();

    if(0u != Tick_backup.enableState)
    {
        Tick_Enable();
    }
}


/* [] END OF FILE */
