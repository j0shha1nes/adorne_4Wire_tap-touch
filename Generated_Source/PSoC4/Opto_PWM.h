/*******************************************************************************
* File Name: Opto_PWM.h
* Version 1.10
*
* Description:
*  This file contains the function prototypes and constants used in
*  the Opamp (Analog Buffer) Component.
*
*
********************************************************************************
* Copyright 2013-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/


#if !defined(CY_OPAMP_Opto_PWM_H)
#define CY_OPAMP_Opto_PWM_H

#include "cytypes.h"
#include "cyfitter.h"


/***************************************
*       Type Definitions
***************************************/

/* Structure to save state before go to sleep */
typedef struct
{
    uint8  enableState;
} Opto_PWM_BACKUP_STRUCT;


/**************************************
*        Function Prototypes
**************************************/
void Opto_PWM_Init(void);
void Opto_PWM_Enable(void);
void Opto_PWM_Start(void);
void Opto_PWM_Stop(void);
void Opto_PWM_SetPower(uint32 power);
void Opto_PWM_PumpControl(uint32 onOff);
void Opto_PWM_Sleep(void);
void Opto_PWM_Wakeup(void);
void Opto_PWM_SaveConfig(void);
void Opto_PWM_RestoreConfig(void);


/**************************************
*           API Constants
**************************************/

/* Parameters for SetPower() function */
#define Opto_PWM_LOW_POWER      (1u)
#define Opto_PWM_MED_POWER      (2u)
#define Opto_PWM_HIGH_POWER     (3u)


/* Parameters for PumpControl() function */
#define Opto_PWM_PUMP_ON        (1u)
#define Opto_PWM_PUMP_OFF       (0u)


/***************************************
*   Initial Parameter Constants
****************************************/

#define Opto_PWM_OUTPUT_CURRENT         (1u)
#define Opto_PWM_POWER                  (1u)
#define Opto_PWM_MODE                   (0u)
#define Opto_PWM_OA_COMP_TRIM_VALUE     (3u)
#define Opto_PWM_DEEPSLEEP_SUPPORT      (0u)


/***************************************
*    Variables with External Linkage
***************************************/

extern uint8  Opto_PWM_initVar;


/**************************************
*             Registers
**************************************/
#define Opto_PWM_CTB_CTRL_REG       (*(reg32 *) Opto_PWM_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define Opto_PWM_CTB_CTRL_PTR       ( (reg32 *) Opto_PWM_cy_psoc4_abuf__CTBM_CTB_CTRL)
#define Opto_PWM_OA_RES_CTRL_REG    (*(reg32 *) Opto_PWM_cy_psoc4_abuf__OA_RES_CTRL)
#define Opto_PWM_OA_RES_CTRL_PTR    ( (reg32 *) Opto_PWM_cy_psoc4_abuf__OA_RES_CTRL)
#define Opto_PWM_OA_COMP_TRIM_REG   (*(reg32 *) Opto_PWM_cy_psoc4_abuf__OA_COMP_TRIM)
#define Opto_PWM_OA_COMP_TRIM_PTR   ( (reg32 *) Opto_PWM_cy_psoc4_abuf__OA_COMP_TRIM)


/***************************************
*        Registers Constants
***************************************/

/* Opto_PWM_CTB_CTRL_REG */
#define Opto_PWM_CTB_CTRL_DEEPSLEEP_ON_SHIFT    (30u)   /* [30] Selects behavior CTB IP in the DeepSleep power mode */
#define Opto_PWM_CTB_CTRL_ENABLED_SHIFT         (31u)   /* [31] Enable of the CTB IP */


#define Opto_PWM_CTB_CTRL_DEEPSLEEP_ON          ((uint32) 0x01u << Opto_PWM_CTB_CTRL_DEEPSLEEP_ON_SHIFT)
#define Opto_PWM_CTB_CTRL_ENABLED               ((uint32) 0x01u << Opto_PWM_CTB_CTRL_ENABLED_SHIFT)


/* Opto_PWM_OA_RES_CTRL_REG */
#define Opto_PWM_OA_PWR_MODE_SHIFT          (0u)    /* [1:0]    Power level */
#define Opto_PWM_OA_DRIVE_STR_SEL_SHIFT     (2u)    /* [2]      Opamp output strenght select: 0 - 1x, 1 - 10x */
#define Opto_PWM_OA_COMP_EN_SHIFT           (4u)    /* [4]      CTB IP mode: 0 - Opamp, 1 - Comparator  */
#define Opto_PWM_OA_PUMP_EN_SHIFT           (11u)   /* [11]     Pump enable */


