/*******************************************************************************
* File Name: Tick.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Tick
*  component
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

#include "Tick.h"

uint8 Tick_initVar = 0u;


/*******************************************************************************
* Function Name: Tick_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Tick configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Tick_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Tick__QUAD == Tick_CONFIG)
        Tick_CONTROL_REG = Tick_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Tick_TRIG_CONTROL1_REG  = Tick_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Tick_SetInterruptMode(Tick_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Tick_SetCounterMode(Tick_COUNT_DOWN);
        Tick_WritePeriod(Tick_QUAD_PERIOD_INIT_VALUE);
        Tick_WriteCounter(Tick_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Tick__QUAD == Tick_CONFIG) */

    #if (Tick__TIMER == Tick_CONFIG)
        Tick_CONTROL_REG = Tick_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Tick_TRIG_CONTROL1_REG  = Tick_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Tick_SetInterruptMode(Tick_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Tick_WritePeriod(Tick_TC_PERIOD_VALUE );

        #if (Tick__COMPARE == Tick_TC_COMP_CAP_MODE)
            Tick_WriteCompare(Tick_TC_COMPARE_VALUE);

            #if (1u == Tick_TC_COMPARE_SWAP)
                Tick_SetCompareSwap(1u);
                Tick_WriteCompareBuf(Tick_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Tick_TC_COMPARE_SWAP) */
        #endif  /* (Tick__COMPARE == Tick_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Tick_CY_TCPWM_V2 && Tick_TIMER_UPDOWN_CNT_USED && !Tick_CY_TCPWM_4000)
            Tick_WriteCounter(1u);
        #elif(Tick__COUNT_DOWN == Tick_TC_COUNTER_MODE)
            Tick_WriteCounter(Tick_TC_PERIOD_VALUE);
        #else
            Tick_WriteCounter(0u);
        #endif /* (Tick_CY_TCPWM_V2 && Tick_TIMER_UPDOWN_CNT_USED && !Tick_CY_TCPWM_4000) */
    #endif  /* (Tick__TIMER == Tick_CONFIG) */

    #if (Tick__PWM_SEL == Tick_CONFIG)
        Tick_CONTROL_REG = Tick_CTRL_PWM_BASE_CONFIG;

        #if (Tick__PWM_PR == Tick_PWM_MODE)
            Tick_CONTROL_REG |= Tick_CTRL_PWM_RUN_MODE;
            Tick_WriteCounter(Tick_PWM_PR_INIT_VALUE);
        #else
            Tick_CONTROL_REG |= Tick_CTRL_PWM_ALIGN | Tick_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Tick_CY_TCPWM_V2 && Tick_PWM_UPDOWN_CNT_USED && !Tick_CY_TCPWM_4000)
                Tick_WriteCounter(1u);
            #elif (Tick__RIGHT == Tick_PWM_ALIGN)
                Tick_WriteCounter(Tick_PWM_PERIOD_VALUE);
            #else 
                Tick_WriteCounter(0u);
            #endif  /* (Tick_CY_TCPWM_V2 && Tick_PWM_UPDOWN_CNT_USED && !Tick_CY_TCPWM_4000) */
        #endif  /* (Tick__PWM_PR == Tick_PWM_MODE) */

        #if (Tick__PWM_DT == Tick_PWM_MODE)
            Tick_CONTROL_REG |= Tick_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Tick__PWM_DT == Tick_PWM_MODE) */

        #if (Tick__PWM == Tick_PWM_MODE)
            Tick_CONTROL_REG |= Tick_CTRL_PWM_PRESCALER;
        #endif  /* (Tick__PWM == Tick_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Tick_TRIG_CONTROL1_REG  = Tick_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Tick_SetInterruptMode(Tick_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Tick__PWM_PR == Tick_PWM_MODE)
            Tick_TRIG_CONTROL2_REG =
                    (Tick_CC_MATCH_NO_CHANGE    |
                    Tick_OVERLOW_NO_CHANGE      |
                    Tick_UNDERFLOW_NO_CHANGE);
        #else
            #if (Tick__LEFT == Tick_PWM_ALIGN)
                Tick_TRIG_CONTROL2_REG = Tick_PWM_MODE_LEFT;
            #endif  /* ( Tick_PWM_LEFT == Tick_PWM_ALIGN) */

            #if (Tick__RIGHT == Tick_PWM_ALIGN)
                Tick_TRIG_CONTROL2_REG = Tick_PWM_MODE_RIGHT;
            #endif  /* ( Tick_PWM_RIGHT == Tick_PWM_ALIGN) */

            #if (Tick__CENTER == Tick_PWM_ALIGN)
                Tick_TRIG_CONTROL2_REG = Tick_PWM_MODE_CENTER;
            #endif  /* ( Tick_PWM_CENTER == Tick_PWM_ALIGN) */

            #if (Tick__ASYMMETRIC == Tick_PWM_ALIGN)
                Tick_TRIG_CONTROL2_REG = Tick_PWM_MODE_ASYM;
            #endif  /* (Tick__ASYMMETRIC == Tick_PWM_ALIGN) */
        #endif  /* (Tick__PWM_PR == Tick_PWM_MODE) */

        /* Set other values from customizer */
        Tick_WritePeriod(Tick_PWM_PERIOD_VALUE );
        Tick_WriteCompare(Tick_PWM_COMPARE_VALUE);

        #if (1u == Tick_PWM_COMPARE_SWAP)
            Tick_SetCompareSwap(1u);
            Tick_WriteCompareBuf(Tick_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Tick_PWM_COMPARE_SWAP) */

        #if (1u == Tick_PWM_PERIOD_SWAP)
            Tick_SetPeriodSwap(1u);
            Tick_WritePeriodBuf(Tick_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Tick_PWM_PERIOD_SWAP) */
    #endif  /* (Tick__PWM_SEL == Tick_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Tick_Enable
