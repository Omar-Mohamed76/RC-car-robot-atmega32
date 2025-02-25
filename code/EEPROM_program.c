#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include <util/delay.h>
#include "TWI_interface.h"
#include "EEPROM_interface.h"
#include "EEPROM_private.h"
#include "EEPROM_config.h"
#include "DIO_interface.h"

// EEPROM initialization function
void EEPROM_Init(void)
{
    // Set SCK and SDA as output pins
	DIO_voidSetPinDirection(EEPROM_PORT, SCK_PIN,PIN_OUT);  // Set SCK_PIN as output
	DIO_voidSetPinDirection(EEPROM_PORT, SDA_PIN,PIN_OUT);  // Set SDA_PIN as output

    // You can also initialize SDA and SCK to a known state if needed
    DIO_writePin(EEPROM_PORT, SCK_PIN,PIN_LOW);  // SCK = LOW
    DIO_writePin(EEPROM_PORT, SDA_PIN,PIN_LOW);  // SDA = LOW
}

// Other EEPROM functions would utilize the configuration defined above

TWI_ErrorState EEPROM_u8WriteDataByte(u16 copy_u16ByteAddress,u8 Copy_u8Data)
{
	u8 Local_u8ErrorState = OK ;
	TWI_ErrorState Local_enuTWIErrorState = TWI_OK ;
	// send start condition
	Local_enuTWIErrorState = TWI_u8SendStartCondition() ;
	Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
	// send slave address with write operation
	TWI_u8SendSlaveAddWithWrite(EEPROM_u8FixedAddress | EEPROM_u8A2Address<< 2 |copy_u16ByteAddress >> 8)  ;
	Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
	// Send Byte Address
	Local_enuTWIErrorState = TWI_u8SendDataByte((u8)copy_u16ByteAddress) ;
	Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
	// Send Data
	Local_enuTWIErrorState = TWI_u8SendDataByte(Copy_u8Data) ;
	Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
	// Stop Condition
	TWI_u8SendStopCondition() ;
	// Delay
	_delay_ms(5);
	return Local_u8ErrorState ;
}



TWI_ErrorState EEPROM_u8ReadDataByte(u16 copy_u16ByteAddress,u8 * Copy_pu8ReturnedData)
{
	u8 Local_u8ErrorState = OK ;
	TWI_ErrorState Local_enuTWIErrorState = TWI_OK ;
	// check pointer
	if (Copy_pu8ReturnedData != NULL)
	{
		// send start condition
		Local_enuTWIErrorState = TWI_u8SendStartCondition() ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// send slave address with write operation
		TWI_u8SendSlaveAddWithWrite(EEPROM_u8FixedAddress | EEPROM_u8A2Address<< 2 |copy_u16ByteAddress >> 8)  ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// Send Byte Address
		Local_enuTWIErrorState = TWI_u8SendDataByte((u8)copy_u16ByteAddress) ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// send repeated start condition
		Local_enuTWIErrorState = TWI_u8SendReStartCondition() ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// send slave address with Read operation
		TWI_u8SendSlaveAddWithRead(EEPROM_u8FixedAddress | EEPROM_u8A2Address<< 2 |copy_u16ByteAddress >> 8)  ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// Read Data
		Local_enuTWIErrorState =TWI_u8ReadDataByte(Copy_pu8ReturnedData) ;
		Local_u8ErrorState = Private_u8CheckErrorState(Local_enuTWIErrorState) ;
		// Stop Condition
		TWI_u8SendStopCondition() ;
		// Delay
		_delay_ms(5);
	}
	else
	{
		Local_u8ErrorState = NOK ;
	}
	return Local_u8ErrorState ;
}

static u8 Private_u8CheckErrorState(TWI_ErrorState Copy_enuErrorState)
{
	u8 Local_u8ErrorState = OK ;
	if (Copy_enuErrorState != TWI_OK)
	{
		Local_u8ErrorState = NOK ;
	}
	return Local_u8ErrorState ;
}
















