#include "PORT.h"






/***********************************************************************************************************************************************

***************************************************** PORT Configuration File ******************************************************************

	First You Need To Put How Many Pins you will Use In the REQUIRD_CONFIGURED_PINS MACRO That Exists in the_Cfg.h File

	Based on how Many Pins you Put in this Macro you will Configure Elements as Below

	1- First Argument -- The PORT Number (PORT_A, PORT_B, PORT_C, PORT_D)

	2- Pin or Channel Number -- (PINx)

	3- OUTPUT_PIN or INPUT_PIN

	4- If Input PULL_UP or PULL_DOWN

	5- If Output This Pin Defualt is Low_Level or High_Level

***********************************************************************************************************************************************/




const PortConfig Port_Config_Pins[REQUIRD_CONFIGURED_PINS] =
{
	/*************** PORTA PINS ******************/
    {PORT_A, PIN0, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN1, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN2, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN3, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
    {PORT_A, PIN4, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN5, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN6, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_A, PIN7, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
		
		
	/*************** PORTB PINS ******************/
	{PORT_B, PIN0, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN1, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN2, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN3, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN4, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN5, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN6, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_B, PIN7, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	
	
	/**************** PORTC PINS *****************/
	{PORT_C, PIN0, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN1, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
    {PORT_C, PIN2, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN3, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN4, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN5, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN6, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_C, PIN7, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	
	
	/**************** PORTD PINS *****************/
	{PORT_D, PIN0, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN1, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN2, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN3, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN4, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN5, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN6, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
	{PORT_D, PIN7, OUTPUT_PIN, PULL_UP, LOW_LEVEL},
};