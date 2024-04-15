/*******************************************************************************
* File Name: OPTO_Drv.h  
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

#if !defined(CY_PINS_OPTO_Drv_H) /* Pins OPTO_Drv_H */
#define CY_PINS_OPTO_Drv_H

#include "cytypes.h"
#include "cyfitter.h"
#include "OPTO_Drv_aliases.h"


/***************************************
*        Function Prototypes             
***************************************/    

void    OPTO_Drv_Write(uint8 value) ;
void    OPTO_Drv_SetDriveMode(uint8 mode) ;
uint8   OPTO_Drv_ReadDataReg(void) ;
uint8   OPTO_Drv_Read(void) ;
uint8   OPTO_Drv_ClearInterrupt(void) ;


/***************************************
*           API Constants        
***************************************/

/* Drive Modes */
#define OPTO_Drv_DRIVE_MODE_BITS        (3)
#define OPTO_Drv_DRIVE_MODE_IND_MASK    (0xFFFFFFFFu >> (32 - OPTO_Drv_DRIVE_MODE_BITS))

#define OPTO_Drv_DM_ALG_HIZ         (0x00u)
#define OPTO_Drv_DM_DIG_HIZ         (0x01u)
#define OPTO_Drv_DM_RES_UP          (0x02u)
#define OPTO_Drv_DM_RES_DWN         (0x03u)
#define OPTO_Drv_DM_OD_LO           (0x04u)
#define OPTO_Drv_DM_OD_HI           (0x05u)
#define OPTO_Drv_DM_STRONG          (0x06u)
#define OPTO_Drv_DM_RES_UPDWN       (0x07u)

/* Digital Port Constants */
#define OPTO_Drv_MASK               OPTO_Drv__MASK
#define OPTO_Drv_SHIFT              OPTO_Drv__SHIFT
#define OPTO_Drv_WIDTH              1u


/***************************************
*             Registers        
***************************************/

/* Main Port Registers */
/* Pin State */
#define OPTO_Drv_PS                     (* (reg32 *) OPTO_Drv__PS)
/* Port Configuration */
#define OPTO_Drv_PC                     (* (reg32 *) OPTO_Drv__PC)
/* Data Register */
#define OPTO_Drv_DR                     (* (reg32 *) OPTO_Drv__DR)
/* Input Buffer Disable Override */
#define OPTO_Drv_INP_DIS                (* (reg32 *) OPTO_Drv__PC2)


#if defined(OPTO_Drv__INTSTAT)  /* Interrupt Registers */

    #define OPTO_Drv_INTSTAT                (* (reg32 *) OPTO_Drv__INTSTAT)

#endif /* Interrupt Registers */


/***************************************
* The following code is DEPRECATED and 
* must not be used.
***************************************/

#define OPTO_Drv_DRIVE_MODE_SHIFT       (0x00u)
#define OPTO_Drv_DRIVE_MODE_MASK        (0x07u << OPTO_Drv_DRIVE_MODE_SHIFT)


#endif /* End Pins OPTO_Drv_H */


/* [] END OF FILE */
