/*******************************************************************************
* File Name: Relay_1P.h  
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

#if !defined(CY_PINS_Relay_1P_H) /* Pins Relay_1P_H */
#define CY_PINS_Relay_1P_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Relay_1P_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Relay_1P_Write(uint8 value) ;
void    Relay_1P_SetDriveMode(uint8 mode) ;
uint8   Relay_1P_ReadDataReg(void) ;
uint8   Relay_1P_Read(void) ;
uint8   Relay_1P_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Relay_1P_DRIVE_MODE_BITS        (3)
#define Relay_1P_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Relay_1P_DRIVE_MODE_BITS))

#define Relay_1P_DM_ALG_HIZ         (0x00u)
#define Relay_1P_DM_DIG_HIZ         (0x01u)
#define Relay_1P_DM_RES_UP          (0x02u)
#define Relay_1P_DM_RES_DWN         (0x03u)
#define Relay_1P_DM_OD_LO           (0x04u)
#define Relay_1P_DM_OD_HI           (0x05u)
#define Relay_1P_DM_STRONG          (0x06u)
#define Relay_1P_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Relay_1P_MASK               Relay_1P__MASK
#define Relay_1P_SHIFT              Relay_1P__SHIFT
#define Relay_1P_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Relay_1P_PS                     (* (reg32 *) Relay_1P__PS)
/* Port Configuration */
#define Relay_1P_PC                     (* (reg32 *) Relay_1P__PC)
/* Data Register */
#define Relay_1P_DR                     (* (reg32 *) Relay_1P__DR)
/* Input Buffer Disable Override */
#define Relay_1P_INP_DIS                (* (reg32 *) Relay_1P__PC2)


#if defined(Relay_1P__INTSTAT)  /* Interrupt Registers */

    #define Relay_1P_INTSTAT                (* (reg32 *) Relay_1P__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Relay_1P_DRIVE_MODE_SHIFT       (0x00u)
#define Relay_1P_DRIVE_MODE_MASK        (0x07u << Relay_1P_DRIVE_MODE_SHIFT)


#endif /* End Pins Relay_1P_H */


/* [] END OF FILE */
