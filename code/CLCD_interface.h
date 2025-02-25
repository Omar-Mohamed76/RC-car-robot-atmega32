#ifndef CLCD_interface_H_
#define CLCD_interface_H_

#include "STD_TYPES.h" // Ensure the standard types (u8, etc.) are defined
#include "BIT_MATH.h"  // Ensure the macros (SET_BIT, CLEAR_BIT, etc.) are included


void CLCD_voidInit(); //init ta48eel


void CLCD_voidSendString (char *PcCopy_String);

void CLCD_voidSetPosition(u8 Copy_u8X, u8 Copy_u8Y) ;

void CLCD_voidSendNum(u16 Copy_u16Num) ;

void CLCD_voidClearDisplay(void) ;

void CLCD_voidSendData(u8 Copy_u8Data);

void CLCD_voidSendCommand(u8 Copy_u8Command);

void CLCD_voidSendSpecialCharacter(u8 Copy_u8LockNum,u8*Pu8ArrayPattern , u8 Copy_u8X,u8 Copy_u8Y); //lock no feh no of block to take pointer

void CLCD_Send_Number(f32 f32_Number) ;

#endif
