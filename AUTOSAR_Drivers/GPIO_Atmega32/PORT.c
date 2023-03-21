/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  PORT.c
 *        \brief  GPIO Driver
 *
 *      \details  The Driver Configure All GPIO Pins 
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "PORT.h"
#include "Bit_Math.h"
#include "Port_REG.h"








 
/**********************************************************************************************************************
*  Service name      : Dio_WritePort
*  Syntax            : void Dio_WritePort( Dio_PortType PortId,
*                                             Dio_PortLevelType Level )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType      - PortID
*                      Dio_PortLevelType - Level of the Port 
*  Parameters (inout): None
*  Parameters (out)  : none
*  Return value      : None
*  Description       : Service to Write on All Port.
*  *********************************************************************************************************************/
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level)
{
    if(PortId == PORT_A)
    {
        PORTA = Level;
    }
	
    else if(PortId == PORT_B)
    {
       PORTB = Level;
    }

    else if(PortId == PORT_C)
    {
        PORTC = Level;
    }

    else if(PortId == PORT_D)
    {
        PORTD = Level;
    }
}






/**********************************************************************************************************************
*  Service name      : Dio_ReadPort
*  Syntax            : Dio_PortLevelType Dio_ReadPort( Dio_PortType PortId )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType      - PortID
*  Parameters (inout): None
*  Parameters (out)  : Value of the Port
*  Return value      : From 0x00 t0 0xFF
*  Description       : Service to Read Port Value.
*  *********************************************************************************************************************/
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId)
{
    if(PortId == PORT_A)
    {
        return PINA;
    }


    else if(PortId == PORT_B)
    {
       return PINB;
    }

    else if(PortId == PORT_C)
    {
        return PINC;
    }

    else if(PortId == PORT_D)
    {
        return PIND;
    }

}


 
/**********************************************************************************************************************
*  Service name      : Dio_ReadChannel
*  Syntax            : Dio_LevelType  Dio_ReadChannel( Dio_PortType PortID,
*                                                         Dio_ChannelType ChannelId )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType -- PortID
*                      Dio_ChannelType --  ChannelId
*  Parameters (inout): None
*  Parameters (out)  : Value of this Channel
*  Return value      : 0 or 1
*  Description       : Service to read the level of a channel.
*  *********************************************************************************************************************/
Dio_LevelType Dio_ReadChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId)
{
    if(PortID == PORT_A)
    {
        return ((PINA & (STD_HIGH << ChannelId)) >> ChannelId);
    }
    

    else if(PortID == PORT_B)
    {
       return ((PINB & (STD_HIGH << ChannelId)) >> ChannelId);
    }


    else if(PortID == PORT_C)
    {
        return ((PINC & (STD_HIGH << ChannelId)) >> ChannelId);
    }


    else if(PortID == PORT_D)
    {
        return ((PIND & (STD_HIGH << ChannelId)) >> ChannelId);
    }
}





/**********************************************************************************************************************
*  Service name      : Dio_WriteChannel
*  Syntax            : void Dio_WriteChannel( Dio_PortType PortID,
*                                             Dio_ChannelType ChannelId)
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType -- PortID
*                      Dio_ChannelType -- ChannelId
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to set a Logical one of a channel.
*  *********************************************************************************************************************/
void Dio_WriteChannel(Dio_PortType PortID , Dio_ChannelType ChannelId)
{
    if(PortID == PORT_A)
    {
        PORTA |=  STD_HIGH << ChannelId ;
    }


    else if(PortID == PORT_B)
    {
        PORTB |=  STD_HIGH << ChannelId ;
    }


    else if(PortID == PORT_C)
    {
        PORTC |=  STD_HIGH << ChannelId ;
    }


    else if(PortID == PORT_D)
    {
        PORTD |=  STD_HIGH << ChannelId ;
    }

}



