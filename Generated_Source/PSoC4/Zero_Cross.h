/*******************************************************************************
* File Name: Zero_Cross.h
* Version 1.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Analog Comparator User Module.
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

#if !defined(CY_COMPARATOR_Zero_Cross_H)
#define CY_COMPARATOR_Zero_Cross_H

#include "cytypes.h"
#include "CyLib.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Zero_Cross_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void    Zero_Cross_Init(void);
void    Zero_Cross_Enable(void);
void    Zero_Cross_Start(void);
void    Zero_Cross_Stop(void);
void    Zero_Cross_SetSpeed(uint32 speed);
uint32  Zero_Cross_ZeroCal(void);
void    Zero_Cross_LoadTrim(uint32 trimVal);
void    Zero_Cross_Sleep(void);
void    Zero_Cross_Wakeup(void);
void    Zero_Cross_SaveConfig(void);
void    Zero_Cross_RestoreConfig(void);
uint32  Zero_Cross_GetCompare(void);
uint32  Zero_Cross_GetInterruptSource(void);
void    Zero_Cross_ClearInterrupt(uint32 interruptMask);
void    Zero_Cross_SetInterrupt(uint32 interruptMask);
void    Zero_Cross_SetInterruptMask(uint32 interruptMask);
uint32  Zero_Cross_GetInterruptMask(void);
uint32  Zero_Cross_GetInterruptSourceMasked(void);
void    Zero_Cross_SetInterruptMode(uint32 mode);
void    Zero_Cross_DisableInterruptOutput(void);

#define Zero_Cross_EnableInterruptOutput(void)     Zero_Cross_SetInterruptMask(Zero_Cross_GetInterruptMask() | Zero_Cross_INTR_MASK)
#define Zero_Cross_GetInterruptOutputStatus(void)  ((0u == (Zero_Cross_GetInterruptSourceMasked() & Zero_Cross_INTR_MASKED)) ? 0u : 1u)
#define Zero_Cross_ClearInterruptOutput(void)      Zero_Cross_ClearInterrupt(Zero_Cross_INTR)
#define Zero_Cross_SetInterruptOutput(void)        Zero_Cross_SetInterrupt(Zero_Cross_INTR_MASK)

/**************************************
*           API Constants
**************************************/

/* Power constants for SetSpeed() function */
#define Zero_Cross_SLOW_SPEED     (0x01u)
#define Zero_Cross_MED_SPEED      (0x02u)
#define Zero_Cross_HIGH_SPEED     (0x03u)

/* Trim defines for ZeroCal() function */
#define Zero_Cross_COMP_TRIM_SIGN_SHIFT   (5u)
#define Zero_Cross_COMP_TRIM_MAX_VALUE    (32u)
#define Zero_Cross_COMP_CALIBRATION_DELAY (10u)

/* Constants for Zero_Cross_SetInterruptMode(), mode parameter */
#define Zero_Cross_INTR_DISABLE       (0x00u)
#define Zero_Cross_INTR_RISING        (0x01u)
#define Zero_Cross_INTR_FALLING       (0x02u)
#define Zero_Cross_INTR_BOTH          (0x03u)

/* Constants for Zero_Cross_GetInterruptSource() and 
* Zero_Cross_ClearInterrupt(), interruptMask parameter 
*/
#define Zero_Cross_INTR_SHIFT         (Zero_Cross_cy_psoc4_abuf__INTR_SHIFT)
#define Zero_Cross_INTR               ((uint32)0x01u << Zero_Cross_INTR_SHIFT)

/* Constants for Zero_Cross_SetInterrupt(), interruptMask parameter */
#define Zero_Cross_INTR_SET_SHIFT     (Zero_Cross_cy_psoc4_abuf__INTR_SET_SHIFT)
#define Zero_Cross_INTR_SET           ((uint32)0x01u << Zero_Cross_INTR_SHIFT)

/* Constants for Zero_Cross_GetInterruptMask() and 
* Zero_Cross_SetInterruptMask(), interruptMask parameter 
*/
#define Zero_Cross_INTR_MASK_SHIFT    (Zero_Cross_cy_psoc4_abuf__INTR_MASK_SHIFT)
#define Zero_Cross_INTR_MASK          ((uint32)0x01u << Zero_Cross_INTR_MASK_SHIFT)

