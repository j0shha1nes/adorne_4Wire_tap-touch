/*******************************************************************************
* File Name: Dimming.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the Dimming
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

#if !defined(CY_TCPWM_Dimming_H)
#define CY_TCPWM_Dimming_H


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
} Dimming_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Dimming_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Dimming_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Dimming_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Dimming_CONFIG                         (7lu)

/* Quad Mode */
/* Parameters */
#define Dimming_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define Dimming_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Dimming_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Dimming_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Dimming_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Dimming_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Dimming_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Dimming_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Dimming_TC_RUN_MODE                    (0lu)
#define Dimming_TC_COUNTER_MODE                (0lu)
#define Dimming_TC_COMP_CAP_MODE               (2lu)
#define Dimming_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Dimming_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Dimming_TC_COUNT_SIGNAL_MODE           (3lu)
#define Dimming_TC_START_SIGNAL_MODE           (0lu)
#define Dimming_TC_STOP_SIGNAL_MODE            (0lu)
#define Dimming_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Dimming_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Dimming_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Dimming_TC_START_SIGNAL_PRESENT        (0lu)
#define Dimming_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Dimming_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Dimming_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Dimming_PWM_KILL_EVENT                 (1lu)
#define Dimming_PWM_STOP_EVENT                 (0lu)
#define Dimming_PWM_MODE                       (4lu)
#define Dimming_PWM_OUT_N_INVERT               (1lu)
#define Dimming_PWM_OUT_INVERT                 (0lu)
#define Dimming_PWM_ALIGN                      (0lu)
#define Dimming_PWM_RUN_MODE                   (0lu)
#define Dimming_PWM_DEAD_TIME_CYCLE            (0lu)
#define Dimming_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Dimming_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Dimming_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Dimming_PWM_START_SIGNAL_MODE          (0lu)
#define Dimming_PWM_STOP_SIGNAL_MODE           (0lu)
#define Dimming_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Dimming_PWM_RELOAD_SIGNAL_PRESENT      (1lu)
#define Dimming_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Dimming_PWM_START_SIGNAL_PRESENT       (0lu)
#define Dimming_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Dimming_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Dimming_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Dimming_TC_PERIOD_VALUE                (65535lu)
#define Dimming_TC_COMPARE_VALUE               (65535lu)
#define Dimming_TC_COMPARE_BUF_VALUE           (65535lu)
#define Dimming_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Dimming_PWM_PERIOD_VALUE               (1000lu)
#define Dimming_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Dimming_PWM_PERIOD_SWAP                (0lu)
#define Dimming_PWM_COMPARE_VALUE              (545lu)
#define Dimming_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Dimming_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Dimming__LEFT 0
#define Dimming__RIGHT 1
#define Dimming__CENTER 2
#define Dimming__ASYMMETRIC 3

#define Dimming__X1 0
#define Dimming__X2 1
#define Dimming__X4 2

#define Dimming__PWM 4
#define Dimming__PWM_DT 5
#define Dimming__PWM_PR 6

#define Dimming__INVERSE 1
#define Dimming__DIRECT 0

#define Dimming__CAPTURE 2
#define Dimming__COMPARE 0

#define Dimming__TRIG_LEVEL 3
#define Dimming__TRIG_RISING 0
#define Dimming__TRIG_FALLING 1
#define Dimming__TRIG_BOTH 2

#define Dimming__INTR_MASK_TC 1
#define Dimming__INTR_MASK_CC_MATCH 2
#define Dimming__INTR_MASK_NONE 0
#define Dimming__INTR_MASK_TC_CC 3

#define Dimming__UNCONFIG 8
#define Dimming__TIMER 1
#define Dimming__QUAD 3
#define Dimming__PWM_SEL 7

#define Dimming__COUNT_UP 0
#define Dimming__COUNT_DOWN 1
#define Dimming__COUNT_UPDOWN0 2
#define Dimming__COUNT_UPDOWN1 3


/* Prescaler */
#define Dimming_PRESCALE_DIVBY1                ((uint32)(0u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY2                ((uint32)(1u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY4                ((uint32)(2u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY8                ((uint32)(3u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY16               ((uint32)(4u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY32               ((uint32)(5u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY64               ((uint32)(6u << Dimming_PRESCALER_SHIFT))
#define Dimming_PRESCALE_DIVBY128              ((uint32)(7u << Dimming_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Dimming_MODE_TIMER_COMPARE             ((uint32)(Dimming__COMPARE         <<  \
                                                                  Dimming_MODE_SHIFT))
