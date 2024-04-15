/*******************************************************************************
* File Name: Zero_Cross.c
* Version 1.10
*
* Description:
*  This file provides the source code to the API for the Comparator component
*
* Note:
*  None
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/

#include "Zero_Cross.h"

uint8 Zero_Cross_initVar = 0u; /* Defines if component was initialized */
static uint32 Zero_Cross_internalSpeed = 0u; /* Defines component Speed value */


/*******************************************************************************
* Function Name: Zero_Cross_Init
********************************************************************************
*
* Summary:
*  Initializes or restores the component according to the customizer Configure 
*  dialog settings. It is not necessary to call Init() because the Start() API 
*  calls this function and is the preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_Init(void)
{
    uint8 enableInterrupts;
    
    Zero_Cross_internalSpeed = Zero_Cross_POWER;
    Zero_Cross_CTB_CTRL_REG = Zero_Cross_DEFAULT_CTB_CTRL;
    Zero_Cross_OA_RES_CTRL_REG = Zero_Cross_DEFAULT_OA_RES_CTRL;
    
    enableInterrupts = CyEnterCriticalSection();
    Zero_Cross_INTR_MASK_REG |= Zero_Cross_INTR_MASK_REG_DEFAULT;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Zero_Cross_Enable
********************************************************************************
*
* Summary:
*  Activates the hardware and begins the component operation. It is not necessary to 
*  call Enable() because the Start() API calls this function, which is the 
*  preferred method to begin the component operation.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_Enable(void)
{
    Zero_Cross_OA_RES_CTRL_REG |= Zero_Cross_internalSpeed | \
                                        Zero_Cross_OA_PUMP_EN;
}


/*******************************************************************************
* Function Name: Zero_Cross_Start
********************************************************************************
*
* Summary:
*  Performs all of the required initialization for the component and enables 
*  power to the block. The first time the routine is executed, the speed/power 
*  level, and hysteresis are set. When called to restart the comparator 
*  following a Stop() call, the current component parameter settings are retained.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Zero_Cross_initVar: Is modified when this function is called for the
*   first time. Is used to ensure that initialization happens only once.
*
*******************************************************************************/
void Zero_Cross_Start(void)
{
    if( 0u == Zero_Cross_initVar)
    {
        Zero_Cross_Init();
        Zero_Cross_initVar = 1u;
    }
    Zero_Cross_Enable();
}


/*******************************************************************************
* Function Name: Zero_Cross_Stop
********************************************************************************
*
* Summary:
*  Turns off the comparator block.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Side Effects:
*  Does not affect the comparator speed settings.
*
*******************************************************************************/
void Zero_Cross_Stop(void)
{
    Zero_Cross_OA_CTRL_REG &= ((uint32)~(Zero_Cross_OA_PWR_MODE_MASK | \
                                               Zero_Cross_OA_PUMP_EN));
}


