/*******************************************************************************
* File Name: Relay_Cal.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the Relay_Cal
*  component.
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

#if !defined(CY_TCPWM_Relay_Cal_H)
#define CY_TCPWM_Relay_Cal_H


#include "CyLib.h"
#include "cytypes.h"
#include "cyfitter.h"


/*******************************************************************************
* Internal Type defines
*******************************************************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Relay_Cal_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Relay_Cal_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Relay_Cal_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Relay_Cal_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Relay_Cal_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Relay_Cal_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define Relay_Cal_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Relay_Cal_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Relay_Cal_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Relay_Cal_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Relay_Cal_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Relay_Cal_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Relay_Cal_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Relay_Cal_TC_RUN_MODE                    (0lu)
#define Relay_Cal_TC_COUNTER_MODE                (0lu)
#define Relay_Cal_TC_COMP_CAP_MODE               (2lu)
#define Relay_Cal_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Relay_Cal_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Relay_Cal_TC_COUNT_SIGNAL_MODE           (3lu)
#define Relay_Cal_TC_START_SIGNAL_MODE           (0lu)
#define Relay_Cal_TC_STOP_SIGNAL_MODE            (0lu)
#define Relay_Cal_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Relay_Cal_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Relay_Cal_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Relay_Cal_TC_START_SIGNAL_PRESENT        (0lu)
#define Relay_Cal_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Relay_Cal_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Relay_Cal_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Relay_Cal_PWM_KILL_EVENT                 (0lu)
#define Relay_Cal_PWM_STOP_EVENT                 (0lu)
#define Relay_Cal_PWM_MODE                       (4lu)
#define Relay_Cal_PWM_OUT_N_INVERT               (0lu)
#define Relay_Cal_PWM_OUT_INVERT                 (0lu)
#define Relay_Cal_PWM_ALIGN                      (0lu)
#define Relay_Cal_PWM_RUN_MODE                   (0lu)
#define Relay_Cal_PWM_DEAD_TIME_CYCLE            (0lu)
#define Relay_Cal_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Relay_Cal_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Relay_Cal_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Relay_Cal_PWM_START_SIGNAL_MODE          (0lu)
#define Relay_Cal_PWM_STOP_SIGNAL_MODE           (0lu)
#define Relay_Cal_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Relay_Cal_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Relay_Cal_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Relay_Cal_PWM_START_SIGNAL_PRESENT       (0lu)
#define Relay_Cal_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Relay_Cal_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Relay_Cal_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Relay_Cal_TC_PERIOD_VALUE                (500lu)
#define Relay_Cal_TC_COMPARE_VALUE               (65535lu)
#define Relay_Cal_TC_COMPARE_BUF_VALUE           (65535lu)
#define Relay_Cal_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Relay_Cal_PWM_PERIOD_VALUE               (65535lu)
#define Relay_Cal_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Relay_Cal_PWM_PERIOD_SWAP                (0lu)
#define Relay_Cal_PWM_COMPARE_VALUE              (65535lu)
#define Relay_Cal_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Relay_Cal_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Relay_Cal__LEFT 0
#define Relay_Cal__RIGHT 1
#define Relay_Cal__CENTER 2
#define Relay_Cal__ASYMMETRIC 3

#define Relay_Cal__X1 0
#define Relay_Cal__X2 1
#define Relay_Cal__X4 2

#define Relay_Cal__PWM 4
#define Relay_Cal__PWM_DT 5
#define Relay_Cal__PWM_PR 6

#define Relay_Cal__INVERSE 1
#define Relay_Cal__DIRECT 0

#define Relay_Cal__CAPTURE 2
#define Relay_Cal__COMPARE 0

#define Relay_Cal__TRIG_LEVEL 3
#define Relay_Cal__TRIG_RISING 0
#define Relay_Cal__TRIG_FALLING 1
#define Relay_Cal__TRIG_BOTH 2

#define Relay_Cal__INTR_MASK_TC 1
#define Relay_Cal__INTR_MASK_CC_MATCH 2
#define Relay_Cal__INTR_MASK_NONE 0
#define Relay_Cal__INTR_MASK_TC_CC 3

#define Relay_Cal__UNCONFIG 8
#define Relay_Cal__TIMER 1
#define Relay_Cal__QUAD 3
#define Relay_Cal__PWM_SEL 7

#define Relay_Cal__COUNT_UP 0
#define Relay_Cal__COUNT_DOWN 1
#define Relay_Cal__COUNT_UPDOWN0 2
#define Relay_Cal__COUNT_UPDOWN1 3


/* Prescaler */
#define Relay_Cal_PRESCALE_DIVBY1                ((uint32)(0u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY2                ((uint32)(1u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY4                ((uint32)(2u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY8                ((uint32)(3u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY16               ((uint32)(4u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY32               ((uint32)(5u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY64               ((uint32)(6u << Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_PRESCALE_DIVBY128              ((uint32)(7u << Relay_Cal_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Relay_Cal_MODE_TIMER_COMPARE             ((uint32)(Relay_Cal__COMPARE         <<  \
                                                                  Relay_Cal_MODE_SHIFT))
