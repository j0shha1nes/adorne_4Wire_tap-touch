/*******************************************************************************
* File Name: Dimming.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Dimming
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

#include "Dimming.h"

uint8 Dimming_initVar = 0u;


/*******************************************************************************
* Function Name: Dimming_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Dimming configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Dimming__QUAD == Dimming_CONFIG)
        Dimming_CONTROL_REG = Dimming_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Dimming_TRIG_CONTROL1_REG  = Dimming_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Dimming_SetInterruptMode(Dimming_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Dimming_SetCounterMode(Dimming_COUNT_DOWN);
        Dimming_WritePeriod(Dimming_QUAD_PERIOD_INIT_VALUE);
        Dimming_WriteCounter(Dimming_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Dimming__QUAD == Dimming_CONFIG) */

    #if (Dimming__TIMER == Dimming_CONFIG)
        Dimming_CONTROL_REG = Dimming_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Dimming_TRIG_CONTROL1_REG  = Dimming_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Dimming_SetInterruptMode(Dimming_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Dimming_WritePeriod(Dimming_TC_PERIOD_VALUE );

        #if (Dimming__COMPARE == Dimming_TC_COMP_CAP_MODE)
            Dimming_WriteCompare(Dimming_TC_COMPARE_VALUE);

            #if (1u == Dimming_TC_COMPARE_SWAP)
                Dimming_SetCompareSwap(1u);
                Dimming_WriteCompareBuf(Dimming_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Dimming_TC_COMPARE_SWAP) */
        #endif  /* (Dimming__COMPARE == Dimming_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Dimming_CY_TCPWM_V2 && Dimming_TIMER_UPDOWN_CNT_USED && !Dimming_CY_TCPWM_4000)
            Dimming_WriteCounter(1u);
        #elif(Dimming__COUNT_DOWN == Dimming_TC_COUNTER_MODE)
            Dimming_WriteCounter(Dimming_TC_PERIOD_VALUE);
        #else
            Dimming_WriteCounter(0u);
        #endif /* (Dimming_CY_TCPWM_V2 && Dimming_TIMER_UPDOWN_CNT_USED && !Dimming_CY_TCPWM_4000) */
    #endif  /* (Dimming__TIMER == Dimming_CONFIG) */

    #if (Dimming__PWM_SEL == Dimming_CONFIG)
        Dimming_CONTROL_REG = Dimming_CTRL_PWM_BASE_CONFIG;

        #if (Dimming__PWM_PR == Dimming_PWM_MODE)
            Dimming_CONTROL_REG |= Dimming_CTRL_PWM_RUN_MODE;
            Dimming_WriteCounter(Dimming_PWM_PR_INIT_VALUE);
        #else
            Dimming_CONTROL_REG |= Dimming_CTRL_PWM_ALIGN | Dimming_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Dimming_CY_TCPWM_V2 && Dimming_PWM_UPDOWN_CNT_USED && !Dimming_CY_TCPWM_4000)
                Dimming_WriteCounter(1u);
            #elif (Dimming__RIGHT == Dimming_PWM_ALIGN)
                Dimming_WriteCounter(Dimming_PWM_PERIOD_VALUE);
            #else 
                Dimming_WriteCounter(0u);
            #endif  /* (Dimming_CY_TCPWM_V2 && Dimming_PWM_UPDOWN_CNT_USED && !Dimming_CY_TCPWM_4000) */
        #endif  /* (Dimming__PWM_PR == Dimming_PWM_MODE) */

        #if (Dimming__PWM_DT == Dimming_PWM_MODE)
            Dimming_CONTROL_REG |= Dimming_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Dimming__PWM_DT == Dimming_PWM_MODE) */

        #if (Dimming__PWM == Dimming_PWM_MODE)
            Dimming_CONTROL_REG |= Dimming_CTRL_PWM_PRESCALER;
        #endif  /* (Dimming__PWM == Dimming_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Dimming_TRIG_CONTROL1_REG  = Dimming_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Dimming_SetInterruptMode(Dimming_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Dimming__PWM_PR == Dimming_PWM_MODE)
            Dimming_TRIG_CONTROL2_REG =
                    (Dimming_CC_MATCH_NO_CHANGE    |
                    Dimming_OVERLOW_NO_CHANGE      |
                    Dimming_UNDERFLOW_NO_CHANGE);
        #else
            #if (Dimming__LEFT == Dimming_PWM_ALIGN)
                Dimming_TRIG_CONTROL2_REG = Dimming_PWM_MODE_LEFT;
            #endif  /* ( Dimming_PWM_LEFT == Dimming_PWM_ALIGN) */

            #if (Dimming__RIGHT == Dimming_PWM_ALIGN)
                Dimming_TRIG_CONTROL2_REG = Dimming_PWM_MODE_RIGHT;
            #endif  /* ( Dimming_PWM_RIGHT == Dimming_PWM_ALIGN) */

            #if (Dimming__CENTER == Dimming_PWM_ALIGN)
                Dimming_TRIG_CONTROL2_REG = Dimming_PWM_MODE_CENTER;
            #endif  /* ( Dimming_PWM_CENTER == Dimming_PWM_ALIGN) */

            #if (Dimming__ASYMMETRIC == Dimming_PWM_ALIGN)
                Dimming_TRIG_CONTROL2_REG = Dimming_PWM_MODE_ASYM;
            #endif  /* (Dimming__ASYMMETRIC == Dimming_PWM_ALIGN) */
        #endif  /* (Dimming__PWM_PR == Dimming_PWM_MODE) */

        /* Set other values from customizer */
        Dimming_WritePeriod(Dimming_PWM_PERIOD_VALUE );
        Dimming_WriteCompare(Dimming_PWM_COMPARE_VALUE);

        #if (1u == Dimming_PWM_COMPARE_SWAP)
            Dimming_SetCompareSwap(1u);
            Dimming_WriteCompareBuf(Dimming_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Dimming_PWM_COMPARE_SWAP) */

        #if (1u == Dimming_PWM_PERIOD_SWAP)
            Dimming_SetPeriodSwap(1u);
            Dimming_WritePeriodBuf(Dimming_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Dimming_PWM_PERIOD_SWAP) */
    #endif  /* (Dimming__PWM_SEL == Dimming_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Dimming_Enable
