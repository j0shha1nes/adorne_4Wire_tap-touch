/*******************************************************************************
* File Name: Cap_Mod.h  
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

#if !defined(CY_PINS_Cap_Mod_H) /* Pins Cap_Mod_H */
#define CY_PINS_Cap_Mod_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Cap_Mod_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Cap_Mod_Write(uint8 value) ;
void    Cap_Mod_SetDriveMode(uint8 mode) ;
uint8   Cap_Mod_ReadDataReg(void) ;
uint8   Cap_Mod_Read(void) ;
uint8   Cap_Mod_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Cap_Mod_DRIVE_MODE_BITS        (3)
#define Cap_Mod_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Cap_Mod_DRIVE_MODE_BITS))

#define Cap_Mod_DM_ALG_HIZ         (0x00u)
#define Cap_Mod_DM_DIG_HIZ         (0x01u)
#define Cap_Mod_DM_RES_UP          (0x02u)
#define Cap_Mod_DM_RES_DWN         (0x03u)
#define Cap_Mod_DM_OD_LO           (0x04u)
#define Cap_Mod_DM_OD_HI           (0x05u)
#define Cap_Mod_DM_STRONG          (0x06u)
#define Cap_Mod_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Cap_Mod_MASK               Cap_Mod__MASK
#define Cap_Mod_SHIFT              Cap_Mod__SHIFT
#define Cap_Mod_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Cap_Mod_PS                     (* (reg32 *) Cap_Mod__PS)
/* Port Configuration */
#define Cap_Mod_PC                     (* (reg32 *) Cap_Mod__PC)
/* Data Register */
#define Cap_Mod_DR                     (* (reg32 *) Cap_Mod__DR)
/* Input Buffer Disable Override */
#define Cap_Mod_INP_DIS                (* (reg32 *) Cap_Mod__PC2)


#if defined(Cap_Mod__INTSTAT)  /* Interrupt Registers */

    #define Cap_Mod_INTSTAT                (* (reg32 *) Cap_Mod__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Cap_Mod_DRIVE_MODE_SHIFT       (0x00u)
#define Cap_Mod_DRIVE_MODE_MASK        (0x07u << Cap_Mod_DRIVE_MODE_SHIFT)


#endif /* End Pins Cap_Mod_H */


/* [] END OF FILE */
