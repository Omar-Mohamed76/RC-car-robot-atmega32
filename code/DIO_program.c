
#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "DIO_interface.h"
#include "DIO_config.h"
#include "DIO_private.h"

void DIO_voidSetPortDirection(u8 Copy_u8PortNum,u8 
Copy_u8PortDirection)
{
	switch(Copy_u8PortNum)
	{
		case PORT_u8A:DDRA=Copy_u8PortDirection;
		break;
		case PORT_u8B:DDRB=Copy_u8PortDirection;
		break;
		case PORT_u8C:DDRC=Copy_u8PortDirection;
		break;
		case PORT_u8D:DDRD=Copy_u8PortDirection;
		break;
	}
}
void DIO_voidSetPinDirection(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 
Copy_u8PinDirection)
{
	if(Copy_u8PinDirection==PIN_OUT)
	{
		switch(Copy_u8PortNum)
		{
			case PORT_u8A:SET_BIT(DDRA,Copy_u8PinNum);
			break;
			case PORT_u8B:SET_BIT(DDRB,Copy_u8PinNum);
			break;
			case PORT_u8C:SET_BIT(DDRC,Copy_u8PinNum);
			break;
			case PORT_u8D:SET_BIT(DDRD,Copy_u8PinNum);
			break;
		}
	}
	else if(Copy_u8PinDirection==PIN_IN)
	{
		switch(Copy_u8PortNum)
		{
			case PORT_u8A:CLR_BIT(DDRA,Copy_u8PinNum);
			break;
			case PORT_u8B:CLR_BIT(DDRB,Copy_u8PinNum);
			break;
			case PORT_u8C:CLR_BIT(DDRC,Copy_u8PinNum);
			break;
			case PORT_u8D:CLR_BIT(DDRD,Copy_u8PinNum);
			break;
		}
	}
}

void DIO_voidSetPortValue(u8 Copy_u8PortNum,u8 Copy_u8PortValue)
{
	switch(Copy_u8PortNum)
	{
		case PORT_u8A:PORTA=Copy_u8PortValue;
		break;
		case PORT_u8B:PORTB=Copy_u8PortValue;
		break;
		case PORT_u8C:PORTC=Copy_u8PortValue;
		break;
		case PORT_u8D:PORTD=Copy_u8PortValue;
		break;
	}
}
void DIO_voidSetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 
Copy_u8PinValue)
{
	if(Copy_u8PinValue==PIN_HIGH)
	{
		switch(Copy_u8PortNum)
		{
			case PORT_u8A:SET_BIT(PORTA,Copy_u8PinNum);
			break;
			case PORT_u8B:SET_BIT(PORTB,Copy_u8PinNum);
			break;
			case PORT_u8C:SET_BIT(PORTC,Copy_u8PinNum);
			break;
			case PORT_u8D:SET_BIT(PORTD,Copy_u8PinNum);
			break;
		}
	}
	else if(Copy_u8PinValue==PIN_LOW)
	{
		switch(Copy_u8PortNum)
		{
			case PORT_u8A:CLR_BIT(PORTA,Copy_u8PinNum);
			break;
			case PORT_u8B:CLR_BIT(PORTB,Copy_u8PinNum);
			break;
			case PORT_u8C:CLR_BIT(PORTC,Copy_u8PinNum);
			break;
			case PORT_u8D:CLR_BIT(PORTD,Copy_u8PinNum);
			break;
		}
	}
}

u8 DIO_u8GetPinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum)
{
	u8 Local_u8PinState=0;
	switch(Copy_u8PortNum)
	{
		case PORT_u8A:Local_u8PinState=GET_BIT(PINA,Copy_u8PinNum);
		break;
		case PORT_u8B:Local_u8PinState=GET_BIT(PINB,Copy_u8PinNum);
		break;
		case PORT_u8C:Local_u8PinState=GET_BIT(PINC,Copy_u8PinNum);
		break;
		case PORT_u8D:Local_u8PinState=GET_BIT(PIND,Copy_u8PinNum);
		break;
	}
	
	return Local_u8PinState;
}

