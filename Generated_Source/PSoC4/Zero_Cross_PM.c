/*******************************************************************************
* File Name: Zero_Cross_PM.c
* Version 1.10
*
* Description:
*  This file provides the power management source code APIs for the
*  Comparator.
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

#include "Zero_Cross.h"

#if(!Zero_Cross_CHECK_DEEPSLEEP_SUPPORT)
    static Zero_Cross_BACKUP_STRUCT Zero_Cross_backup =
    {
        0u, /* enableState */
    };
#endif /* (Zero_Cross_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: Zero_Cross_SaveConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Zero_Cross_RestoreConfig
********************************************************************************
*
* Summary:
*  Empty function. Included for consistency with other components.
*
* Parameters:
*  None
*
* Return:
*  None
*
********************************************************************************/
void Zero_Cross_RestoreConfig(void)
{

}


/*******************************************************************************
* Function Name: Zero_Cross_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Comp_Sleep() function before 
*  calling the CySysPmDeepSleep() or the CySysPmHibernate() functions.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_Sleep(void)
{
#if(!Zero_Cross_CHECK_DEEPSLEEP_SUPPORT)
    if(Zero_Cross_CHECK_PWR_MODE_OFF)
    {
        Zero_Cross_backup.enableState = 1u;
        Zero_Cross_Stop();
    }
    else /* Component is disabled */
    {
        Zero_Cross_backup.enableState = 0u;
    }
#endif /* (Zero_Cross_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: Zero_Cross_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  was called. The Wakeup() function will also re-enable the component. 
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_Wakeup(void)
{
#if(!Zero_Cross_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != Zero_Cross_backup.enableState)
    {
        /* Enable Comp's operation */
        Zero_Cross_Enable();
    } /* Do nothing if Comp was disabled before */
#endif /* (Zero_Cross_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */

