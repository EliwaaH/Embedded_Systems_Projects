#include "DC_Motor.h"
#include "Platform_Types.h"

#include "Timer0.h"

#define      TIMER0_REGISTER_MAX_COUNTS              (0xFF)
#define      MAX_DUTY_CYCLE                          (100.0)


void DC_Motor_on (const DcMotor_ConfigType ConfigCont, uint8 duty_cycle, uint8 Direction)
{
    uint8 PortId        = ConfigCont.PortID;
    uint8 Right_dir_pin = ConfigCont.ChannelID_Right;
    uint8 Left_dir_pin  = ConfigCont.ChannelID_Left; 

    uint8 dc_counts =   ( (duty_cycle) * (TIMER0_REGISTER_MAX_COUNTS / MAX_DUTY_CYCLE) );
	
	Dio_SetChannelDirection(PortId, Right_dir_pin, OUTPUT);
	Dio_SetChannelDirection(PortId, Left_dir_pin,  OUTPUT);

    if(Direction == RIGHT)
    {
        Dio_WriteChannel(PortId, Right_dir_pin);
        Dio_ClearChannel(PortId, Left_dir_pin);
    }

    else if (Direction == LEFT)
    {   
        Dio_WriteChannel(PortId, Left_dir_pin);
        Dio_ClearChannel(PortId, Right_dir_pin);
        
    }

    PWM_ON(dc_counts);

}


void DC_Motor_off(const DcMotor_ConfigType ConfigCont)
{
    PWM_ON(0x00);
	Dio_ClearChannel(ConfigCont.PortID, ConfigCont.ChannelID_Right);
	Dio_ClearChannel(ConfigCont.PortID, ConfigCont.ChannelID_Left);
}