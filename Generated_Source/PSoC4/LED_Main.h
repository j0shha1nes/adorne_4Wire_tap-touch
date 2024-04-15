/*******************************************************************************
* File Name: LED_Main.h  
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

#if !defined(CY_PINS_LED_Main_H) /* Pins LED_Main_H */
#define CY_PINS_LED_Main_H

#include "cytypes.h"
#include "cyfitter.h"
#include "LED_Main_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    LED_Main_Write(uint8 value) ;
void    LED_Main_SetDriveMode(uint8 mode) ;
uint8   LED_Main_ReadDataReg(void) ;
uint8   LED_Main_Read(void) ;
uint8   LED_Main_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define LED_Main_DRIVE_MODE_BITS        (3)
#define LED_Main_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - LED_Main_DRIVE_MODE_BITS))

#define LED_Main_DM_ALG_HIZ         (0x00u)
#define LED_Main_DM_DIG_HIZ         (0x01u)
#define LED_Main_DM_RES_UP          (0x02u)
#define LED_Main_DM_RES_DWN         (0x03u)
#define LED_Main_DM_OD_LO           (0x04u)
#define LED_Main_DM_OD_HI           (0x05u)
#define LED_Main_DM_STRONG          (0x06u)
#define LED_Main_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define LED_Main_MASK               LED_Main__MASK
#define LED_Main_SHIFT              LED_Main__SHIFT
#define LED_Main_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define LED_Main_PS                     (* (reg32 *) LED_Main__PS)
/* Port Configuration */
#define LED_Main_PC                     (* (reg32 *) LED_Main__PC)
/* Data Register */
#define LED_Main_DR                     (* (reg32 *) LED_Main__DR)
/* Input Buffer Disable Override */
#define LED_Main_INP_DIS                (* (reg32 *) LED_Main__PC2)


#if defined(LED_Main__INTSTAT)  /* Interrupt Registers */

    #define LED_Main_INTSTAT                (* (reg32 *) LED_Main__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define LED_Main_DRIVE_MODE_SHIFT       (0x00u)
#define LED_Main_DRIVE_MODE_MASK        (0x07u << LED_Main_DRIVE_MODE_SHIFT)


#endif /* End Pins LED_Main_H */


/* [] END OF FILE */