#define Dimming_MODE_TIMER_CAPTURE             ((uint32)(Dimming__CAPTURE         <<  \
                                                                  Dimming_MODE_SHIFT))
#define Dimming_MODE_QUAD                      ((uint32)(Dimming__QUAD            <<  \
                                                                  Dimming_MODE_SHIFT))
#define Dimming_MODE_PWM                       ((uint32)(Dimming__PWM             <<  \
                                                                  Dimming_MODE_SHIFT))
#define Dimming_MODE_PWM_DT                    ((uint32)(Dimming__PWM_DT          <<  \
                                                                  Dimming_MODE_SHIFT))
#define Dimming_MODE_PWM_PR                    ((uint32)(Dimming__PWM_PR          <<  \
                                                                  Dimming_MODE_SHIFT))

/* Quad Modes */
#define Dimming_MODE_X1                        ((uint32)(Dimming__X1              <<  \
                                                                  Dimming_QUAD_MODE_SHIFT))
#define Dimming_MODE_X2                        ((uint32)(Dimming__X2              <<  \
                                                                  Dimming_QUAD_MODE_SHIFT))
#define Dimming_MODE_X4                        ((uint32)(Dimming__X4              <<  \
                                                                  Dimming_QUAD_MODE_SHIFT))

/* Counter modes */
#define Dimming_COUNT_UP                       ((uint32)(Dimming__COUNT_UP        <<  \
                                                                  Dimming_UPDOWN_SHIFT))
#define Dimming_COUNT_DOWN                     ((uint32)(Dimming__COUNT_DOWN      <<  \
                                                                  Dimming_UPDOWN_SHIFT))
#define Dimming_COUNT_UPDOWN0                  ((uint32)(Dimming__COUNT_UPDOWN0   <<  \
                                                                  Dimming_UPDOWN_SHIFT))
#define Dimming_COUNT_UPDOWN1                  ((uint32)(Dimming__COUNT_UPDOWN1   <<  \
                                                                  Dimming_UPDOWN_SHIFT))

/* PWM output invert */
#define Dimming_INVERT_LINE                    ((uint32)(Dimming__INVERSE         <<  \
                                                                  Dimming_INV_OUT_SHIFT))
#define Dimming_INVERT_LINE_N                  ((uint32)(Dimming__INVERSE         <<  \
                                                                  Dimming_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Dimming_TRIG_RISING                    ((uint32)Dimming__TRIG_RISING)
#define Dimming_TRIG_FALLING                   ((uint32)Dimming__TRIG_FALLING)
#define Dimming_TRIG_BOTH                      ((uint32)Dimming__TRIG_BOTH)
#define Dimming_TRIG_LEVEL                     ((uint32)Dimming__TRIG_LEVEL)

/* Interrupt mask */
#define Dimming_INTR_MASK_TC                   ((uint32)Dimming__INTR_MASK_TC)
#define Dimming_INTR_MASK_CC_MATCH             ((uint32)Dimming__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Dimming_CC_MATCH_SET                   (0x00u)
#define Dimming_CC_MATCH_CLEAR                 (0x01u)
#define Dimming_CC_MATCH_INVERT                (0x02u)
#define Dimming_CC_MATCH_NO_CHANGE             (0x03u)
#define Dimming_OVERLOW_SET                    (0x00u)
#define Dimming_OVERLOW_CLEAR                  (0x04u)
#define Dimming_OVERLOW_INVERT                 (0x08u)
#define Dimming_OVERLOW_NO_CHANGE              (0x0Cu)
#define Dimming_UNDERFLOW_SET                  (0x00u)
#define Dimming_UNDERFLOW_CLEAR                (0x10u)
#define Dimming_UNDERFLOW_INVERT               (0x20u)
#define Dimming_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Dimming_PWM_MODE_LEFT                  (Dimming_CC_MATCH_CLEAR        |   \
                                                         Dimming_OVERLOW_SET           |   \
                                                         Dimming_UNDERFLOW_NO_CHANGE)
#define Dimming_PWM_MODE_RIGHT                 (Dimming_CC_MATCH_SET          |   \
                                                         Dimming_OVERLOW_NO_CHANGE     |   \
                                                         Dimming_UNDERFLOW_CLEAR)
#define Dimming_PWM_MODE_ASYM                  (Dimming_CC_MATCH_INVERT       |   \
                                                         Dimming_OVERLOW_SET           |   \
                                                         Dimming_UNDERFLOW_CLEAR)

