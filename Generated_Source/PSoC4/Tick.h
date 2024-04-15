/*******************************************************************************
* File Name: Tick.h
* Version 2.0
*
* Description:
*  This file provides constants and parameter values for the Tick
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

#if !defined(CY_TCPWM_Tick_H)
#define CY_TCPWM_Tick_H


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
} Tick_BACKUP_STRUCT;


/*******************************************************************************
* Variables
*******************************************************************************/
extern uint8  Tick_initVar;


/***************************************
*   Conditional Compilation Parameters
****************************************/

#define Tick_CY_TCPWM_V2                    (CYIPBLOCK_m0s8tcpwm_VERSION == 2u)
#define Tick_CY_TCPWM_4000                  (CY_PSOC4_4000)

/* TCPWM Configuration */
#define Tick_CONFIG                         (1lu)

/* Quad Mode */
/* Parameters */
#define Tick_QUAD_ENCODING_MODES            (0lu)

/* Signal modes */
#define Tick_QUAD_INDEX_SIGNAL_MODE         (0lu)
#define Tick_QUAD_PHIA_SIGNAL_MODE          (3lu)
#define Tick_QUAD_PHIB_SIGNAL_MODE          (3lu)
#define Tick_QUAD_STOP_SIGNAL_MODE          (0lu)

/* Signal present */
#define Tick_QUAD_INDEX_SIGNAL_PRESENT      (0lu)
#define Tick_QUAD_STOP_SIGNAL_PRESENT       (0lu)

/* Interrupt Mask */
#define Tick_QUAD_INTERRUPT_MASK            (1lu)

/* Timer/Counter Mode */
/* Parameters */
#define Tick_TC_RUN_MODE                    (0lu)
#define Tick_TC_COUNTER_MODE                (0lu)
#define Tick_TC_COMP_CAP_MODE               (2lu)
#define Tick_TC_PRESCALER                   (0lu)

/* Signal modes */
#define Tick_TC_RELOAD_SIGNAL_MODE          (0lu)
#define Tick_TC_COUNT_SIGNAL_MODE           (3lu)
#define Tick_TC_START_SIGNAL_MODE           (0lu)
#define Tick_TC_STOP_SIGNAL_MODE            (0lu)
#define Tick_TC_CAPTURE_SIGNAL_MODE         (0lu)

/* Signal present */
#define Tick_TC_RELOAD_SIGNAL_PRESENT       (0lu)
#define Tick_TC_COUNT_SIGNAL_PRESENT        (0lu)
#define Tick_TC_START_SIGNAL_PRESENT        (0lu)
#define Tick_TC_STOP_SIGNAL_PRESENT         (0lu)
#define Tick_TC_CAPTURE_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Tick_TC_INTERRUPT_MASK              (1lu)

/* PWM Mode */
/* Parameters */
#define Tick_PWM_KILL_EVENT                 (0lu)
#define Tick_PWM_STOP_EVENT                 (0lu)
#define Tick_PWM_MODE                       (4lu)
#define Tick_PWM_OUT_N_INVERT               (0lu)
#define Tick_PWM_OUT_INVERT                 (0lu)
#define Tick_PWM_ALIGN                      (0lu)
#define Tick_PWM_RUN_MODE                   (0lu)
#define Tick_PWM_DEAD_TIME_CYCLE            (0lu)
#define Tick_PWM_PRESCALER                  (0lu)

/* Signal modes */
#define Tick_PWM_RELOAD_SIGNAL_MODE         (0lu)
#define Tick_PWM_COUNT_SIGNAL_MODE          (3lu)
#define Tick_PWM_START_SIGNAL_MODE          (0lu)
#define Tick_PWM_STOP_SIGNAL_MODE           (0lu)
#define Tick_PWM_SWITCH_SIGNAL_MODE         (0lu)

/* Signal present */
#define Tick_PWM_RELOAD_SIGNAL_PRESENT      (0lu)
#define Tick_PWM_COUNT_SIGNAL_PRESENT       (0lu)
#define Tick_PWM_START_SIGNAL_PRESENT       (0lu)
#define Tick_PWM_STOP_SIGNAL_PRESENT        (0lu)
#define Tick_PWM_SWITCH_SIGNAL_PRESENT      (0lu)

