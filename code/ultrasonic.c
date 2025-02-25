#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define F_CPU 8000000UL  // 8 MHz clock frequency

#define TRIGGER_PIN PD7  // Trigger pin connected to PA0
#define ECHO_PIN PD6     // Echo pin connected to PD6

volatile int TimerOverflow = 0;

// Timer1 overflow interrupt service routine
ISR(TIMER1_OVF_vect)
{
    TimerOverflow++;  // Increment Timer Overflow count
}

// Initialize the ultrasonic sensor
void Ultrasonic_Init()
{
    DDRD |= (1 << TRIGGER_PIN);  // Set trigger pin as output
    PORTD |= (1 << ECHO_PIN);    // Enable pull-up on echo pin

    // Timer1 initialization
    TCCR1A = 0x00;  // Normal operation
    TIMSK = (1 << TOIE1);  // Enable Timer1 overflow interrupt
    sei();  // Enable global interrupts
}

// Measure distance in centimeters
double Ultrasonic_MeasureDistance()
{
    long count;
    double distance;

    // Send 10us pulse to trigger pin
    PORTD|= (1 << TRIGGER_PIN);
    _delay_us(10);
    PORTD &= ~(1 << TRIGGER_PIN);

    // Wait for the rising edge on the echo pin
    TCNT1 = 0;  // Clear Timer1 counter
    TCCR1B = 0x41;  // Capture rising edge, no prescaler
    TIFR = (1 << ICF1) | (1 << TOV1);  // Clear ICP and Timer Overflow flags
    TimerOverflow = 0;  // Clear Timer overflow count

    while (!(TIFR & (1 << ICF1)));  // Wait for rising edge

    // Wait for the falling edge on the echo pin
    TCNT1 = 0;  // Clear Timer1 counter
    TCCR1B = 0x01;  // Capture falling edge, no prescaler
    TIFR = (1 << ICF1) | (1 << TOV1);  // Clear ICP and Timer Overflow flags

    while (!(TIFR & (1 << ICF1)));  // Wait for falling edge

    // Calculate the pulse width
    count = ICR1 + (65535 * TimerOverflow);

    // Calculate distance in centimeters
    // Speed of sound = 343 m/s = 34300 cm/s
    // Time for 1 cm = 1 / 34300 seconds = 29.1 us
    // Since the timer counts both the time to the object and back,
    // we divide by 2 to get the one-way distance.
    distance = (double)count / 466.47;  // 8 MHz clock, 1 count = 0.125 us

    return distance;
}
