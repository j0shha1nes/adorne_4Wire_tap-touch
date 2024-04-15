/*******************************************************************************
* File Name: ZC_NInv.h  
* Version 2.10
*
* Description:
*  This file containts Control Register function prototypes and register defines
*
* Note:
*
********************************************************************************
* Copyright 2008-2014, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/

#if !defined(CY_PINS_ZC_NInv_H) /* Pins ZC_NInv_H */
#define CY_PINS_ZC_NInv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ZC_NInv_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ZC_NInv_Write(uint8 value) ;
void    ZC_NInv_SetDriveMode(uint8 mode) ;
uint8   ZC_NInv_ReadDataReg(void) ;
uint8   ZC_NInv_Read(void) ;
uint8   ZC_NInv_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ZC_NInv_DRIVE_MODE_BITS        (3)
#define ZC_NInv_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ZC_NInv_DRIVE_MODE_BITS))

#define ZC_NInv_DM_ALG_HIZ         (0x00u)
#define ZC_NInv_DM_DIG_HIZ         (0x01u)
#define ZC_NInv_DM_RES_UP          (0x02u)
#define ZC_NInv_DM_RES_DWN         (0x03u)
#define ZC_NInv_DM_OD_LO           (0x04u)
#define ZC_NInv_DM_OD_HI           (0x05u)
#define ZC_NInv_DM_STRONG          (0x06u)
#define ZC_NInv_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ZC_NInv_MASK               ZC_NInv__MASK
#define ZC_NInv_SHIFT              ZC_NInv__SHIFT
#define ZC_NInv_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ZC_NInv_PS                     (* (reg32 *) ZC_NInv__PS)
/* Port Configuration */
#define ZC_NInv_PC                     (* (reg32 *) ZC_NInv__PC)
/* Data Register */
#define ZC_NInv_DR                     (* (reg32 *) ZC_NInv__DR)
/* Input Buffer Disable Override */
#define ZC_NInv_INP_DIS                (* (reg32 *) ZC_NInv__PC2)


#if defined(ZC_NInv__INTSTAT)  /* Interrupt Registers */

    #define ZC_NInv_INTSTAT                (* (reg32 *) ZC_NInv__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ZC_NInv_DRIVE_MODE_SHIFT       (0x00u)
#define ZC_NInv_DRIVE_MODE_MASK        (0x07u << ZC_NInv_DRIVE_MODE_SHIFT)


#endif /* End Pins ZC_NInv_H */


/* [] END OF FILE */
