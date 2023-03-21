/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  PORT.h
 *       Module:  PORT
 *
 *  Description:  header file for Port Module    
 *  
 *********************************************************************************************************************/
#ifndef PORT_H
#define PORT_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "Port_Cfg.h"

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

#define PORT_PIN_DEN  (0U)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
 
/* Description: Data type for the symbolic name of a port num */
typedef uint8 Port_Num;


/* Description: Data type for the symbolic name of a port pin num */
typedef uint8 Port_PinNum;


/* Description: Data type for the symbolic name of a port pin */
typedef uint8 Port_PinType;
	
	
/* Description: Possible directions of a port pin */
typedef enum
{
	PORT_PIN_IN,
	PORT_PIN_OUT,
	
}Port_PinDirectionType;


/* Description: Different port pin modes */
typedef uint8 Port_PinModeType;


/* Description: Port Pin Level value from Port pin list */
typedef enum
{
	PORT_PIN_LEVEL_LOW,
	PORT_PIN_LEVEL_HIGH,

}Port_PinLevel;


/* Description: Enum to hold internal resistor type for PIN */
typedef enum
{
	OFF,
	PULL_UP,
	PULL_DOWN,
	
}Port_PinInternalAttachType;


/* Description: Enum to hold Output current for PIN */
typedef enum
{
	PORT_PIN_CURRENT_2MA = 0,
	PORT_PIN_CURRENT_4MA,
	PORT_PIN_CURRENT_8MA,
	
}Port_PinOutputCurrentType;

typedef struct
{
	Port_PinModeType  						PortPinMode;
	Port_PinLevel     						PortPinLevelValue;
	Port_PinDirectionType         PortPinDirection;
	Port_PinInternalAttachType    PortPinInternalAttach;
	Port_PinOutputCurrentType    	PortOutputCurrent;
	Port_Num                     	PortNum;
	Port_PinNum                  	PortPinNum;
	
}Port_ConfigType;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern const Port_ConfigType Port_PinConfig[PORT_CONFIGURED_PINS];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/



/**********************************************************************************************************************
*  Service name      : Dio_FlipChannel
*  Syntax            : void Dio_FlipChannel( Port_Num PortNum,
*                                             Port_PinNum PinNum )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : PortNum - PortID
*                      PinNum - Channel to work on
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Flip the level of a channel.
*  *********************************************************************************************************************/
void Dio_FlipChannel(Port_Num PortNum, Port_PinNum PinNum);



/**********************************************************************************************************************
*  Service name      : Dio_WriteChannel
*  Syntax            : void Dio_WriteChannel( Port_Num PortNum,
*                                             Port_PinNum PinNum )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : PortNum - PortID
*                      PinNum - Channel to work on
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to set a level of a channel.
*  *********************************************************************************************************************/
void Dio_WriteChannel(Port_Num PortNum, Port_PinNum PinNum);



/**********************************************************************************************************************
*  Service name      : Dio_ClearChannel
*  Syntax            : void Dio_ClearChannel( Port_Num PortNum,
*                                             Port_PinNum PinNum )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : PortNum - PortID
*                      PinNum - Channel to work on
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Clear this channel.
*  *********************************************************************************************************************/
void Dio_ClearChannel(Port_Num PortNum, Port_PinNum PinNum);


/**********************************************************************************************************************
*  Service name      : Dio_ReadChannel
*  Syntax            : uint8 Dio_ReadChannel( Port_Num PortNum,
*                                             Port_PinNum PinNum )
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : PortNum - PortID
*                      PinNum - Channel to work on
*  Parameters (inout): None
*  Parameters (out)  : Value of this Channel
*  Return value      : None
*  Description       : Service to read the level of a channel.
*  *********************************************************************************************************************/
uint8 Dio_ReadChannel(Port_Num PortNum, Port_PinNum PinNum);




/**********************************************************************************************************************
*  Service name      : Port_Init
*  Syntax            : void Port_Init(const Port_ConfigType* ConfigPtr) 
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Non Reentrant
*  Parameters (in)   : const Port_ConfigType* - ConfigPtr --> Pointer to array of struct that holds user Configurations
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : initialize Selected Ports and Specific Pins modes 
*  *********************************************************************************************************************/
void Port_Init(const Port_ConfigType* ConfigPtr);


 
#endif  /* PORT_H */

/**********************************************************************************************************************
 *  END OF FILE: PORT.h
 *********************************************************************************************************************/
