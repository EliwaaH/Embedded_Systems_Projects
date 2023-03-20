

#ifndef PORT_REG_H
#define PORT_REG_H


/* Registers Adresses for AVR ATMega32 MicroController*/



/* PORTA  Registers*/
#define PORTA                               *(( volatile uint8*)0x3B)
#define PINA                                *(( volatile uint8*)0x39)
#define DDRA                                *(( volatile uint8*)0x3A)

/* PORTB  Registers*/
#define PORTB                               *(( volatile uint8*)0x38)
#define DDRB                                *(( volatile uint8*)0x37)
#define PINB                                *(( volatile uint8*)0x36)

/* PORTC  Registers*/
#define PORTC                               *(( volatile uint8*)0x35)
#define DDRC                                *(( volatile uint8*)0x34)
#define PINC                                *(( volatile uint8*)0x33)

/* PORTD  Registers*/
#define PORTD                               *(( volatile uint8*)0x32)
#define DDRD                                *(( volatile uint8*)0x31)
#define PIND                                *(( volatile uint8*)0x30)



#endif