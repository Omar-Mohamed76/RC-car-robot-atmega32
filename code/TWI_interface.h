#ifndef TWI_interface_H_
#define TWI_interface_H_

typedef enum
{
	TWI_OK = 1 ,
	TWI_SC_Error ,
	TWI_RSC_Error ,
	TWI_SLA_W_Error ,
	TWI_SLA_R_Error ,
	TWI_MASTER_TRANSMIT_DATA_ERROR ,
	TWI_NULL_POINTER ,
	TWI_MASTER_RECEIVE_DATA_ERROR

}TWI_ErrorState;


void TWI_voidMasterInit() ;

TWI_ErrorState TWI_u8SlaveInit(u8 Copy_u8Address) ;

TWI_ErrorState TWI_u8SendStartCondition(void);

TWI_ErrorState TWI_u8SendReStartCondition(void);

TWI_ErrorState TWI_u8SendStopCondition(void);

TWI_ErrorState TWI_u8SendSlaveAddWithWrite(u8 Copy_u8Address) ;

TWI_ErrorState TWI_u8SendSlaveAddWithRead(u8 Copy_u8Address) ;

TWI_ErrorState TWI_u8SendDataByte(u8 Copy_u8DataByte) ;

TWI_ErrorState TWI_u8ReadDataByte(u8 *Copypu8ReturnedDataByte) ;




#endif 
