/*
 * TMR_private.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */

#ifndef TMR_PRIVATE_H_
#define TMR_PRIVATE_H_

//typedef struct {
//	volatile u8 TIMSK;
//	volatile u8 TIFR;
//	volatile u8 res[9];
//	volatile u8 TCCR1A;
//	volatile u8 TCCR1B;
//	volatile u16 TCNT1;
//	volatile u16 OCR1A;
//	volatile u16 OCR1B;
//	volatile u16 ICR1;
//} TMR1_Reg_t;

typedef struct {

	volatile u16 ICR1;
	volatile u16 OCR1B;
	volatile u16 OCR1A;
	volatile u16 TCNT1;
	volatile u8 TCCR1B;
	volatile u8 TCCR1A;
	volatile u8 res[8];
	volatile u8 TIFR;
	volatile u8 TIMSK;

} TMR1_Reg_t;

#define TMR1_MAX_TICKS		65536UL

#define TMR1_REG_ADDRESS		0x46

#define TMR1_REG	((volatile TMR1_Reg_t*) TMR1_REG_ADDRESS)

#endif /* TMR_PRIVATE_H_ */