/* Constants for Zero_Cross_GetInterruptSourceMasked() */ 
#define Zero_Cross_INTR_MASKED_SHIFT  (Zero_Cross_cy_psoc4_abuf__INTR_MASKED_SHIFT)
#define Zero_Cross_INTR_MASKED        ((uint32)0x01u << Zero_Cross_INTR_MASKED_SHIFT)


/***************************************
*   Initial Parameter Constants
****************************************/

#define Zero_Cross_HYSTERESIS         (1u)
#define Zero_Cross_POWER              (1u)
#define Zero_Cross_DEEPSLEEP_SUPPORT  (0u)
#define Zero_Cross_INTERRUPT_EN       (1u)
#define Zero_Cross_INTERRUPT          (1u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  Zero_Cross_initVar;


/**************************************
*             Registers
**************************************/

#define Zero_Cross_CTB_CTRL_REG               (* (reg32 *) Zero_Cross_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define Zero_Cross_CTB_CTRL_PTR               (  (reg32 *) Zero_Cross_cy_psoc4_abuf__CTBM_CTB_CTRL)

#define Zero_Cross_OA_RES_CTRL_REG            (* (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_RES_CTRL)
#define Zero_Cross_OA_RES_CTRL_PTR            (  (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_RES_CTRL)

#define Zero_Cross_OA_COMP_STAT_REG           (* (reg32 *) Zero_Cross_cy_psoc4_abuf__COMP_STAT)
#define Zero_Cross_OA_COMP_STAT_PTR           (  (reg32 *) Zero_Cross_cy_psoc4_abuf__COMP_STAT)

#define Zero_Cross_OA_OFFSET_TRIM_REG         (* (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_OFFSET_TRIM)
#define Zero_Cross_OA_OFFSET_TRIM_PTR         (  (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_OFFSET_TRIM)

#define Zero_Cross_OA_SLOPE_OFFSET_TRIM_REG   (* (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)
#define Zero_Cross_OA_SLOPE_OFFSET_TRIM_PTR   (  (reg32 *) Zero_Cross_cy_psoc4_abuf__OA_SLOPE_OFFSET_TRIM)

#define Zero_Cross_OA_COMP_SHIFT              (Zero_Cross_cy_psoc4_abuf__COMP_STAT_SHIFT)

#define Zero_Cross_INTR_REG       (*(reg32 *)Zero_Cross_cy_psoc4_abuf__INTR)
#define Zero_Cross_INTR_PTR       ( (reg32 *)Zero_Cross_cy_psoc4_abuf__INTR)

#define Zero_Cross_INTR_SET_REG   (*(reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_SET)
#define Zero_Cross_INTR_SET_PTR   ( (reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_SET)

#define Zero_Cross_INTR_MASK_REG    (*(reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_MASK) 
#define Zero_Cross_INTR_MASK_PTR    ( (reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_MASK) 

#define Zero_Cross_INTR_MASKED_REG  (*(reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_MASKED) 
#define Zero_Cross_INTR_MASKED_PTR  ( (reg32 *)Zero_Cross_cy_psoc4_abuf__INTR_MASKED)

/***************************************
*        Registers Constants
***************************************/

/* Zero_Cross_CTB_CTRL_REG */
#define Zero_Cross_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define Zero_Cross_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */

#define Zero_Cross_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << Zero_Cross_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define Zero_Cross_CTB_CTRL_ENABLED               ((uint32) 0x01u << Zero_Cross_CTB_CTRL_ENABLED_SHIFT)

/* Zero_Cross_OA_RES_CTRL_REG */
#define Zero_Cross_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define Zero_Cross_OA_COMP_EN_SHIFT           (4u)    /* [4]      Comparator enable */
#define Zero_Cross_OA_HYST_EN_SHIFT           (5u)    /* [5]      Hysteresis enable (10mV) */
#define Zero_Cross_OA_BYPASS_DSI_SYNC_SHIFT   (6u)    /* [6]      Bypass comparator output synchronization for DSI (trigger) output */
#define Zero_Cross_OA_COMPINT_SHIFT           (8u)    /* [9:8]    Sets Interrupt mode */
#define Zero_Cross_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */

