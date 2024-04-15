/*******************************************************************************
* File Name: Relay_3W.h  
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

#if !defined(CY_PINS_Relay_3W_H) /* Pins Relay_3W_H */
#define CY_PINS_Relay_3W_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Relay_3W_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Relay_3W_Write(uint8 value) ;
void    Relay_3W_SetDriveMode(uint8 mode) ;
uint8   Relay_3W_ReadDataReg(void) ;
uint8   Relay_3W_Read(void) ;
uint8   Relay_3W_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Relay_3W_DRIVE_MODE_BITS        (3)
#define Relay_3W_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Relay_3W_DRIVE_MODE_BITS))

#define Relay_3W_DM_ALG_HIZ         (0x00u)
#define Relay_3W_DM_DIG_HIZ         (0x01u)
#define Relay_3W_DM_RES_UP          (0x02u)
#define Relay_3W_DM_RES_DWN         (0x03u)
#define Relay_3W_DM_OD_LO           (0x04u)
#define Relay_3W_DM_OD_HI           (0x05u)
#define Relay_3W_DM_STRONG          (0x06u)
#define Relay_3W_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Relay_3W_MASK               Relay_3W__MASK
#define Relay_3W_SHIFT              Relay_3W__SHIFT
#define Relay_3W_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Relay_3W_PS                     (* (reg32 *) Relay_3W__PS)
/* Port Configuration */
#define Relay_3W_PC                     (* (reg32 *) Relay_3W__PC)
/* Data Register */
#define Relay_3W_DR                     (* (reg32 *) Relay_3W__DR)
/* Input Buffer Disable Override */
#define Relay_3W_INP_DIS                (* (reg32 *) Relay_3W__PC2)


#if defined(Relay_3W__INTSTAT)  /* Interrupt Registers */

    #define Relay_3W_INTSTAT                (* (reg32 *) Relay_3W__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Relay_3W_DRIVE_MODE_SHIFT       (0x00u)
#define Relay_3W_DRIVE_MODE_MASK        (0x07u << Relay_3W_DRIVE_MODE_SHIFT)


#endif /* End Pins Relay_3W_H */


/* [] END OF FILE */
