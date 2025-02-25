#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "GI_interface.h"
#include "GI_private.h"


void GI_voidEnable(void)
{
	SET_BIT(SREG,GIE);
}
void GI_voidDisable(void)
{
	CLR_BIT(SREG,GIE);
}
