/*******************************************************************************
* File Name: Test.c  
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
#include "Test.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        Test_PC =   (Test_PC & \
                                (uint32)(~(uint32)(Test_DRIVE_MODE_IND_MASK << (Test_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (Test_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: Test_Write
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
void Test_Write(uint8 value) 
{
    uint8 drVal = (uint8)(Test_DR & (uint8)(~Test_MASK));
    drVal = (drVal | ((uint8)(value << Test_SHIFT) & Test_MASK));
    Test_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: Test_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  Test_DM_STRONG     Strong Drive 
*  Test_DM_OD_HI      Open Drain, Drives High 
*  Test_DM_OD_LO      Open Drain, Drives Low 
*  Test_DM_RES_UP     Resistive Pull Up 
*  Test_DM_RES_DWN    Resistive Pull Down 
*  Test_DM_RES_UPDWN  Resistive Pull Up/Down 
*  Test_DM_DIG_HIZ    High Impedance Digital 
*  Test_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void Test_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(Test__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: Test_Read
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
*  Macro Test_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 Test_Read(void) 
{
    return (uint8)((Test_PS & Test_MASK) >> Test_SHIFT);
}


/*******************************************************************************
* Function Name: Test_ReadDataReg
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
uint8 Test_ReadDataReg(void) 
{
    return (uint8)((Test_DR & Test_MASK) >> Test_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(Test_INTSTAT) 

    /*******************************************************************************
    * Function Name: Test_ClearInterrupt
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
    uint8 Test_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(Test_INTSTAT & Test_MASK);
		Test_INTSTAT = maskedStatus;
        return maskedStatus >> Test_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