#define Relay_Cal_MODE_TIMER_CAPTURE             ((uint32)(Relay_Cal__CAPTURE         <<  \
                                                                  Relay_Cal_MODE_SHIFT))
#define Relay_Cal_MODE_QUAD                      ((uint32)(Relay_Cal__QUAD            <<  \
                                                                  Relay_Cal_MODE_SHIFT))
#define Relay_Cal_MODE_PWM                       ((uint32)(Relay_Cal__PWM             <<  \
                                                                  Relay_Cal_MODE_SHIFT))
#define Relay_Cal_MODE_PWM_DT                    ((uint32)(Relay_Cal__PWM_DT          <<  \
                                                                  Relay_Cal_MODE_SHIFT))
#define Relay_Cal_MODE_PWM_PR                    ((uint32)(Relay_Cal__PWM_PR          <<  \
                                                                  Relay_Cal_MODE_SHIFT))

/* Quad Modes */
#define Relay_Cal_MODE_X1                        ((uint32)(Relay_Cal__X1              <<  \
                                                                  Relay_Cal_QUAD_MODE_SHIFT))
#define Relay_Cal_MODE_X2                        ((uint32)(Relay_Cal__X2              <<  \
                                                                  Relay_Cal_QUAD_MODE_SHIFT))
#define Relay_Cal_MODE_X4                        ((uint32)(Relay_Cal__X4              <<  \
                                                                  Relay_Cal_QUAD_MODE_SHIFT))

/* Counter modes */
#define Relay_Cal_COUNT_UP                       ((uint32)(Relay_Cal__COUNT_UP        <<  \
                                                                  Relay_Cal_UPDOWN_SHIFT))
#define Relay_Cal_COUNT_DOWN                     ((uint32)(Relay_Cal__COUNT_DOWN      <<  \
                                                                  Relay_Cal_UPDOWN_SHIFT))
#define Relay_Cal_COUNT_UPDOWN0                  ((uint32)(Relay_Cal__COUNT_UPDOWN0   <<  \
                                                                  Relay_Cal_UPDOWN_SHIFT))
#define Relay_Cal_COUNT_UPDOWN1                  ((uint32)(Relay_Cal__COUNT_UPDOWN1   <<  \
                                                                  Relay_Cal_UPDOWN_SHIFT))

/* PWM output invert */
#define Relay_Cal_INVERT_LINE                    ((uint32)(Relay_Cal__INVERSE         <<  \
                                                                  Relay_Cal_INV_OUT_SHIFT))
#define Relay_Cal_INVERT_LINE_N                  ((uint32)(Relay_Cal__INVERSE         <<  \
                                                                  Relay_Cal_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Relay_Cal_TRIG_RISING                    ((uint32)Relay_Cal__TRIG_RISING)
#define Relay_Cal_TRIG_FALLING                   ((uint32)Relay_Cal__TRIG_FALLING)
#define Relay_Cal_TRIG_BOTH                      ((uint32)Relay_Cal__TRIG_BOTH)
#define Relay_Cal_TRIG_LEVEL                     ((uint32)Relay_Cal__TRIG_LEVEL)

