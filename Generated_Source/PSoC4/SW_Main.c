/*******************************************************************************
* File Name: SW_Main.c  
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
#include "SW_Main.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        SW_Main_PC =   (SW_Main_PC & \
                                (uint32)(~(uint32)(SW_Main_DRIVE_MODE_IND_MASK << (SW_Main_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (SW_Main_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: SW_Main_Write
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
void SW_Main_Write(uint8 value) 
{
    uint8 drVal = (uint8)(SW_Main_DR & (uint8)(~SW_Main_MASK));
    drVal = (drVal | ((uint8)(value << SW_Main_SHIFT) & SW_Main_MASK));
    SW_Main_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: SW_Main_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  SW_Main_DM_STRONG     Strong Drive 
*  SW_Main_DM_OD_HI      Open Drain, Drives High 
*  SW_Main_DM_OD_LO      Open Drain, Drives Low 
*  SW_Main_DM_RES_UP     Resistive Pull Up 
*  SW_Main_DM_RES_DWN    Resistive Pull Down 
*  SW_Main_DM_RES_UPDWN  Resistive Pull Up/Down 
*  SW_Main_DM_DIG_HIZ    High Impedance Digital 
*  SW_Main_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void SW_Main_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(SW_Main__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: SW_Main_Read
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
*  Macro SW_Main_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 SW_Main_Read(void) 
{
    return (uint8)((SW_Main_PS & SW_Main_MASK) >> SW_Main_SHIFT);
}


/*******************************************************************************
* Function Name: SW_Main_ReadDataReg
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
uint8 SW_Main_ReadDataReg(void) 
{
    return (uint8)((SW_Main_DR & SW_Main_MASK) >> SW_Main_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(SW_Main_INTSTAT) 

    /*******************************************************************************
    * Function Name: SW_Main_ClearInterrupt
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
    uint8 SW_Main_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(SW_Main_INTSTAT & SW_Main_MASK);
		SW_Main_INTSTAT = maskedStatus;
        return maskedStatus >> SW_Main_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
