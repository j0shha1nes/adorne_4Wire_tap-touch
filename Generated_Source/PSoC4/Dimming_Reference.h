/*******************************************************************************
* File Name: Dimming_Reference.h  
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

#if !defined(CY_PINS_Dimming_Reference_H) /* Pins Dimming_Reference_H */
#define CY_PINS_Dimming_Reference_H

#include "cytypes.h"
#include "cyfitter.h"
#include "Dimming_Reference_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    Dimming_Reference_Write(uint8 value) ;
void    Dimming_Reference_SetDriveMode(uint8 mode) ;
uint8   Dimming_Reference_ReadDataReg(void) ;
uint8   Dimming_Reference_Read(void) ;
uint8   Dimming_Reference_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define Dimming_Reference_DRIVE_MODE_BITS        (3)
#define Dimming_Reference_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - Dimming_Reference_DRIVE_MODE_BITS))

#define Dimming_Reference_DM_ALG_HIZ         (0x00u)
#define Dimming_Reference_DM_DIG_HIZ         (0x01u)
#define Dimming_Reference_DM_RES_UP          (0x02u)
#define Dimming_Reference_DM_RES_DWN         (0x03u)
#define Dimming_Reference_DM_OD_LO           (0x04u)
#define Dimming_Reference_DM_OD_HI           (0x05u)
#define Dimming_Reference_DM_STRONG          (0x06u)
#define Dimming_Reference_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define Dimming_Reference_MASK               Dimming_Reference__MASK
#define Dimming_Reference_SHIFT              Dimming_Reference__SHIFT
#define Dimming_Reference_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define Dimming_Reference_PS                     (* (reg32 *) Dimming_Reference__PS)
/* Port Configuration */
#define Dimming_Reference_PC                     (* (reg32 *) Dimming_Reference__PC)
/* Data Register */
#define Dimming_Reference_DR                     (* (reg32 *) Dimming_Reference__DR)
/* Input Buffer Disable Override */
#define Dimming_Reference_INP_DIS                (* (reg32 *) Dimming_Reference__PC2)


#if defined(Dimming_Reference__INTSTAT)  /* Interrupt Registers */

    #define Dimming_Reference_INTSTAT                (* (reg32 *) Dimming_Reference__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define Dimming_Reference_DRIVE_MODE_SHIFT       (0x00u)
#define Dimming_Reference_DRIVE_MODE_MASK        (0x07u << Dimming_Reference_DRIVE_MODE_SHIFT)


#endif /* End Pins Dimming_Reference_H */


/* [] END OF FILE */
