/*******************************************************************************
* File Name: Dimming_PM.c
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

#include "Dimming.h"

static Dimming_BACKUP_STRUCT Dimming_backup;


/*******************************************************************************
* Function Name: Dimming_SaveConfig
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
void Dimming_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Dimming_Sleep
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
void Dimming_Sleep(void)
{
    if(0u != (Dimming_BLOCK_CONTROL_REG & Dimming_MASK))
    {
        Dimming_backup.enableState = 1u;
    }
    else
    {
        Dimming_backup.enableState = 0u;
    }

    Dimming_Stop();
    Dimming_SaveConfig();
}


/*******************************************************************************
* Function Name: Dimming_RestoreConfig
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
void Dimming_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Dimming_Wakeup
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
void Dimming_Wakeup(void)
{
    Dimming_RestoreConfig();

    if(0u != Dimming_backup.enableState)
    {
        Dimming_Enable();
    }
}


/* [] END OF FILE */