/* Interrupt Mask */
#define Tick_PWM_INTERRUPT_MASK             (1lu)


/***************************************
*    Initial Parameter Constants
***************************************/

/* Timer/Counter Mode */
#define Tick_TC_PERIOD_VALUE                (1250lu)
#define Tick_TC_COMPARE_VALUE               (65535lu)
#define Tick_TC_COMPARE_BUF_VALUE           (65535lu)
#define Tick_TC_COMPARE_SWAP                (0lu)

/* PWM Mode */
#define Tick_PWM_PERIOD_VALUE               (65535lu)
#define Tick_PWM_PERIOD_BUF_VALUE           (65535lu)
#define Tick_PWM_PERIOD_SWAP                (0lu)
#define Tick_PWM_COMPARE_VALUE              (65535lu)
#define Tick_PWM_COMPARE_BUF_VALUE          (65535lu)
#define Tick_PWM_COMPARE_SWAP               (0lu)


/***************************************
*    Enumerated Types and Parameters
***************************************/

#define Tick__LEFT 0
#define Tick__RIGHT 1
#define Tick__CENTER 2
#define Tick__ASYMMETRIC 3

#define Tick__X1 0
#define Tick__X2 1
#define Tick__X4 2

#define Tick__PWM 4
#define Tick__PWM_DT 5
#define Tick__PWM_PR 6

#define Tick__INVERSE 1
#define Tick__DIRECT 0

#define Tick__CAPTURE 2
#define Tick__COMPARE 0

#define Tick__TRIG_LEVEL 3
#define Tick__TRIG_RISING 0
#define Tick__TRIG_FALLING 1
#define Tick__TRIG_BOTH 2

#define Tick__INTR_MASK_TC 1
#define Tick__INTR_MASK_CC_MATCH 2
#define Tick__INTR_MASK_NONE 0
#define Tick__INTR_MASK_TC_CC 3

#define Tick__UNCONFIG 8
#define Tick__TIMER 1
#define Tick__QUAD 3
#define Tick__PWM_SEL 7

#define Tick__COUNT_UP 0
#define Tick__COUNT_DOWN 1
#define Tick__COUNT_UPDOWN0 2
#define Tick__COUNT_UPDOWN1 3


/* Prescaler */
#define Tick_PRESCALE_DIVBY1                ((uint32)(0u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY2                ((uint32)(1u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY4                ((uint32)(2u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY8                ((uint32)(3u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY16               ((uint32)(4u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY32               ((uint32)(5u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY64               ((uint32)(6u << Tick_PRESCALER_SHIFT))
#define Tick_PRESCALE_DIVBY128              ((uint32)(7u << Tick_PRESCALER_SHIFT))

/* TCPWM set modes */
#define Tick_MODE_TIMER_COMPARE             ((uint32)(Tick__COMPARE         <<  \
                                                                  Tick_MODE_SHIFT))
#define Tick_MODE_TIMER_CAPTURE             ((uint32)(Tick__CAPTURE         <<  \
                                                                  Tick_MODE_SHIFT))
#define Tick_MODE_QUAD                      ((uint32)(Tick__QUAD            <<  \
                                                                  Tick_MODE_SHIFT))
#define Tick_MODE_PWM                       ((uint32)(Tick__PWM             <<  \
                                                                  Tick_MODE_SHIFT))
#define Tick_MODE_PWM_DT                    ((uint32)(Tick__PWM_DT          <<  \
                                                                  Tick_MODE_SHIFT))
#define Tick_MODE_PWM_PR                    ((uint32)(Tick__PWM_PR          <<  \
                                                                  Tick_MODE_SHIFT))

/* Quad Modes */
#define Tick_MODE_X1                        ((uint32)(Tick__X1              <<  \
                                                                  Tick_QUAD_MODE_SHIFT))
