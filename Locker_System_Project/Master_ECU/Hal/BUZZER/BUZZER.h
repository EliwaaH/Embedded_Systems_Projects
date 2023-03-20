#ifndef BUZEER_H
#define BUZZER_H


#include "PORT.h"


typedef struct
{
    Dio_PortType        PortId;
    Dio_ChannelType     ChannelId;

}BUZZER_Config_T;

extern const  BUZZER_Config_T BUZZER_Config;

void BUZZER_On(const  BUZZER_Config_T ConfigCont);

void BUZZER_Off(const  BUZZER_Config_T ConfigCont);



#endif /* BUZZER_H */