********************************************************************************
*
* Summary:
*  Enables the Tick.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Tick_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Tick_BLOCK_CONTROL_REG |= Tick_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Tick__PWM_SEL == Tick_CONFIG)
        #if (0u == Tick_PWM_START_SIGNAL_PRESENT)
            Tick_TriggerCommand(Tick_MASK, Tick_CMD_START);
        #endif /* (0u == Tick_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Tick__PWM_SEL == Tick_CONFIG) */

    #if (Tick__TIMER == Tick_CONFIG)
        #if (0u == Tick_TC_START_SIGNAL_PRESENT)
            Tick_TriggerCommand(Tick_MASK, Tick_CMD_START);
        #endif /* (0u == Tick_TC_START_SIGNAL_PRESENT) */
    #endif /* (Tick__TIMER == Tick_CONFIG) */
}


/*******************************************************************************
* Function Name: Tick_Start
********************************************************************************
*
* Summary:
*  Initializes the Tick with default customizer
*  values when called the first time and enables the Tick.
*  For subsequent calls the configuration is left unchanged and the component is
*  just enabled.
*
* Parameters:
*  None
*
* Return:
*  None
*
* Global variables:
*  Tick_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Tick_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Tick_Start() routine.
*
*******************************************************************************/
void Tick_Start(void)
{
    if (0u == Tick_initVar)
    {
        Tick_Init();
        Tick_initVar = 1u;
    }

    Tick_Enable();
}