#if (Dimming_CY_TCPWM_V2)
    #if(Dimming_CY_TCPWM_4000)
        #define Dimming_PWM_MODE_CENTER                (Dimming_CC_MATCH_INVERT       |   \
                                                                 Dimming_OVERLOW_NO_CHANGE     |   \
                                                                 Dimming_UNDERFLOW_CLEAR)
    #else
        #define Dimming_PWM_MODE_CENTER                (Dimming_CC_MATCH_INVERT       |   \
                                                                 Dimming_OVERLOW_SET           |   \
                                                                 Dimming_UNDERFLOW_CLEAR)
    #endif /* (Dimming_CY_TCPWM_4000) */
#else
    #define Dimming_PWM_MODE_CENTER                (Dimming_CC_MATCH_INVERT       |   \
                                                             Dimming_OVERLOW_NO_CHANGE     |   \
                                                             Dimming_UNDERFLOW_CLEAR)
#endif /* (Dimming_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Dimming_CMD_CAPTURE                    (0u)
#define Dimming_CMD_RELOAD                     (8u)
#define Dimming_CMD_STOP                       (16u)
#define Dimming_CMD_START                      (24u)

/* Status */
#define Dimming_STATUS_DOWN                    (1u)
#define Dimming_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Dimming_Init(void);
void   Dimming_Enable(void);
void   Dimming_Start(void);
void   Dimming_Stop(void);

void   Dimming_SetMode(uint32 mode);
void   Dimming_SetCounterMode(uint32 counterMode);
void   Dimming_SetPWMMode(uint32 modeMask);
void   Dimming_SetQDMode(uint32 qdMode);

void   Dimming_SetPrescaler(uint32 prescaler);
void   Dimming_TriggerCommand(uint32 mask, uint32 command);
void   Dimming_SetOneShot(uint32 oneShotEnable);
uint32 Dimming_ReadStatus(void);

void   Dimming_SetPWMSyncKill(uint32 syncKillEnable);
void   Dimming_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Dimming_SetPWMDeadTime(uint32 deadTime);
void   Dimming_SetPWMInvert(uint32 mask);

void   Dimming_SetInterruptMode(uint32 interruptMask);
uint32 Dimming_GetInterruptSourceMasked(void);
uint32 Dimming_GetInterruptSource(void);
void   Dimming_ClearInterrupt(uint32 interruptMask);
void   Dimming_SetInterrupt(uint32 interruptMask);

void   Dimming_WriteCounter(uint32 count);
uint32 Dimming_ReadCounter(void);

uint32 Dimming_ReadCapture(void);
uint32 Dimming_ReadCaptureBuf(void);

void   Dimming_WritePeriod(uint32 period);
uint32 Dimming_ReadPeriod(void);
void   Dimming_WritePeriodBuf(uint32 periodBuf);
uint32 Dimming_ReadPeriodBuf(void);

void   Dimming_WriteCompare(uint32 compare);
uint32 Dimming_ReadCompare(void);
void   Dimming_WriteCompareBuf(uint32 compareBuf);
uint32 Dimming_ReadCompareBuf(void);

void   Dimming_SetPeriodSwap(uint32 swapEnable);
void   Dimming_SetCompareSwap(uint32 swapEnable);

void   Dimming_SetCaptureMode(uint32 triggerMode);
void   Dimming_SetReloadMode(uint32 triggerMode);
void   Dimming_SetStartMode(uint32 triggerMode);
void   Dimming_SetStopMode(uint32 triggerMode);
void   Dimming_SetCountMode(uint32 triggerMode);

