#include "newTypes.h"

#include "DIO_interface.h"

#include "POV_interface.h"
#include "POV_config.h"

#define MODULUS(N, MOD) ((((N)%(MOD))+(MOD))%(MOD))

static const u8 Glob_u8arrLED_PORTS[] = POV_LEDS_PORTS_ARR;
static const u8 Glob_u8arrLED_PINS[] = POV_LEDS_PINS_ARR;

void POV_voidDisplayChar(u8 Copy_u8CurrentIndex, u8 Copy_u8CenterOffset,
		u8 Copy_u8CharWidth, const u8 **Copy_u8PtrArrChar) {

	static u8 Local_u8leftBoundaryIndex;
	static u8 Local_u8CurrentCol;

	Local_u8leftBoundaryIndex = MODULUS(Copy_u8CenterOffset - (Copy_u8CharWidth / 2), POV_MAX_INDEX);
	Local_u8CurrentCol = MODULUS(Copy_u8CurrentIndex - Local_u8leftBoundaryIndex, POV_MAX_INDEX);

	// within the wanted range

	if (Local_u8CurrentCol < Copy_u8CharWidth) {

		for (u8 i = 0; i < sizeof Glob_u8arrLED_PINS; i++) {
			if (Copy_u8PtrArrChar[Local_u8CurrentCol][i] == POV_LED_STOP/*break*/) {
				break;
			}

			DIO_u8SetPinValue(
					Glob_u8arrLED_PORTS[Copy_u8PtrArrChar[Local_u8CurrentCol][i]
							- 1],
					Glob_u8arrLED_PINS[Copy_u8PtrArrChar[Local_u8CurrentCol][i]
							- 1], 1);

		}
	}

}

void POV_voidOffLEDS(void) {

	for (register u8 ledIndex = 0; ledIndex < sizeof Glob_u8arrLED_PINS; ledIndex++) {
		DIO_u8SetPinValue(Glob_u8arrLED_PORTS[ledIndex], Glob_u8arrLED_PINS[ledIndex], 0);
	}
}

//////////////////////////////////////////	OLD

//void POV_voidDisplayChar(u8 Copy_u8CurrentIndex, u8 Copy_u8CenterOffset,
//		u8 Copy_u8CharRows, u8 Copy_u8CharCols,
//		u8 (*Copy_u8arrChar)[Copy_u8CharCols]) {
//
//	// within the wanted range
//
//	if ((Copy_u8CurrentIndex >= (Copy_u8CenterOffset - (Copy_u8CharCols / 2)))
//			&& (Copy_u8CurrentIndex
//					<= (Copy_u8CenterOffset + (Copy_u8CharCols / 2)))) {
//
//		static u8 temp_u8leftBoundary;
//		static u8 temp_u8CurrentCol;
//
//		temp_u8leftBoundary = Copy_u8CenterOffset - (Copy_u8CharCols / 2);
//		temp_u8CurrentCol = Copy_u8CurrentIndex - temp_u8leftBoundary;
//
//		for (u8 row_LED = 0; row_LED < Copy_u8CharRows; row_LED++) {
//
//			DIO_u8SetPinValue(glob_u8arrLED_PORTS[row_LED] - 1,
//					glob_u8arrLED_PINS[row_LED] - 1, 1);
//
////			if (Copy_u8arrChar[row_LED][temp_u8CurrentCol] != 0) {
////				DIO_u8SetPinValue(glob_u8arrLED_PORTS[row_LED], glob_u8arrLED_PINS[row_LED], 1);
////			}
//		}
//
//	}
//
//}
