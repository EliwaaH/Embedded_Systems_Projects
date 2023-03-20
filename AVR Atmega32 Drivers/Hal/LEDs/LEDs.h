/*
 * LEDs.h
 *
 * Created: 18/03/2023 20:10:44
 *  Author: Ahmed_Eliwa
 */ 


#ifndef LEDS_H_
#define LEDS_H_

#include "LEDs_Cfg.h"
#include "Platform_Types.h"
#include "PORT.h"

typedef struct  
{
	Dio_PortType           PortId;
	Dio_ChannelType        ChannelId;
	
}LEDs_ConfigType;


extern const LEDs_ConfigType  LEDs_Config[NUMBER_OF_CONFIGURABLE_LEDS];


void LEDs_Init(const LEDs_ConfigType* ConfigPtr);
void LED_On(const LEDs_ConfigType* ConfigPtr, uint8 LED_Number);
void LED_Off(const LEDs_ConfigType* ConfigPtr, uint8 LED_Number);



#endif /* LEDS_H_ */