#ifndef TWI_private_H_
#define TWI_private_H_

#define TWI_TWDR *((volatile u8*)0x23)

#define TWI_TWAR *((volatile u8*)0x22)

#define TWI_TWSR *((volatile u8*)0x21)

#define TWI_TWBR *((volatile u8*)0x20)

#define TWI_TWCR *((volatile u8*)0x56)

static u8 Private_CheckErrorState(TWI_ErrorState Copy_enuErrorState) ;

#endif
