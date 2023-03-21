/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  Port_Lcfg.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "PORT.h"

/* Struct to Hold The Configurations of The Selected Pins to Pass

	1- Pin Mode
	2- Pin Level
	3- Pin Type
	4- Internal Resistor
	5- Internal Current
	6- Selected Port 
	7- Selected Pin

 */

const Port_ConfigType Port_PinConfig[PORT_CONFIGURED_PINS] = {
	
	{PORT_PIN_DEN, PORT_PIN_LEVEL_HIGH, PORT_PIN_OUT,PULL_UP, PORT_PIN_CURRENT_4MA, PORT_PortF, PORT_Pin1},
	{PORT_PIN_DEN, PORT_PIN_LEVEL_LOW, PORT_PIN_IN, PULL_UP, PORT_PIN_CURRENT_2MA, PORT_PortB, PORT_Pin1},
	{PORT_PIN_DEN, PORT_PIN_LEVEL_LOW, PORT_PIN_IN, PULL_UP, PORT_PIN_CURRENT_2MA, PORT_PortB, PORT_Pin2},
	
};



/**********************************************************************************************************************
 *  END OF FILE: Port_Lcfg.c
 *********************************************************************************************************************/