/**********************************************************************************************************************
*  Service name      : Dio_ClearChannel
*  Syntax            : void Dio_ClearChannel( Dio_PortType PortID,
*                                             Dio_ChannelType ChannelId )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType -- PortID 
*                      Dio_ChannelType -- ChannelId
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Clear this channel.
*  *********************************************************************************************************************/
void Dio_ClearChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId)
{
    if(PortID == PORT_A)
    {
        PORTA &=  (~(STD_HIGH << ChannelId));
    }


    else if(PortID == PORT_B)
    {
        PORTB &=  (~(STD_HIGH << ChannelId));
    }


    else if(PortID == PORT_C)
    {
        PORTC &=  (~(STD_HIGH << ChannelId));
    }


    else if(PortID == PORT_D)
    {
        PORTD &=  (~(STD_HIGH << ChannelId));
    }

}




/**********************************************************************************************************************
*  Service name      : Dio_FlipChannel
*  Syntax            : void Dio_FlipChannel( Dio_PortType PortID,
*                                             Dio_ChannelType ChannelId )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType - PortID
*                      Dio_ChannelType - ChannelId
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Flip the level of a channel.
*  *********************************************************************************************************************/
void Dio_FlipChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId)
{
    if(PortID == PORT_A)
    {
        PORTA ^=  (STD_HIGH << ChannelId);
    }


    else if(PortID == PORT_B)
    {
        PORTB ^=  (STD_HIGH << ChannelId);
    }

    else if(PortID == PORT_C)
    {
        PORTC ^=  (STD_HIGH << ChannelId);
    }


    else if(PortID == PORT_D)
    {
        PORTD ^=  (STD_HIGH << ChannelId);
    }
}










/**********************************************************************************************************************
*  Service name      : Dio_SetChannelDirection
*  Syntax            : void Dio_SetChannelDirection( Dio_PortType PortID,
*                                                       Dio_ChannelType ChannelId,
                                                        Dio_DirectionType Level )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType -- PortID
*                      Dio_ChannelType -- ChannelId
                       Dio_DirectionType -- Level
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Configure the Direction of a Channel.
*  *********************************************************************************************************************/
void Dio_SetChannelDirection(Dio_PortType PortID, Dio_ChannelType ChannelId, Dio_DirectionType Level)
{
	if(PortID == PORT_A)
	{
		DDRA |=  (Level << ChannelId);
	}


	else if(PortID == PORT_B)
	{
		DDRB |=  (Level << ChannelId);
	}


	else if(PortID == PORT_C)
	{
		DDRC |=  (Level << ChannelId);
	}


	else if(PortID == PORT_D)
	{
		DDRD |=  (Level << ChannelId);
	}

}







/**********************************************************************************************************************
*  Service name      : Dio_SetPortDirection
*  Syntax            : void Dio_SetPortDirection( Dio_PortType PortID,
                                                    Dio_DirectionType Level )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : Dio_PortType -- PortID
*                      Dio_DirectionType -- Level
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Configure the Direction of a Port.
*  *********************************************************************************************************************/
void Dio_SetPortDirection(Dio_PortType PortID, Dio_DirectionType Level)
{
	if(PortID == PORT_A)
	{
		DDRA =  Level;
	}


	else if(PortID == PORT_B)
	{
		DDRB = Level;
	}


	else if(PortID == PORT_C)
	{
		DDRC = Level;
	}


	else if(PortID == PORT_D)
	{
		DDRD = Level;
	}

}