void   Dimming_SaveConfig(void);
void   Dimming_RestoreConfig(void);
void   Dimming_Sleep(void);
void   Dimming_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Dimming_BLOCK_CONTROL_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Dimming_BLOCK_CONTROL_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Dimming_COMMAND_REG                    (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Dimming_COMMAND_PTR                    ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Dimming_INTRRUPT_CAUSE_REG             (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Dimming_INTRRUPT_CAUSE_PTR             ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Dimming_CONTROL_REG                    (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__CTRL )
#define Dimming_CONTROL_PTR                    ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__CTRL )
#define Dimming_STATUS_REG                     (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__STATUS )
#define Dimming_STATUS_PTR                     ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__STATUS )
#define Dimming_COUNTER_REG                    (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__COUNTER )
#define Dimming_COUNTER_PTR                    ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__COUNTER )
#define Dimming_COMP_CAP_REG                   (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__CC )
#define Dimming_COMP_CAP_PTR                   ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__CC )
#define Dimming_COMP_CAP_BUF_REG               (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__CC_BUFF )
#define Dimming_COMP_CAP_BUF_PTR               ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__CC_BUFF )
#define Dimming_PERIOD_REG                     (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__PERIOD )
#define Dimming_PERIOD_PTR                     ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__PERIOD )
#define Dimming_PERIOD_BUF_REG                 (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Dimming_PERIOD_BUF_PTR                 ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Dimming_TRIG_CONTROL0_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Dimming_TRIG_CONTROL0_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Dimming_TRIG_CONTROL1_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Dimming_TRIG_CONTROL1_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Dimming_TRIG_CONTROL2_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Dimming_TRIG_CONTROL2_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Dimming_INTERRUPT_REQ_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR )
#define Dimming_INTERRUPT_REQ_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR )
#define Dimming_INTERRUPT_SET_REG              (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_SET )
#define Dimming_INTERRUPT_SET_PTR              ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_SET )
#define Dimming_INTERRUPT_MASK_REG             (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_MASK )
#define Dimming_INTERRUPT_MASK_PTR             ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_MASK )
#define Dimming_INTERRUPT_MASKED_REG           (*(reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Dimming_INTERRUPT_MASKED_PTR           ( (reg32 *) Dimming_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Dimming_MASK                           ((uint32)Dimming_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Dimming_RELOAD_CC_SHIFT                (0u)
#define Dimming_RELOAD_PERIOD_SHIFT            (1u)
#define Dimming_PWM_SYNC_KILL_SHIFT            (2u)
#define Dimming_PWM_STOP_KILL_SHIFT            (3u)
#define Dimming_PRESCALER_SHIFT                (8u)
#define Dimming_UPDOWN_SHIFT                   (16u)
#define Dimming_ONESHOT_SHIFT                  (18u)
#define Dimming_QUAD_MODE_SHIFT                (20u)
#define Dimming_INV_OUT_SHIFT                  (20u)
#define Dimming_INV_COMPL_OUT_SHIFT            (21u)
#define Dimming_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Dimming_RELOAD_CC_MASK                 ((uint32)(Dimming_1BIT_MASK        <<  \
                                                                            Dimming_RELOAD_CC_SHIFT))
#define Dimming_RELOAD_PERIOD_MASK             ((uint32)(Dimming_1BIT_MASK        <<  \
                                                                            Dimming_RELOAD_PERIOD_SHIFT))
#define Dimming_PWM_SYNC_KILL_MASK             ((uint32)(Dimming_1BIT_MASK        <<  \
                                                                            Dimming_PWM_SYNC_KILL_SHIFT))
#define Dimming_PWM_STOP_KILL_MASK             ((uint32)(Dimming_1BIT_MASK        <<  \
                                                                            Dimming_PWM_STOP_KILL_SHIFT))
#define Dimming_PRESCALER_MASK                 ((uint32)(Dimming_8BIT_MASK        <<  \
                                                                            Dimming_PRESCALER_SHIFT))
#define Dimming_UPDOWN_MASK                    ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                            Dimming_UPDOWN_SHIFT))
#define Dimming_ONESHOT_MASK                   ((uint32)(Dimming_1BIT_MASK        <<  \
                                                                            Dimming_ONESHOT_SHIFT))
#define Dimming_QUAD_MODE_MASK                 ((uint32)(Dimming_3BIT_MASK        <<  \
                                                                            Dimming_QUAD_MODE_SHIFT))
#define Dimming_INV_OUT_MASK                   ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                            Dimming_INV_OUT_SHIFT))
#define Dimming_MODE_MASK                      ((uint32)(Dimming_3BIT_MASK        <<  \
                                                                            Dimming_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Dimming_CAPTURE_SHIFT                  (0u)
#define Dimming_COUNT_SHIFT                    (2u)
#define Dimming_RELOAD_SHIFT                   (4u)
#define Dimming_STOP_SHIFT                     (6u)
#define Dimming_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Dimming_CAPTURE_MASK                   ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                  Dimming_CAPTURE_SHIFT))
#define Dimming_COUNT_MASK                     ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                  Dimming_COUNT_SHIFT))
#define Dimming_RELOAD_MASK                    ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                  Dimming_RELOAD_SHIFT))
#define Dimming_STOP_MASK                      ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                  Dimming_STOP_SHIFT))
#define Dimming_START_MASK                     ((uint32)(Dimming_2BIT_MASK        <<  \
                                                                  Dimming_START_SHIFT))