#define Tick_MODE_X2                        ((uint32)(Tick__X2              <<  \
                                                                  Tick_QUAD_MODE_SHIFT))
#define Tick_MODE_X4                        ((uint32)(Tick__X4              <<  \
                                                                  Tick_QUAD_MODE_SHIFT))

/* Counter modes */
#define Tick_COUNT_UP                       ((uint32)(Tick__COUNT_UP        <<  \
                                                                  Tick_UPDOWN_SHIFT))
#define Tick_COUNT_DOWN                     ((uint32)(Tick__COUNT_DOWN      <<  \
                                                                  Tick_UPDOWN_SHIFT))
#define Tick_COUNT_UPDOWN0                  ((uint32)(Tick__COUNT_UPDOWN0   <<  \
                                                                  Tick_UPDOWN_SHIFT))
#define Tick_COUNT_UPDOWN1                  ((uint32)(Tick__COUNT_UPDOWN1   <<  \
                                                                  Tick_UPDOWN_SHIFT))

/* PWM output invert */
#define Tick_INVERT_LINE                    ((uint32)(Tick__INVERSE         <<  \
                                                                  Tick_INV_OUT_SHIFT))
#define Tick_INVERT_LINE_N                  ((uint32)(Tick__INVERSE         <<  \
                                                                  Tick_INV_COMPL_OUT_SHIFT))

/* Trigger modes */
#define Tick_TRIG_RISING                    ((uint32)Tick__TRIG_RISING)
#define Tick_TRIG_FALLING                   ((uint32)Tick__TRIG_FALLING)
#define Tick_TRIG_BOTH                      ((uint32)Tick__TRIG_BOTH)
#define Tick_TRIG_LEVEL                     ((uint32)Tick__TRIG_LEVEL)

/* Interrupt mask */
#define Tick_INTR_MASK_TC                   ((uint32)Tick__INTR_MASK_TC)
#define Tick_INTR_MASK_CC_MATCH             ((uint32)Tick__INTR_MASK_CC_MATCH)

/* PWM Output Controls */
#define Tick_CC_MATCH_SET                   (0x00u)
#define Tick_CC_MATCH_CLEAR                 (0x01u)
#define Tick_CC_MATCH_INVERT                (0x02u)
#define Tick_CC_MATCH_NO_CHANGE             (0x03u)
#define Tick_OVERLOW_SET                    (0x00u)
#define Tick_OVERLOW_CLEAR                  (0x04u)
#define Tick_OVERLOW_INVERT                 (0x08u)
#define Tick_OVERLOW_NO_CHANGE              (0x0Cu)
#define Tick_UNDERFLOW_SET                  (0x00u)
#define Tick_UNDERFLOW_CLEAR                (0x10u)
#define Tick_UNDERFLOW_INVERT               (0x20u)
#define Tick_UNDERFLOW_NO_CHANGE            (0x30u)

/* PWM Align */
#define Tick_PWM_MODE_LEFT                  (Tick_CC_MATCH_CLEAR        |   \
                                                         Tick_OVERLOW_SET           |   \
                                                         Tick_UNDERFLOW_NO_CHANGE)
#define Tick_PWM_MODE_RIGHT                 (Tick_CC_MATCH_SET          |   \
                                                         Tick_OVERLOW_NO_CHANGE     |   \
                                                         Tick_UNDERFLOW_CLEAR)
#define Tick_PWM_MODE_ASYM                  (Tick_CC_MATCH_INVERT       |   \
                                                         Tick_OVERLOW_SET           |   \
                                                         Tick_UNDERFLOW_CLEAR)

#if (Tick_CY_TCPWM_V2)
    #if(Tick_CY_TCPWM_4000)
        #define Tick_PWM_MODE_CENTER                (Tick_CC_MATCH_INVERT       |   \
                                                                 Tick_OVERLOW_NO_CHANGE     |   \
                                                                 Tick_UNDERFLOW_CLEAR)
    #else
        #define Tick_PWM_MODE_CENTER                (Tick_CC_MATCH_INVERT       |   \
                                                                 Tick_OVERLOW_SET           |   \
                                                                 Tick_UNDERFLOW_CLEAR)
    #endif /* (Tick_CY_TCPWM_4000) */
