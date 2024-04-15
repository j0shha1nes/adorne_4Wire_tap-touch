/*******************************************************************************
* File Name: SW_Minus.h  
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

#if !defined(CY_PINS_SW_Minus_H) /* Pins SW_Minus_H */
#define CY_PINS_SW_Minus_H

#include "cytypes.h"
#include "cyfitter.h"
#include "SW_Minus_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    SW_Minus_Write(uint8 value) ;
void    SW_Minus_SetDriveMode(uint8 mode) ;
uint8   SW_Minus_ReadDataReg(void) ;
uint8   SW_Minus_Read(void) ;
uint8   SW_Minus_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define SW_Minus_DRIVE_MODE_BITS        (3)
#define SW_Minus_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - SW_Minus_DRIVE_MODE_BITS))

#define SW_Minus_DM_ALG_HIZ         (0x00u)
#define SW_Minus_DM_DIG_HIZ         (0x01u)
#define SW_Minus_DM_RES_UP          (0x02u)
#define SW_Minus_DM_RES_DWN         (0x03u)
#define SW_Minus_DM_OD_LO           (0x04u)
#define SW_Minus_DM_OD_HI           (0x05u)
#define SW_Minus_DM_STRONG          (0x06u)
#define SW_Minus_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define SW_Minus_MASK               SW_Minus__MASK
#define SW_Minus_SHIFT              SW_Minus__SHIFT
#define SW_Minus_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define SW_Minus_PS                     (* (reg32 *) SW_Minus__PS)
/* Port Configuration */
#define SW_Minus_PC                     (* (reg32 *) SW_Minus__PC)
/* Data Register */
#define SW_Minus_DR                     (* (reg32 *) SW_Minus__DR)
/* Input Buffer Disable Override */
#define SW_Minus_INP_DIS                (* (reg32 *) SW_Minus__PC2)


#if defined(SW_Minus__INTSTAT)  /* Interrupt Registers */

    #define SW_Minus_INTSTAT                (* (reg32 *) SW_Minus__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define SW_Minus_DRIVE_MODE_SHIFT       (0x00u)
#define SW_Minus_DRIVE_MODE_MASK        (0x07u << SW_Minus_DRIVE_MODE_SHIFT)


#endif /* End Pins SW_Minus_H */


/* [] END OF FILE */