/* Interrupt mask */
#define Relay_Cal_INTR_MASK_TC                   ((uint32)Relay_Cal__INTR_MASK_TC)
#define Relay_Cal_INTR_MASK_CC_MATCH             ((uint32)Relay_Cal__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Relay_Cal_CC_MATCH_SET                   (0x00u)
#define Relay_Cal_CC_MATCH_CLEAR                 (0x01u)
#define Relay_Cal_CC_MATCH_INVERT                (0x02u)
#define Relay_Cal_CC_MATCH_NO_CHANGE             (0x03u)
#define Relay_Cal_OVERLOW_SET                    (0x00u)
#define Relay_Cal_OVERLOW_CLEAR                  (0x04u)
#define Relay_Cal_OVERLOW_INVERT                 (0x08u)
#define Relay_Cal_OVERLOW_NO_CHANGE              (0x0Cu)
#define Relay_Cal_UNDERFLOW_SET                  (0x00u)
#define Relay_Cal_UNDERFLOW_CLEAR                (0x10u)
#define Relay_Cal_UNDERFLOW_INVERT               (0x20u)
#define Relay_Cal_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Relay_Cal_PWM_MODE_LEFT                  (Relay_Cal_CC_MATCH_CLEAR        |   \
                                                         Relay_Cal_OVERLOW_SET           |   \
                                                         Relay_Cal_UNDERFLOW_NO_CHANGE)
#define Relay_Cal_PWM_MODE_RIGHT                 (Relay_Cal_CC_MATCH_SET          |   \
                                                         Relay_Cal_OVERLOW_NO_CHANGE     |   \
                                                         Relay_Cal_UNDERFLOW_CLEAR)
#define Relay_Cal_PWM_MODE_ASYM                  (Relay_Cal_CC_MATCH_INVERT       |   \
                                                         Relay_Cal_OVERLOW_SET           |   \
                                                         Relay_Cal_UNDERFLOW_CLEAR)

#if (Relay_Cal_CY_TCPWM_V2)
    #if(Relay_Cal_CY_TCPWM_4000)
        #define Relay_Cal_PWM_MODE_CENTER                (Relay_Cal_CC_MATCH_INVERT       |   \
                                                                 Relay_Cal_OVERLOW_NO_CHANGE     |   \
                                                                 Relay_Cal_UNDERFLOW_CLEAR)
    #else
        #define Relay_Cal_PWM_MODE_CENTER                (Relay_Cal_CC_MATCH_INVERT       |   \
                                                                 Relay_Cal_OVERLOW_SET           |   \
                                                                 Relay_Cal_UNDERFLOW_CLEAR)
    #endif /* (Relay_Cal_CY_TCPWM_4000) */
#else
    #define Relay_Cal_PWM_MODE_CENTER                (Relay_Cal_CC_MATCH_INVERT       |   \
                                                             Relay_Cal_OVERLOW_NO_CHANGE     |   \
                                                             Relay_Cal_UNDERFLOW_CLEAR)
#endif /* (Relay_Cal_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Relay_Cal_CMD_CAPTURE                    (0u)
#define Relay_Cal_CMD_RELOAD                     (8u)
#define Relay_Cal_CMD_STOP                       (16u)
#define Relay_Cal_CMD_START                      (24u)

/* Status */
#define Relay_Cal_STATUS_DOWN                    (1u)
#define Relay_Cal_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Relay_Cal_Init(void);
void   Relay_Cal_Enable(void);
void   Relay_Cal_Start(void);
void   Relay_Cal_Stop(void);

void   Relay_Cal_SetMode(uint32 mode);
void   Relay_Cal_SetCounterMode(uint32 counterMode);
void   Relay_Cal_SetPWMMode(uint32 modeMask);
void   Relay_Cal_SetQDMode(uint32 qdMode);

void   Relay_Cal_SetPrescaler(uint32 prescaler);
void   Relay_Cal_TriggerCommand(uint32 mask, uint32 command);
void   Relay_Cal_SetOneShot(uint32 oneShotEnable);
uint32 Relay_Cal_ReadStatus(void);

void   Relay_Cal_SetPWMSyncKill(uint32 syncKillEnable);
void   Relay_Cal_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Relay_Cal_SetPWMDeadTime(uint32 deadTime);
void   Relay_Cal_SetPWMInvert(uint32 mask);

void   Relay_Cal_SetInterruptMode(uint32 interruptMask);
uint32 Relay_Cal_GetInterruptSourceMasked(void);
uint32 Relay_Cal_GetInterruptSource(void);
void   Relay_Cal_ClearInterrupt(uint32 interruptMask);
void   Relay_Cal_SetInterrupt(uint32 interruptMask);

