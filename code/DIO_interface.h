#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

#include "STD_TYPES.h" // Ensure the standard types (u8, etc.) are defined
#include "BIT_MATH.h"  // Ensure the macros (SET_BIT, CLEAR_BIT, etc.) are included

/* Function Prototypes */
void DIO_voidSetPortDirection(u8 Copy_u8PortNum, u8 Copy_u8PortDirection);
void DIO_voidSetPinDirection(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinDirection);

void DIO_voidSetPortValue(u8 Copy_u8PortNum, u8 Copy_u8PortValue);
void DIO_voidSetPinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinValue);

u8 DIO_u8GetPinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum);

void DIO_Set_Pin_Resistance(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 u8_Res);

void DIO_voidTogglePinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum);
void DIO_voidTogglePortValue(u8 Copy_u8PortNum);

u8 DIO_readPin(u8 Copy_u8PortNum, u8 Copy_u8PinNum);
void DIO_writePin(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8Value);

/* Pin Definitions */
#define PIN0       0
#define PIN1       1
#define PIN2       2
#define PIN3       3
#define PIN4       4
#define PIN5       5
#define PIN6       6
#define PIN7       7

/* Port Definitions */
#define PORT_u8A     1
#define PORT_u8B     2
#define PORT_u8C     3
#define PORT_u8D     4

/* Pin Directions */
#define PIN_OUT      1
#define PIN_IN       0

/* Pin Values */
#define PIN_HIGH     1
#define PIN_LOW      0

/* Port Values */
#define PORT_HIGH   0xFF
#define PORT_LOW    0x00

/* Port Directions */
#define PORT_OUT    0xFF
#define PORT_IN     0x00

/* Resistor States */
#define PULL_UP      0
#define FLOAT        1

#endif