#define Zero_Cross_OA_PWR_MODE                ((uint32) 0x02u << Zero_Cross_OA_PWR_MODE_SHIFT)
#define Zero_Cross_OA_PWR_MODE_MASK           ((uint32) 0x03u << Zero_Cross_OA_PWR_MODE_SHIFT)
#define Zero_Cross_OA_COMP_EN                 ((uint32) 0x01u << Zero_Cross_OA_COMP_EN_SHIFT)
#define Zero_Cross_OA_HYST_EN                 ((uint32) 0x01u << Zero_Cross_OA_HYST_EN_SHIFT)
#define Zero_Cross_OA_BYPASS_DSI_SYNC         ((uint32) 0x01u << Zero_Cross_OA_BYPASS_DSI_SYNC_SHIFT)
#define Zero_Cross_OA_COMPINT_MASK            ((uint32) 0x03u << Zero_Cross_OA_COMPINT_SHIFT)
#define Zero_Cross_OA_PUMP_EN                 ((uint32) 0x01u << Zero_Cross_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define Zero_Cross_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (Zero_Cross_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define Zero_Cross_GET_OA_HYST_EN(hyst)           ((0u != (hyst)) ? (Zero_Cross_OA_HYST_EN) : (0u))
#define Zero_Cross_GET_OA_PWR_MODE(mode)          ((mode) & Zero_Cross_OA_PWR_MODE_MASK)
#define Zero_Cross_CHECK_PWR_MODE_OFF             (0u != (Zero_Cross_OA_RES_CTRL_REG & \
                                                                Zero_Cross_OA_PWR_MODE_MASK))
#define Zero_Cross_GET_OA_COMPINT(intType)        ((uint32) ((((uint32)(intType) << Zero_Cross_OA_COMPINT_SHIFT)) & \
                                                        Zero_Cross_OA_COMPINT_MASK))

#define Zero_Cross_GET_INTR_MASK(mask)            ((0u != (mask)) ? (Zero_Cross_INTR_MASK) : (0u))

/* Returns true if component available in Deep Sleep power mode*/ 
#define Zero_Cross_CHECK_DEEPSLEEP_SUPPORT        (0u != Zero_Cross_DEEPSLEEP_SUPPORT) 

#define Zero_Cross_DEFAULT_CTB_CTRL (Zero_Cross_GET_DEEPSLEEP_ON(Zero_Cross_DEEPSLEEP_SUPPORT) | \
                                           Zero_Cross_CTB_CTRL_ENABLED)

#define Zero_Cross_DEFAULT_OA_RES_CTRL (Zero_Cross_OA_COMP_EN | \
                                              Zero_Cross_GET_OA_HYST_EN(Zero_Cross_HYSTERESIS)  | \
                                              Zero_Cross_GET_OA_COMPINT(Zero_Cross_INTERRUPT) |\
                                              Zero_Cross_OA_BYPASS_DSI_SYNC)

#define Zero_Cross_INTR_MASK_REG_DEFAULT  (Zero_Cross_GET_INTR_MASK(Zero_Cross_INTERRUPT_EN))


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

/* Power constants for SetSpeed() function */
#define Zero_Cross_SLOWSPEED      (Zero_Cross_SLOW_SPEED)
#define Zero_Cross_MEDSPEED       (Zero_Cross_MED_SPEED)
#define Zero_Cross_HIGHSPEED      (Zero_Cross_HIGH_SPEED)

#define Zero_Cross_OA_CTRL_REG        (Zero_Cross_OA_RES_CTRL_REG)
#define Zero_Cross_OA_COMPSTAT_REG    (Zero_Cross_OA_COMP_STAT_REG)
#define Zero_Cross_OA_COMPSHIFT       (Zero_Cross_OA_COMP_SHIFT)

#define Zero_Cross_OA_CTB_EN_SHIFT    (Zero_Cross_CTB_CTRL_ENABLED_SHIFT)
#define Zero_Cross_OA_PWR_MODE_HIGH   (Zero_Cross_HIGH_SPEED) 
#define Zero_Cross_OA_BYPASS_SHIFT    (Zero_Cross_OA_BYPASS_DSI_SYNC_SHIFT)

#endif /*  CY_COMPARATOR_Zero_Cross_H */


/* [] END OF FILE */
