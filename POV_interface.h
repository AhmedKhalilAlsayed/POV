/*
 * POV_interface.h
 *
 *  Created on: Jul 31, 2022
 *      Author: Mega Store
 */

#ifndef POV_INTERFACE_H_
#define POV_INTERFACE_H_

// Can choose the scale (act as pexels)
#define POV_INDEX_SCALE				1

#ifndef POV_INDEX_SCALE
#define POV_INDEX_SCALE				1
#endif

// The max index can be reached
#define POV_MAX_INDEX	(POV_INDEX_SCALE*60)

// Should be at the end of array
#define POV_LED_STOP	0

// LED IDs
#define POV_LED1		1
#define POV_LED2		2
#define POV_LED3		3
#define POV_LED4		4
#define POV_LED5		5
#define POV_LED6		6
#define POV_LED7		7
#define POV_LED8		8
#define POV_LED9		9
#define POV_LED10		10
#define POV_LED11		11
#define POV_LED12		12
#define POV_LED13		13
#define POV_LED14		14
#define POV_LED15		15
#define POV_LED16		16
#define POV_LED17		17
#define POV_LED18		18
#define POV_LED19		19

/*
 * How to Write a Char to be displayed:
 *
 * 	myCharCol0 array = {............ , POV_LED_STOP 'to stop'}
 * 	myCharCol1 array = {............ , POV_LED_STOP 'to stop'}
 * 	myCharCol2 array = {............ , POV_LED_STOP 'to stop'}
 * 	and complete your char as cols
 *
 * then add all of them to one array >>> myChar[]
 *
 *************/

/* POV_voidDisplayChar()
 * Desc:
 * you can easily display a char with make an array of needed ON LEDs only, and it's position ('center offset')
 * Retun:
 *  void
 * Pars:
 *  Copy_u8CurrentIndex: the current index(position) in the clock
 * 	Copy_u8CenterOffset: the index of your char to be displayed
 * 	Copy_u8CharWidth: the width of char (the number of cols)
 * 	Copy_u8arrChar: the CHAR
 **************/
void POV_voidDisplayChar(u8 Copy_u8CurrentIndex, u8 Copy_u8CenterOffset,
		u8 Copy_u8CharWidth, const u8 **Copy_u8PtrArrChar);

/* POV_voidOffLEDS()
 * Desc:
 * 	off all LEDs
 *
 *********/
void POV_voidOffLEDS(void);

#endif /* POV_INTERFACE_H_ */
