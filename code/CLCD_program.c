#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "CLCD_interface.h"
#include "CLCD_private.h"
#include "CLCD_config.h"
#include <util/delay.h>


void CLCD_voidSendData(u8 Copy_u8Data)
{
	//RS->1   ,RW=0
	DIO_voidSetPinValue(CTRL_PORT,RS,PIN_HIGH);
	DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Set Data -> data port
	DIO_voidSetPortValue(DATA_PORT,Copy_u8Data);
	//enable pulse
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_LOW);
}
void CLCD_voidSendCommand(u8 Copy_u8Command)
{
	//RS->0   ,RW=0
	DIO_voidSetPinValue(CTRL_PORT,RS,PIN_LOW);
	DIO_voidSetPinValue(CTRL_PORT,RW,PIN_LOW);
	//Set Data -> data port
	DIO_voidSetPortValue(DATA_PORT,Copy_u8Command);
	//enable pulse
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT,EN,PIN_LOW);
}

void CLCD_voidInit(void)
{
	
    DIO_voidSetPortDirection(DATA_PORT, PORT_OUT);
    DIO_voidSetPinDirection(CTRL_PORT, RW, PIN_OUT);
    DIO_voidSetPinDirection(CTRL_PORT, RS, PIN_OUT);
    DIO_voidSetPinDirection(CTRL_PORT, EN, PIN_OUT);	

	_delay_ms(40);
	CLCD_voidSendCommand(0b00111000);
	_delay_ms(1);
	CLCD_voidSendCommand(0b00001100);
	_delay_ms(1);
	CLCD_voidSendCommand(1);
	_delay_ms(2);
}

void CLCD_voidSendString (char *PcCopy_String)
{
	u8 Local_u8Iterator=0 ;
	while (PcCopy_String[Local_u8Iterator]!='\0')
	{
		CLCD_voidSendData(PcCopy_String[Local_u8Iterator]);
		Local_u8Iterator ++ ;
	}
}

void CLCD_voidSetPosition (u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 Local_u8Position=0 ;
	switch (Copy_u8Y)
	{
	case 0 : Local_u8Position = Copy_u8X ; break ;
	case 1 : Local_u8Position = Copy_u8X+LINE1_BASE ; break ;
	}
	CLCD_voidSendCommand(Local_u8Position+128) ; // set DDRAM address

}

void CLCD_voidClearDisplay(void)
{
	CLCD_voidSendCommand(1) ;
}
void CLCD_voidSendSpecialCharacter(u8 Copy_u8LockNum,u8*Pu8ArrayPattern , u8 Copy_u8X,u8 Copy_u8Y)
{
	// go to cgram ->cmd set cgram address
	u8 Local_u8Position =Copy_u8LockNum*8 ;
	CLCD_voidSendCommand(Local_u8Position+CGRAM_MSB) ;

	//start drawing pattern
	for (u8 i=0 ; i<8 ; i++)
	{
		CLCD_voidSendData (Pu8ArrayPattern[i]) ; // p is pointer for lock num
	}
	//display pattern
	CLCD_voidSetPosition( Copy_u8X, Copy_u8Y) ;
	CLCD_voidSendData(Copy_u8LockNum) ;
}
void CLCD_voidSendNum(u16 Copy_u16Num)
{
	u8 arr[10],i=0,j;

	if(Copy_u16Num==0)
	{
		CLCD_voidSendData('0');
	}
	else
	{
		while(Copy_u16Num)
		{
			arr[i]=	Copy_u16Num%10 +'0';
			Copy_u16Num/=10;
			i++;
		}
	}
	for(j=i;j>0;j--)
	{
		CLCD_voidSendData(arr[j-1]);
	}
}

void CLCD_Send_Number(f32 f32_Number)
{
	u32 u32_Number=f32_Number;
	u32 dot=f32_Number;
	u32 flag=0;
	u8 c=0;
	if(u32_Number<10)
	{
		CLCD_voidSendData(u32_Number+48);
	}
	else
	{


		do
		{
			flag=10*flag+u32_Number%10;
			u32_Number/=10;
			if(flag==0)c++;
		}
		while(u32_Number!=0);
		u32_Number=flag;
		do
		{

			CLCD_voidSendData((u32_Number%10)+48);
			u32_Number=u32_Number/10;
		}
		while(u32_Number!=0);
		while(c>0)
		{
			CLCD_voidSendData('0');
			c--;

		}

		/* */

	}
	if(dot<f32_Number)
	{
		CLCD_voidSendData('.');
		u32_Number=(f32_Number*100-dot*100);
		do
		{
			flag=10*flag+u32_Number%10;
			u32_Number/=10;
		}
		while(u32_Number!=0);
		u32_Number=flag;

		for( c=0;c<2;c++)
		{
			CLCD_voidSendData((u32_Number%10)+48);
			u32_Number=u32_Number/10;
		}
	}

}














