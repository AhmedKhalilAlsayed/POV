/*
 * EXTI_program.c
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */
#include "newTypes.h"

#include "EXTI_interface.h"
#include "EXTI_config.h"
#include "EXTI_private.h"

static EXTI_voidCallbackVoid Glob_EXTIcallbacks[3] = { NULL, NULL, NULL };

void EXTI_voidInit(EXTIx_t Copy_enumEXTIx, EXTI_Mode_t Copy_enumEXTImode,
		EXTI_voidCallbackVoid voidCallbackVoid) {

	if (voidCallbackVoid != NULL) {

		Glob_EXTIcallbacks[Copy_enumEXTIx] = voidCallbackVoid;

		switch (Copy_enumEXTIx) {
		case EXTIx_0:
		case EXTIx_1:

			EXTI_REG->MCUCR &= ~(0b11 << ((2 * Copy_enumEXTIx) + 1));
			EXTI_REG->MCUCR |=
					(Copy_enumEXTImode << ((2 * Copy_enumEXTIx) + 1));

			break;

			//	case EXTIx_2:
			//		break;
		}
	}

}

void EXTI_voidEnable(EXTIx_t Copy_enumEXTIx) {

	switch (Copy_enumEXTIx) {
	case EXTIx_0:

		SET_BIT(EXTI_REG->GICR, 6);

		break;
	case EXTIx_1:

		SET_BIT(EXTI_REG->GICR, 7);

		break;

		//	case EXTIx_2:
		//		break;
	}

}

void EXTI_voidDisable(EXTIx_t Copy_enumEXTIx) {
	switch (Copy_enumEXTIx) {
	case EXTIx_0:

		CLR_BIT(EXTI_REG->GICR, 6);

		break;
	case EXTIx_1:

		CLR_BIT(EXTI_REG->GICR, 7);

		break;

		//	case EXTIx_2:
		//		break;
	}
}

/// ISRs

void __vector_1(void) __attribute__((signal));	//INT0
void __vector_2(void) __attribute__((signal));	//INT1
void __vector_3(void) __attribute__((signal));	//INT2

void __vector_1(void) {

	if (Glob_EXTIcallbacks[0] != NULL) {
		Glob_EXTIcallbacks[0]();
	}

}

void __vector_2(void) {
	if (Glob_EXTIcallbacks[1] != NULL) {
		Glob_EXTIcallbacks[1]();
	}
}

void __vector_3(void) {
	if (Glob_EXTIcallbacks[2] != NULL) {
		Glob_EXTIcallbacks[2]();
	}
}

