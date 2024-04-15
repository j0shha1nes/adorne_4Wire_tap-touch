/*******************************************************************************
* File Name: OPTO_Drv.c  
* Version 2.10
*
* Description:
*  This file contains API to enable firmware control of a Pins component.
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#include "cytypes.h"
#include "OPTO_Drv.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        OPTO_Drv_PC =   (OPTO_Drv_PC & \
                                (uint32)(~(uint32)(OPTO_Drv_DRIVE_MODE_IND_MASK << (OPTO_Drv_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (OPTO_Drv_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: OPTO_Drv_Write
********************************************************************************
*
* Summary:
*  Assign a new value to the digital port's data output register.  
*
* Parameters:  
*  prtValue:  The value to be assigned to the Digital Port. 
*
* Return: 
*  None 
*  
*******************************************************************************/
void OPTO_Drv_Write(uint8 value) 
{
    uint8 drVal = (uint8)(OPTO_Drv_DR & (uint8)(~OPTO_Drv_MASK));
    drVal = (drVal | ((uint8)(value << OPTO_Drv_SHIFT) & OPTO_Drv_MASK));
    OPTO_Drv_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: OPTO_Drv_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  OPTO_Drv_DM_STRONG     Strong Drive 
*  OPTO_Drv_DM_OD_HI      Open Drain, Drives High 
*  OPTO_Drv_DM_OD_LO      Open Drain, Drives Low 
*  OPTO_Drv_DM_RES_UP     Resistive Pull Up 
*  OPTO_Drv_DM_RES_DWN    Resistive Pull Down 
*  OPTO_Drv_DM_RES_UPDWN  Resistive Pull Up/Down 
*  OPTO_Drv_DM_DIG_HIZ    High Impedance Digital 
*  OPTO_Drv_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void OPTO_Drv_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(OPTO_Drv__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: OPTO_Drv_Read
********************************************************************************
*
* Summary:
*  Read the current value on the pins of the Digital Port in right justified 
*  form.
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value of the Digital Port as a right justified number
*  
* Note:
*  Macro OPTO_Drv_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 OPTO_Drv_Read(void) 
{
    return (uint8)((OPTO_Drv_PS & OPTO_Drv_MASK) >> OPTO_Drv_SHIFT);
}


/*******************************************************************************
* Function Name: OPTO_Drv_ReadDataReg
********************************************************************************
*
* Summary:
*  Read the current value assigned to a Digital Port's data output register
*
* Parameters:  
*  None 
*
* Return: 
*  Returns the current value assigned to the Digital Port's data output register
*  
*******************************************************************************/
uint8 OPTO_Drv_ReadDataReg(void) 
{
    return (uint8)((OPTO_Drv_DR & OPTO_Drv_MASK) >> OPTO_Drv_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(OPTO_Drv_INTSTAT) 

    /*******************************************************************************
    * Function Name: OPTO_Drv_ClearInterrupt
    ********************************************************************************
    *
    * Summary:
    *  Clears any active interrupts attached to port and returns the value of the 
    *  interrupt status register.
    *
    * Parameters:  
    *  None 
    *
    * Return: 
    *  Returns the value of the interrupt status register
    *  
    *******************************************************************************/
    uint8 OPTO_Drv_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(OPTO_Drv_INTSTAT & OPTO_Drv_MASK);
		OPTO_Drv_INTSTAT = maskedStatus;
        return maskedStatus >> OPTO_Drv_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