/*******************************************************************************
* Function Name: Zero_Cross_SetSpeed
********************************************************************************
*
* Summary:
*  Sets the speed to one of three settings: slow, medium, or fast.
*
* Parameters:
*  speed: Enumerated speed mode value.
*   Zero_Cross_SLOW_SPEED  - Slow speed
*   Zero_Cross_MED_SPEED   - Medium speed
*   Zero_Cross_FAST_SPEED  - Fast speed
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_SetSpeed(uint32 speed)
{
    uint32 tmp;
    
    Zero_Cross_internalSpeed = Zero_Cross_GET_OA_PWR_MODE(speed);
    tmp = Zero_Cross_OA_RES_CTRL_REG & \
           (uint32)~Zero_Cross_OA_PWR_MODE_MASK;
    Zero_Cross_OA_RES_CTRL_REG = tmp | Zero_Cross_internalSpeed;
}


/*******************************************************************************
* Function Name: Zero_Cross_ZeroCal
********************************************************************************
*
* Summary:
*  Performs custom calibration of the input offset to minimize the error for a 
*  specific set of conditions: the comparator reference voltage, supply voltage, 
*  and operating temperature. A reference voltage in the range at which the 
*  comparator will be used must be applied to the Negative and Positive inputs 
*  of the comparator while the offset calibration is performed. This can be done 
*  external to the device or by using an internal analog mux on the positive input 
*  that selects between the positive input signal for normal operation and the 
*  negative input signal for calibration.
*
* Parameters:
*  None
*
* Return:
*  (uint32): The value from the comparator trim register after the offset 
*  calibration is complete. This value has the same format as the input parameter 
*  for the LoadTrim() API routine.
*
*
* Side Effects:
*  During the calibration procedure, the comparator output may behave erratically. 
*  The comparator output should be ignored during calibration.
*
*******************************************************************************/
uint32 Zero_Cross_ZeroCal(void)
{
    uint32 cmpOut;
    uint32 i;
    
    /* Clear trim registers before trimming */
    Zero_Cross_OA_OFFSET_TRIM_REG       = 0u;
    Zero_Cross_OA_SLOPE_OFFSET_TRIM_REG = 0u;
    
    /* Check comparator's output state */
    cmpOut = Zero_Cross_GetCompare();
    
    /* Connect the outputs of trim IDACs to the positive
    * output leg of the folded cascade 
    */
    if(cmpOut == 0u)
    {
        Zero_Cross_OA_OFFSET_TRIM_REG       = ((uint32) 1u << Zero_Cross_COMP_TRIM_SIGN_SHIFT);
        Zero_Cross_OA_SLOPE_OFFSET_TRIM_REG = ((uint32) 1u << Zero_Cross_COMP_TRIM_SIGN_SHIFT);
    }
        
    /* Searching offset trim setting, 
    * that flips comparator output 
    */
    for(i = Zero_Cross_COMP_TRIM_MAX_VALUE; i != 0u; i--)
    {
        Zero_Cross_OA_OFFSET_TRIM_REG++;
        CyDelayUs(Zero_Cross_COMP_CALIBRATION_DELAY);
        if(cmpOut != Zero_Cross_GetCompare())
        {
            break;
        }
    }
    
    /* Returns offset trim value */
    return (Zero_Cross_OA_OFFSET_TRIM_REG);
}


/*******************************************************************************
* Function Name: Zero_Cross_LoadTrim
********************************************************************************
*
* Summary:
*  This function writes a value into the comparator offset trim register.
*
* Parameters:
*  uint32 trimVal: Value to be stored in the comparator offset trim register. 
*  This value has the same format as the parameter returned by the ZeroCal() 
*  routine.
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_LoadTrim(uint32 trimVal)
{
    Zero_Cross_OA_OFFSET_TRIM_REG = trimVal;
}


/*******************************************************************************
* Function Name: Zero_Cross_GetCompare
********************************************************************************
*
* Summary:
*  This function returns a non-zero value when the voltage connected to the positive 
*  input is greater than the negative input voltage. This value is not affected by 
*  the Polarity parameter. This value always reflects a non-inverted state 
*  configuration.
*  This function reads the direct (unflopped) comparator output which can also be 
*  metastable (since it may result in incorrect data).
*
* Parameters:
*   None
*
* Return:
*  The comparator output state. A non-zero value when the positive input voltage is 
*  greater than the negative input voltage; otherwise, the return value is zero.
*
*******************************************************************************/
uint32 Zero_Cross_GetCompare(void)
{
    return ((uint32)(Zero_Cross_OA_COMP_STAT_REG >> Zero_Cross_OA_COMP_SHIFT) & 1u);
}