void   Relay_Cal_WriteCounter(uint32 count);
uint32 Relay_Cal_ReadCounter(void);

uint32 Relay_Cal_ReadCapture(void);
uint32 Relay_Cal_ReadCaptureBuf(void);

void   Relay_Cal_WritePeriod(uint32 period);
uint32 Relay_Cal_ReadPeriod(void);
void   Relay_Cal_WritePeriodBuf(uint32 periodBuf);
uint32 Relay_Cal_ReadPeriodBuf(void);

void   Relay_Cal_WriteCompare(uint32 compare);
uint32 Relay_Cal_ReadCompare(void);
void   Relay_Cal_WriteCompareBuf(uint32 compareBuf);
uint32 Relay_Cal_ReadCompareBuf(void);

void   Relay_Cal_SetPeriodSwap(uint32 swapEnable);
void   Relay_Cal_SetCompareSwap(uint32 swapEnable);

void   Relay_Cal_SetCaptureMode(uint32 triggerMode);
void   Relay_Cal_SetReloadMode(uint32 triggerMode);
void   Relay_Cal_SetStartMode(uint32 triggerMode);
void   Relay_Cal_SetStopMode(uint32 triggerMode);
void   Relay_Cal_SetCountMode(uint32 triggerMode);

void   Relay_Cal_SaveConfig(void);
void   Relay_Cal_RestoreConfig(void);
void   Relay_Cal_Sleep(void);
void   Relay_Cal_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Relay_Cal_BLOCK_CONTROL_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Relay_Cal_BLOCK_CONTROL_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Relay_Cal_COMMAND_REG                    (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Relay_Cal_COMMAND_PTR                    ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Relay_Cal_INTRRUPT_CAUSE_REG             (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Relay_Cal_INTRRUPT_CAUSE_PTR             ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Relay_Cal_CONTROL_REG                    (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CTRL )
#define Relay_Cal_CONTROL_PTR                    ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CTRL )
#define Relay_Cal_STATUS_REG                     (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__STATUS )
#define Relay_Cal_STATUS_PTR                     ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__STATUS )
#define Relay_Cal_COUNTER_REG                    (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__COUNTER )
#define Relay_Cal_COUNTER_PTR                    ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__COUNTER )
#define Relay_Cal_COMP_CAP_REG                   (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CC )
#define Relay_Cal_COMP_CAP_PTR                   ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CC )
#define Relay_Cal_COMP_CAP_BUF_REG               (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CC_BUFF )
#define Relay_Cal_COMP_CAP_BUF_PTR               ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__CC_BUFF )
#define Relay_Cal_PERIOD_REG                     (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__PERIOD )
#define Relay_Cal_PERIOD_PTR                     ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__PERIOD )
#define Relay_Cal_PERIOD_BUF_REG                 (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Relay_Cal_PERIOD_BUF_PTR                 ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Relay_Cal_TRIG_CONTROL0_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Relay_Cal_TRIG_CONTROL0_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Relay_Cal_TRIG_CONTROL1_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Relay_Cal_TRIG_CONTROL1_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Relay_Cal_TRIG_CONTROL2_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Relay_Cal_TRIG_CONTROL2_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Relay_Cal_INTERRUPT_REQ_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR )
#define Relay_Cal_INTERRUPT_REQ_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR )
#define Relay_Cal_INTERRUPT_SET_REG              (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_SET )
#define Relay_Cal_INTERRUPT_SET_PTR              ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_SET )
#define Relay_Cal_INTERRUPT_MASK_REG             (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_MASK )
#define Relay_Cal_INTERRUPT_MASK_PTR             ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_MASK )
#define Relay_Cal_INTERRUPT_MASKED_REG           (*(reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Relay_Cal_INTERRUPT_MASKED_PTR           ( (reg32 *) Relay_Cal_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Relay_Cal_MASK                           ((uint32)Relay_Cal_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Relay_Cal_RELOAD_CC_SHIFT                (0u)
#define Relay_Cal_RELOAD_PERIOD_SHIFT            (1u)
#define Relay_Cal_PWM_SYNC_KILL_SHIFT            (2u)
#define Relay_Cal_PWM_STOP_KILL_SHIFT            (3u)
#define Relay_Cal_PRESCALER_SHIFT                (8u)
#define Relay_Cal_UPDOWN_SHIFT                   (16u)
#define Relay_Cal_ONESHOT_SHIFT                  (18u)
#define Relay_Cal_QUAD_MODE_SHIFT                (20u)
#define Relay_Cal_INV_OUT_SHIFT                  (20u)
#define Relay_Cal_INV_COMPL_OUT_SHIFT            (21u)
#define Relay_Cal_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Relay_Cal_RELOAD_CC_MASK                 ((uint32)(Relay_Cal_1BIT_MASK        <<  \
                                                                            Relay_Cal_RELOAD_CC_SHIFT))
