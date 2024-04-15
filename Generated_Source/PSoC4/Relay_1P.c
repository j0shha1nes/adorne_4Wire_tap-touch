/*******************************************************************************
* File Name: Relay_1P.c  
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
#include "Relay_1P.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Relay_1P_PC =   (Relay_1P_PC & \
                                (uint32)(~(uint32)(Relay_1P_DRIVE_MODE_IND_MASK << (Relay_1P_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Relay_1P_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Relay_1P_Write
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
void Relay_1P_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Relay_1P_DR & (uint8)(~Relay_1P_MASK));
    drVal = (drVal | ((uint8)(value << Relay_1P_SHIFT) & Relay_1P_MASK));
    Relay_1P_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Relay_1P_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Relay_1P_DM_STRONG     Strong Drive 
*  Relay_1P_DM_OD_HI      Open Drain, Drives High 
*  Relay_1P_DM_OD_LO      Open Drain, Drives Low 
*  Relay_1P_DM_RES_UP     Resistive Pull Up 
*  Relay_1P_DM_RES_DWN    Resistive Pull Down 
*  Relay_1P_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Relay_1P_DM_DIG_HIZ    High Impedance Digital 
*  Relay_1P_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Relay_1P_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Relay_1P__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Relay_1P_Read
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
*  Macro Relay_1P_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Relay_1P_Read(void) 
{
    return (uint8)((Relay_1P_PS & Relay_1P_MASK) >> Relay_1P_SHIFT);
}


/*******************************************************************************
* Function Name: Relay_1P_ReadDataReg
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
uint8 Relay_1P_ReadDataReg(void) 
{
    return (uint8)((Relay_1P_DR & Relay_1P_MASK) >> Relay_1P_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Relay_1P_INTSTAT) 

    /*******************************************************************************
    * Function Name: Relay_1P_ClearInterrupt
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
    uint8 Relay_1P_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Relay_1P_INTSTAT & Relay_1P_MASK);
		Relay_1P_INTSTAT = maskedStatus;
        return maskedStatus >> Relay_1P_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