********************************************************************************
*
* Summary:
*  Enables the Dimming.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Dimming_BLOCK_CONTROL_REG |= Dimming_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Dimming__PWM_SEL == Dimming_CONFIG)
        #if (0u == Dimming_PWM_START_SIGNAL_PRESENT)
            Dimming_TriggerCommand(Dimming_MASK, Dimming_CMD_START);
        #endif /* (0u == Dimming_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Dimming__PWM_SEL == Dimming_CONFIG) */

    #if (Dimming__TIMER == Dimming_CONFIG)
        #if (0u == Dimming_TC_START_SIGNAL_PRESENT)
            Dimming_TriggerCommand(Dimming_MASK, Dimming_CMD_START);
        #endif /* (0u == Dimming_TC_START_SIGNAL_PRESENT) */
    #endif /* (Dimming__TIMER == Dimming_CONFIG) */
}


/*******************************************************************************
* Function Name: Dimming_Start
********************************************************************************
*
* Summary:
*  Initializes the Dimming with default customizer
*  values when called the first time and enables the Dimming.
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
*  Dimming_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Dimming_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Dimming_Start() routine.
*
*******************************************************************************/
void Dimming_Start(void)
{
    if (0u == Dimming_initVar)
    {
        Dimming_Init();
        Dimming_initVar = 1u;
    }

    Dimming_Enable();
}