/* MASK */
#define Dimming_1BIT_MASK                      ((uint32)0x01u)
#define Dimming_2BIT_MASK                      ((uint32)0x03u)
#define Dimming_3BIT_MASK                      ((uint32)0x07u)
#define Dimming_6BIT_MASK                      ((uint32)0x3Fu)
#define Dimming_8BIT_MASK                      ((uint32)0xFFu)
#define Dimming_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Dimming_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Dimming_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Dimming_QUAD_ENCODING_MODES     << Dimming_QUAD_MODE_SHIFT))       |\
         ((uint32)(Dimming_CONFIG                  << Dimming_MODE_SHIFT)))

#define Dimming_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Dimming_PWM_STOP_EVENT          << Dimming_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Dimming_PWM_OUT_INVERT          << Dimming_INV_OUT_SHIFT))         |\
         ((uint32)(Dimming_PWM_OUT_N_INVERT        << Dimming_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Dimming_PWM_MODE                << Dimming_MODE_SHIFT)))

#define Dimming_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Dimming_PWM_RUN_MODE         << Dimming_ONESHOT_SHIFT))
            
#define Dimming_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Dimming_PWM_ALIGN            << Dimming_UPDOWN_SHIFT))

#define Dimming_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Dimming_PWM_KILL_EVENT      << Dimming_PWM_SYNC_KILL_SHIFT))

#define Dimming_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Dimming_PWM_DEAD_TIME_CYCLE  << Dimming_PRESCALER_SHIFT))

#define Dimming_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Dimming_PWM_PRESCALER        << Dimming_PRESCALER_SHIFT))

#define Dimming_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Dimming_TC_PRESCALER            << Dimming_PRESCALER_SHIFT))       |\
         ((uint32)(Dimming_TC_COUNTER_MODE         << Dimming_UPDOWN_SHIFT))          |\
         ((uint32)(Dimming_TC_RUN_MODE             << Dimming_ONESHOT_SHIFT))         |\
         ((uint32)(Dimming_TC_COMP_CAP_MODE        << Dimming_MODE_SHIFT)))
        
#define Dimming_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Dimming_QUAD_PHIA_SIGNAL_MODE   << Dimming_COUNT_SHIFT))           |\
         ((uint32)(Dimming_QUAD_INDEX_SIGNAL_MODE  << Dimming_RELOAD_SHIFT))          |\
         ((uint32)(Dimming_QUAD_STOP_SIGNAL_MODE   << Dimming_STOP_SHIFT))            |\
         ((uint32)(Dimming_QUAD_PHIB_SIGNAL_MODE   << Dimming_START_SHIFT)))

#define Dimming_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Dimming_PWM_SWITCH_SIGNAL_MODE  << Dimming_CAPTURE_SHIFT))         |\
         ((uint32)(Dimming_PWM_COUNT_SIGNAL_MODE   << Dimming_COUNT_SHIFT))           |\
         ((uint32)(Dimming_PWM_RELOAD_SIGNAL_MODE  << Dimming_RELOAD_SHIFT))          |\
         ((uint32)(Dimming_PWM_STOP_SIGNAL_MODE    << Dimming_STOP_SHIFT))            |\
         ((uint32)(Dimming_PWM_START_SIGNAL_MODE   << Dimming_START_SHIFT)))

#define Dimming_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Dimming_TC_CAPTURE_SIGNAL_MODE  << Dimming_CAPTURE_SHIFT))         |\
         ((uint32)(Dimming_TC_COUNT_SIGNAL_MODE    << Dimming_COUNT_SHIFT))           |\
         ((uint32)(Dimming_TC_RELOAD_SIGNAL_MODE   << Dimming_RELOAD_SHIFT))          |\
         ((uint32)(Dimming_TC_STOP_SIGNAL_MODE     << Dimming_STOP_SHIFT))            |\
         ((uint32)(Dimming_TC_START_SIGNAL_MODE    << Dimming_START_SHIFT)))
        
#define Dimming_TIMER_UPDOWN_CNT_USED                                                          \
                ((Dimming__COUNT_UPDOWN0 == Dimming_TC_COUNTER_MODE)                  ||\
                 (Dimming__COUNT_UPDOWN1 == Dimming_TC_COUNTER_MODE))

#define Dimming_PWM_UPDOWN_CNT_USED                                                            \
                ((Dimming__CENTER == Dimming_PWM_ALIGN)                               ||\
                 (Dimming__ASYMMETRIC == Dimming_PWM_ALIGN))               
        
#define Dimming_PWM_PR_INIT_VALUE              (1u)
#define Dimming_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Dimming_H */

/* [] END OF FILE */
