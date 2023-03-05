#include "newTypes.h"

#include "DIO_interface.h"
#include "GIE_INTERFACE.h"
#include "EXTI_interface.h"
#include "TMR_interface.h"

#include "POV_interface.h"

#define CHAR_WITH(ARR) (sizeof(ARR) / sizeof(u8*))

//hourHandChar
const u8 hourHandCharCol0[] = { POV_LED1, POV_LED2, POV_LED3, POV_LED4,
POV_LED5, POV_LED6, POV_LED7, POV_LED8, POV_LED9, POV_LED10,
POV_LED_STOP };
//const u8 hourHandCharCol1[] = { POV_LED2, POV_LED_STOP };
//const u8 hourHandCharCol2[] = { POV_LED3, POV_LED_STOP };
const u8* hourHandChar[] = { hourHandCharCol0 };
//minuteHandChar
const u8 minuteHandCharCol0[] = { POV_LED1, POV_LED2, POV_LED3, POV_LED4,
POV_LED5, POV_LED6, POV_LED7, POV_LED8, POV_LED9, POV_LED10, POV_LED11,
POV_LED12, POV_LED13, POV_LED14, POV_LED15, POV_LED_STOP };
const u8* minuteHandChar[] = { minuteHandCharCol0 };
//secondHandChar
const u8 secondHandCharCol0[] = { POV_LED1, POV_LED2, POV_LED3, POV_LED4,
POV_LED5, POV_LED6, POV_LED7, POV_LED8, POV_LED9, POV_LED10, POV_LED11,
POV_LED12, POV_LED13, POV_LED14, POV_LED15, POV_LED16, POV_LED17,
POV_LED18, POV_LED19, POV_LED_STOP };
const u8* secondHandChar[] = { secondHandCharCol0 };

// ***********************************************

// Count how many ticks are taked to to update the clock time
volatile u32 Glob_u32TimeTicksOneSecond = 0;

// The time needed to fire an INT of TMR
volatile u32 Glob_u32TimeTicksUnit = 0;

// The current index of Axis
volatile u8 Glob_u8AxisIndex = 0;
//
volatile u8 Glob_u8HourHandIndex = 0;
//
volatile u8 Glob_u8MinuteHandIndex = 0;
//
volatile u8 Glob_u8SecondHandIndex = 0;
//
volatile u8 Glob_u8isDisplay = TRUE;

void detectMagnentCallback() {

	GIE_voidDisable();

	Glob_u32TimeTicksUnit = (TMR1_u32GetTime() / POV_MAX_INDEX);
	TMR1_voidWaitAsync_us(Glob_u32TimeTicksUnit, 0, NULL);
	Glob_u8AxisIndex = 0;

	GIE_voidEnable();
}

void timerCallback() {

	GIE_voidDisable();

	Glob_u32TimeTicksOneSecond += Glob_u32TimeTicksUnit;

	Glob_u8AxisIndex++;
	Glob_u8AxisIndex %= POV_MAX_INDEX;

	POV_voidOffLEDS();

	Glob_u8isDisplay = TRUE;

	GIE_voidEnable();

}

void testTimerCallback() {

	GIE_voidDisable();

	Glob_u8AxisIndex++;
	Glob_u8AxisIndex %= POV_MAX_INDEX;

	POV_voidOffLEDS();

	Glob_u8isDisplay = TRUE;

	GIE_voidEnable();

}

int main() {

	/// init

	// DIO
	DIO_Init();
	//GIE
	GIE_voidEnable();
	// EXTI
	EXTI_voidInit(EXTIx_0, EXTI_Mode_Falling_Edge, detectMagnentCallback);
	EXTI_voidEnable(EXTIx_0);
	// TMR
	TMR1_voidInit(TMR1_Clk_By_8);
	TMR1_voidWaitAsync_us(733, TMR1_Mode_Circular, timerCallback);

	///end init

	while (1) {

		/// Update Time
		if (Glob_u32TimeTicksOneSecond >= TMR1_CONST_1_SEC) {
			Glob_u32TimeTicksOneSecond = 0;

			Glob_u8SecondHandIndex += 1;
			if (Glob_u8SecondHandIndex == 60) {
				Glob_u8SecondHandIndex = 0;

				Glob_u8MinuteHandIndex += 1;
				if (Glob_u8MinuteHandIndex == 60) {
					Glob_u8MinuteHandIndex = 0;

					Glob_u8HourHandIndex += 1;
					if (Glob_u8HourHandIndex == 60) {
						Glob_u8HourHandIndex = 0;
					}

				}

			}

		}

		/// if TRUE make a Display update
		if (Glob_u8isDisplay) {

			Glob_u8isDisplay = FALSE;
			/*
			 // todo :test : what happened if GIE disable in if(Glob_u8isDisplay)

			 /// Display Our Chars .............(TEST)..............
			 //			POV_voidDisplayChar(Glob_u8AxisIndex, 0, CHAR_WITH(hourHandChar),
			 //					hourHandChar);

			 //			POV_voidDisplayChar(Glob_u8AxisIndex, 1, CHAR_WITH(minuteHandChar),
			 //					minuteHandChar);
			 ////
			 //			POV_voidDisplayChar(Glob_u8AxisIndex, 2, CHAR_WITH(secondHandChar),
			 //					secondHandChar);
			 */
//		/// Display Our Chars
			POV_voidDisplayChar(Glob_u8AxisIndex, Glob_u8HourHandIndex,
					CHAR_WITH(hourHandChar), hourHandChar);

			POV_voidDisplayChar(Glob_u8AxisIndex, Glob_u8MinuteHandIndex,
					CHAR_WITH(minuteHandChar), minuteHandChar);

			POV_voidDisplayChar(Glob_u8AxisIndex, Glob_u8SecondHandIndex,
					CHAR_WITH(secondHandChar), secondHandChar);

///

		}

	}

	return 0;
}

#define POV_REMOTE_CONTROL_ID0_hourHand			0
typedef enum {
	POV_Remote_Control_ID0_Options_IncHour,
	POV_Remote_Control_ID0_Options_DecHour,

} POV_Remote_Control_ID0_Options_t;

#define POV_REMOTE_CONTROL_ID1_minuteHand		1
typedef enum {
	POV_Remote_Control_ID1_Options_IncMinute,
	POV_Remote_Control_ID1_Options_DecMinute,

} POV_Remote_Control_ID1_Options_t;

#define POV_REMOTE_CONTROL_ID2_secondHand		2
typedef enum {
	POV_Remote_Control_ID2_Options_IncSecond,
	POV_Remote_Control_ID2_Options_DecSecond,

} POV_Remote_Control_ID2_Options_t;

