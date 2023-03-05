/*
 * EXTI_interface.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */

#ifndef EXTI_INTERFACE_H_
#define EXTI_INTERFACE_H_

typedef void (*EXTI_voidCallbackVoid)(void);

typedef enum {

	EXTIx_0, EXTIx_1,
//	EXTIx_2,

} EXTIx_t;

typedef enum {

	EXTI_Mode_Low_Level,
	EXTI_Mode_Any_Logical_Change,
	EXTI_Mode_Falling_Edge,
	EXTI_Mode_Rising_Edge,

} EXTI_Mode_t;

void EXTI_voidInit(EXTIx_t Copy_enumEXTIx, EXTI_Mode_t Copy_enumEXTImode,
		EXTI_voidCallbackVoid voidCallbackVoid);

void EXTI_voidEnable(EXTIx_t Copy_enumEXTIx);

void EXTI_voidDisable(EXTIx_t Copy_enumEXTIx);

#endif /* EXTI_INTERFACE_H_ */
