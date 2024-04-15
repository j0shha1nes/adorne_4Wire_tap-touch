/*******************************************************************************
* File Name: LED_LO.c  
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
#include "LED_LO.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        LED_LO_PC =   (LED_LO_PC & \
                                (uint32)(~(uint32)(LED_LO_DRIVE_MODE_IND_MASK << (LED_LO_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (LED_LO_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: LED_LO_Write
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
void LED_LO_Write(uint8 value) 
{
    uint8 drVal = (uint8)(LED_LO_DR & (uint8)(~LED_LO_MASK));
    drVal = (drVal | ((uint8)(value << LED_LO_SHIFT) & LED_LO_MASK));
    LED_LO_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: LED_LO_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  LED_LO_DM_STRONG     Strong Drive 
*  LED_LO_DM_OD_HI      Open Drain, Drives High 
*  LED_LO_DM_OD_LO      Open Drain, Drives Low 
*  LED_LO_DM_RES_UP     Resistive Pull Up 
*  LED_LO_DM_RES_DWN    Resistive Pull Down 
*  LED_LO_DM_RES_UPDWN  Resistive Pull Up/Down 
*  LED_LO_DM_DIG_HIZ    High Impedance Digital 
*  LED_LO_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void LED_LO_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(LED_LO__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: LED_LO_Read
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
*  Macro LED_LO_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 LED_LO_Read(void) 
{
    return (uint8)((LED_LO_PS & LED_LO_MASK) >> LED_LO_SHIFT);
}


/*******************************************************************************
* Function Name: LED_LO_ReadDataReg
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
uint8 LED_LO_ReadDataReg(void) 
{
    return (uint8)((LED_LO_DR & LED_LO_MASK) >> LED_LO_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(LED_LO_INTSTAT) 

    /*******************************************************************************
    * Function Name: LED_LO_ClearInterrupt
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
    uint8 LED_LO_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(LED_LO_INTSTAT & LED_LO_MASK);
		LED_LO_INTSTAT = maskedStatus;
        return maskedStatus >> LED_LO_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
