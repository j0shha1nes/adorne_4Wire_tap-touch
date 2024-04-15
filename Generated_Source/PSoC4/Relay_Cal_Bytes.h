/*******************************************************************************
* File Name: Relay_Cal_Bytes.h
* Version 1.10
*
* Description:
*  This file provides constants and parameter values for the Emulated EEPROM
*  Component.
*
********************************************************************************
* Copyright 2013, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions,
* disclaimers, and limitations in the end user license agreement accompanying
* the software package with which this file was provided.
*******************************************************************************/
#ifndef CY_EM_EEPROM_Relay_Cal_Bytes_H
#define CY_EM_EEPROM_Relay_Cal_Bytes_H

#include "cytypes.h"
#include "CyFlash.h"

#if !defined(CYDEV_FLASH_BASE)
    #define CYDEV_FLASH_BASE                    (CYDEV_FLS_BASE)
#endif  /* !defined(CYDEV_FLS_BASE) */

#define Relay_Cal_Bytes_FLASH_BASE_ADDR        (CYDEV_FLASH_BASE)
#define Relay_Cal_Bytes_FLASH_SIZE             (CYDEV_FLASH_SIZE)
#define Relay_Cal_Bytes_FLASH_END_ADDR         (Relay_Cal_Bytes_FLASH_BASE_ADDR + Relay_Cal_Bytes_FLASH_SIZE)

#if (CY_PSOC3)
    #define Relay_Cal_Bytes_CODE_ADDR_OFFSET   (0xff0000u)
    #define Relay_Cal_Bytes_CODE_ADDR_END      (Relay_Cal_Bytes_CODE_ADDR_OFFSET + (Relay_Cal_Bytes_FLASH_SIZE - 1u))
    #define Relay_Cal_Bytes_CODE_ADDR_MASK     (0xffffu)
#endif /* (CY_PSOC3) */

#define Relay_Cal_Bytes_ROWS_IN_ARRAY          (CY_FLASH_SIZEOF_ARRAY/CY_FLASH_SIZEOF_ROW)


/***************************************
*        Function Prototypes
***************************************/
void Relay_Cal_Bytes_Start(void) ;
void Relay_Cal_Bytes_Stop(void) ;
#if (CY_PSOC3)
    cystatus Relay_Cal_Bytes_Write(const uint8 srcBuf[], const uint8 eepromPtr[],
                                                uint16 byteCount) ;
#else
    cystatus Relay_Cal_Bytes_Write(const uint8 srcBuf[], const uint8 eepromPtr[], uint32 byteCount);
#endif /* (CY_PSOC3) */

#endif /* CY_EM_EEPROM_Relay_Cal_Bytes_H */


/* [] END OF FILE */
