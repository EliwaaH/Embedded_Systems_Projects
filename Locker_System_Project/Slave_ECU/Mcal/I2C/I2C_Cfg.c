#include "I2C.h"







/***********************************************************************************************************************************************

***************************************************** I2C Configurations File *****************************************************************

    1- First Argument is the mode Of The I2C (Master or Slave)
    
    2- Second Argument is the Ack Control You Need To Turn Ack on or Off

    3- The Third Argument is Prescaler Mode On or Off

    4- The Fourth Argument is the Prescaler Value

***********************************************************************************************************************************************/




const I2C_ConfigType I2C_Config =
{
	MASTER_MODE,
    ACKControl_ON,
    Prescaler_OFF,
    Prescaler_4,

};