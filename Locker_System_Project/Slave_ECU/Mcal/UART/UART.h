#ifndef UART_H
#define UART_H


#include "UART_Cfg.h"
#include "Platform_Types.h"


typedef enum
{

    ParityBit_OFF,
    ParityBit_ON,

}UART_Parity;

typedef enum
{
    EvenParity_Mode,
    OddParity_Mode,

}UART_Parity_Mode;


typedef enum
{
    Five_Bits_Mode,
    Six_Bits_Mode,
    Seven_Bits_Mode,
    Eight_Bits_Mode,

}UART_BITS_Mode;

typedef enum
{
    OneStop_Bit,
    TwoStop_Bits,

}UART_STOP_BITS;


typedef struct
{   
    UART_BITS_Mode          UartBitsNum;
    UART_Parity             UartParity;
    UART_Parity_Mode        UartParityMode;
    UART_STOP_BITS          UartStopBits;

}UART_Config;


extern const UART_Config   UARTConfig;

void UART_Init(const UART_Config  ConfigCont, uint32  Baud_Rate);
void UART_Transmit(uint8 Data);
uint8 UART_Receive(void);

#endif // !UART_H
