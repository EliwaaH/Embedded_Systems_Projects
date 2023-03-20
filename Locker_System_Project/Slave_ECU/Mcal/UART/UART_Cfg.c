#include "UART.h"



/*

Below is a Struct that will Hold the Configurations of the UART Module

1- Number of Data Bits in the Frame
2- Parity Bit ---- ON or OFF
3- Parity Bit Mode - Even or Odd
4- Number of Stop Bits in the Frame


Hint --> You Have to Configure The RX(PD0) and TX(PD1) Pins in your Microcntroller as Input and Output Respectively

*/


const UART_Config   UARTConfig = 
{
    Eight_Bits_Mode,
    ParityBit_ON,
    EvenParity_Mode,
    TwoStop_Bits
};