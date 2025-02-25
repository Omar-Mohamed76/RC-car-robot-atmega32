#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "TWI_interface.h"
#include "TWI_config.h"
#include "TWI_private.h"


void TWI_voidMasterInit()
{
	// set pre scaler value
	CLR_BIT (TWI_TWSR,1);
	CLR_BIT (TWI_TWSR,0);
	// SetTWBR >= 200 KHZ
	TWI_TWBR = 12 ;
	// Enable Ack
	SET_BIT(TWI_TWCR,6);
	// Enable I2c
	SET_BIT(TWI_TWCR,2);
}

TWI_ErrorState TWI_u8SlaveInit(u8 Copy_u8Address)

{
	TWI_ErrorState Local_u8ErrorState = OK ;
	// SetSlaveAdd In TWAR
	TWI_TWAR = Copy_u8Address << 1 ;
	// Enable ACk
	SET_BIT(TWI_TWCR,6);
	// Enable I2c
	SET_BIT(TWI_TWCR,2);
	return Local_u8ErrorState ;
}

TWI_ErrorState TWI_u8SendStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// CLear FLag And Start Condition
	SET_BIT(TWI_TWCR,7) ;
	SET_BIT(TWI_TWCR,5) ;
	// wait for the flag to be 1
	while (!GET_BIT(TWI_TWCR,7)) ;
	// check Status Code
	if ((TWI_TWSR & 0XF8) != 0X08)
	{
		Local_enuErrorState = TWI_SC_Error ;
	}
	// Clear Start Condition Bit
	SET_BIT(TWI_TWCR,5) ;
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8SendReStartCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// CLear FLag And Start Condition
	SET_BIT(TWI_TWCR,7) ;
	SET_BIT(TWI_TWCR,5) ;
	// wait for the flag to be 1
	while (!GET_BIT(TWI_TWCR,7)) ;
	// check Status Code
	if ((TWI_TWSR & 0XF8) != 0X10)
	{
		Local_enuErrorState = TWI_RSC_Error ;
	}
	// Clear Start Condition Bit
	SET_BIT(TWI_TWCR,5) ;
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8SendStopCondition(void)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// Clear Flag And Stop Condition
	SET_BIT(TWI_TWCR,7) ;
	SET_BIT(TWI_TWCR,4) ;
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8SendSlaveAddWithWrite(u8 Copy_u8Address)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// write slave add plus Zero TWDR
	TWI_TWDR = Copy_u8Address << 1 ;
	CLR_BIT(TWI_TWDR,0) ;
	// CLear FLag
	SET_BIT(TWI_TWCR,7) ;
	while (!GET_BIT(TWI_TWCR,7)) ;
	// check Status Code
	if ((TWI_TWSR & 0XF8) != 0X18)
	{
		Local_enuErrorState = TWI_SLA_W_Error ;
	}
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8SendSlaveAddWithRead(u8 Copy_u8Address)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// write slave add plus Zero TWDR
	TWI_TWDR = Copy_u8Address << 1 ;
	SET_BIT(TWI_TWDR,0) ;
	// CLear FLag
	SET_BIT(TWI_TWCR,7) ;
	while (!GET_BIT(TWI_TWCR,7)) ;
	// check Status Code
	if ((TWI_TWSR & 0XF8) != 0X40)
	{
		Local_enuErrorState = TWI_SLA_R_Error ;
	}
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8SendDataByte(u8 Copy_u8DataByte)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// write slave add plus Zero TWDR
	TWI_TWDR = Copy_u8DataByte << 1 ;
	// CLear FLag
	SET_BIT(TWI_TWCR,7) ;
	// waiting for flag
	while (!GET_BIT(TWI_TWCR,7)) ;
	// check Status Code
	if ((TWI_TWSR & 0XF8) != 0X28)
	{
		Local_enuErrorState = TWI_MASTER_TRANSMIT_DATA_ERROR ;
	}
	return Local_enuErrorState ;
}

TWI_ErrorState TWI_u8ReadDataByte(u8 *Copypu8ReturnedDataByte)
{
	TWI_ErrorState Local_enuErrorState = TWI_OK ;
	// check pointer
	if (Copypu8ReturnedDataByte != NULL)
	{
		// clear flag
		SET_BIT(TWI_TWCR,7) ;
		// wait for the flag to be 1
		while (!GET_BIT(TWI_TWCR,7)) ;
		// check Status Code
		if ((TWI_TWSR & 0XF8) != 0X50)
		{
			Local_enuErrorState = TWI_MASTER_RECEIVE_DATA_ERROR ;
		}
		else
		{
			*Copypu8ReturnedDataByte = TWI_TWDR ;
		}
	}
	else
	{
		TWI_ErrorState Local_enuErrorState = TWI_NULL_POINTER ;
	}
	return Local_enuErrorState ;
}