#define Relay_Cal_RELOAD_PERIOD_MASK             ((uint32)(Relay_Cal_1BIT_MASK        <<  \
                                                                            Relay_Cal_RELOAD_PERIOD_SHIFT))
#define Relay_Cal_PWM_SYNC_KILL_MASK             ((uint32)(Relay_Cal_1BIT_MASK        <<  \
                                                                            Relay_Cal_PWM_SYNC_KILL_SHIFT))
#define Relay_Cal_PWM_STOP_KILL_MASK             ((uint32)(Relay_Cal_1BIT_MASK        <<  \
                                                                            Relay_Cal_PWM_STOP_KILL_SHIFT))
#define Relay_Cal_PRESCALER_MASK                 ((uint32)(Relay_Cal_8BIT_MASK        <<  \
                                                                            Relay_Cal_PRESCALER_SHIFT))
#define Relay_Cal_UPDOWN_MASK                    ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                            Relay_Cal_UPDOWN_SHIFT))
#define Relay_Cal_ONESHOT_MASK                   ((uint32)(Relay_Cal_1BIT_MASK        <<  \
                                                                            Relay_Cal_ONESHOT_SHIFT))
#define Relay_Cal_QUAD_MODE_MASK                 ((uint32)(Relay_Cal_3BIT_MASK        <<  \
                                                                            Relay_Cal_QUAD_MODE_SHIFT))
#define Relay_Cal_INV_OUT_MASK                   ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                            Relay_Cal_INV_OUT_SHIFT))
#define Relay_Cal_MODE_MASK                      ((uint32)(Relay_Cal_3BIT_MASK        <<  \
                                                                            Relay_Cal_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Relay_Cal_CAPTURE_SHIFT                  (0u)
#define Relay_Cal_COUNT_SHIFT                    (2u)
#define Relay_Cal_RELOAD_SHIFT                   (4u)
#define Relay_Cal_STOP_SHIFT                     (6u)
#define Relay_Cal_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Relay_Cal_CAPTURE_MASK                   ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                  Relay_Cal_CAPTURE_SHIFT))
#define Relay_Cal_COUNT_MASK                     ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                  Relay_Cal_COUNT_SHIFT))
#define Relay_Cal_RELOAD_MASK                    ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                  Relay_Cal_RELOAD_SHIFT))
#define Relay_Cal_STOP_MASK                      ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                  Relay_Cal_STOP_SHIFT))
#define Relay_Cal_START_MASK                     ((uint32)(Relay_Cal_2BIT_MASK        <<  \
                                                                  Relay_Cal_START_SHIFT))

/* MASK */
#define Relay_Cal_1BIT_MASK                      ((uint32)0x01u)
#define Relay_Cal_2BIT_MASK                      ((uint32)0x03u)
#define Relay_Cal_3BIT_MASK                      ((uint32)0x07u)
#define Relay_Cal_6BIT_MASK                      ((uint32)0x3Fu)
#define Relay_Cal_8BIT_MASK                      ((uint32)0xFFu)
#define Relay_Cal_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Relay_Cal_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Relay_Cal_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Relay_Cal_QUAD_ENCODING_MODES     << Relay_Cal_QUAD_MODE_SHIFT))       |\
         ((uint32)(Relay_Cal_CONFIG                  << Relay_Cal_MODE_SHIFT)))

#define Relay_Cal_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Relay_Cal_PWM_STOP_EVENT          << Relay_Cal_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Relay_Cal_PWM_OUT_INVERT          << Relay_Cal_INV_OUT_SHIFT))         |\
         ((uint32)(Relay_Cal_PWM_OUT_N_INVERT        << Relay_Cal_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Relay_Cal_PWM_MODE                << Relay_Cal_MODE_SHIFT)))

