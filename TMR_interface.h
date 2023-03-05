/*
 * TMR_interface.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */

#ifndef TMR_INTERFACE_H_
#define TMR_INTERFACE_H_

#define TMR1_CONST_1_MILLI_SEC 	1000UL
#define TMR1_CONST_1_SEC 		1000000UL
#define TMR1_CONST_1_MINUTE 	60000000UL
#define TMR1_CONST_1_HOUR   	3600000000UL

typedef enum {

	TMR1_Clk_No_Clk,
//	TMR1_Clk_By_1,
	TMR1_Clk_By_8 = 2,
//	TMR1_Clk_By_64,
//	TMR1_Clk_By_256,
//	TMR1_Clk_By_1024,

} TMR1_Clk_t;

typedef enum {

	TMR1_Mode_Circular, TMR1_Mode_Once, TMR1_Mode_None

} TMR1_Mode_t;

typedef void (*TMR_voidCallbackVoid)(void);

void TMR1_voidInit(TMR1_Clk_t Copy_enumTMR1_Clk);

// todo : need more test
u32 TMR1_u32GetTime();

void TMR1_voidWaitAsync_us(u32 Copy_u32TimeUs, TMR1_Mode_t Copy_enumMode,
		TMR_voidCallbackVoid callback);

#endif /* TMR_INTERFACE_H_ */