#define Opto_PWM_OA_PWR_MODE                ((uint32) 0x02u << Opto_PWM_OA_PWR_MODE_SHIFT)
#define Opto_PWM_OA_PWR_MODE_MASK           ((uint32) 0x03u << Opto_PWM_OA_PWR_MODE_SHIFT)
#define Opto_PWM_OA_DRIVE_STR_SEL_1X        ((uint32) 0x00u << Opto_PWM_OA_DRIVE_STR_SEL_SHIFT)
#define Opto_PWM_OA_DRIVE_STR_SEL_10X       ((uint32) 0x01u << Opto_PWM_OA_DRIVE_STR_SEL_SHIFT)
#define Opto_PWM_OA_DRIVE_STR_SEL_MASK      ((uint32) 0x01u << Opto_PWM_OA_DRIVE_STR_SEL_SHIFT)
#define Opto_PWM_OA_COMP_EN                 ((uint32) 0x00u << Opto_PWM_OA_COMP_EN_SHIFT)
#define Opto_PWM_OA_PUMP_EN                 ((uint32) 0x01u << Opto_PWM_OA_PUMP_EN_SHIFT)


/***************************************
*       Init Macros Definitions
***************************************/

#define Opto_PWM_GET_DEEPSLEEP_ON(deepSleep)    ((0u != (deepSleep)) ? (Opto_PWM_CTB_CTRL_DEEPSLEEP_ON) : (0u))
#define Opto_PWM_GET_OA_DRIVE_STR(current)      ((0u != (current)) ? (Opto_PWM_OA_DRIVE_STR_SEL_10X) : \
                                                                             (Opto_PWM_OA_DRIVE_STR_SEL_1X))
#define Opto_PWM_GET_OA_PWR_MODE(mode)          ((mode) & Opto_PWM_OA_PWR_MODE_MASK)
#define Opto_PWM_CHECK_PWR_MODE_OFF             (0u != (Opto_PWM_OA_RES_CTRL_REG & \
                                                                Opto_PWM_OA_PWR_MODE_MASK))

/* Returns true if component available in Deep Sleep power mode*/ 
#define Opto_PWM_CHECK_DEEPSLEEP_SUPPORT        (0u != Opto_PWM_DEEPSLEEP_SUPPORT) 

#define Opto_PWM_DEFAULT_CTB_CTRL (Opto_PWM_GET_DEEPSLEEP_ON(Opto_PWM_DEEPSLEEP_SUPPORT) | \
                                           Opto_PWM_CTB_CTRL_ENABLED)

#define Opto_PWM_DEFAULT_OA_RES_CTRL (Opto_PWM_OA_COMP_EN | \
                                              Opto_PWM_GET_OA_DRIVE_STR(Opto_PWM_OUTPUT_CURRENT))

#define Opto_PWM_DEFAULT_OA_COMP_TRIM_REG (Opto_PWM_OA_COMP_TRIM_VALUE)


/***************************************
* The following code is DEPRECATED and 
* should not be used in new projects.
***************************************/

#define Opto_PWM_LOWPOWER                   (Opto_PWM_LOW_POWER)
#define Opto_PWM_MEDPOWER                   (Opto_PWM_MED_POWER)
#define Opto_PWM_HIGHPOWER                  (Opto_PWM_HIGH_POWER)

/* PUMP ON/OFF defines */
#define Opto_PWM_PUMPON                     (Opto_PWM_PUMP_ON)
#define Opto_PWM_PUMPOFF                    (Opto_PWM_PUMP_OFF)

#define Opto_PWM_OA_CTRL                    (Opto_PWM_CTB_CTRL_REG)
#define Opto_PWM_OA_RES_CTRL                (Opto_PWM_OA_RES_CTRL_REG)

/* Bit Field  OA_CTRL */
#define Opto_PWM_OA_CTB_EN_SHIFT            (Opto_PWM_CTB_CTRL_ENABLED_SHIFT)
#define Opto_PWM_OA_PUMP_CTRL_SHIFT         (Opto_PWM_OA_PUMP_EN_SHIFT)
#define Opto_PWM_OA_PUMP_EN_MASK            (0x800u)
#define Opto_PWM_PUMP_PROTECT_MASK          (1u)


#endif    /* CY_OPAMP_Opto_PWM_H */


/* [] END OF FILE */
