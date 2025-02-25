#ifndef EEPROM_interface_H_
#define EEPROM_interface_H_

void EEPROM_Init(void);

u8 EEPROM_u8WriteDataByte(u16 copy_u16ByteAddress,u8 Copy_u8Data) ;


u8 EEPROM_u8ReadDataByte(u16 copy_u16ByteAddress,u8 * Copy_pu8ReturnedData) ;





#endif
