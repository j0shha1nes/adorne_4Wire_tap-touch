/*******************************************************************************
* File Name: I_Sense.h  
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

#if !defined(CY_PINS_I_Sense_H) /* Pins I_Sense_H */
#define CY_PINS_I_Sense_H

#include "cytypes.h"
#include "cyfitter.h"
#include "I_Sense_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    I_Sense_Write(uint8 value) ;
void    I_Sense_SetDriveMode(uint8 mode) ;
uint8   I_Sense_ReadDataReg(void) ;
uint8   I_Sense_Read(void) ;
uint8   I_Sense_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define I_Sense_DRIVE_MODE_BITS        (3)
#define I_Sense_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - I_Sense_DRIVE_MODE_BITS))

#define I_Sense_DM_ALG_HIZ         (0x00u)
#define I_Sense_DM_DIG_HIZ         (0x01u)
#define I_Sense_DM_RES_UP          (0x02u)
#define I_Sense_DM_RES_DWN         (0x03u)
#define I_Sense_DM_OD_LO           (0x04u)
#define I_Sense_DM_OD_HI           (0x05u)
#define I_Sense_DM_STRONG          (0x06u)
#define I_Sense_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define I_Sense_MASK               I_Sense__MASK
#define I_Sense_SHIFT              I_Sense__SHIFT
#define I_Sense_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define I_Sense_PS                     (* (reg32 *) I_Sense__PS)
/* Port Configuration */
#define I_Sense_PC                     (* (reg32 *) I_Sense__PC)
/* Data Register */
#define I_Sense_DR                     (* (reg32 *) I_Sense__DR)
/* Input Buffer Disable Override */
#define I_Sense_INP_DIS                (* (reg32 *) I_Sense__PC2)


#if defined(I_Sense__INTSTAT)  /* Interrupt Registers */

    #define I_Sense_INTSTAT                (* (reg32 *) I_Sense__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define I_Sense_DRIVE_MODE_SHIFT       (0x00u)
#define I_Sense_DRIVE_MODE_MASK        (0x07u << I_Sense_DRIVE_MODE_SHIFT)


#endif /* End Pins I_Sense_H */


/* [] END OF FILE */
