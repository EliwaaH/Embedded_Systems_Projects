/*
 * LockerSystem_SWCs_Slave.h
 *
 * Created: 13/03/2023 22:39:53
 *  Author: Ahmed_Eliwa
 */ 


#ifndef LOCKERSYSTEM_SWCS_SLAVE_H_
#define LOCKERSYSTEM_SWCS_SLAVE_H_


#include <util/delay.h>

#include "PORT.h"
#include "UART.h"
#include "I2C.h"
#include "Timer0.h"

#include "EEPROM.h"
#include "DC_Motor.h"


/* MACROS For UART Communications Between Slave and Master */
#define     BAUD_RATE                   (9600)
#define     COMMUNICATIONS_NUMBERS      (10U)	


#define     RECEIVE_PASSWORD_COMM       (10)
#define     CHECK_PASSWORD_COMM         (11)

#define     OPEN_LOCKER_COMM            (12)
#define     CLOSE_LOCKER_COMM           (13)

#define     CHECK_WRONG_TIMES_COMM      (14)
#define     CLEAR_WRONG_TIMES_COMM		(15)
#define     RECEIVE_WRONG_TIMES_COMM    (16)

#define     FIRST_OPEN_CHECK_COMM		(17)
#define     FIRST_OPEN_ACTIVATE_COMM	(18)
#define     FIRST_OPEN_DEACTIVATE_COMM  (19)





/* EEPROM Word Addresses */
#define     WRONG_TIMES_WORD_ADDRESS    (0x05)
#define     FIRST_OPEN_WORD_ADDRESS		(0x0A)



/* Some Important Macros */
#define     PASWWORD_DIGITS			4


#define		ECU_ADDRESS			   (10)

#define     VALID_CODE              10
#define     NOT_VALID_CODE          20




/*****************************************************************************************************************************************************************************************************************
																		We Will Divide Our System To Separate Software Components(SWCs)

																									( SLAVE ECU )
The Software Components are Divided into Several Tasks Which are: 

Here in Slave ECU we are Receving Messages Codes Via UART BUS from the MASTER ECU and Taking Actions Depending on these Codes


-- We Can Divide This Slave System to Messages IDs or Componenets IDs

*************** FIRST OPEN Messages IDs **********************
1- Check_First_Open()
2- Activate_First_Open()
3- Deactivate_First_Open()

************** PASSWORD Meesages IDs *************************
1- ReceivePassword_EEPROM()
2- Check_Password()

************ LOCKER OPENING AND CLOSING Messages IDs ************
1- Open_Lock()
2- Close_Lock()

**************** WRONG TIMES Messages IDs **************************
1- Wrong_Times_Save()
2- Wrong_Times_Clear()
3- Wrong_Times_Send()
															
*****************************************************************************************************************************************************************************************************************/






/*******************************************************************************************************************************************
*  Task name         : Init_System
*  Syntax            : void Init_System()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Initializing all the System Components and Drivers either MCAL or HAl Layers.
									
********************************************************************** Modules Used are ****************************************************
	Hardware Abstraction Layer
	-->	DC Motor
	--> EEPROM
	
	
	Microcontroller Abstraction Layer
	--> DIO
	--> TIMER0 -- PWM
	--> I2C
	--> UART Communication Protocol

**********************************************************************************************************************************************/
void System_Init();







/************************************************************* FIRST TIME OPEN SOFTWARE COMPONENT *****************************************************************************************************************


/*******************************************************************************************************************************************
*  Task name         : Check_First_Open
*  Syntax            : void Check_First_Open()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Transmiting The First Open Status to the Master
					
********************************************************************************************************************************************/ 
void Check_First_Open();

/*******************************************************************************************************************************************
*  Task name         : Activate_First_Open
*  Syntax            : void Activate_First_Open()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Write one or Activating the First Open Status
					
********************************************************************************************************************************************/ 
void Activate_First_Open();

/*******************************************************************************************************************************************
*  Task name         : Deactivate_First_Open
*  Syntax            : void Deactivate_First_Open()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Write Zero or Deactivating the First Open Status
					
********************************************************************************************************************************************/ 
void Deactivate_First_Open();








/************************************************************* PASSWORD SOFTWARE COMPONENT *****************************************************************************************************************/




/*******************************************************************************************************************************************
*  Task name         : ReceivePassword_EEPROM
*  Syntax            : void ReceivePassword_EEPROM()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose To Receive the Password From The Master and Save it in the EEPROM
					
********************************************************************************************************************************************/
void ReceivePassword_EEPROM();


/*******************************************************************************************************************************************
*  Task name         : Check_Password
*  Syntax            : void Check_Password()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose To Receive Password from the Master and Compare It with The Saved One in the EEPROM
					   If Matched --> The Program will Send VALID on the UART BUS
					   If Not Matched --> The Program will Send Not VALID on the UART BUS
					
********************************************************************************************************************************************/
void Check_Password();







/************************************************************* LOCKER OPENING AND CLOSING SOFTWARE COMPONENT *************************************************************************************************/


/*******************************************************************************************************************************************
*  Task name         : Open_Lock
*  Syntax            : void Open_Lock()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Communicating with the DC Motor Component and Control it to Open the Locker with Speed of 50%
					
********************************************************************************************************************************************/
void Open_Lock();


/*******************************************************************************************************************************************
*  Task name         : Close_Lock
*  Syntax            : void Close_Lock()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Communicating with the DC Motor Component and Control it to Close the Locker with Speed of 50%
					
********************************************************************************************************************************************/
void Close_Lock();






/************************************************************* WRONG TIMES SOFTWARE COMPONENT *************************************************************************************************/



/*******************************************************************************************************************************************
*  Task name         : Wrong_Times_Save
*  Syntax            : void Wrong_Times_Save()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Receving the Number of Wrong Times Via UART BUS and then Save it on the Word Address of the Wrong Times
					
********************************************************************************************************************************************/
void Wrong_Times_Save();



/*******************************************************************************************************************************************
*  Task name         : Wrong_Times_Clear
*  Syntax            : void Wrong_Times_Clear()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Clearing the Number of Wrong Times and Writing ZERO on the Word Address of the Wrong Times
					
********************************************************************************************************************************************/
void Wrong_Times_Clear();



/*******************************************************************************************************************************************
*  Task name         : Wrong_Times_Send
*  Syntax            : void Wrong_Times_Send()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Transmitting the Number of Wrong times To the Master ECU Via UART BUS
					
********************************************************************************************************************************************/
void Wrong_Times_Send();


#endif /* LOCKERSYSTEM_SWCS_SLAVE_H_ */