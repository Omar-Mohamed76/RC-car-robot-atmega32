#include "BIT_MATH.h"
#include "STD_TYPES.h"
#include "DIO_interface.h"
#include "motor.h"
#include "ultrasonic.h"
#include "movement.h"
#include "uart_interface.h"
#include "CLCD_interface.h"
#include "EEPROM_interface.h"
#include <util/delay.h>
void obstacle_counting(f64 distance);

#define F_CPU 8000000UL
u16 obstacle_counter = 0;

// Global variable to store the current mode
u8 current_mode = 0;	// 0 = Manual, 1 = Autonomous
u16 obstacle_count = 0; // Variable to store the number of obstacles detected
// Function to select initial mode before startup
u8 Get_Mode(void);
void Initial_Mode(void);
void RC_mode(void);
void ULTRA_mode(void);
void Log_Data(f64 distance);
// Main Function
int main(void)
{
	Initial_Mode();
	_delay_ms(100);
	CLCD_voidClearDisplay();

	CLCD_voidSetPosition(0, 0);
	CLCD_voidSendString("Select Mode:");
	DIO_voidSetPinDirection(PORT_u8D, PIN2, PIN_IN);
	DIO_voidSetPinValue(PORT_u8D, PIN2, PIN_HIGH); // Enable internal pull-up resistor
	while (1)
	{
		CLCD_voidSetPosition(0, 0);

		// Check Mode Selection
		if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0)
		{				   // Button pressed
			_delay_ms(50); // Debounce
			if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0)
			{

				// Display selected mode
				CLCD_voidSetPosition(0, 1);
				if (current_mode == 0)
				{
					CLCD_voidSendString("Manual Mode    ");
					_delay_ms(100);
					CLCD_voidClearDisplay();
					_delay_ms(100);

					do
					{
						RC_mode();
					}
					while (current_mode == 0);

				}
				else
				{
					CLCD_voidSendString("Autonomous Mode");
					_delay_ms(100);
					CLCD_voidClearDisplay();
					_delay_ms(100);
					do{
						ULTRA_mode();
					}
					while (current_mode != 0);
				}

				// Wait for button release
				while (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0);
				_delay_ms(200);
			}
		}

		// Exit mode selection if button is long pressed
		if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0)
		{
			_delay_ms(1000); // Long press duration
			if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0)
			{
				break; // Exit mode selection
			}
		}
		// RC_mode();
		// ULTRA_mode();
	}
	return 1;
}

void Initial_Mode(void)
{
	_delay_ms(50);
	CLCD_voidInit();
	_delay_ms(100);
	Motor_Init();
	UART_voidInitial();
	Ultrasonic_Init();
	EEPROM_Init();
}

void RC_mode(void)
{
	CLCD_voidClearDisplay();
	_delay_ms(50);
	CLCD_voidSetPosition(0, 0);
	CLCD_voidSendString("Mode: RC");
	u8 command;
	UART_u8RecieveData(&command); // Receive data from Bluetooth

	switch (command)
	{
	case 'F': // Forward
		Move_Forward();
		break;
	case 'B': // Backward
		Move_Backward();
		break;
	case 'L': // Left
		Move_Left();
		break;
	case 'R': // Right
		Move_Right();
		break;
	case 'S': // Stop
		stop();
		break;
	case 'D': // Switch to ULTRA mode
		current_mode = 1;
		ULTRA_mode();
		break;
	default:
		break;
	}
}
void ULTRA_mode(void)
{
	f64 distance = 0;

	while (current_mode != 0) // Stay in ULTRA mode until mode changes
	{
		distance = Ultrasonic_MeasureDistance();
		CLCD_voidClearDisplay();
		_delay_ms(50);
		CLCD_voidSetPosition(0, 0);
		CLCD_voidSendString("Mode: ULTRA");

		if (distance < 20)
		{
			stop();
			_delay_ms(1000);
			Move_Backward();
			_delay_ms(1000);
			Move_Right();
			_delay_ms(1000);
		}
		else
		{
			Move_Forward();
		}

		obstacle_counting(distance);

		// Check if the button is pressed to switch back to RC mode
		if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0) // Button pressed
		{
			_delay_ms(50); // Debounce
			if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0) // Confirm button press
			{
				while (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0); // Wait for button release
				_delay_ms(200); // Extra debounce delay

				// *Switch back to RC Mode*
				current_mode = 0;  //
				Motor_Init();      //
				stop();
				return;            //
			}
		}
	}
}
void Log_Data(f64 distance)
{
	static u16 obstacle_count = 0;
	if (distance < 20.0)
	{
		EEPROM_u8WriteDataByte(0x00, (u8)(obstacle_count & 0xFF)); // Log obstacle count to EEPROM
	}
}

void obstacle_counting(f64 distance)
{

	if (distance < 20)
	{
		_delay_ms(500);
		obstacle_counter++;
	}

	CLCD_voidSetPosition(0, 1);
	CLCD_voidSendString("obstacle: ");
	CLCD_voidSetPosition(11, 1);
	CLCD_Send_Number(obstacle_counter);
	_delay_ms(500);
}
u8 Get_Mode(void) {
	// Read the button state (assuming active LOW)
	if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0) { // Button pressed
		_delay_ms(50); // Simple debounce delay
		if (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0) { // Confirm button press
			current_mode = !current_mode; // Toggle the mode
			while (DIO_u8GetPinValue(PORT_u8D, PIN2) == 0); // Wait for button release
		}
	}
	return current_mode;
	// Return the current mode (0 = Manual, 1 = Autonomous)
}