void DIO_voidTogglePinValue(u8 Copy_u8PortNum,u8 Copy_u8PinNum){
    if(DIO_u8GetPinValue(Copy_u8PortNum,Copy_u8PinNum)==0){
         DIO_voidSetPinValue(Copy_u8PortNum,Copy_u8PinNum,PIN_HIGH);
    }else if(DIO_u8GetPinValue(Copy_u8PortNum,Copy_u8PinNum)==1){
        DIO_voidSetPinValue(Copy_u8PortNum,Copy_u8PinNum,PIN_LOW);
    }
}

void DIO_voidTogglePortValue(u8 Copy_u8PortNum){
    for (u8 pin = 0; pin < 8; pin++) {
    	DIO_voidTogglePinValue(Copy_u8PortNum,pin);
    }
}

void DIO_Set_Pin_Resistance(u8 Copy_u8PortNum,u8 Copy_u8PinNum,u8 u8_Res)
 {
	 switch(Copy_u8PortNum)
	 {
		 case PORT_u8A:
		 switch(u8_Res)
		 {
		 case PULL_UP:
		 SET_BIT(PORTA,Copy_u8PinNum);
		 break;
		 case FLOAT:
			 CLR_BIT(PORTA,Copy_u8PinNum);
		 break;
		 }
		 break;
		 case PORT_u8B:
		 switch(u8_Res)
		 {
		 case PULL_UP:
			 SET_BIT(PORTB,Copy_u8PinNum);
		 break;
		 case FLOAT :
			 CLR_BIT(PORTB,Copy_u8PinNum);
		 break;
		 }
		 break;
		  
		  case PORT_u8C:
		 switch(u8_Res)
		 {
		 case PULL_UP:
			 SET_BIT(PORTC,Copy_u8PinNum);
		 break;
		 case FLOAT :
			 CLR_BIT(PORTC,Copy_u8PinNum);
		 break;
		 }
		 break;
		 
		 case PORT_u8D:
		 switch(u8_Res)
		 {
		 case PULL_UP:
			 SET_BIT(PORTD,Copy_u8PinNum);
		 break;
		 case FLOAT :
		 CLR_BIT(PORTD,Copy_u8PinNum);
		 break;
		 }
		 break;
		 default:
		 break;
	 }
	 
 }

u8 DIO_readPin(u8 Copy_u8PortNum, u8 Copy_u8PinNum)
{
    u8 Local_u8PinState = PIN_LOW; // Default value is low

    if (Copy_u8PinNum < 8) // Ensure pin number is valid
    {
        switch (Copy_u8PortNum)
        {
            case PORT_u8A:
                Local_u8PinState = GET_BIT(PINA, Copy_u8PinNum);
                break;
            case PORT_u8B:
                Local_u8PinState = GET_BIT(PINB, Copy_u8PinNum);
                break;
            case PORT_u8C:
                Local_u8PinState = GET_BIT(PINC, Copy_u8PinNum);
                break;
            case PORT_u8D:
                Local_u8PinState = GET_BIT(PIND, Copy_u8PinNum);
                break;
            default:
                // Invalid port, do nothing
                break;
        }
    }

    return Local_u8PinState;
}

void DIO_writePin(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8Value)
{
    if (Copy_u8PinNum < 8) // Ensure pin number is valid
    {
        switch (Copy_u8PortNum)
        {
            case PORT_u8A:
                if (Copy_u8Value == PIN_LOW)
                {
                    CLR_BIT(PORTA, Copy_u8PinNum);
                }
                else
                {
                    SET_BIT(PORTA, Copy_u8PinNum);
                }
                break;
            case PORT_u8B:
                if (Copy_u8Value == PIN_LOW)
                {
                    CLR_BIT(PORTB, Copy_u8PinNum);
                }
                else
                {
                    SET_BIT(PORTB, Copy_u8PinNum);
                }
                break;
            case PORT_u8C:
                if (Copy_u8Value == PIN_LOW)
                {
                    CLR_BIT(PORTC, Copy_u8PinNum);
                }
                else
                {
                    SET_BIT(PORTC, Copy_u8PinNum);
                }
                break;
            case PORT_u8D:
                if (Copy_u8Value == PIN_LOW)
                {
                    CLR_BIT(PORTD, Copy_u8PinNum);
                }
                else
                {
                    SET_BIT(PORTD, Copy_u8PinNum);
                }
                break;
            default:
                // Invalid port, do nothing
                break;
        }
    }
}

