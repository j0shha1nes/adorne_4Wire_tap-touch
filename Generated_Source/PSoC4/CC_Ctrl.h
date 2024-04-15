/*******************************************************************************
* File Name: CC_Ctrl.h  
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

#if !defined(CY_PINS_CC_Ctrl_H) /* Pins CC_Ctrl_H */
#define CY_PINS_CC_Ctrl_H

#include "cytypes.h"
#include "cyfitter.h"
#include "CC_Ctrl_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    CC_Ctrl_Write(uint8 value) ;
void    CC_Ctrl_SetDriveMode(uint8 mode) ;
uint8   CC_Ctrl_ReadDataReg(void) ;
uint8   CC_Ctrl_Read(void) ;
uint8   CC_Ctrl_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define CC_Ctrl_DRIVE_MODE_BITS        (3)
#define CC_Ctrl_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - CC_Ctrl_DRIVE_MODE_BITS))

#define CC_Ctrl_DM_ALG_HIZ         (0x00u)
#define CC_Ctrl_DM_DIG_HIZ         (0x01u)
#define CC_Ctrl_DM_RES_UP          (0x02u)
#define CC_Ctrl_DM_RES_DWN         (0x03u)
#define CC_Ctrl_DM_OD_LO           (0x04u)
#define CC_Ctrl_DM_OD_HI           (0x05u)
#define CC_Ctrl_DM_STRONG          (0x06u)
#define CC_Ctrl_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define CC_Ctrl_MASK               CC_Ctrl__MASK
#define CC_Ctrl_SHIFT              CC_Ctrl__SHIFT
#define CC_Ctrl_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define CC_Ctrl_PS                     (* (reg32 *) CC_Ctrl__PS)
/* Port Configuration */
#define CC_Ctrl_PC                     (* (reg32 *) CC_Ctrl__PC)
/* Data Register */
#define CC_Ctrl_DR                     (* (reg32 *) CC_Ctrl__DR)
/* Input Buffer Disable Override */
#define CC_Ctrl_INP_DIS                (* (reg32 *) CC_Ctrl__PC2)


#if defined(CC_Ctrl__INTSTAT)  /* Interrupt Registers */

    #define CC_Ctrl_INTSTAT                (* (reg32 *) CC_Ctrl__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define CC_Ctrl_DRIVE_MODE_SHIFT       (0x00u)
#define CC_Ctrl_DRIVE_MODE_MASK        (0x07u << CC_Ctrl_DRIVE_MODE_SHIFT)


#endif /* End Pins CC_Ctrl_H */


/* [] END OF FILE */
