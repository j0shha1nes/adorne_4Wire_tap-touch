/*******************************************************************************
* File Name: Relay_Cal.c
* Version 2.0
*
* Description:
*  This file provides the source code to the API for the Relay_Cal
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

#include "Relay_Cal.h"

uint8 Relay_Cal_initVar = 0u;


/*******************************************************************************
* Function Name: Relay_Cal_Init
********************************************************************************
*
* Summary:
*  Initialize/Restore default Relay_Cal configuration.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_Init(void)
{

    /* Set values from customizer to CTRL */
    #if (Relay_Cal__QUAD == Relay_Cal_CONFIG)
        Relay_Cal_CONTROL_REG = Relay_Cal_CTRL_QUAD_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Relay_Cal_TRIG_CONTROL1_REG  = Relay_Cal_QUAD_SIGNALS_MODES;

        /* Set values from customizer to INTR */
        Relay_Cal_SetInterruptMode(Relay_Cal_QUAD_INTERRUPT_MASK);
        
         /* Set other values */
        Relay_Cal_SetCounterMode(Relay_Cal_COUNT_DOWN);
        Relay_Cal_WritePeriod(Relay_Cal_QUAD_PERIOD_INIT_VALUE);
        Relay_Cal_WriteCounter(Relay_Cal_QUAD_PERIOD_INIT_VALUE);
    #endif  /* (Relay_Cal__QUAD == Relay_Cal_CONFIG) */

    #if (Relay_Cal__TIMER == Relay_Cal_CONFIG)
        Relay_Cal_CONTROL_REG = Relay_Cal_CTRL_TIMER_BASE_CONFIG;
        
        /* Set values from customizer to CTRL1 */
        Relay_Cal_TRIG_CONTROL1_REG  = Relay_Cal_TIMER_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Relay_Cal_SetInterruptMode(Relay_Cal_TC_INTERRUPT_MASK);
        
        /* Set other values from customizer */
        Relay_Cal_WritePeriod(Relay_Cal_TC_PERIOD_VALUE );

        #if (Relay_Cal__COMPARE == Relay_Cal_TC_COMP_CAP_MODE)
            Relay_Cal_WriteCompare(Relay_Cal_TC_COMPARE_VALUE);

            #if (1u == Relay_Cal_TC_COMPARE_SWAP)
                Relay_Cal_SetCompareSwap(1u);
                Relay_Cal_WriteCompareBuf(Relay_Cal_TC_COMPARE_BUF_VALUE);
            #endif  /* (1u == Relay_Cal_TC_COMPARE_SWAP) */
        #endif  /* (Relay_Cal__COMPARE == Relay_Cal_TC_COMP_CAP_MODE) */

        /* Initialize counter value */
        #if (Relay_Cal_CY_TCPWM_V2 && Relay_Cal_TIMER_UPDOWN_CNT_USED && !Relay_Cal_CY_TCPWM_4000)
            Relay_Cal_WriteCounter(1u);
        #elif(Relay_Cal__COUNT_DOWN == Relay_Cal_TC_COUNTER_MODE)
            Relay_Cal_WriteCounter(Relay_Cal_TC_PERIOD_VALUE);
        #else
            Relay_Cal_WriteCounter(0u);
        #endif /* (Relay_Cal_CY_TCPWM_V2 && Relay_Cal_TIMER_UPDOWN_CNT_USED && !Relay_Cal_CY_TCPWM_4000) */
    #endif  /* (Relay_Cal__TIMER == Relay_Cal_CONFIG) */

    #if (Relay_Cal__PWM_SEL == Relay_Cal_CONFIG)
        Relay_Cal_CONTROL_REG = Relay_Cal_CTRL_PWM_BASE_CONFIG;

        #if (Relay_Cal__PWM_PR == Relay_Cal_PWM_MODE)
            Relay_Cal_CONTROL_REG |= Relay_Cal_CTRL_PWM_RUN_MODE;
            Relay_Cal_WriteCounter(Relay_Cal_PWM_PR_INIT_VALUE);
        #else
            Relay_Cal_CONTROL_REG |= Relay_Cal_CTRL_PWM_ALIGN | Relay_Cal_CTRL_PWM_KILL_EVENT;
            
            /* Initialize counter value */
            #if (Relay_Cal_CY_TCPWM_V2 && Relay_Cal_PWM_UPDOWN_CNT_USED && !Relay_Cal_CY_TCPWM_4000)
                Relay_Cal_WriteCounter(1u);
            #elif (Relay_Cal__RIGHT == Relay_Cal_PWM_ALIGN)
                Relay_Cal_WriteCounter(Relay_Cal_PWM_PERIOD_VALUE);
            #else 
                Relay_Cal_WriteCounter(0u);
            #endif  /* (Relay_Cal_CY_TCPWM_V2 && Relay_Cal_PWM_UPDOWN_CNT_USED && !Relay_Cal_CY_TCPWM_4000) */
        #endif  /* (Relay_Cal__PWM_PR == Relay_Cal_PWM_MODE) */

        #if (Relay_Cal__PWM_DT == Relay_Cal_PWM_MODE)
            Relay_Cal_CONTROL_REG |= Relay_Cal_CTRL_PWM_DEAD_TIME_CYCLE;
        #endif  /* (Relay_Cal__PWM_DT == Relay_Cal_PWM_MODE) */

        #if (Relay_Cal__PWM == Relay_Cal_PWM_MODE)
            Relay_Cal_CONTROL_REG |= Relay_Cal_CTRL_PWM_PRESCALER;
        #endif  /* (Relay_Cal__PWM == Relay_Cal_PWM_MODE) */

        /* Set values from customizer to CTRL1 */
        Relay_Cal_TRIG_CONTROL1_REG  = Relay_Cal_PWM_SIGNALS_MODES;
    
        /* Set values from customizer to INTR */
        Relay_Cal_SetInterruptMode(Relay_Cal_PWM_INTERRUPT_MASK);

        /* Set values from customizer to CTRL2 */
        #if (Relay_Cal__PWM_PR == Relay_Cal_PWM_MODE)
            Relay_Cal_TRIG_CONTROL2_REG =
                    (Relay_Cal_CC_MATCH_NO_CHANGE    |
                    Relay_Cal_OVERLOW_NO_CHANGE      |
                    Relay_Cal_UNDERFLOW_NO_CHANGE);
        #else
            #if (Relay_Cal__LEFT == Relay_Cal_PWM_ALIGN)
                Relay_Cal_TRIG_CONTROL2_REG = Relay_Cal_PWM_MODE_LEFT;
            #endif  /* ( Relay_Cal_PWM_LEFT == Relay_Cal_PWM_ALIGN) */

            #if (Relay_Cal__RIGHT == Relay_Cal_PWM_ALIGN)
                Relay_Cal_TRIG_CONTROL2_REG = Relay_Cal_PWM_MODE_RIGHT;
            #endif  /* ( Relay_Cal_PWM_RIGHT == Relay_Cal_PWM_ALIGN) */

            #if (Relay_Cal__CENTER == Relay_Cal_PWM_ALIGN)
                Relay_Cal_TRIG_CONTROL2_REG = Relay_Cal_PWM_MODE_CENTER;
            #endif  /* ( Relay_Cal_PWM_CENTER == Relay_Cal_PWM_ALIGN) */

            #if (Relay_Cal__ASYMMETRIC == Relay_Cal_PWM_ALIGN)
                Relay_Cal_TRIG_CONTROL2_REG = Relay_Cal_PWM_MODE_ASYM;
            #endif  /* (Relay_Cal__ASYMMETRIC == Relay_Cal_PWM_ALIGN) */
        #endif  /* (Relay_Cal__PWM_PR == Relay_Cal_PWM_MODE) */

        /* Set other values from customizer */
        Relay_Cal_WritePeriod(Relay_Cal_PWM_PERIOD_VALUE );
        Relay_Cal_WriteCompare(Relay_Cal_PWM_COMPARE_VALUE);

        #if (1u == Relay_Cal_PWM_COMPARE_SWAP)
            Relay_Cal_SetCompareSwap(1u);
            Relay_Cal_WriteCompareBuf(Relay_Cal_PWM_COMPARE_BUF_VALUE);
        #endif  /* (1u == Relay_Cal_PWM_COMPARE_SWAP) */

        #if (1u == Relay_Cal_PWM_PERIOD_SWAP)
            Relay_Cal_SetPeriodSwap(1u);
            Relay_Cal_WritePeriodBuf(Relay_Cal_PWM_PERIOD_BUF_VALUE);
        #endif  /* (1u == Relay_Cal_PWM_PERIOD_SWAP) */
    #endif  /* (Relay_Cal__PWM_SEL == Relay_Cal_CONFIG) */
    
}


