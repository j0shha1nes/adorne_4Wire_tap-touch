/*******************************************************************************
* File Name: ZC_Inv.h  
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

#if !defined(CY_PINS_ZC_Inv_H) /* Pins ZC_Inv_H */
#define CY_PINS_ZC_Inv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "ZC_Inv_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    ZC_Inv_Write(uint8 value) ;
void    ZC_Inv_SetDriveMode(uint8 mode) ;
uint8   ZC_Inv_ReadDataReg(void) ;
uint8   ZC_Inv_Read(void) ;
uint8   ZC_Inv_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define ZC_Inv_DRIVE_MODE_BITS        (3)
#define ZC_Inv_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - ZC_Inv_DRIVE_MODE_BITS))

#define ZC_Inv_DM_ALG_HIZ         (0x00u)
#define ZC_Inv_DM_DIG_HIZ         (0x01u)
#define ZC_Inv_DM_RES_UP          (0x02u)
#define ZC_Inv_DM_RES_DWN         (0x03u)
#define ZC_Inv_DM_OD_LO           (0x04u)
#define ZC_Inv_DM_OD_HI           (0x05u)
#define ZC_Inv_DM_STRONG          (0x06u)
#define ZC_Inv_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define ZC_Inv_MASK               ZC_Inv__MASK
#define ZC_Inv_SHIFT              ZC_Inv__SHIFT
#define ZC_Inv_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define ZC_Inv_PS                     (* (reg32 *) ZC_Inv__PS)
/* Port Configuration */
#define ZC_Inv_PC                     (* (reg32 *) ZC_Inv__PC)
/* Data Register */
#define ZC_Inv_DR                     (* (reg32 *) ZC_Inv__DR)
/* Input Buffer Disable Override */
#define ZC_Inv_INP_DIS                (* (reg32 *) ZC_Inv__PC2)


#if defined(ZC_Inv__INTSTAT)  /* Interrupt Registers */

    #define ZC_Inv_INTSTAT                (* (reg32 *) ZC_Inv__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define ZC_Inv_DRIVE_MODE_SHIFT       (0x00u)
#define ZC_Inv_DRIVE_MODE_MASK        (0x07u << ZC_Inv_DRIVE_MODE_SHIFT)


#endif /* End Pins ZC_Inv_H */


/* [] END OF FILE */
