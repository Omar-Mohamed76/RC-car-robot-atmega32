#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "uart_config.h"
#include "uart_interface.h"
#include "uart_private.h"


void UART_voidInitial(void)
{
	u8 Local_u8UCSRCValue = 0b10000000; 
	/*Select Baud Rate 9600*/
	u16 Local_u16UBRRValue = UART_u16_UBRR_VALUE;
	UBRRL_u8_REG = (u8)Local_u16UBRRValue;
	UBRRH_u8_REG = (u8)(Local_u16UBRRValue>>8);
	/*Enable TX*/
	SET_BIT(UCSRB_u8_REG,4);
	/*Enable RX*/
	SET_BIT(UCSRB_u8_REG,3);
	/*Select Character Size 8Bit*/
	CLR_BIT(UCSRB_u8_REG,2);
	SET_BIT(Local_u8UCSRCValue,2);
	SET_BIT(Local_u8UCSRCValue,1);
	/*Select Mode */ 
	switch(UART_u8_MODE)
	{
		case(UART_u8_ASYNCH):
		{
			CLR_BIT(Local_u8UCSRCValue,6);
			break;
		}
		case(UART_u8_SYNCH):
		{
			SET_BIT(Local_u8UCSRCValue,6);
			break;
		}
	}
	switch(UART_u8_PARITY_MODE)
	{
		case(UART_u8_DISABLE_PARITY):
		{
			CLR_BIT(Local_u8UCSRCValue,5);
			CLR_BIT(Local_u8UCSRCValue,4);
			break;
		}
		case(UART_u8_EVEN):
		{
			SET_BIT(Local_u8UCSRCValue,5);
			CLR_BIT(Local_u8UCSRCValue,4);
			break;
		}
		case(UART_u8_ODD):
		{
			SET_BIT(Local_u8UCSRCValue,5);
			SET_BIT(Local_u8UCSRCValue,4);
			break;
		}
	}
	/* Select Numbers of Stop Bit */
	switch(UART_u8_STOP_BIT_NO)
	{
		case(1):
		{
			CLR_BIT(Local_u8UCSRCValue,3);
			break;
		}
		case(2):
		{
			SET_BIT(Local_u8UCSRCValue,3);
			break;
		}
	}
	/* Put the value of Local_u8UCSRCValue in UCSRC_u8_Reg*/
	UCSRC_u8_REG = Local_u8UCSRCValue;
}
void UART_voidSendData(u8 Copy_u8Data)
{
	/* Check if TX buffer is empty */
	while((GET_BIT(UCSRA_u8_REG,5))==0);
	UDR_u8_REG = Copy_u8Data;
}
u8 UART_u8RecieveData(u8 *Copy_pu8Data)
{
	u8 Local_u8ReturnedState = OK;
	if(Copy_pu8Data != NULL)
	{
		while((GET_BIT(UCSRA_u8_REG,7))==0);
		*Copy_pu8Data = UDR_u8_REG;
	}
	else
	{
		Local_u8ReturnedState = NOK;
	}
	return Local_u8ReturnedState;
}