#define Relay_Cal_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Relay_Cal_PWM_RUN_MODE         << Relay_Cal_ONESHOT_SHIFT))
            
#define Relay_Cal_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Relay_Cal_PWM_ALIGN            << Relay_Cal_UPDOWN_SHIFT))

#define Relay_Cal_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Relay_Cal_PWM_KILL_EVENT      << Relay_Cal_PWM_SYNC_KILL_SHIFT))

#define Relay_Cal_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Relay_Cal_PWM_DEAD_TIME_CYCLE  << Relay_Cal_PRESCALER_SHIFT))

#define Relay_Cal_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Relay_Cal_PWM_PRESCALER        << Relay_Cal_PRESCALER_SHIFT))

#define Relay_Cal_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Relay_Cal_TC_PRESCALER            << Relay_Cal_PRESCALER_SHIFT))       |\
         ((uint32)(Relay_Cal_TC_COUNTER_MODE         << Relay_Cal_UPDOWN_SHIFT))          |\
         ((uint32)(Relay_Cal_TC_RUN_MODE             << Relay_Cal_ONESHOT_SHIFT))         |\
         ((uint32)(Relay_Cal_TC_COMP_CAP_MODE        << Relay_Cal_MODE_SHIFT)))
        
#define Relay_Cal_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Relay_Cal_QUAD_PHIA_SIGNAL_MODE   << Relay_Cal_COUNT_SHIFT))           |\
         ((uint32)(Relay_Cal_QUAD_INDEX_SIGNAL_MODE  << Relay_Cal_RELOAD_SHIFT))          |\
         ((uint32)(Relay_Cal_QUAD_STOP_SIGNAL_MODE   << Relay_Cal_STOP_SHIFT))            |\
         ((uint32)(Relay_Cal_QUAD_PHIB_SIGNAL_MODE   << Relay_Cal_START_SHIFT)))

#define Relay_Cal_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Relay_Cal_PWM_SWITCH_SIGNAL_MODE  << Relay_Cal_CAPTURE_SHIFT))         |\
         ((uint32)(Relay_Cal_PWM_COUNT_SIGNAL_MODE   << Relay_Cal_COUNT_SHIFT))           |\
         ((uint32)(Relay_Cal_PWM_RELOAD_SIGNAL_MODE  << Relay_Cal_RELOAD_SHIFT))          |\
         ((uint32)(Relay_Cal_PWM_STOP_SIGNAL_MODE    << Relay_Cal_STOP_SHIFT))            |\
         ((uint32)(Relay_Cal_PWM_START_SIGNAL_MODE   << Relay_Cal_START_SHIFT)))

#define Relay_Cal_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Relay_Cal_TC_CAPTURE_SIGNAL_MODE  << Relay_Cal_CAPTURE_SHIFT))         |\
         ((uint32)(Relay_Cal_TC_COUNT_SIGNAL_MODE    << Relay_Cal_COUNT_SHIFT))           |\
         ((uint32)(Relay_Cal_TC_RELOAD_SIGNAL_MODE   << Relay_Cal_RELOAD_SHIFT))          |\
         ((uint32)(Relay_Cal_TC_STOP_SIGNAL_MODE     << Relay_Cal_STOP_SHIFT))            |\
         ((uint32)(Relay_Cal_TC_START_SIGNAL_MODE    << Relay_Cal_START_SHIFT)))
        
#define Relay_Cal_TIMER_UPDOWN_CNT_USED                                                          \
                ((Relay_Cal__COUNT_UPDOWN0 == Relay_Cal_TC_COUNTER_MODE)                  ||\
                 (Relay_Cal__COUNT_UPDOWN1 == Relay_Cal_TC_COUNTER_MODE))

#define Relay_Cal_PWM_UPDOWN_CNT_USED                                                            \
                ((Relay_Cal__CENTER == Relay_Cal_PWM_ALIGN)                               ||\
                 (Relay_Cal__ASYMMETRIC == Relay_Cal_PWM_ALIGN))               
        
#define Relay_Cal_PWM_PR_INIT_VALUE              (1u)
#define Relay_Cal_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Relay_Cal_H */

/* [] END OF FILE */
