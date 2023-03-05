/*
 * EXTI_private.h
 *
 *  Created on: Sep 4, 2022
 *      Author: Mega Store
 */

#ifndef EXTI_PRIVATE_H_
#define EXTI_PRIVATE_H_
/*
 typedef struct {

 volatile u8 MCUCSR;
 volatile u8 MCUCR;
 volatile u32 res;
 volatile u8 GIFR;
 volatile u8 GICR;

 } EXTI_Reg_t;
 */
typedef struct {

	volatile u8 MCUCSR;
	volatile u8 MCUCR;
	volatile u8 res[4];
	volatile u8 GIFR;
	volatile u8 GICR;

} EXTI_Reg_t;

#define EXTI_REG_ADDRESS		0x54
#define EXTI_REG ((volatile EXTI_Reg_t*)EXTI_REG_ADDRESS)

#endif /* EXTI_PRIVATE_H_ */
