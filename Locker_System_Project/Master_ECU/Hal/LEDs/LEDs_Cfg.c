/*
 * LEDs_Cfg.c
 *
 * Created: 18/03/2023 20:11:13
 *  Author: Ahmed_Eliwa
 */ 


#include "LEDs.h"






/***********************************************************************************************************************************************

***************************************************** LEDs Configurations File ***************************************************************

********* Please Note That you Have To Configure Each Led in A specific Element in the Configuration Arra
		  And you Have to Put The Number of Used Leds In the MACRO that Called NUMBER_OF_CONFIGURABLE_LEDS and exists in the Cfg.h File

    1- First Argument is the PORT that Is Connected To Your Led
    
    2- The Second Argument is The Channel That is Connected to That Led

***********************************************************************************************************************************************/


const LEDs_ConfigType  LEDs_Config[NUMBER_OF_CONFIGURABLE_LEDS] = 
{
	{PORT_D, PIN3},
	{PORT_D, PIN4},
	{PORT_D, PIN5},	
};