/*******************************************************************************
* Function Name: Relay_Cal_Enable
********************************************************************************
*
* Summary:
*  Enables the Relay_Cal.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_Enable(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();
    Relay_Cal_BLOCK_CONTROL_REG |= Relay_Cal_MASK;
    CyExitCriticalSection(enableInterrupts);

    /* Start Timer or PWM if start input is absent */
    #if (Relay_Cal__PWM_SEL == Relay_Cal_CONFIG)
        #if (0u == Relay_Cal_PWM_START_SIGNAL_PRESENT)
            Relay_Cal_TriggerCommand(Relay_Cal_MASK, Relay_Cal_CMD_START);
        #endif /* (0u == Relay_Cal_PWM_START_SIGNAL_PRESENT) */
    #endif /* (Relay_Cal__PWM_SEL == Relay_Cal_CONFIG) */

    #if (Relay_Cal__TIMER == Relay_Cal_CONFIG)
        #if (0u == Relay_Cal_TC_START_SIGNAL_PRESENT)
            Relay_Cal_TriggerCommand(Relay_Cal_MASK, Relay_Cal_CMD_START);
        #endif /* (0u == Relay_Cal_TC_START_SIGNAL_PRESENT) */
    #endif /* (Relay_Cal__TIMER == Relay_Cal_CONFIG) */
}


