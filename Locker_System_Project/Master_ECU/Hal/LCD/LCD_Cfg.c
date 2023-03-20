#include "LCD.h"



/*

    -----------------------------------------------------------------------------------------------------

    -- This the order that you have to follow to fill the LCD Configuration Struct

    First --> The Port that Data Bits of LCD are Connected to 
   
    Second --> The Port that Control Pins of LCD is Connected to

    Third --> Which Pin number is Connected to the RS Pin of the LCD

    Fourth --> Which Pin Number is Connected to The Enable Pin

	Dio_PortType 	 	    portID;
	Dio_PortType     		portContorl;
	Dio_ChannelType 		RS_PIN;
	Dio_ChannelType 		E_PIN;
    -------------------------------------------------------------------------------------------------------


    KINDLY NOTE THAT YOU HAVE TO MAKE THE DATA PORT IS AN OUTPUT PORT 
    AND THE RS AND E PINS ARE OUTPUT TOO

*/



const LCD_config_T  LCD_Config = 
{
	PORT_A,
	PORT_D,
	PIN7,
	PIN6,

};