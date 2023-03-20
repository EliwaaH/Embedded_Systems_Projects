#include "UART.h"
#include "REGISTERS.h"
#include "Platform_Types.h"
#include "Bit_Math.h"
#include "UART_HW.h"
#include "PORT.h"



void UART_Init(const UART_Config  ConfigCont, uint32  Baud_Rate)
{

    uint8 BitsNum     = ConfigCont.UartBitsNum;
    uint8 Parity      = ConfigCont.UartParity;
    uint8 ParityMode  = ConfigCont.UartParityMode;
    uint8 StopBitsNum = ConfigCont.UartStopBits; 
	
	
	/* Configure the RX and TX Pins in ATmega32 As Input and Output Pins Respectively */
	Dio_SetChannelDirection(PORT_D, PIN0, INPUT);
	Dio_SetChannelDirection(PORT_D, PIN1, OUTPUT);



	uint8 UBBR_Register_Value = ( (CPU_FREQ / (16 * Baud_Rate)) - 1 );

	// First we need to set the BAUD rate in the Specific Register UBRR(H-L)
	// To Write in the UBBRH Register we need to clear URSEL BIT in the UBRR Register

	CLEAR_BIT(UBRRH, URSEL);

	UBRRH = (uint8)(UBBR_Register_Value >> 8);
	UBRRL = (uint8)(UBBR_Register_Value);


    // Second Step is Enabling Receiver and Transmitter In UART

    UCSRB |= (LOGICAL_ONE << RXEN) | (LOGICAL_ONE << TXEN);


    // Third Step is Setting the Configurations of the DATA FRAME as Selected

    if(BitsNum == Eight_Bits_Mode)
    {
        switch(Parity)
        {
            case ParityBit_OFF:

                switch (StopBitsNum)
                {
                    case OneStop_Bit:
                        // Eight Bits mode, Parity Mode Off, One Stop Bit

                        UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                (LOGICAL_ZERO << UPM0) | // Parity Mode Off
                                (LOGICAL_ZERO << UPM1) | // Parity Mode Off
                                (LOGICAL_ZERO << USBS);  // One Stop Bits

                        break;
                
                    case TwoStop_Bits:

                        // Eight Bits mode, Parity Mode Off, Two Stop Bits

                        UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                (LOGICAL_ZERO << UPM0) | // Parity Mode Off
                                (LOGICAL_ZERO << UPM1) | // Parity Mode Off
                                (LOGICAL_ONE << USBS);   // Two Stop Bits
                }

                break;

            case ParityBit_ON:

                switch (StopBitsNum)
                {
                    case OneStop_Bit:

                        if(ParityMode == EvenParity_Mode)
                        {
                            // Eight Bits mode, Parity Mode On, Even Parity Mode, One Stop Bit
                            
                            UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                    (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                    (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                    (LOGICAL_ZERO << UPM0) | // Parity Mode On
                                    (LOGICAL_ONE  << UPM1) | // Parity Mode On -- Even Parity
                                    (LOGICAL_ZERO << USBS);  // One Stop Bits
                        }

                        else if(ParityMode== OddParity_Mode)
                        {

                            UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                    (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                    (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                    (LOGICAL_ZERO << UPM0) | // Parity Mode Off
                                    (LOGICAL_ZERO << UPM1) | // Parity Mode Off
                                    (LOGICAL_ZERO << USBS);  // One Stop Bits
                        }
 

                        break;
                
                    case TwoStop_Bits:

                        if(ParityMode == EvenParity_Mode)
                        {
                            
                            UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                    (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                    (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                    (LOGICAL_ZERO << UPM0) | // Parity Mode Off
                                    (LOGICAL_ZERO << UPM1) | // Parity Mode Off
                                    (LOGICAL_ZERO << USBS);  // One Stop Bits
                        }

                        else if(ParityMode== OddParity_Mode)
                        {

                            UCSRC = (LOGICAL_ONE << URSEL) | // Set this Bit to High to Write in the UCSRC Register
                                    (LOGICAL_ONE << UCSZ0) | // Eight Bits Mode
                                    (LOGICAL_ONE << UCSZ1) | // Eight Bits Mode
                                    (LOGICAL_ZERO << UPM0) | // Parity Mode Off
                                    (LOGICAL_ZERO << UPM1) | // Parity Mode Off
                                    (LOGICAL_ZERO << USBS);  // One Stop Bits
                        }
                }
        }
    }

}


static void UART_Enable()
{
	UCSRB |= (LOGICAL_ONE << RXEN) | (LOGICAL_ONE << TXEN);
}


static void UART_Disable(void)
{
	/* Clear the RXEN and TXEN BITS in the Control Register*/
	UCSRB &= (LOGICAL_ZERO << RXEN) | (LOGICAL_ZERO << TXEN);

}


void UART_Transmit(uint8 Data)
{
	//UART_Enable();
	
    // Pooling Mode
    /* Keeps Pooling on the UDRE Flag Until The Transmit Buffer be ready to Transmit Another Data Frame*/
    while ( !(UCSRA & (LOGICAL_ONE << UDRE)) )
    {
        /* Wait for UDRE to Be One Again */
    }

    /* Load your Data into the UDR Register*/
    UDR = Data;

    //while ( !(UCSRA & (LOGICAL_ONE << TXC)) )
    //{
        /*
        Wait for TXC to Be One 
        This indicates that the whole frame has shifted out 
        */
    //}
	//UART_Disable();
}



uint8 UART_Receive(void)
{
	//UART_Enable();

    // Pooling Mode

    while ( !(UCSRA & (LOGICAL_ONE << RXC)) )
    {
        /*
        Wait for RXC to Be One 
        This indicates that There are Unread Data in the Receive Buffer
        */
    }


    /*
    Checking if the frame Received has an errors or not 
    */
   // if( ((UCSRA & (LOGICAL_ONE << FE)) == LOGICAL_ONE) || ((UCSRA & (LOGICAL_ONE << PE)) == LOGICAL_ONE) || ((UCSRA & (LOGICAL_ONE << DOR)) == LOGICAL_ONE) )
   // {
    
     //   return -1;
    //}

    //else
    //{
     
	return UDR;

    //}
	
	//UART_Disable();

}
