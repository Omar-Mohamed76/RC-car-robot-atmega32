#ifndef uart_interface
#define uart_interface
#include "STD_TYPES.h"
#include "BIT_MATH.h"
void UART_voidInitial(void);

void UART_voidSendData(u8 Copy_u8Data);

u8 UART_u8RecieveData(u8 *Copy_pu8Data);



#endif
