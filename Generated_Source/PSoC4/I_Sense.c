/*******************************************************************************
* File Name: I_Sense.c  
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
#include "I_Sense.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        I_Sense_PC =   (I_Sense_PC & \
                                (uint32)(~(uint32)(I_Sense_DRIVE_MODE_IND_MASK << (I_Sense_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (I_Sense_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: I_Sense_Write
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
void I_Sense_Write(uint8 value) 
{
    uint8 drVal = (uint8)(I_Sense_DR & (uint8)(~I_Sense_MASK));
    drVal = (drVal | ((uint8)(value << I_Sense_SHIFT) & I_Sense_MASK));
    I_Sense_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: I_Sense_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  I_Sense_DM_STRONG     Strong Drive 
*  I_Sense_DM_OD_HI      Open Drain, Drives High 
*  I_Sense_DM_OD_LO      Open Drain, Drives Low 
*  I_Sense_DM_RES_UP     Resistive Pull Up 
*  I_Sense_DM_RES_DWN    Resistive Pull Down 
*  I_Sense_DM_RES_UPDWN  Resistive Pull Up/Down 
*  I_Sense_DM_DIG_HIZ    High Impedance Digital 
*  I_Sense_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void I_Sense_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(I_Sense__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: I_Sense_Read
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
*  Macro I_Sense_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 I_Sense_Read(void) 
{
    return (uint8)((I_Sense_PS & I_Sense_MASK) >> I_Sense_SHIFT);
}


/*******************************************************************************
* Function Name: I_Sense_ReadDataReg
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
uint8 I_Sense_ReadDataReg(void) 
{
    return (uint8)((I_Sense_DR & I_Sense_MASK) >> I_Sense_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(I_Sense_INTSTAT) 

    /*******************************************************************************
    * Function Name: I_Sense_ClearInterrupt
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
    uint8 I_Sense_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(I_Sense_INTSTAT & I_Sense_MASK);
		I_Sense_INTSTAT = maskedStatus;
        return maskedStatus >> I_Sense_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
