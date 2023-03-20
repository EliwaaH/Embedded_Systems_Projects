#include "EXT_INT.h"
#include "Platform_Types.h"
#include "Bit_Math.h"
#include "ExtINT_MC.h"
#include "PORT.h"
#include <avr/io.h>
#include <avr/interrupt.h>




typedef uint8 IntNum;
typedef uint8 IntMode;


CB_type Callback_ptr_INT0 = NULL;
CB_type Callback_ptr_INT1 = NULL;
CB_type Callback_ptr_INT2 = NULL;


void INT0_CB(CB_type ptr)
{
    if(NULL != ptr)
    {
        Callback_ptr_INT0 = ptr;
    }

}

void INT1_CB(CB_type ptr)
{
    if(NULL != ptr)
    {
        Callback_ptr_INT1 = ptr;
    }

}

void INT2_CB(CB_type ptr)
{
    if(NULL != ptr)
    {
        Callback_ptr_INT2 = ptr;
    }

}




void ExtInt_Init(const ExtInt_Config* ConfigPtr)
{
    uint8 u8_intcounter = 0;


    for(u8_intcounter = 0; u8_intcounter < REQUIRED_EXTERNAL_INTERRUPTS; u8_intcounter++)
    {
        IntNum				int_num	  = ConfigPtr[u8_intcounter].ExtIntNum;
        IntMode				int_mode  = ConfigPtr[u8_intcounter].ExtIntMode;
		Dio_PortType		PortId    = ConfigPtr[u8_intcounter].PortID;
		Dio_ChannelType		ChannelId = ConfigPtr[u8_intcounter].ChannelID; 

        if(int_num == Ext_Int0)
        {
			
			/* Set The Pin INT0 As Input Pin Based On ATmega32 MicroController Pins */
			Dio_SetChannelDirection(PortId, ChannelId, INPUT);
			
			
            // Enable The Interrupt First Gate in the GICR Register

            SET_BIT(GICR, INT0);

            // Set The Specific Bits Depending on Selected Mode
            switch(int_mode)
            {
                case LowLevelMode:
					Dio_WriteChannel(PortId, ChannelId);
                    CLEAR_BIT(MCUCR, ISC00);
                    CLEAR_BIT(MCUCR, ISC01);
                    break;

                case LogicalChangeMode:
                    SET_BIT(MCUCR, ISC00);
                    CLEAR_BIT(MCUCR, ISC01);
                    break;

                case FallingEdgeMode:
					Dio_WriteChannel(PortId, ChannelId);
                    CLEAR_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
                    break;

                case RisingEdgeMode:
					Dio_ClearChannel(PortId, ChannelId);
                    SET_BIT(MCUCR, ISC00);
                    SET_BIT(MCUCR, ISC01);
            }
        }


        else if(int_num == Ext_Int1)
        {
			
			/* Set The Pin INT0 As Input Pin Based On ATmega32 Micrcontroller Pins */
			Dio_SetChannelDirection(PortId, ChannelId, INPUT);
			//Dio_WriteChannel(PortId, ChannelId);

            // Enable The Interrupt First Gate in the GICR Register

            SET_BIT(GICR, INT1);

            // Set The Specific Bits Depending on Selected Mode
            switch(int_mode)
            {
                case LowLevelMode: 
					Dio_WriteChannel(PortId, ChannelId);
                    CLEAR_BIT(MCUCR, ISC10);
                    CLEAR_BIT(MCUCR, ISC11);
                    break;

                case LogicalChangeMode:
                    SET_BIT(MCUCR, ISC10);
                    CLEAR_BIT(MCUCR, ISC11);
                    break;

                case FallingEdgeMode:
					Dio_WriteChannel(PortId, ChannelId);
                    CLEAR_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
                    break;

                case RisingEdgeMode:
					Dio_ClearChannel(PortId, ChannelId);
                    SET_BIT(MCUCR, ISC10);
                    SET_BIT(MCUCR, ISC11);
            }
        }

        else if(int_num == Ext_Int2)
        {
			/* Set The Pin INT0 As Input Pin Based On ATmega32 Microcontroller Pins */
			Dio_SetChannelDirection(PortId, ChannelId, INPUT);
			Dio_WriteChannel(PortId, ChannelId);
            
            // Enable The Interrupt First Gate in the GICR Register

            SET_BIT(GICR, INT1);

            // Set The Specific Bits Depending on Selected Mode
            switch(int_mode)
            {

                case FallingEdgeMode:
                    CLEAR_BIT(MCUCR, ISC2);
                    break;

                case RisingEdgeMode:
                    SET_BIT(MCUCR, ISC2);
            }
        }

    }

    // Enabling the Second Gate Which is The Global Interrupt BIT - I

    SET_BIT(SREG, I);
    
}




ISR(INT0_vect)
{
    if(NULL != Callback_ptr_INT0)
    {
        Callback_ptr_INT0();
    }
}



ISR(INT1_vect)
{
    if(NULL != Callback_ptr_INT1)
    {
        Callback_ptr_INT1();
    }
}

ISR(INT2_vect)
{
        if(NULL != Callback_ptr_INT2)
    {
        Callback_ptr_INT2();
    }
}
