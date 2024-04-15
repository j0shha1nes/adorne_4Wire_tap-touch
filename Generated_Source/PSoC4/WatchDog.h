/*******************************************************************************
* File Name: WatchDog.h
* Version 1.70
*
*  Description:
*   Provides the function definitions for the Interrupt Controller.
*
*
********************************************************************************
* Copyright 2008-2015, Cypress Semiconductor Corporation.  All rights reserved.
* You may use this file only in accordance with the license, terms, conditions, 
* disclaimers, and limitations in the end user license agreement accompanying 
* the software package with which this file was provided.
*******************************************************************************/
#if !defined(CY_ISR_WatchDog_H)
#define CY_ISR_WatchDog_H


#include <cytypes.h>
#include <cyfitter.h>

/* Interrupt Controller API. */
void WatchDog_Start(void);
void WatchDog_StartEx(cyisraddress address);
void WatchDog_Stop(void);

CY_ISR_PROTO(WatchDog_Interrupt);

void WatchDog_SetVector(cyisraddress address);
cyisraddress WatchDog_GetVector(void);

void WatchDog_SetPriority(uint8 priority);
uint8 WatchDog_GetPriority(void);

void WatchDog_Enable(void);
uint8 WatchDog_GetState(void);
void WatchDog_Disable(void);

void WatchDog_SetPending(void);
void WatchDog_ClearPending(void);


/* Interrupt Controller Constants */

/* Address of the INTC.VECT[x] register that contains the Address of the WatchDog ISR. */
#define WatchDog_INTC_VECTOR            ((reg32 *) WatchDog__INTC_VECT)

/* Address of the WatchDog ISR priority. */
#define WatchDog_INTC_PRIOR             ((reg32 *) WatchDog__INTC_PRIOR_REG)

/* Priority of the WatchDog interrupt. */
#define WatchDog_INTC_PRIOR_NUMBER      WatchDog__INTC_PRIOR_NUM

/* Address of the INTC.SET_EN[x] byte to bit enable WatchDog interrupt. */
#define WatchDog_INTC_SET_EN            ((reg32 *) WatchDog__INTC_SET_EN_REG)

/* Address of the INTC.CLR_EN[x] register to bit clear the WatchDog interrupt. */
#define WatchDog_INTC_CLR_EN            ((reg32 *) WatchDog__INTC_CLR_EN_REG)

/* Address of the INTC.SET_PD[x] register to set the WatchDog interrupt state to pending. */
#define WatchDog_INTC_SET_PD            ((reg32 *) WatchDog__INTC_SET_PD_REG)

/* Address of the INTC.CLR_PD[x] register to clear the WatchDog interrupt. */
#define WatchDog_INTC_CLR_PD            ((reg32 *) WatchDog__INTC_CLR_PD_REG)



#endif /* CY_ISR_WatchDog_H */


/* [] END OF FILE */
