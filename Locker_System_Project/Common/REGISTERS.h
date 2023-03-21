#ifndef REGISTERS_H
#define REGISTERS_H


/*
	Header File includes Registers Address of ATmega32L
*/

#include "Platform_Types.h"

/*
	For DDR Registers
*/

#define DDRA                            *((volatile uint8*) 0x3A)
#define DDRB                            *((volatile uint8*) 0x37)
#define DDRC                            *((volatile uint8*) 0x34)
#define DDRD                            *((volatile uint8*) 0x31)

/*
	For PORT Registers
*/

#define PORTA                           *((volatile uint8*) 0x3B)
#define PORTB                           *((volatile uint8*) 0x38)
#define PORTC                           *((volatile uint8*) 0x35)
#define PORTD                           *((volatile uint8*) 0x32)

/*
	For PIN Registers
*/

#define PINA                            *((volatile uint8*) 0x39)
#define PINB                            *((volatile uint8*) 0x36)
#define PINC                            *((volatile uint8*) 0x33)
#define PIND                            *((volatile uint8*) 0x30)

/*
 *	For Interrupt
 */

#define SREG                            *((volatile uint8*) 0x5F)
#define GICR                            *((volatile uint8*) 0x5B)
#define MCUCR                           *((volatile uint8*) 0x55)


/*
 *  For ADC Registers
 */

#define ADMUX                           *((volatile uint8*) 0x27)
#define ADCSRA                          *((volatile uint8*) 0x26)
#define ADCH                            *((volatile uint8*) 0x25)

/*
 *  For Timer-0
 */

#define TCCR0                           *((volatile uint8*) 0x53)
#define TIMSK                           *((volatile uint8*) 0x59)
#define TIFR                            *((volatile uint8*) 0x38)
#define OCR0                            *((volatile uint8*) 0x5c)

/*
 * For Timer-1
 */

#define TCCR1A                          *((volatile uint8*) 0x4F)
#define TCCR1B                          *((volatile uint8*) 0x4E)
#define TCNT1H                          *((volatile uint8*) 0x4D)
#define TCNT1L                          *((volatile uint8*) 0x4C)
#define ICR1L                           *((volatile uint16*) 0x46)
#define TIMSK                           *((volatile uint8*) 0x59)
#define OCR1A                           *((volatile uint16*) 0x4A)

/*
 * For UART
 */

#define UCSRB                           *((volatile uint8*) 0x2A)
#define UCSRC                           *((volatile uint8*) 0x40)
#define UBRRH                           *((volatile uint8*) 0x40)
#define UBRRL                           *((volatile uint8*) 0x29)
#define UCSRA                           *((volatile uint8*) 0x2B)
#define UDR                             *((volatile uint8*) 0x2C)


/*
 * For SPI
 */
#define SPCR                            *((volatile uint8*) 0x2D)
#define SPSR                            *((volatile uint8*) 0x2E)
#define SPDR                            *((volatile uint8*) 0x2F)


/*
 *	For I2C
 */

#define TWBR                            *((volatile uint8*) 0x20)
#define TWCR                            *((volatile uint8*) 0x56)
#define TWSR                            *((volatile uint8*) 0x21)
#define TWDR                            *((volatile uint8*) 0x23)
#define TWAR                            *((volatile uint8*) 0x22)

#endif /* REGISTERS_H_ */