/**********************************************************************************************************************
*  Service name      : Port_Init
*  Syntax            : void Port_Init(const PortConfig* ConfigPtr) 
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Non Reentrant
*  Parameters (in)   : const Port_ConfigType* - ConfigPtr --> Pointer to array of struct that holds user Configurations
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : initialize Selected Ports and Specific Pins modes 
*  *********************************************************************************************************************/
void Port_Init(const PortConfig* ConfigPtr)
{
    uint8 u8_PinCounter=0;
    

    for(u8_PinCounter =0; u8_PinCounter < REQUIRD_CONFIGURED_PINS; u8_PinCounter++)
    {
        Dio_PortType        PortID     = ConfigPtr[u8_PinCounter].PortId;
        Dio_ChannelType     ChannelId  = ConfigPtr[u8_PinCounter].ChannelId;

        if(PortID == PORT_A)
        {
            if(ConfigPtr[u8_PinCounter].Pin_type == INPUT_PIN)
            {   
                CLEAR_BIT(DDRA,  ChannelId);

                if(ConfigPtr[u8_PinCounter].Pin_mode == PULL_UP)
                {
                    SET_BIT(PORTA, ChannelId);
                }

                else if (ConfigPtr[u8_PinCounter].Pin_mode == PULL_DOWN)
                {
                    CLEAR_BIT(PORTA, ChannelId);
                }

            }

            else if (ConfigPtr[u8_PinCounter].Pin_type == OUTPUT_PIN)
            {
               SET_BIT(DDRA, ChannelId);

               if(ConfigPtr[u8_PinCounter].Pin_status == HIGH_LEVEL)
               {
                    SET_BIT(PORTA, ChannelId);
               }

               else if(ConfigPtr[u8_PinCounter].Pin_status == LOW_LEVEL)
               {
                    CLEAR_BIT(PORTA, ChannelId);
               }
            }
        }

        
        else if(PortID == PORT_B)
        {
            if(ConfigPtr[u8_PinCounter].Pin_type == INPUT_PIN)
            {   
                CLEAR_BIT(DDRB, ChannelId);

                if(ConfigPtr[u8_PinCounter].Pin_mode == PULL_UP)
                {
                    SET_BIT(PORTB, ChannelId);
                }

                else if (ConfigPtr[u8_PinCounter].Pin_mode == PULL_DOWN)
                {
                    CLEAR_BIT(PORTB, ChannelId);
                }

            }

            else if (ConfigPtr[u8_PinCounter].Pin_type == OUTPUT_PIN)
            {
               SET_BIT(DDRB, ChannelId);

               if(ConfigPtr[u8_PinCounter].Pin_status == HIGH_LEVEL)
               {
                    SET_BIT(PORTB, ChannelId);
               }

               else if(ConfigPtr[u8_PinCounter].Pin_status == LOW_LEVEL)
               {
                    CLEAR_BIT(PORTB, ChannelId);
               }
            }
        }



        
        else if(PortID == PORT_C)
        {
            if(ConfigPtr[u8_PinCounter].Pin_type == INPUT_PIN)
            {   
                CLEAR_BIT(DDRC, ChannelId);

                if(ConfigPtr[u8_PinCounter].Pin_mode == PULL_UP)
                {
                    SET_BIT(PORTC, ChannelId);
                }

                else if (ConfigPtr[u8_PinCounter].Pin_mode == PULL_DOWN)
                {
                    CLEAR_BIT(PORTC, ChannelId);
                }

            }

            else if (ConfigPtr[u8_PinCounter].Pin_type == OUTPUT_PIN)
            {
               SET_BIT(DDRC, ChannelId);

               if(ConfigPtr[u8_PinCounter].Pin_status == HIGH_LEVEL)
               {
                    SET_BIT(PORTC, ChannelId);
               }

               else if(ConfigPtr[u8_PinCounter].Pin_status == LOW_LEVEL)
               {
                    CLEAR_BIT(PORTC, ChannelId);
               }
            }
        }


        
        else if(PortID == PORT_D)
        {
            if(ConfigPtr[u8_PinCounter].Pin_type == INPUT_PIN)
            {   
                CLEAR_BIT(DDRD, ChannelId);

                if(ConfigPtr[u8_PinCounter].Pin_mode == PULL_UP)
                {
                    SET_BIT(PORTD, ChannelId);
                }

                else if (ConfigPtr[u8_PinCounter].Pin_mode == PULL_DOWN)
                {
                    CLEAR_BIT(PORTD, ChannelId);
                }

            }

            else if (ConfigPtr[u8_PinCounter].Pin_type == OUTPUT_PIN)
            {
               SET_BIT(DDRD, ChannelId);

               if(ConfigPtr[u8_PinCounter].Pin_status == HIGH_LEVEL)
               {
                    SET_BIT(PORTD, ChannelId);
               }

               else if(ConfigPtr[u8_PinCounter].Pin_status == LOW_LEVEL)
               {
                    CLEAR_BIT(PORTD, ChannelId);
               }
            }
        }
    }
}