/*******************************************************************************
* Function Name: Tick_Stop
********************************************************************************
*
* Summary:
*  Disables the Tick.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Tick_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_BLOCK_CONTROL_REG &= (uint32)~Tick_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Tick. This function is used when
*  configured as a generic Tick and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Tick to operate in
*   Values:
*   - Tick_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Tick_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Tick_MODE_QUAD - Quadrature decoder
*         - Tick_MODE_PWM - PWM
*         - Tick_MODE_PWM_DT - PWM with dead time
*         - Tick_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_MODE_MASK;
    Tick_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Tick_MODE_X1 - Counts on phi 1 rising
*         - Tick_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Tick_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_QUAD_MODE_MASK;
    Tick_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Tick_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Tick_PRESCALE_DIVBY2    - Divide by 2
*         - Tick_PRESCALE_DIVBY4    - Divide by 4
*         - Tick_PRESCALE_DIVBY8    - Divide by 8
*         - Tick_PRESCALE_DIVBY16   - Divide by 16
*         - Tick_PRESCALE_DIVBY32   - Divide by 32
*         - Tick_PRESCALE_DIVBY64   - Divide by 64
*         - Tick_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_PRESCALER_MASK;
    Tick_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Tick runs
*  continuously or stops when terminal count is reached.  By default the
*  Tick operates in the continuous mode.
*
* Parameters:
*  oneShotEnable
*   Values:
*     - 0 - Continuous
*     - 1 - Enable One Shot
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_ONESHOT_MASK;
    Tick_CONTROL_REG |= ((uint32)((oneShotEnable & Tick_1BIT_MASK) <<
                                                               Tick_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetPWMMode
********************************************************************************
*
* Summary:
*  Writes the control register that determines what mode of operation the PWM
*  output lines are driven in.  There is a setting for what to do on a
*  comparison match (CC_MATCH), on an overflow (OVERFLOW) and on an underflow
*  (UNDERFLOW).  The value for each of the three must be ORed together to form
*  the mode.
*
* Parameters:
*  modeMask: A combination of three mode settings.  Mask must include a value
*  for each of the three or use one of the preconfigured PWM settings.
*   Values:
*     - CC_MATCH_SET        - Set on comparison match
*     - CC_MATCH_CLEAR      - Clear on comparison match
*     - CC_MATCH_INVERT     - Invert on comparison match
*     - CC_MATCH_NO_CHANGE  - No change on comparison match
*     - OVERLOW_SET         - Set on overflow
*     - OVERLOW_CLEAR       - Clear on  overflow
*     - OVERLOW_INVERT      - Invert on overflow
*     - OVERLOW_NO_CHANGE   - No change on overflow
*     - UNDERFLOW_SET       - Set on underflow
*     - UNDERFLOW_CLEAR     - Clear on underflow
*     - UNDERFLOW_INVERT    - Invert on underflow
*     - UNDERFLOW_NO_CHANGE - No change on underflow
*     - PWM_MODE_LEFT       - Setting for left aligned PWM.  Should be combined
*                             with up counting mode
*     - PWM_MODE_RIGHT      - Setting for right aligned PWM.  Should be combined
*                             with down counting mode
*     - PWM_MODE_CENTER     - Setting for center aligned PWM.  Should be
*                             combined with up/down 0 mode
*     - PWM_MODE_ASYM       - Setting for asymmetric PWM.  Should be combined
*                             with up/down 1 mode
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPWMMode(uint32 modeMask)
{
    Tick_TRIG_CONTROL2_REG = (modeMask & Tick_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Tick_SetPWMSyncKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes asynchronous or synchronous kill operation.  By default the kill
*  operation is asynchronous.  This functionality is only applicable to the PWM
*  and PWM with dead time modes.
*
*  For Synchronous mode the kill signal disables both the line and line_n
*  signals until the next terminal count.
*
*  For Asynchronous mode the kill signal disables both the line and line_n
*  signals when the kill signal is present.  This mode should only be used
*  when the kill signal (stop input) is configured in the pass through mode
*  (Level sensitive signal).

*
* Parameters:
*  syncKillEnable
*   Values:
*     - 0 - Asynchronous
*     - 1 - Synchronous
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_PWM_SYNC_KILL_MASK;
    Tick_CONTROL_REG |= ((uint32)((syncKillEnable & Tick_1BIT_MASK)  <<
                                               Tick_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetPWMStopOnKill
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the PWM kill signal (stop input)
*  causes the PWM counter to stop.  By default the kill operation does not stop
*  the counter.  This functionality is only applicable to the three PWM modes.
*
*
* Parameters:
*  stopOnKillEnable
*   Values:
*     - 0 - Don't stop
*     - 1 - Stop
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_PWM_STOP_KILL_MASK;
    Tick_CONTROL_REG |= ((uint32)((stopOnKillEnable & Tick_1BIT_MASK)  <<
                                                         Tick_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetPWMDeadTime
********************************************************************************
*
* Summary:
*  Writes the dead time control value.  This value delays the rising edge of
*  both the line and line_n signals the designated number of cycles resulting
*  in both signals being inactive for that many cycles.  This functionality is
*  only applicable to the PWM in the dead time mode.

*
* Parameters:
*  Dead time to insert
*   Values: 0 to 255
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_PRESCALER_MASK;
    Tick_CONTROL_REG |= ((uint32)((deadTime & Tick_8BIT_MASK) <<
                                                          Tick_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetPWMInvert
********************************************************************************
*
* Summary:
*  Writes the bits that control whether the line and line_n outputs are
*  inverted from their normal output values.  This functionality is only
*  applicable to the three PWM modes.
*
* Parameters:
*  mask: Mask of outputs to invert.
*   Values:
*         - Tick_INVERT_LINE   - Inverts the line output
*         - Tick_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_INV_OUT_MASK;
    Tick_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Tick_WriteCounter
********************************************************************************
*
* Summary:
*  Writes a new 16bit counter value directly into the counter register, thus
*  setting the counter (not the period) to the value written. It is not
*  advised to write to this field when the counter is running.
*
* Parameters:
*  count: value to write
*
* Return:
*  None
*
*******************************************************************************/
void Tick_WriteCounter(uint32 count)
{
    Tick_COUNTER_REG = (count & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadCounter
********************************************************************************
*
* Summary:
*  Reads the current counter value.
*
* Parameters:
*  None
*
* Return:
*  Current counter value
*
*******************************************************************************/
uint32 Tick_ReadCounter(void)
{
    return (Tick_COUNTER_REG & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Tick_COUNT_UP       - Counts up
*     - Tick_COUNT_DOWN     - Counts down
*     - Tick_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Tick_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_UPDOWN_MASK;
    Tick_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_WritePeriod
********************************************************************************
*
* Summary:
*  Writes the 16 bit period register with the new period value.
*  To cause the counter to count for N cycles this register should be written
*  with N-1 (counts from 0 to period inclusive).
*
* Parameters:
*  period: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Tick_WritePeriod(uint32 period)
{
    Tick_PERIOD_REG = (period & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadPeriod
********************************************************************************
*
* Summary:
*  Reads the 16 bit period register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Tick_ReadPeriod(void)
{
    return (Tick_PERIOD_REG & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_SetCompareSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the compare registers are
*  swapped. When enabled in the Timer/Counter mode(without capture) the swap
*  occurs at a TC event. In the PWM mode the swap occurs at the next TC event
*  following a hardware switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_RELOAD_CC_MASK;
    Tick_CONTROL_REG |= (swapEnable & Tick_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_WritePeriodBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit period buf register with the new period value.
*
* Parameters:
*  periodBuf: Period value
*
* Return:
*  None
*
*******************************************************************************/
void Tick_WritePeriodBuf(uint32 periodBuf)
{
    Tick_PERIOD_BUF_REG = (periodBuf & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadPeriodBuf
********************************************************************************
*
* Summary:
*  Reads the 16 bit period buf register.
*
* Parameters:
*  None
*
* Return:
*  Period value
*
*******************************************************************************/
uint32 Tick_ReadPeriodBuf(void)
{
    return (Tick_PERIOD_BUF_REG & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_SetPeriodSwap
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the period registers are
*  swapped. When enabled in Timer/Counter mode the swap occurs at a TC event.
*  In the PWM mode the swap occurs at the next TC event following a hardware
*  switch event.
*
* Parameters:
*  swapEnable
*   Values:
*     - 0 - Disable swap
*     - 1 - Enable swap
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_CONTROL_REG &= (uint32)~Tick_RELOAD_PERIOD_MASK;
    Tick_CONTROL_REG |= ((uint32)((swapEnable & Tick_1BIT_MASK) <<
                                                            Tick_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_WriteCompare
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compare: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void Tick_WriteCompare(uint32 compare)
{
    #if (Tick_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Tick_CY_TCPWM_4000) */

    #if (Tick_CY_TCPWM_4000)
        currentMode = ((Tick_CONTROL_REG & Tick_UPDOWN_MASK) >> Tick_UPDOWN_SHIFT);

        if (((uint32)Tick__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Tick__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Tick_CY_TCPWM_4000) */
    
    Tick_COMP_CAP_REG = (compare & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadCompare
********************************************************************************
*
* Summary:
*  Reads the compare register. Not applicable for Timer/Counter with Capture
*  or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare value
*
*******************************************************************************/
uint32 Tick_ReadCompare(void)
{
    #if (Tick_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Tick_CY_TCPWM_4000) */

    #if (Tick_CY_TCPWM_4000)
        currentMode = ((Tick_CONTROL_REG & Tick_UPDOWN_MASK) >> Tick_UPDOWN_SHIFT);
        
        regVal = Tick_COMP_CAP_REG;
        
        if (((uint32)Tick__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Tick__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Tick_16BIT_MASK);
    #else
        return (Tick_COMP_CAP_REG & Tick_16BIT_MASK);
    #endif /* (Tick_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Tick_WriteCompareBuf
********************************************************************************
*
* Summary:
*  Writes the 16 bit compare buffer register with the new compare value. Not
*  applicable for Timer/Counter with Capture or in Quadrature Decoder modes.
*
* Parameters:
*  compareBuf: Compare value
*
* Return:
*  None
*
*******************************************************************************/
void Tick_WriteCompareBuf(uint32 compareBuf)
{
    #if (Tick_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Tick_CY_TCPWM_4000) */

    #if (Tick_CY_TCPWM_4000)
        currentMode = ((Tick_CONTROL_REG & Tick_UPDOWN_MASK) >> Tick_UPDOWN_SHIFT);

        if (((uint32)Tick__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Tick__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Tick_CY_TCPWM_4000) */
    
    Tick_COMP_CAP_BUF_REG = (compareBuf & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadCompareBuf
********************************************************************************
*
* Summary:
*  Reads the compare buffer register. Not applicable for Timer/Counter with
*  Capture or in Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Compare buffer value
*
*******************************************************************************/
uint32 Tick_ReadCompareBuf(void)
{
    #if (Tick_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Tick_CY_TCPWM_4000) */

    #if (Tick_CY_TCPWM_4000)
        currentMode = ((Tick_CONTROL_REG & Tick_UPDOWN_MASK) >> Tick_UPDOWN_SHIFT);

        regVal = Tick_COMP_CAP_BUF_REG;
        
        if (((uint32)Tick__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Tick__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Tick_16BIT_MASK);
    #else
        return (Tick_COMP_CAP_BUF_REG & Tick_16BIT_MASK);
    #endif /* (Tick_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Tick_ReadCapture
********************************************************************************
*
* Summary:
*  Reads the captured counter value. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture value
*
*******************************************************************************/
uint32 Tick_ReadCapture(void)
{
    return (Tick_COMP_CAP_REG & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_ReadCaptureBuf
********************************************************************************
*
* Summary:
*  Reads the capture buffer register. This API is applicable only for
*  Timer/Counter with the capture mode and Quadrature Decoder modes.
*
* Parameters:
*  None
*
* Return:
*  Capture buffer value
*
*******************************************************************************/
uint32 Tick_ReadCaptureBuf(void)
{
    return (Tick_COMP_CAP_BUF_REG & Tick_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Tick_SetCaptureMode
********************************************************************************
*
* Summary:
*  Sets the capture trigger mode. For PWM mode this is the switch input.
*  This input is not applicable to the Timer/Counter without Capture and
*  Quadrature Decoder modes.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Tick_TRIG_LEVEL     - Level
*     - Tick_TRIG_RISING    - Rising edge
*     - Tick_TRIG_FALLING   - Falling edge
*     - Tick_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_TRIG_CONTROL1_REG &= (uint32)~Tick_CAPTURE_MASK;
    Tick_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Tick_TRIG_LEVEL     - Level
*     - Tick_TRIG_RISING    - Rising edge
*     - Tick_TRIG_FALLING   - Falling edge
*     - Tick_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_TRIG_CONTROL1_REG &= (uint32)~Tick_RELOAD_MASK;
    Tick_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Tick_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Tick_TRIG_LEVEL     - Level
*     - Tick_TRIG_RISING    - Rising edge
*     - Tick_TRIG_FALLING   - Falling edge
*     - Tick_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_TRIG_CONTROL1_REG &= (uint32)~Tick_START_MASK;
    Tick_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Tick_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Tick_TRIG_LEVEL     - Level
*     - Tick_TRIG_RISING    - Rising edge
*     - Tick_TRIG_FALLING   - Falling edge
*     - Tick_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_TRIG_CONTROL1_REG &= (uint32)~Tick_STOP_MASK;
    Tick_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Tick_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Tick_TRIG_LEVEL     - Level
*     - Tick_TRIG_RISING    - Rising edge
*     - Tick_TRIG_FALLING   - Falling edge
*     - Tick_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_TRIG_CONTROL1_REG &= (uint32)~Tick_COUNT_MASK;
    Tick_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Tick_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_TriggerCommand
********************************************************************************
*
* Summary:
*  Triggers the designated command to occur on the designated TCPWM instances.
*  The mask can be used to apply this command simultaneously to more than one
*  instance.  This allows multiple TCPWM instances to be synchronized.
*
* Parameters:
*  mask: A combination of mask bits for each instance of the TCPWM that the
*        command should apply to.  This function from one instance can be used
*        to apply the command to any of the instances in the design.
*        The mask value for a specific instance is available with the MASK
*        define.
*  command: Enumerated command values. Capture command only applicable for
*           Timer/Counter with Capture and PWM modes.
*   Values:
*     - Tick_CMD_CAPTURE    - Trigger Capture command
*     - Tick_CMD_RELOAD     - Trigger Reload command
*     - Tick_CMD_STOP       - Trigger Stop command
*     - Tick_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void Tick_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Tick_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Tick_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Tick.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Tick_STATUS_DOWN    - Set if counting down
*     - Tick_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Tick_ReadStatus(void)
{
    return ((Tick_STATUS_REG >> Tick_RUNNING_STATUS_SHIFT) |
            (Tick_STATUS_REG & Tick_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Tick_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Tick_INTR_MASK_TC       - Terminal count mask
*     - Tick_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetInterruptMode(uint32 interruptMask)
{
    Tick_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Tick_GetInterruptSourceMasked
********************************************************************************
*
* Summary:
*  Gets the interrupt requests masked by the interrupt mask.
*
* Parameters:
*   None
*
* Return:
*  Masked interrupt source
*   Values:
*     - Tick_INTR_MASK_TC       - Terminal count mask
*     - Tick_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Tick_GetInterruptSourceMasked(void)
{
    return (Tick_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Tick_GetInterruptSource
********************************************************************************
*
* Summary:
*  Gets the interrupt requests (without masking).
*
* Parameters:
*  None
*
* Return:
*  Interrupt request value
*   Values:
*     - Tick_INTR_MASK_TC       - Terminal count mask
*     - Tick_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Tick_GetInterruptSource(void)
{
    return (Tick_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Tick_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Tick_INTR_MASK_TC       - Terminal count mask
*     - Tick_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Tick_ClearInterrupt(uint32 interruptMask)
{
    Tick_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Tick_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Tick_INTR_MASK_TC       - Terminal count mask
*     - Tick_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Tick_SetInterrupt(uint32 interruptMask)
{
    Tick_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