/*******************************************************************************
* Function Name: Zero_Cross_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests. This function is for use when using the combined
*  interrupt signal from the global signal reference. This function from either
*  component instance can be used to determine the interrupt source for all the
*  comparator interrupts combined.
*
* Parameters:
*  None
*
* Return:
*  uint32: Interrupt source. Each component instance has a mask value:
*  Zero_Cross_INTR.
*
*******************************************************************************/
uint32 Zero_Cross_GetInterruptSource(void)
{
    return (Zero_Cross_INTR_REG); 
}


/*******************************************************************************
* Function Name: Zero_Cross_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to clear either or both
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to clear. Each component instance
*  has a mask value: Zero_Cross_INTR.
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_ClearInterrupt(uint32 interruptMask)
{   
    Zero_Cross_INTR_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Zero_Cross_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request. This function is for use when using the
*  combined interrupt signal from the global signal reference. This function
*  from either component instance can be used to trigger either or both software
*  interrupts.
*
* Parameters:
*  uint32 interruptMask: Mask of interrupts to set. Each component instance has
*  a mask value: Zero_Cross_INTR_SET.
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_SetInterrupt(uint32 interruptMask)
{
    uint8 enableInterrupts;
    
    enableInterrupts = CyEnterCriticalSection();
    Zero_Cross_INTR_SET_REG |= interruptMask;
    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Zero_Cross_SetInterruptMask
********************************************************************************
*
* Summary:
*  Configures the interrupt mask for all comparators in the system.
*
* Parameters:
*  uint32 interruptMask: Bit-mask of interrupt sources to be enabled. Each 
*  component instance has a mask value: Zero_Cross_INTR_MASK.
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_SetInterruptMask(uint32 interruptMask)
{
    Zero_Cross_INTR_MASK_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Zero_Cross_GetInterruptMask
********************************************************************************
*
* Summary:
*  Returns interrupt mask for all comparators.
*
* Parameters:
*  None
*
* Return:
*  uint32:  Mask of enabled interrupt source. Each component instance 
*  has a mask value: Zero_Cross_INTR_MASK.
*
*******************************************************************************/
uint32 Zero_Cross_GetInterruptMask(void)
{
    return (Zero_Cross_INTR_MASK_REG);
}


/*******************************************************************************
* Function Name: Zero_Cross_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Returns interrupt request register masked by interrupt mask for all comparators. 
*  Returns the result of bitwise AND operation between corresponding interrupt 
*  request and mask bits.
*
* Parameters:
*  None
*
* Return:
*  uint32: Status of enabled interrupt source. Each component instance 
*  has a mask value: Zero_Cross_INTR_MASKED.
*
*******************************************************************************/
uint32 Zero_Cross_GetInterruptSourceMasked(void)
{
    return (Zero_Cross_INTR_MASKED_REG);
}

/*******************************************************************************
* Function Name: Zero_Cross_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt edge detect mode.
*
* Parameters:
*  uint32 mode: Enumerated edge detect mode value:
*  Zero_Cross_INTR_DISABLE - Disable
*  Zero_Cross_INTR_RISING  - Rising edge detect
*  Zero_Cross_INTR_FALLING - Falling edge detect
*  Zero_Cross_INTR_BOTH    - Detect both edges
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_SetInterruptMode(uint32 mode)
{
    uint32 tmp;

    tmp = Zero_Cross_OA_RES_CTRL_REG & (uint32)~Zero_Cross_OA_COMPINT_MASK;
    Zero_Cross_OA_RES_CTRL_REG = tmp | Zero_Cross_GET_OA_COMPINT(mode);
}

/*******************************************************************************
* Function Name: Zero_Cross_DisableInterruptOutput
********************************************************************************
*
* Summary:
*  Disables the interrupt output so that it will not be ORed to the global 
*  Signal CTBmInt with the other comparator interrupt outputs.  
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Zero_Cross_DisableInterruptOutput(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Zero_Cross_INTR_MASK_REG &= ~Zero_Cross_INTR_MASK;
    CyExitCriticalSection(enableInterrupts);
}


/* [] END OF FILE */
