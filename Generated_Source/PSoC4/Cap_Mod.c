/*******************************************************************************
* File Name: Cap_Mod.c  
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
#include "Cap_Mod.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Cap_Mod_PC =   (Cap_Mod_PC & \
                                (uint32)(~(uint32)(Cap_Mod_DRIVE_MODE_IND_MASK << (Cap_Mod_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Cap_Mod_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Cap_Mod_Write
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
void Cap_Mod_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Cap_Mod_DR & (uint8)(~Cap_Mod_MASK));
    drVal = (drVal | ((uint8)(value << Cap_Mod_SHIFT) & Cap_Mod_MASK));
    Cap_Mod_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Cap_Mod_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Cap_Mod_DM_STRONG     Strong Drive 
*  Cap_Mod_DM_OD_HI      Open Drain, Drives High 
*  Cap_Mod_DM_OD_LO      Open Drain, Drives Low 
*  Cap_Mod_DM_RES_UP     Resistive Pull Up 
*  Cap_Mod_DM_RES_DWN    Resistive Pull Down 
*  Cap_Mod_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Cap_Mod_DM_DIG_HIZ    High Impedance Digital 
*  Cap_Mod_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Cap_Mod_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Cap_Mod__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Cap_Mod_Read
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
*  Macro Cap_Mod_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Cap_Mod_Read(void) 
{
    return (uint8)((Cap_Mod_PS & Cap_Mod_MASK) >> Cap_Mod_SHIFT);
}


/*******************************************************************************
* Function Name: Cap_Mod_ReadDataReg
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
uint8 Cap_Mod_ReadDataReg(void) 
{
    return (uint8)((Cap_Mod_DR & Cap_Mod_MASK) >> Cap_Mod_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Cap_Mod_INTSTAT) 

    /*******************************************************************************
    * Function Name: Cap_Mod_ClearInterrupt
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
    uint8 Cap_Mod_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Cap_Mod_INTSTAT & Cap_Mod_MASK);
		Cap_Mod_INTSTAT = maskedStatus;
        return maskedStatus >> Cap_Mod_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