#else
    #define Tick_PWM_MODE_CENTER                (Tick_CC_MATCH_INVERT       |   \
                                                             Tick_OVERLOW_NO_CHANGE     |   \
                                                             Tick_UNDERFLOW_CLEAR)
#endif /* (Tick_CY_TCPWM_NEW) */

/* Command operations without condition */
#define Tick_CMD_CAPTURE                    (0u)
#define Tick_CMD_RELOAD                     (8u)
#define Tick_CMD_STOP                       (16u)
#define Tick_CMD_START                      (24u)

/* Status */
#define Tick_STATUS_DOWN                    (1u)
#define Tick_STATUS_RUNNING                 (2u)


/***************************************
*        Function Prototypes
****************************************/

void   Tick_Init(void);
void   Tick_Enable(void);
void   Tick_Start(void);
void   Tick_Stop(void);

void   Tick_SetMode(uint32 mode);
void   Tick_SetCounterMode(uint32 counterMode);
void   Tick_SetPWMMode(uint32 modeMask);
void   Tick_SetQDMode(uint32 qdMode);

void   Tick_SetPrescaler(uint32 prescaler);
void   Tick_TriggerCommand(uint32 mask, uint32 command);
void   Tick_SetOneShot(uint32 oneShotEnable);
uint32 Tick_ReadStatus(void);

void   Tick_SetPWMSyncKill(uint32 syncKillEnable);
void   Tick_SetPWMStopOnKill(uint32 stopOnKillEnable);
void   Tick_SetPWMDeadTime(uint32 deadTime);
void   Tick_SetPWMInvert(uint32 mask);

void   Tick_SetInterruptMode(uint32 interruptMask);
uint32 Tick_GetInterruptSourceMasked(void);
uint32 Tick_GetInterruptSource(void);
void   Tick_ClearInterrupt(uint32 interruptMask);
void   Tick_SetInterrupt(uint32 interruptMask);

void   Tick_WriteCounter(uint32 count);
uint32 Tick_ReadCounter(void);

uint32 Tick_ReadCapture(void);
uint32 Tick_ReadCaptureBuf(void);

void   Tick_WritePeriod(uint32 period);
uint32 Tick_ReadPeriod(void);
void   Tick_WritePeriodBuf(uint32 periodBuf);
uint32 Tick_ReadPeriodBuf(void);

void   Tick_WriteCompare(uint32 compare);
uint32 Tick_ReadCompare(void);
void   Tick_WriteCompareBuf(uint32 compareBuf);
uint32 Tick_ReadCompareBuf(void);

void   Tick_SetPeriodSwap(uint32 swapEnable);
void   Tick_SetCompareSwap(uint32 swapEnable);

void   Tick_SetCaptureMode(uint32 triggerMode);
void   Tick_SetReloadMode(uint32 triggerMode);
void   Tick_SetStartMode(uint32 triggerMode);
void   Tick_SetStopMode(uint32 triggerMode);
void   Tick_SetCountMode(uint32 triggerMode);

void   Tick_SaveConfig(void);
void   Tick_RestoreConfig(void);
void   Tick_Sleep(void);
void   Tick_Wakeup(void);


/***************************************
*             Registers
***************************************/

