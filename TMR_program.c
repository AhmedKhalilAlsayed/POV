/*
 * TMR_program.c
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */

#include "newTypes.h"

#include "TMR_interface.h"
#include "TMR_config.h"
#include "TMR_private.h"

static volatile u32 Glob_u32GetTimeUs = 0;
static volatile u16 Glob_u16GetTimeOverflows = 0;

static volatile u32 Glob_u32TimeUs = 0;
static volatile u16 Glob_u16Preload = 0;
static volatile u16 Glob_u16Overflows = 0;
static volatile TMR_voidCallbackVoid Glob_TMR1callback = NULL;
static volatile TMR1_Mode_t Glob_enumTMR1mode = TMR1_Mode_None;

void TMR1_voidInit(TMR1_Clk_t Copy_enumTMR1_Clk) {
	// Normal mode

	CLR_BIT(TMR1_REG->TCCR1A, 0);
	CLR_BIT(TMR1_REG->TCCR1A, 1);

	CLR_BIT(TMR1_REG->TCCR1B, 3);
	CLR_BIT(TMR1_REG->TCCR1B, 4);

	// clock

	TMR1_REG->TCCR1B &= ~(0b111);
	TMR1_REG->TCCR1B |= Copy_enumTMR1_Clk;

}

// todo : need more test
u32 TMR1_u32GetTime() {

	u32 temp = (u32) ((u32) TMR1_REG->TCNT1
			- (u32) ((u16) (TMR1_MAX_TICKS - Glob_u16Preload))
			+ (u32) ((Glob_u16GetTimeOverflows * TMR1_MAX_TICKS)));

	temp += Glob_u32GetTimeUs;

	Glob_u32GetTimeUs = 0;
	Glob_u16Preload = 0;
	Glob_u16GetTimeOverflows = 0;

	return temp;
}

void TMR1_voidWaitAsync_us(u32 Copy_u32TimeUs, TMR1_Mode_t Copy_enumMode,
		TMR_voidCallbackVoid callback) {

	u16 tempOldPreload = Glob_u16Preload;

	Glob_u32TimeUs = Copy_u32TimeUs;

	Glob_u16Overflows = Copy_u32TimeUs / TMR1_MAX_TICKS;
	Glob_u16Preload = Copy_u32TimeUs % TMR1_MAX_TICKS;

	/// for GetTime If Preload Is Changed
	// todo : need more test
	// todo : need more test
	if (tempOldPreload != Glob_u16Preload) {
		Glob_u32GetTimeUs += TMR1_REG->TCNT1
				- (u16) (TMR1_MAX_TICKS - tempOldPreload);
	}
	///end

	if ((Glob_enumTMR1mode == TMR1_Mode_Circular) && (callback == NULL)
			&& (Glob_TMR1callback != NULL)) {
		// old request

		// set REG value
		if (Glob_u16Preload > 0) {
			Glob_u16Overflows++;
			TMR1_REG->TCNT1 = TMR1_MAX_TICKS - Glob_u16Preload;
			//Glob_u16Preload = 0;
		} else {
			TMR1_REG->TCNT1 = 0;
		}

	} else {
		// new request

		if ((callback != NULL)
				&& ((Glob_u16Preload != 0) || (Glob_u16Overflows != 0))) {

			// init
			Glob_TMR1callback = callback;
			Glob_enumTMR1mode = Copy_enumMode;

			switch (Copy_enumMode) {
			case TMR1_Mode_Circular:
//				Glob_u32TimeUs = Copy_u32TimeUs;
				break;
			case TMR1_Mode_Once:
				Glob_u32TimeUs = 0;
				break;
			default:
				Glob_u32TimeUs = 0;
				break;

			}

			// set REG value
			if (Glob_u16Preload > 0) {
				Glob_u16Overflows++;
				TMR1_REG->TCNT1 = TMR1_MAX_TICKS - Glob_u16Preload;
				//Glob_u16Preload = 0;
			} else {
				TMR1_REG->TCNT1 = 0;
			}

			// INT enable TMR1 OVF
			SET_BIT(TMR1_REG->TIMSK, 2);

		} else {
			Glob_enumTMR1mode = TMR1_Mode_None;
//			Glob_u16Overflows = 0;
//			Glob_u16Preload = 0;
		}

	}

}

///

// OVF TMR1 ISR
void __vector_9(void) __attribute__((signal));
void __vector_9(void) {

	///
	Glob_u16GetTimeOverflows++;
	///
	Glob_u16Overflows--;

	if (Glob_u16Overflows == 0) {

		if (Glob_TMR1callback != NULL) {
			Glob_TMR1callback();
		}

		if (Glob_enumTMR1mode == TMR1_Mode_Circular) {
			TMR1_voidWaitAsync_us(Glob_u32TimeUs, 0, NULL);

		} else {
			// INT disable TMR1 OVF
			CLR_BIT(TMR1_REG->TIMSK, 2);
			Glob_enumTMR1mode = TMR1_Mode_None;
			Glob_TMR1callback = NULL;
		}

	} else {
		// set time
		TMR1_REG->TCNT1 = 0;
	}

}

