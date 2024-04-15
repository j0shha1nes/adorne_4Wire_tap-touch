/*******************************************************************************
* File Name: ZC_NInv.c  
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
#include "ZC_NInv.h"

#define SetP4PinDriveMode(shift, mode)  \
    do { \
        ZC_NInv_PC =   (ZC_NInv_PC & \
                                (uint32)(~(uint32)(ZC_NInv_DRIVE_MODE_IND_MASK << (ZC_NInv_DRIVE_MODE_BITS * (shift))))) | \
                                (uint32)((uint32)(mode) << (ZC_NInv_DRIVE_MODE_BITS * (shift))); \
    } while (0)


/*******************************************************************************
* Function Name: ZC_NInv_Write
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
void ZC_NInv_Write(uint8 value) 
{
    uint8 drVal = (uint8)(ZC_NInv_DR & (uint8)(~ZC_NInv_MASK));
    drVal = (drVal | ((uint8)(value << ZC_NInv_SHIFT) & ZC_NInv_MASK));
    ZC_NInv_DR = (uint32)drVal;
}


/*******************************************************************************
* Function Name: ZC_NInv_SetDriveMode
********************************************************************************
*
* Summary:
*  Change the drive mode on the pins of the port.
* 
* Parameters:  
*  mode:  Change the pins to one of the following drive modes.
*
*  ZC_NInv_DM_STRONG     Strong Drive 
*  ZC_NInv_DM_OD_HI      Open Drain, Drives High 
*  ZC_NInv_DM_OD_LO      Open Drain, Drives Low 
*  ZC_NInv_DM_RES_UP     Resistive Pull Up 
*  ZC_NInv_DM_RES_DWN    Resistive Pull Down 
*  ZC_NInv_DM_RES_UPDWN  Resistive Pull Up/Down 
*  ZC_NInv_DM_DIG_HIZ    High Impedance Digital 
*  ZC_NInv_DM_ALG_HIZ    High Impedance Analog 
*
* Return: 
*  None
*
*******************************************************************************/
void ZC_NInv_SetDriveMode(uint8 mode) 
{
	SetP4PinDriveMode(ZC_NInv__0__SHIFT, mode);
}


/*******************************************************************************
* Function Name: ZC_NInv_Read
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
*  Macro ZC_NInv_ReadPS calls this function. 
*  
*******************************************************************************/
uint8 ZC_NInv_Read(void) 
{
    return (uint8)((ZC_NInv_PS & ZC_NInv_MASK) >> ZC_NInv_SHIFT);
}


/*******************************************************************************
* Function Name: ZC_NInv_ReadDataReg
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
uint8 ZC_NInv_ReadDataReg(void) 
{
    return (uint8)((ZC_NInv_DR & ZC_NInv_MASK) >> ZC_NInv_SHIFT);
}


/* If Interrupts Are Enabled for this Pins component */ 
#if defined(ZC_NInv_INTSTAT) 

    /*******************************************************************************
    * Function Name: ZC_NInv_ClearInterrupt
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
    uint8 ZC_NInv_ClearInterrupt(void) 
    {
		uint8 maskedStatus = (uint8)(ZC_NInv_INTSTAT & ZC_NInv_MASK);
		ZC_NInv_INTSTAT = maskedStatus;
        return maskedStatus >> ZC_NInv_SHIFT;
    }

#endif /* If Interrupts Are Enabled for this Pins component */ 


/* [] END OF FILE */