/*******************************************************************************
* Function Name: Relay_Cal_Start
********************************************************************************
*
* Summary:
*  Initializes the Relay_Cal with default customizer
*  values when called the first time and enables the Relay_Cal.
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
*  Relay_Cal_initVar: global variable is used to indicate initial
*  configuration of this component.  The variable is initialized to zero and set
*  to 1 the first time Relay_Cal_Start() is called. This allows
*  enabling/disabling a component without re-initialization in all subsequent
*  calls to the Relay_Cal_Start() routine.
*
*******************************************************************************/
void Relay_Cal_Start(void)
{
    if (0u == Relay_Cal_initVar)
    {
        Relay_Cal_Init();
        Relay_Cal_initVar = 1u;
    }

    Relay_Cal_Enable();
}


/*******************************************************************************
* Function Name: Relay_Cal_Stop
********************************************************************************
*
* Summary:
*  Disables the Relay_Cal.
*
* Parameters:
*  None
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_Stop(void)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_BLOCK_CONTROL_REG &= (uint32)~Relay_Cal_MASK;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetMode
********************************************************************************
*
* Summary:
*  Sets the operation mode of the Relay_Cal. This function is used when
*  configured as a generic Relay_Cal and the actual mode of operation is
*  set at runtime. The mode must be set while the component is disabled.
*
* Parameters:
*  mode: Mode for the Relay_Cal to operate in
*   Values:
*   - Relay_Cal_MODE_TIMER_COMPARE - Timer / Counter with
*                                                 compare capability
*         - Relay_Cal_MODE_TIMER_CAPTURE - Timer / Counter with
*                                                 capture capability
*         - Relay_Cal_MODE_QUAD - Quadrature decoder
*         - Relay_Cal_MODE_PWM - PWM
*         - Relay_Cal_MODE_PWM_DT - PWM with dead time
*         - Relay_Cal_MODE_PWM_PR - PWM with pseudo random capability
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetMode(uint32 mode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_MODE_MASK;
    Relay_Cal_CONTROL_REG |= mode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetQDMode
********************************************************************************
*
* Summary:
*  Sets the the Quadrature Decoder to one of the 3 supported modes.
*  Its functionality is only applicable to Quadrature Decoder operation.
*
* Parameters:
*  qdMode: Quadrature Decoder mode
*   Values:
*         - Relay_Cal_MODE_X1 - Counts on phi 1 rising
*         - Relay_Cal_MODE_X2 - Counts on both edges of phi1 (2x faster)
*         - Relay_Cal_MODE_X4 - Counts on both edges of phi1 and phi2
*                                        (4x faster)
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetQDMode(uint32 qdMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_QUAD_MODE_MASK;
    Relay_Cal_CONTROL_REG |= qdMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPrescaler
********************************************************************************
*
* Summary:
*  Sets the prescaler value that is applied to the clock input.  Not applicable
*  to a PWM with the dead time mode or Quadrature Decoder mode.
*
* Parameters:
*  prescaler: Prescaler divider value
*   Values:
*         - Relay_Cal_PRESCALE_DIVBY1    - Divide by 1 (no prescaling)
*         - Relay_Cal_PRESCALE_DIVBY2    - Divide by 2
*         - Relay_Cal_PRESCALE_DIVBY4    - Divide by 4
*         - Relay_Cal_PRESCALE_DIVBY8    - Divide by 8
*         - Relay_Cal_PRESCALE_DIVBY16   - Divide by 16
*         - Relay_Cal_PRESCALE_DIVBY32   - Divide by 32
*         - Relay_Cal_PRESCALE_DIVBY64   - Divide by 64
*         - Relay_Cal_PRESCALE_DIVBY128  - Divide by 128
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetPrescaler(uint32 prescaler)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_PRESCALER_MASK;
    Relay_Cal_CONTROL_REG |= prescaler;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetOneShot
********************************************************************************
*
* Summary:
*  Writes the register that controls whether the Relay_Cal runs
*  continuously or stops when terminal count is reached.  By default the
*  Relay_Cal operates in the continuous mode.
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
void Relay_Cal_SetOneShot(uint32 oneShotEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_ONESHOT_MASK;
    Relay_Cal_CONTROL_REG |= ((uint32)((oneShotEnable & Relay_Cal_1BIT_MASK) <<
                                                               Relay_Cal_ONESHOT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPWMMode
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
void Relay_Cal_SetPWMMode(uint32 modeMask)
{
    Relay_Cal_TRIG_CONTROL2_REG = (modeMask & Relay_Cal_6BIT_MASK);
}



/*******************************************************************************
* Function Name: Relay_Cal_SetPWMSyncKill
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
void Relay_Cal_SetPWMSyncKill(uint32 syncKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_PWM_SYNC_KILL_MASK;
    Relay_Cal_CONTROL_REG |= ((uint32)((syncKillEnable & Relay_Cal_1BIT_MASK)  <<
                                               Relay_Cal_PWM_SYNC_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPWMStopOnKill
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
void Relay_Cal_SetPWMStopOnKill(uint32 stopOnKillEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_PWM_STOP_KILL_MASK;
    Relay_Cal_CONTROL_REG |= ((uint32)((stopOnKillEnable & Relay_Cal_1BIT_MASK)  <<
                                                         Relay_Cal_PWM_STOP_KILL_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPWMDeadTime
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
void Relay_Cal_SetPWMDeadTime(uint32 deadTime)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_PRESCALER_MASK;
    Relay_Cal_CONTROL_REG |= ((uint32)((deadTime & Relay_Cal_8BIT_MASK) <<
                                                          Relay_Cal_PRESCALER_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPWMInvert
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
*         - Relay_Cal_INVERT_LINE   - Inverts the line output
*         - Relay_Cal_INVERT_LINE_N - Inverts the line_n output
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetPWMInvert(uint32 mask)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_INV_OUT_MASK;
    Relay_Cal_CONTROL_REG |= mask;

    CyExitCriticalSection(enableInterrupts);
}



/*******************************************************************************
* Function Name: Relay_Cal_WriteCounter
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
void Relay_Cal_WriteCounter(uint32 count)
{
    Relay_Cal_COUNTER_REG = (count & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadCounter
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
uint32 Relay_Cal_ReadCounter(void)
{
    return (Relay_Cal_COUNTER_REG & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetCounterMode
********************************************************************************
*
* Summary:
*  Sets the counter mode.  Applicable to all modes except Quadrature Decoder
*  and the PWM with a pseudo random output.
*
* Parameters:
*  counterMode: Enumerated counter type values
*   Values:
*     - Relay_Cal_COUNT_UP       - Counts up
*     - Relay_Cal_COUNT_DOWN     - Counts down
*     - Relay_Cal_COUNT_UPDOWN0  - Counts up and down. Terminal count
*                                         generated when counter reaches 0
*     - Relay_Cal_COUNT_UPDOWN1  - Counts up and down. Terminal count
*                                         generated both when counter reaches 0
*                                         and period
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetCounterMode(uint32 counterMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_UPDOWN_MASK;
    Relay_Cal_CONTROL_REG |= counterMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_WritePeriod
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
void Relay_Cal_WritePeriod(uint32 period)
{
    Relay_Cal_PERIOD_REG = (period & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadPeriod
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
uint32 Relay_Cal_ReadPeriod(void)
{
    return (Relay_Cal_PERIOD_REG & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetCompareSwap
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
void Relay_Cal_SetCompareSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_RELOAD_CC_MASK;
    Relay_Cal_CONTROL_REG |= (swapEnable & Relay_Cal_1BIT_MASK);

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_WritePeriodBuf
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
void Relay_Cal_WritePeriodBuf(uint32 periodBuf)
{
    Relay_Cal_PERIOD_BUF_REG = (periodBuf & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadPeriodBuf
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
uint32 Relay_Cal_ReadPeriodBuf(void)
{
    return (Relay_Cal_PERIOD_BUF_REG & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetPeriodSwap
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
void Relay_Cal_SetPeriodSwap(uint32 swapEnable)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_CONTROL_REG &= (uint32)~Relay_Cal_RELOAD_PERIOD_MASK;
    Relay_Cal_CONTROL_REG |= ((uint32)((swapEnable & Relay_Cal_1BIT_MASK) <<
                                                            Relay_Cal_RELOAD_PERIOD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_WriteCompare
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
void Relay_Cal_WriteCompare(uint32 compare)
{
    #if (Relay_Cal_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Relay_Cal_CY_TCPWM_4000) */

    #if (Relay_Cal_CY_TCPWM_4000)
        currentMode = ((Relay_Cal_CONTROL_REG & Relay_Cal_UPDOWN_MASK) >> Relay_Cal_UPDOWN_SHIFT);

        if (((uint32)Relay_Cal__COUNT_DOWN == currentMode) && (0xFFFFu != compare))
        {
            compare++;
        }
        else if (((uint32)Relay_Cal__COUNT_UP == currentMode) && (0u != compare))
        {
            compare--;
        }
        else
        {
        }
        
    
    #endif /* (Relay_Cal_CY_TCPWM_4000) */
    
    Relay_Cal_COMP_CAP_REG = (compare & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadCompare
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
uint32 Relay_Cal_ReadCompare(void)
{
    #if (Relay_Cal_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Relay_Cal_CY_TCPWM_4000) */

    #if (Relay_Cal_CY_TCPWM_4000)
        currentMode = ((Relay_Cal_CONTROL_REG & Relay_Cal_UPDOWN_MASK) >> Relay_Cal_UPDOWN_SHIFT);
        
        regVal = Relay_Cal_COMP_CAP_REG;
        
        if (((uint32)Relay_Cal__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Relay_Cal__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Relay_Cal_16BIT_MASK);
    #else
        return (Relay_Cal_COMP_CAP_REG & Relay_Cal_16BIT_MASK);
    #endif /* (Relay_Cal_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Relay_Cal_WriteCompareBuf
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
void Relay_Cal_WriteCompareBuf(uint32 compareBuf)
{
    #if (Relay_Cal_CY_TCPWM_4000)
        uint32 currentMode;
    #endif /* (Relay_Cal_CY_TCPWM_4000) */

    #if (Relay_Cal_CY_TCPWM_4000)
        currentMode = ((Relay_Cal_CONTROL_REG & Relay_Cal_UPDOWN_MASK) >> Relay_Cal_UPDOWN_SHIFT);

        if (((uint32)Relay_Cal__COUNT_DOWN == currentMode) && (0xFFFFu != compareBuf))
        {
            compareBuf++;
        }
        else if (((uint32)Relay_Cal__COUNT_UP == currentMode) && (0u != compareBuf))
        {
            compareBuf --;
        }
        else
        {
        }
    #endif /* (Relay_Cal_CY_TCPWM_4000) */
    
    Relay_Cal_COMP_CAP_BUF_REG = (compareBuf & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadCompareBuf
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
uint32 Relay_Cal_ReadCompareBuf(void)
{
    #if (Relay_Cal_CY_TCPWM_4000)
        uint32 currentMode;
        uint32 regVal;
    #endif /* (Relay_Cal_CY_TCPWM_4000) */

    #if (Relay_Cal_CY_TCPWM_4000)
        currentMode = ((Relay_Cal_CONTROL_REG & Relay_Cal_UPDOWN_MASK) >> Relay_Cal_UPDOWN_SHIFT);

        regVal = Relay_Cal_COMP_CAP_BUF_REG;
        
        if (((uint32)Relay_Cal__COUNT_DOWN == currentMode) && (0u != regVal))
        {
            regVal--;
        }
        else if (((uint32)Relay_Cal__COUNT_UP == currentMode) && (0xFFFFu != regVal))
        {
            regVal++;
        }
        else
        {
        }

        return (regVal & Relay_Cal_16BIT_MASK);
    #else
        return (Relay_Cal_COMP_CAP_BUF_REG & Relay_Cal_16BIT_MASK);
    #endif /* (Relay_Cal_CY_TCPWM_4000) */
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadCapture
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
uint32 Relay_Cal_ReadCapture(void)
{
    return (Relay_Cal_COMP_CAP_REG & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadCaptureBuf
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
uint32 Relay_Cal_ReadCaptureBuf(void)
{
    return (Relay_Cal_COMP_CAP_BUF_REG & Relay_Cal_16BIT_MASK);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetCaptureMode
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
*     - Relay_Cal_TRIG_LEVEL     - Level
*     - Relay_Cal_TRIG_RISING    - Rising edge
*     - Relay_Cal_TRIG_FALLING   - Falling edge
*     - Relay_Cal_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetCaptureMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_TRIG_CONTROL1_REG &= (uint32)~Relay_Cal_CAPTURE_MASK;
    Relay_Cal_TRIG_CONTROL1_REG |= triggerMode;

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetReloadMode
********************************************************************************
*
* Summary:
*  Sets the reload trigger mode. For Quadrature Decoder mode this is the index
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Relay_Cal_TRIG_LEVEL     - Level
*     - Relay_Cal_TRIG_RISING    - Rising edge
*     - Relay_Cal_TRIG_FALLING   - Falling edge
*     - Relay_Cal_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetReloadMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_TRIG_CONTROL1_REG &= (uint32)~Relay_Cal_RELOAD_MASK;
    Relay_Cal_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Relay_Cal_RELOAD_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetStartMode
********************************************************************************
*
* Summary:
*  Sets the start trigger mode. For Quadrature Decoder mode this is the
*  phiB input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Relay_Cal_TRIG_LEVEL     - Level
*     - Relay_Cal_TRIG_RISING    - Rising edge
*     - Relay_Cal_TRIG_FALLING   - Falling edge
*     - Relay_Cal_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetStartMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_TRIG_CONTROL1_REG &= (uint32)~Relay_Cal_START_MASK;
    Relay_Cal_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Relay_Cal_START_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetStopMode
********************************************************************************
*
* Summary:
*  Sets the stop trigger mode. For PWM mode this is the kill input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Relay_Cal_TRIG_LEVEL     - Level
*     - Relay_Cal_TRIG_RISING    - Rising edge
*     - Relay_Cal_TRIG_FALLING   - Falling edge
*     - Relay_Cal_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetStopMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_TRIG_CONTROL1_REG &= (uint32)~Relay_Cal_STOP_MASK;
    Relay_Cal_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Relay_Cal_STOP_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_SetCountMode
********************************************************************************
*
* Summary:
*  Sets the count trigger mode. For Quadrature Decoder mode this is the phiA
*  input.
*
* Parameters:
*  triggerMode: Enumerated trigger mode value
*   Values:
*     - Relay_Cal_TRIG_LEVEL     - Level
*     - Relay_Cal_TRIG_RISING    - Rising edge
*     - Relay_Cal_TRIG_FALLING   - Falling edge
*     - Relay_Cal_TRIG_BOTH      - Both rising and falling edge
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetCountMode(uint32 triggerMode)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_TRIG_CONTROL1_REG &= (uint32)~Relay_Cal_COUNT_MASK;
    Relay_Cal_TRIG_CONTROL1_REG |= ((uint32)(triggerMode << Relay_Cal_COUNT_SHIFT));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_TriggerCommand
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
*     - Relay_Cal_CMD_CAPTURE    - Trigger Capture command
*     - Relay_Cal_CMD_RELOAD     - Trigger Reload command
*     - Relay_Cal_CMD_STOP       - Trigger Stop command
*     - Relay_Cal_CMD_START      - Trigger Start command
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_TriggerCommand(uint32 mask, uint32 command)
{
    uint8 enableInterrupts;

    enableInterrupts = CyEnterCriticalSection();

    Relay_Cal_COMMAND_REG = ((uint32)(mask << command));

    CyExitCriticalSection(enableInterrupts);
}


/*******************************************************************************
* Function Name: Relay_Cal_ReadStatus
********************************************************************************
*
* Summary:
*  Reads the status of the Relay_Cal.
*
* Parameters:
*  None
*
* Return:
*  Status
*   Values:
*     - Relay_Cal_STATUS_DOWN    - Set if counting down
*     - Relay_Cal_STATUS_RUNNING - Set if counter is running
*
*******************************************************************************/
uint32 Relay_Cal_ReadStatus(void)
{
    return ((Relay_Cal_STATUS_REG >> Relay_Cal_RUNNING_STATUS_SHIFT) |
            (Relay_Cal_STATUS_REG & Relay_Cal_STATUS_DOWN));
}


/*******************************************************************************
* Function Name: Relay_Cal_SetInterruptMode
********************************************************************************
*
* Summary:
*  Sets the interrupt mask to control which interrupt
*  requests generate the interrupt signal.
*
* Parameters:
*   interruptMask: Mask of bits to be enabled
*   Values:
*     - Relay_Cal_INTR_MASK_TC       - Terminal count mask
*     - Relay_Cal_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetInterruptMode(uint32 interruptMask)
{
    Relay_Cal_INTERRUPT_MASK_REG =  interruptMask;
}


/*******************************************************************************
* Function Name: Relay_Cal_GetInterruptSourceMasked
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
*     - Relay_Cal_INTR_MASK_TC       - Terminal count mask
*     - Relay_Cal_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Relay_Cal_GetInterruptSourceMasked(void)
{
    return (Relay_Cal_INTERRUPT_MASKED_REG);
}


/*******************************************************************************
* Function Name: Relay_Cal_GetInterruptSource
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
*     - Relay_Cal_INTR_MASK_TC       - Terminal count mask
*     - Relay_Cal_INTR_MASK_CC_MATCH - Compare count / capture mask
*
*******************************************************************************/
uint32 Relay_Cal_GetInterruptSource(void)
{
    return (Relay_Cal_INTERRUPT_REQ_REG);
}


/*******************************************************************************
* Function Name: Relay_Cal_ClearInterrupt
********************************************************************************
*
* Summary:
*  Clears the interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to clear
*   Values:
*     - Relay_Cal_INTR_MASK_TC       - Terminal count mask
*     - Relay_Cal_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_ClearInterrupt(uint32 interruptMask)
{
    Relay_Cal_INTERRUPT_REQ_REG = interruptMask;
}


/*******************************************************************************
* Function Name: Relay_Cal_SetInterrupt
********************************************************************************
*
* Summary:
*  Sets a software interrupt request.
*
* Parameters:
*   interruptMask: Mask of interrupts to set
*   Values:
*     - Relay_Cal_INTR_MASK_TC       - Terminal count mask
*     - Relay_Cal_INTR_MASK_CC_MATCH - Compare count / capture mask
*
* Return:
*  None
*
*******************************************************************************/
void Relay_Cal_SetInterrupt(uint32 interruptMask)
{
    Relay_Cal_INTERRUPT_SET_REG = interruptMask;
}


/* [] END OF FILE */
