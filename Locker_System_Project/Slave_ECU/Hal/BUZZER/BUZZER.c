#include "BUZZER.h"
#include "Platform_Types.h"





void BUZZER_On(const  BUZZER_Config_T ConfigCont)
{
    /* First we Need to Make The Pin that Connected to The Buzzer Output Pin */

    Dio_SetChannelDirection(ConfigCont.PortId, ConfigCont.ChannelId, OUTPUT);

    /* Second We Output Logical One On the Buzzer Pin*/

    Dio_WriteChannel(ConfigCont.PortId, ConfigCont.ChannelId);

}

void BUZZER_Off(const  BUZZER_Config_T ConfigCont)
{

    /*  We Output Logical Zero On the Buzzer Pin*/

    Dio_ClearChannel(ConfigCont.PortId, ConfigCont.ChannelId);

}