/*******************************************************************************
* Function Name: Dimming_Stop
********************************************************************************
*
* Summary:
*  Disables the Dimming.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_BLOCK_CONTROL_REG &= (uint32)~Dimming_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Dimming. This function is used when
*  configured as a generic Dimming and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Dimming to operate in
*   Values:
*   - Dimming_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Dimming_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Dimming_MODE_QUAD - Quadrature decoder
*         - Dimming_MODE_PWM - PWM
*         - Dimming_MODE_PWM_DT - PWM with dead time
*         - Dimming_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_MODE_MASK;
    Dimming_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Dimming_MODE_X1 - Counts on phi 1 rising
*         - Dimming_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Dimming_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_QUAD_MODE_MASK;
    Dimming_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Dimming_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Dimming_PRESCALE_DIVBY2    - Divide by 2
*         - Dimming_PRESCALE_DIVBY4    - Divide by 4
*         - Dimming_PRESCALE_DIVBY8    - Divide by 8
*         - Dimming_PRESCALE_DIVBY16   - Divide by 16
*         - Dimming_PRESCALE_DIVBY32   - Divide by 32
*         - Dimming_PRESCALE_DIVBY64   - Divide by 64
*         - Dimming_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_PRESCALER_MASK;
    Dimming_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Dimming runs
*  continuously or stops when terminal count is reached.  By default the
*  Dimming operates in the continuous mode.
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
void Dimming_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_ONESHOT_MASK;
    Dimming_CONTROL_REG |= ((uint32)((oneShotEnable & Dimming_1BIT_MASK) <<
                                                               Dimming_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetPWMMode
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
void Dimming_SetPWMMode(uint32 modeMask)
{
    Dimming_TRIG_CONTROL2_REG = (modeMask & Dimming_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Dimming_SetPWMSyncKill
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
void Dimming_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_PWM_SYNC_KILL_MASK;
    Dimming_CONTROL_REG |= ((uint32)((syncKillEnable & Dimming_1BIT_MASK)  <<
                                               Dimming_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetPWMStopOnKill
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
void Dimming_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_PWM_STOP_KILL_MASK;
    Dimming_CONTROL_REG |= ((uint32)((stopOnKillEnable & Dimming_1BIT_MASK)  <<
                                                         Dimming_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetPWMDeadTime
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
void Dimming_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_PRESCALER_MASK;
    Dimming_CONTROL_REG |= ((uint32)((deadTime & Dimming_8BIT_MASK) <<
                                                          Dimming_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetPWMInvert
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
*         - Dimming_INVERT_LINE   - Inverts the line output
*         - Dimming_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_INV_OUT_MASK;
    Dimming_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Dimming_WriteCounter
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
void Dimming_WriteCounter(uint32 count)
{
    Dimming_COUNTER_REG = (count & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadCounter
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
uint32 Dimming_ReadCounter(void)
{
    return (Dimming_COUNTER_REG & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Dimming_COUNT_UP       - Counts up
*     - Dimming_COUNT_DOWN     - Counts down
*     - Dimming_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Dimming_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_UPDOWN_MASK;
    Dimming_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_WritePeriod
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
void Dimming_WritePeriod(uint32 period)
{
    Dimming_PERIOD_REG = (period & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadPeriod
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
uint32 Dimming_ReadPeriod(void)
{
    return (Dimming_PERIOD_REG & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_SetCompareSwap
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
void Dimming_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_RELOAD_CC_MASK;
    Dimming_CONTROL_REG |= (swapEnable & Dimming_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_WritePeriodBuf
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
void Dimming_WritePeriodBuf(uint32 periodBuf)
{
    Dimming_PERIOD_BUF_REG = (periodBuf & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadPeriodBuf
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
uint32 Dimming_ReadPeriodBuf(void)
{
    return (Dimming_PERIOD_BUF_REG & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_SetPeriodSwap
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
void Dimming_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_CONTROL_REG &= (uint32)~Dimming_RELOAD_PERIOD_MASK;
    Dimming_CONTROL_REG |= ((uint32)((swapEnable & Dimming_1BIT_MASK) <<
                                                            Dimming_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_WriteCompare
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
void Dimming_WriteCompare(uint32 compare)
{
    #if (Dimming_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Dimming_CY_TCPWM_4000) */

    #if (Dimming_CY_TCPWM_4000)
        currentMode = ((Dimming_CONTROL_REG & Dimming_UPDOWN_MASK) >> Dimming_UPDOWN_SHIFT);

        if (((uint32)Dimming__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Dimming__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Dimming_CY_TCPWM_4000) */
    
    Dimming_COMP_CAP_REG = (compare & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadCompare
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
uint32 Dimming_ReadCompare(void)
{
    #if (Dimming_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Dimming_CY_TCPWM_4000) */

    #if (Dimming_CY_TCPWM_4000)
        currentMode = ((Dimming_CONTROL_REG & Dimming_UPDOWN_MASK) >> Dimming_UPDOWN_SHIFT);
        
        regVal = Dimming_COMP_CAP_REG;
        
        if (((uint32)Dimming__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Dimming__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Dimming_16BIT_MASK);
    #else
        return (Dimming_COMP_CAP_REG & Dimming_16BIT_MASK);
    #endif /* (Dimming_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Dimming_WriteCompareBuf
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
void Dimming_WriteCompareBuf(uint32 compareBuf)
{
    #if (Dimming_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Dimming_CY_TCPWM_4000) */

    #if (Dimming_CY_TCPWM_4000)
        currentMode = ((Dimming_CONTROL_REG & Dimming_UPDOWN_MASK) >> Dimming_UPDOWN_SHIFT);

        if (((uint32)Dimming__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Dimming__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Dimming_CY_TCPWM_4000) */
    
    Dimming_COMP_CAP_BUF_REG = (compareBuf & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadCompareBuf
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
uint32 Dimming_ReadCompareBuf(void)
{
    #if (Dimming_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Dimming_CY_TCPWM_4000) */

    #if (Dimming_CY_TCPWM_4000)
        currentMode = ((Dimming_CONTROL_REG & Dimming_UPDOWN_MASK) >> Dimming_UPDOWN_SHIFT);

        regVal = Dimming_COMP_CAP_BUF_REG;
        
        if (((uint32)Dimming__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Dimming__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Dimming_16BIT_MASK);
    #else
        return (Dimming_COMP_CAP_BUF_REG & Dimming_16BIT_MASK);
    #endif /* (Dimming_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Dimming_ReadCapture
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
uint32 Dimming_ReadCapture(void)
{
    return (Dimming_COMP_CAP_REG & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_ReadCaptureBuf
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
uint32 Dimming_ReadCaptureBuf(void)
{
    return (Dimming_COMP_CAP_BUF_REG & Dimming_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Dimming_SetCaptureMode
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
*     - Dimming_TRIG_LEVEL     - Level
*     - Dimming_TRIG_RISING    - Rising edge
*     - Dimming_TRIG_FALLING   - Falling edge
*     - Dimming_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_TRIG_CONTROL1_REG &= (uint32)~Dimming_CAPTURE_MASK;
    Dimming_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Dimming_TRIG_LEVEL     - Level
*     - Dimming_TRIG_RISING    - Rising edge
*     - Dimming_TRIG_FALLING   - Falling edge
*     - Dimming_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_TRIG_CONTROL1_REG &= (uint32)~Dimming_RELOAD_MASK;
    Dimming_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Dimming_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Dimming_TRIG_LEVEL     - Level
*     - Dimming_TRIG_RISING    - Rising edge
*     - Dimming_TRIG_FALLING   - Falling edge
*     - Dimming_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_TRIG_CONTROL1_REG &= (uint32)~Dimming_START_MASK;
    Dimming_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Dimming_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Dimming_TRIG_LEVEL     - Level
*     - Dimming_TRIG_RISING    - Rising edge
*     - Dimming_TRIG_FALLING   - Falling edge
*     - Dimming_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_TRIG_CONTROL1_REG &= (uint32)~Dimming_STOP_MASK;
    Dimming_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Dimming_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Dimming_TRIG_LEVEL     - Level
*     - Dimming_TRIG_RISING    - Rising edge
*     - Dimming_TRIG_FALLING   - Falling edge
*     - Dimming_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_TRIG_CONTROL1_REG &= (uint32)~Dimming_COUNT_MASK;
    Dimming_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Dimming_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_TriggerCommand
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
*     - Dimming_CMD_CAPTURE    - Trigger Capture command
*     - Dimming_CMD_RELOAD     - Trigger Reload command
*     - Dimming_CMD_STOP       - Trigger Stop command
*     - Dimming_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Dimming_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Dimming_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Dimming.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Dimming_STATUS_DOWN    - Set if counting down
*     - Dimming_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Dimming_ReadStatus(void)
{
    return ((Dimming_STATUS_REG >> Dimming_RUNNING_STATUS_SHIFT) |
            (Dimming_STATUS_REG & Dimming_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Dimming_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Dimming_INTR_MASK_TC       - Terminal count mask
*     - Dimming_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetInterruptMode(uint32 interruptMask)
{
    Dimming_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Dimming_GetInterruptSourceMasked
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
*     - Dimming_INTR_MASK_TC       - Terminal count mask
*     - Dimming_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Dimming_GetInterruptSourceMasked(void)
{
    return (Dimming_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Dimming_GetInterruptSource
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
*     - Dimming_INTR_MASK_TC       - Terminal count mask
*     - Dimming_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Dimming_GetInterruptSource(void)
{
    return (Dimming_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Dimming_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Dimming_INTR_MASK_TC       - Terminal count mask
*     - Dimming_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_ClearInterrupt(uint32 interruptMask)
{
    Dimming_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Dimming_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Dimming_INTR_MASK_TC       - Terminal count mask
*     - Dimming_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Dimming_SetInterrupt(uint32 interruptMask)
{
    Dimming_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