#define Tick_BLOCK_CONTROL_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Tick_BLOCK_CONTROL_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_CTRL )
#define Tick_COMMAND_REG                    (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Tick_COMMAND_PTR                    ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_CMD )
#define Tick_INTRRUPT_CAUSE_REG             (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Tick_INTRRUPT_CAUSE_PTR             ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TCPWM_INTR_CAUSE )
#define Tick_CONTROL_REG                    (*(reg32 *) Tick_cy_m0s8_tcpwm_1__CTRL )
#define Tick_CONTROL_PTR                    ( (reg32 *) Tick_cy_m0s8_tcpwm_1__CTRL )
#define Tick_STATUS_REG                     (*(reg32 *) Tick_cy_m0s8_tcpwm_1__STATUS )
#define Tick_STATUS_PTR                     ( (reg32 *) Tick_cy_m0s8_tcpwm_1__STATUS )
#define Tick_COUNTER_REG                    (*(reg32 *) Tick_cy_m0s8_tcpwm_1__COUNTER )
#define Tick_COUNTER_PTR                    ( (reg32 *) Tick_cy_m0s8_tcpwm_1__COUNTER )
#define Tick_COMP_CAP_REG                   (*(reg32 *) Tick_cy_m0s8_tcpwm_1__CC )
#define Tick_COMP_CAP_PTR                   ( (reg32 *) Tick_cy_m0s8_tcpwm_1__CC )
#define Tick_COMP_CAP_BUF_REG               (*(reg32 *) Tick_cy_m0s8_tcpwm_1__CC_BUFF )
#define Tick_COMP_CAP_BUF_PTR               ( (reg32 *) Tick_cy_m0s8_tcpwm_1__CC_BUFF )
#define Tick_PERIOD_REG                     (*(reg32 *) Tick_cy_m0s8_tcpwm_1__PERIOD )
#define Tick_PERIOD_PTR                     ( (reg32 *) Tick_cy_m0s8_tcpwm_1__PERIOD )
#define Tick_PERIOD_BUF_REG                 (*(reg32 *) Tick_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Tick_PERIOD_BUF_PTR                 ( (reg32 *) Tick_cy_m0s8_tcpwm_1__PERIOD_BUFF )
#define Tick_TRIG_CONTROL0_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Tick_TRIG_CONTROL0_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL0 )
#define Tick_TRIG_CONTROL1_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Tick_TRIG_CONTROL1_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL1 )
#define Tick_TRIG_CONTROL2_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Tick_TRIG_CONTROL2_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__TR_CTRL2 )
#define Tick_INTERRUPT_REQ_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__INTR )
#define Tick_INTERRUPT_REQ_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__INTR )
#define Tick_INTERRUPT_SET_REG              (*(reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_SET )
#define Tick_INTERRUPT_SET_PTR              ( (reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_SET )
#define Tick_INTERRUPT_MASK_REG             (*(reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_MASK )
#define Tick_INTERRUPT_MASK_PTR             ( (reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_MASK )
#define Tick_INTERRUPT_MASKED_REG           (*(reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_MASKED )
#define Tick_INTERRUPT_MASKED_PTR           ( (reg32 *) Tick_cy_m0s8_tcpwm_1__INTR_MASKED )


/***************************************
*       Registers Constants
***************************************/

/* Mask */
#define Tick_MASK                           ((uint32)Tick_cy_m0s8_tcpwm_1__TCPWM_CTRL_MASK)

/* Shift constants for control register */
#define Tick_RELOAD_CC_SHIFT                (0u)
#define Tick_RELOAD_PERIOD_SHIFT            (1u)
#define Tick_PWM_SYNC_KILL_SHIFT            (2u)
#define Tick_PWM_STOP_KILL_SHIFT            (3u)
#define Tick_PRESCALER_SHIFT                (8u)
#define Tick_UPDOWN_SHIFT                   (16u)
#define Tick_ONESHOT_SHIFT                  (18u)
#define Tick_QUAD_MODE_SHIFT                (20u)
#define Tick_INV_OUT_SHIFT                  (20u)
#define Tick_INV_COMPL_OUT_SHIFT            (21u)
#define Tick_MODE_SHIFT                     (24u)

/* Mask constants for control register */
#define Tick_RELOAD_CC_MASK                 ((uint32)(Tick_1BIT_MASK        <<  \
                                                                            Tick_RELOAD_CC_SHIFT))
#define Tick_RELOAD_PERIOD_MASK             ((uint32)(Tick_1BIT_MASK        <<  \
                                                                            Tick_RELOAD_PERIOD_SHIFT))
#define Tick_PWM_SYNC_KILL_MASK             ((uint32)(Tick_1BIT_MASK        <<  \
                                                                            Tick_PWM_SYNC_KILL_SHIFT))
