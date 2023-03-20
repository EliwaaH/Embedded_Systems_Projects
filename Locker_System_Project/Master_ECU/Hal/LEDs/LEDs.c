/*
 * LEDs.c
 *
 * Created: 18/03/2023 20:10:30
 *  Author: Ahmed_Eliwa
 */ 
#include "LEDs.h"


void LEDs_Init(const LEDs_ConfigType* ConfigPtr)
{
	uint8 u8Counter = 0;
	
	for(u8Counter = 0; u8Counter < NUMBER_OF_CONFIGURABLE_LEDS; u8Counter++)
	{
		uint8 PortId    = ConfigPtr[u8Counter].PortId;
		uint8 ChannelId = ConfigPtr[u8Counter].ChannelId;
		
		Dio_SetChannelDirection(PortId, ChannelId, OUTPUT);
		Dio_ClearChannel(PortId, ChannelId);
		
	}
	
}



void LED_On(const LEDs_ConfigType* ConfigPtr, uint8 LED_Number)
{
	uint8 PortId    = ConfigPtr[LED_Number].PortId;
	uint8 ChannelId = ConfigPtr[LED_Number].ChannelId;
	
	Dio_WriteChannel(PortId, ChannelId);
	
}


void LED_Off(const LEDs_ConfigType* ConfigPtr, uint8 LED_Number)
{
	uint8 PortId    = ConfigPtr[LED_Number].PortId;
	uint8 ChannelId = ConfigPtr[LED_Number].ChannelId;
	
	Dio_ClearChannel(PortId, ChannelId);
	
}