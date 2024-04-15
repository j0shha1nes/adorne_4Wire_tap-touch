/*******************************************************************************
* File Name: SW_Plus.c  
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
#include "SW_Plus.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SW_Plus_PC =   (SW_Plus_PC & \
                                (uint32)(~(uint32)(SW_Plus_DRIVE_MODE_IND_MASK << (SW_Plus_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SW_Plus_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SW_Plus_Write
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
void SW_Plus_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SW_Plus_DR & (uint8)(~SW_Plus_MASK));
    drVal = (drVal | ((uint8)(value << SW_Plus_SHIFT) & SW_Plus_MASK));
    SW_Plus_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SW_Plus_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SW_Plus_DM_STRONG     Strong Drive 
*  SW_Plus_DM_OD_HI      Open Drain, Drives High 
*  SW_Plus_DM_OD_LO      Open Drain, Drives Low 
*  SW_Plus_DM_RES_UP     Resistive Pull Up 
*  SW_Plus_DM_RES_DWN    Resistive Pull Down 
*  SW_Plus_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SW_Plus_DM_DIG_HIZ    High Impedance Digital 
*  SW_Plus_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SW_Plus_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SW_Plus__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SW_Plus_Read
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
*  Macro SW_Plus_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SW_Plus_Read(void) 
{
    return (uint8)((SW_Plus_PS & SW_Plus_MASK) >> SW_Plus_SHIFT);
}


/*******************************************************************************
* Function Name: SW_Plus_ReadDataReg
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
uint8 SW_Plus_ReadDataReg(void) 
{
    return (uint8)((SW_Plus_DR & SW_Plus_MASK) >> SW_Plus_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SW_Plus_INTSTAT) 

    /*******************************************************************************
    * Function Name: SW_Plus_ClearInterrupt
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
    uint8 SW_Plus_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SW_Plus_INTSTAT & SW_Plus_MASK);
		SW_Plus_INTSTAT = maskedStatus;
        return maskedStatus >> SW_Plus_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