#define Tick_PWM_STOP_KILL_MASK             ((uint32)(Tick_1BIT_MASK        <<  \
                                                                            Tick_PWM_STOP_KILL_SHIFT))
#define Tick_PRESCALER_MASK                 ((uint32)(Tick_8BIT_MASK        <<  \
                                                                            Tick_PRESCALER_SHIFT))
#define Tick_UPDOWN_MASK                    ((uint32)(Tick_2BIT_MASK        <<  \
                                                                            Tick_UPDOWN_SHIFT))
#define Tick_ONESHOT_MASK                   ((uint32)(Tick_1BIT_MASK        <<  \
                                                                            Tick_ONESHOT_SHIFT))
#define Tick_QUAD_MODE_MASK                 ((uint32)(Tick_3BIT_MASK        <<  \
                                                                            Tick_QUAD_MODE_SHIFT))
#define Tick_INV_OUT_MASK                   ((uint32)(Tick_2BIT_MASK        <<  \
                                                                            Tick_INV_OUT_SHIFT))
#define Tick_MODE_MASK                      ((uint32)(Tick_3BIT_MASK        <<  \
                                                                            Tick_MODE_SHIFT))

/* Shift constants for trigger control register 1 */
#define Tick_CAPTURE_SHIFT                  (0u)
#define Tick_COUNT_SHIFT                    (2u)
#define Tick_RELOAD_SHIFT                   (4u)
#define Tick_STOP_SHIFT                     (6u)
#define Tick_START_SHIFT                    (8u)

/* Mask constants for trigger control register 1 */
#define Tick_CAPTURE_MASK                   ((uint32)(Tick_2BIT_MASK        <<  \
                                                                  Tick_CAPTURE_SHIFT))
#define Tick_COUNT_MASK                     ((uint32)(Tick_2BIT_MASK        <<  \
                                                                  Tick_COUNT_SHIFT))
#define Tick_RELOAD_MASK                    ((uint32)(Tick_2BIT_MASK        <<  \
                                                                  Tick_RELOAD_SHIFT))
#define Tick_STOP_MASK                      ((uint32)(Tick_2BIT_MASK        <<  \
                                                                  Tick_STOP_SHIFT))
#define Tick_START_MASK                     ((uint32)(Tick_2BIT_MASK        <<  \
                                                                  Tick_START_SHIFT))

/* MASK */
#define Tick_1BIT_MASK                      ((uint32)0x01u)
#define Tick_2BIT_MASK                      ((uint32)0x03u)
#define Tick_3BIT_MASK                      ((uint32)0x07u)
#define Tick_6BIT_MASK                      ((uint32)0x3Fu)
#define Tick_8BIT_MASK                      ((uint32)0xFFu)
#define Tick_16BIT_MASK                     ((uint32)0xFFFFu)

/* Shift constant for status register */
#define Tick_RUNNING_STATUS_SHIFT           (30u)


/***************************************
*    Initial Constants
***************************************/

#define Tick_CTRL_QUAD_BASE_CONFIG                                                          \
        (((uint32)(Tick_QUAD_ENCODING_MODES     << Tick_QUAD_MODE_SHIFT))       |\
         ((uint32)(Tick_CONFIG                  << Tick_MODE_SHIFT)))

#define Tick_CTRL_PWM_BASE_CONFIG                                                           \
        (((uint32)(Tick_PWM_STOP_EVENT          << Tick_PWM_STOP_KILL_SHIFT))   |\
         ((uint32)(Tick_PWM_OUT_INVERT          << Tick_INV_OUT_SHIFT))         |\
         ((uint32)(Tick_PWM_OUT_N_INVERT        << Tick_INV_COMPL_OUT_SHIFT))   |\
         ((uint32)(Tick_PWM_MODE                << Tick_MODE_SHIFT)))

#define Tick_CTRL_PWM_RUN_MODE                                                              \
            ((uint32)(Tick_PWM_RUN_MODE         << Tick_ONESHOT_SHIFT))
            
