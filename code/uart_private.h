#ifndef uart_private
#define uart_private

#define UBRRH_u8_REG   *((volatile u8*)0x40)

#define UCSRC_u8_REG   *((volatile u8*)0x40)

#define UDR_u8_REG     *((volatile u8*)0x2C)

#define UCSRA_u8_REG   *((volatile u8*)0x2B)

#define UCSRB_u8_REG   *((volatile u8*)0x2A)

#define UBRRL_u8_REG   *((volatile u8*)0x29)





#define UART_u8_ASYNCH    0
#define UART_u8_SYNCH     1

#define UART_u8_EVEN                0
#define UART_u8_ODD                 1
#define UART_u8_DISABLE_PARITY      2





#endif