/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT.h
 *       Module:  PORT
 *
 *  Description:  header file for Port Module    
 *  
 *********************************************************************************************************************/
#ifndef  PORT_H
#define  PORT_H


/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Platform_Types.h"
#include "Port_Cfg.h"
#include "Port_REG.h"



/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define    STD_LOW         (0U)
#define    STD_HIGH        (1U)

#define    OUTPUT          (1U)
#define    INPUT           (0U)




/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/


/* Description: Data type for the symbolic name of a PortID*/
typedef uint8 Dio_PortType;


/* Description: Data type for the symbolic name of a ChannelID */
typedef uint8 Dio_ChannelType;


/* Description: Data type for the symbolic name The Level of the Channel */
typedef uint8 Dio_LevelType;


/* Description: Data type for the symbolic name of the Level of the Port */
typedef uint8 Dio_PortLevelType;


/* Description: Data type for the symbolic name of a the Direction of Channel */
typedef uint8 Dio_DirectionType;


/* Description: Possible directions of a port pin */
typedef enum
{
	INPUT_PIN,
	OUTPUT_PIN

}Pintype;



/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
	PULL_DOWN,
	PULL_UP

}PinMode;


/* Description: Port Pin Level value from Port pin list */
typedef enum
{
	LOW_LEVEL,
	HIGH_LEVEL

}PinStatus;


/* Description: Struct that hold the Configurations of PORT Pins */
typedef struct Port_Config
{
	Dio_PortType               PortId;
	Dio_ChannelType            ChannelId;
	Pintype                    Pin_type;
	PinMode                    Pin_mode;
	PinStatus                  Pin_status;

}PortConfig;




/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const PortConfig  Port_Config_Pins[REQUIRD_CONFIGURED_PINS];


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



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
void Dio_WritePort(Dio_PortType PortId, Dio_PortLevelType Level);


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
Dio_PortLevelType Dio_ReadPort(Dio_PortType PortId);



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
Dio_LevelType Dio_ReadChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);



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
void Dio_WriteChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);


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
void Dio_ClearChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);



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
void Dio_FlipChannel(Dio_PortType PortID ,Dio_ChannelType ChannelId);



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
void Dio_SetChannelDirection(Dio_PortType PortID, Dio_ChannelType ChannelId, Dio_DirectionType Level);



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
void Dio_SetPortDirection(Dio_PortType PortID, Dio_DirectionType Level);





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
void Port_Init(const PortConfig* ConfigPtr);

#endif