#define Tick_CTRL_PWM_ALIGN                                                                 \
            ((uint32)(Tick_PWM_ALIGN            << Tick_UPDOWN_SHIFT))

#define Tick_CTRL_PWM_KILL_EVENT                                                            \
             ((uint32)(Tick_PWM_KILL_EVENT      << Tick_PWM_SYNC_KILL_SHIFT))

#define Tick_CTRL_PWM_DEAD_TIME_CYCLE                                                       \
            ((uint32)(Tick_PWM_DEAD_TIME_CYCLE  << Tick_PRESCALER_SHIFT))

#define Tick_CTRL_PWM_PRESCALER                                                             \
            ((uint32)(Tick_PWM_PRESCALER        << Tick_PRESCALER_SHIFT))

#define Tick_CTRL_TIMER_BASE_CONFIG                                                         \
        (((uint32)(Tick_TC_PRESCALER            << Tick_PRESCALER_SHIFT))       |\
         ((uint32)(Tick_TC_COUNTER_MODE         << Tick_UPDOWN_SHIFT))          |\
         ((uint32)(Tick_TC_RUN_MODE             << Tick_ONESHOT_SHIFT))         |\
         ((uint32)(Tick_TC_COMP_CAP_MODE        << Tick_MODE_SHIFT)))
        
#define Tick_QUAD_SIGNALS_MODES                                                             \
        (((uint32)(Tick_QUAD_PHIA_SIGNAL_MODE   << Tick_COUNT_SHIFT))           |\
         ((uint32)(Tick_QUAD_INDEX_SIGNAL_MODE  << Tick_RELOAD_SHIFT))          |\
         ((uint32)(Tick_QUAD_STOP_SIGNAL_MODE   << Tick_STOP_SHIFT))            |\
         ((uint32)(Tick_QUAD_PHIB_SIGNAL_MODE   << Tick_START_SHIFT)))

#define Tick_PWM_SIGNALS_MODES                                                              \
        (((uint32)(Tick_PWM_SWITCH_SIGNAL_MODE  << Tick_CAPTURE_SHIFT))         |\
         ((uint32)(Tick_PWM_COUNT_SIGNAL_MODE   << Tick_COUNT_SHIFT))           |\
         ((uint32)(Tick_PWM_RELOAD_SIGNAL_MODE  << Tick_RELOAD_SHIFT))          |\
         ((uint32)(Tick_PWM_STOP_SIGNAL_MODE    << Tick_STOP_SHIFT))            |\
         ((uint32)(Tick_PWM_START_SIGNAL_MODE   << Tick_START_SHIFT)))

#define Tick_TIMER_SIGNALS_MODES                                                            \
        (((uint32)(Tick_TC_CAPTURE_SIGNAL_MODE  << Tick_CAPTURE_SHIFT))         |\
         ((uint32)(Tick_TC_COUNT_SIGNAL_MODE    << Tick_COUNT_SHIFT))           |\
         ((uint32)(Tick_TC_RELOAD_SIGNAL_MODE   << Tick_RELOAD_SHIFT))          |\
         ((uint32)(Tick_TC_STOP_SIGNAL_MODE     << Tick_STOP_SHIFT))            |\
         ((uint32)(Tick_TC_START_SIGNAL_MODE    << Tick_START_SHIFT)))
        
#define Tick_TIMER_UPDOWN_CNT_USED                                                          \
                ((Tick__COUNT_UPDOWN0 == Tick_TC_COUNTER_MODE)                  ||\
                 (Tick__COUNT_UPDOWN1 == Tick_TC_COUNTER_MODE))

#define Tick_PWM_UPDOWN_CNT_USED                                                            \
                ((Tick__CENTER == Tick_PWM_ALIGN)                               ||\
                 (Tick__ASYMMETRIC == Tick_PWM_ALIGN))               
        
#define Tick_PWM_PR_INIT_VALUE              (1u)
#define Tick_QUAD_PERIOD_INIT_VALUE         (0x8000u)



#endif /* End CY_TCPWM_Tick_H */

/* [] END OF FILE */
