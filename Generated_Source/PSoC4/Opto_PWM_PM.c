/*******************************************************************************
* File Name: Opto_PWM_PM.c
* Version 1.10
*
* Description:
*  This file provides the power management source code to the API for the
*  Opamp (Analog Buffer) component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Opto_PWM.h"

#if(!Opto_PWM_CHECK_DEEPSLEEP_SUPPORT)
    static Opto_PWM_BACKUP_STRUCT Opto_PWM_backup =
    {
        0u, /* enableState */
    };
#endif /* (Opto_PWM_CHECK_DEEPSLEEP_SUPPORT) */


/*******************************************************************************
* Function Name: Opto_PWM_SaveConfig
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
void Opto_PWM_SaveConfig(void)
{

}


/*******************************************************************************
* Function Name: Opto_PWM_RestoreConfig
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
void Opto_PWM_RestoreConfig(void)
{
    
}


/*******************************************************************************
* Function Name: Opto_PWM_Sleep
********************************************************************************
*
* Summary:
*  This is the preferred API to prepare the component for sleep. The Sleep() API 
*  saves the current component state. Call the Sleep() function before calling the 
*  CySysPmDeepSleep() or the CySysPmHibernate() functions. The "Deep sleep operation" 
*  option has an influence on this function implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opto_PWM_backup: The structure field 'enableState' is modified
*  depending on the enable state of the block before entering the sleep mode.
*
*******************************************************************************/
void Opto_PWM_Sleep(void)
{
#if(!Opto_PWM_CHECK_DEEPSLEEP_SUPPORT)
    if(Opto_PWM_CHECK_PWR_MODE_OFF)
    {
        Opto_PWM_backup.enableState = 1u;
        Opto_PWM_Stop();
    }
    else /* The component is disabled */
    {
        Opto_PWM_backup.enableState = 0u;
    }
#endif /* (Opto_PWM_CHECK_DEEPSLEEP_SUPPORT) */
}


/*******************************************************************************
* Function Name: Opto_PWM_Wakeup
********************************************************************************
*
* Summary:
*  This is the preferred API to restore the component to the state when Sleep() 
*  is called. If the component has been enabled before the Sleep() function is 
*  called, the Wakeup() function will also re-enable the component.
*  The "Deep sleep operation" option has an influence on this function
*  implementation.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Opto_PWM_backup: The structure field 'enableState' is used to
*  restore the enable state of block after wakeup from sleep mode.
*
*******************************************************************************/
void Opto_PWM_Wakeup(void)
{
#if(!Opto_PWM_CHECK_DEEPSLEEP_SUPPORT)
    if(0u != Opto_PWM_backup.enableState)
    {
        /* Enable Opamp's operation */
        Opto_PWM_Enable();
    } /* Do nothing if Opamp was disabled before */
#endif /* (Opto_PWM_CHECK_DEEPSLEEP_SUPPORT) */
}


/* [] END OF FILE */
