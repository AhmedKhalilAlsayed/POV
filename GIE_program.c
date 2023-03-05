#include "newTypes.h"

#include "GIE_INTERFACE.h"
#include "GIE_PRIVATE.h"

void GIE_voidEnable(void){
	SET_BIT(GIE_u8_SREG, BIT7);
}

void GIE_voidDisable(void){
	CLR_BIT(GIE_u8_SREG, BIT7);
}
