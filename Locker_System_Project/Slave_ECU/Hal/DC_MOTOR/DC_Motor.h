#ifndef DC_MOTOR_H
#define DC_MOTOR_H

#include "PORT.h"

typedef enum
{
    RIGHT,
    LEFT

}Directions_Enum;



typedef struct 
{
    Dio_PortLevelType      PortID;
    Dio_ChannelType        ChannelID_Right;
    Dio_ChannelType        ChannelID_Left;

}DcMotor_ConfigType;


extern const DcMotor_ConfigType   DC_Motor_Config;


void DC_Motor_on (const DcMotor_ConfigType ConfigCont, uint8 duty_cycle, uint8 Direction);
void DC_Motor_off(const DcMotor_ConfigType ConfigCont);


#endif