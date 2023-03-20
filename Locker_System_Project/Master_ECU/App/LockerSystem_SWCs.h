/*
 * LockerSystem_SWCs.h
 *
 * Created: 13/03/2023 19:52:37
 *  Author: Ahmed_Eliwa
 */ 


#ifndef LOCKERSYSTEM_SWCS_H_
#define LOCKERSYSTEM_SWCS_H_



#include <util/delay.h>
#include <setjmp.h>
#include <stdio.h>
#include <signal.h>

#include "PORT.h"
#include "UART.h"
#include "EXT_INT.h"

#include "LCD.h"
#include "KEYPAD.h"
#include "SEVEN_SEGMENT.h"
#include "LEDs.h"


/* MACROS For UART Communications Between Slave and Master*/
#define     BAUD_RATE                   (9600)
#define     COMMUNICATIONS_NUMBERS      (10U)	


#define     SEND_PASSWORD				(10)
#define     CHECK_PASSWORD				(11)
#define     OPEN_LOCKER					(12)
#define     CLOSE_LOCKER				(13)
#define     CHECK_WRONG_TIMES_COMM		(14)
#define     CLEAR_WRONG_TIMES_COMM		(15)
#define     SEND_WRONG_TIMES_COMM		(16)
#define     FIRST_OPEN_CHECK_COMM		(17)
#define     FIRST_OPEN_ACTIVATE_COMM	(18)
#define     FIRST_OPEN_DEACTIVATE_COMM  (19)

/* Some Important Macros */

#define     PASWWORD_DIGITS			4

#define     CHANGE_PASSWORD_DIGITS	4

#define     CLOSE_LOCK_SYMBOL	   'C'

#define     CHANGE_PASSWORD_SYMBOL '*'


/* Validation Macros */

#define     VALID_CODE              10
#define     NOT_VALID_CODE          20


/* The Required Semaphores That System will Keep Check on them To Decide Which Task will Be Excuted*/

extern  uint8  FirstTime_Open_Semaphore;
extern  uint8  Change_Password_Semaphore;
extern  uint8  Default_Semaphore;
extern  uint8  Open_Locker_Semaphore;



/*****************************************************************************************************************************************************************************************************************
																		We Will Divide Our System To Separate Software Components(SWCs)


The Software Components are Divided into Several Tasks Which are: (Please Note That you Might Find Repeated Tasks, This Means That These Tasks are being used by More Than One SWC)

FIRST TIME OPEN SWC:
	1- FirstTime_Open()
	2- First_Open_Check()
	3- First_Open_Activate()
	4- First_Open_Deactivate()
	5- Change_Password()
	6- Send_Password_EEPROM()
	
	
DEFAULT:
	1-Default()
	2-Get_Wrong_Times()
	3-Check_Wrong_Times()
	4-CheckPassword()
	5-Send_Wrong_Times()	
	
	
RESET:
	1-Wrong_Times_Error()
	2-Reset_Handler()
	3-Activate_First_Open()
	4-Clear_Wrong_Times()
	
	
OPEN LOCKER:
	1-Open_Locker()
	2-Open_Locker_DC()
	3-Change_Password_Check()
	4-Change_Password()
	5- Send_Password_EEPROM()
	6-Close_Locker()
	7-Close_Locker_DC()
															
*****************************************************************************************************************************************************************************************************************/


/************************************************************* FIRST TIME OPEN SOFTWARE COMPONENT *****************************************************************************************************************




/******************************************************************* Tasks ProtoTypes *****************************************************************************************************************************/




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
					   Also used for Initialization the System Semaphores.
									
********************************************************************** Modules Used are ************************************************** 
	Hardware Abstraction Layer
	-->	LCD
	-->	7-Segment 
	-->	KEYPAD
	-->	LEDS
	
	Microcontroller Abstraction Layer
	--> DIO
	--> External Interrupts
	--> UART Communication Protocol

*  ******************************************************************************************************************************************/
void Init_System();



/*******************************************************************************************************************************************
*  Task name         : FirstTime_Open
*  Syntax            : void FirstTime_Open()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Asking User to Enter the FTO code Which is Delivered with The Product
					 -- Customer Must enter this code in first time open the system after manufacturing process or when he start the reset process
									
********************************************************************************************************************************************/ 
void FirstTime_Open();


/*******************************************************************************************************************************************
*  Task name         : First_Open_Check
*  Syntax            : uint8 First_Open_Check()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : The Value of the First Open Check 
*  Return value      : 1 or 0
*  Description       : This Task Purpose is Checking on the Address of the First Open in The EEPROM and return it
					
********************************************************************************************************************************************/ 
uint8 First_Open_Check();


/*******************************************************************************************************************************************
*  Task name         : First_Open_Activate
*  Syntax            : void First_Open_Activate()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Sending the Right Communication Code for The Slave to Write one or Activate the FTO Address in the EEPROM
					
********************************************************************************************************************************************/ 
void First_Open_Activate();


/*******************************************************************************************************************************************
*  Task name         : First_Open_Deactivate
*  Syntax            : void First_Open_Deactivate()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Sending the Right Communication Code for The Slave to Write Zero or Deactivate the FTO Address in the EEPROM
					
********************************************************************************************************************************************/ 
void First_Open_Deactivate();





/************************************************************* DEFAULT SOFTWARE COMPONENT *****************************************************************************************************************/

/*******************************************************************************************************************************************
*  Task name         : Default
*  Syntax            : void Default()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task can be divided to Three Stages
					   1- Checking if System has Passed the FTO Check or not
					   2- Checking the Number of  Times Customer Has Entered Password Wrong
					   3- Checking if the Password That Customer will Enter is Correct or not
					   4- if the Entered Password isn't Correct Send the Number of Wrong Times to The Slave to Increment The Number of 
					   Wrong Times Address in EEPROM.
					
********************************************************************************************************************************************/ 
void Default();


/*******************************************************************************************************************************************
*  Task name         : Get_Wrong_Times
*  Syntax            : uint8  Get_Wrong_Times()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : The Number of times Wrong Password Entered
*  Return value      : 0 to 3
*  Description       : This Task Purpose is Returning the Number of times of Entered Wrong Password 
					
********************************************************************************************************************************************/ 
uint8 Get_Wrong_Times();


/*******************************************************************************************************************************************
*  Task name         : Check_Wrong_Times
*  Syntax            : void  Check_Wrong_Times()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Just Checking if tjhe Number of Wrong times is Excedded or not
					
********************************************************************************************************************************************/ 
void Check_Wrong_Times();


/*******************************************************************************************************************************************
*  Task name         : CheckPassword
*  Syntax            : uint8  CheckPassword(uint8* TempPass)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : An Array the Hold the Password Entered by Customer
*  Parameters (inout): None
*  Parameters (out)  : Password Matching Result (VALID CODE -- NOT VALID CODE)
*  Return value      : VALID or Not VALID
*  Description       : This Task Purpose is Returning Result of Comparing the Password Entered by hte Customer by hte Password Saved in The EEPROM 
					
********************************************************************************************************************************************/ 
uint8 CheckPassword(uint8* TempPass);

/*******************************************************************************************************************************************
*  Task name         : CheckPassword_EEPROM
*  Syntax            : uint8 CheckPassword_EEPROM(uint8* TempPass)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : An Array the Hold the Password Entered by Customer
*  Parameters (inout): None
*  Parameters (out)  : Password Matching Result (VALID CODE -- NOT VALID CODE)
*  Return value      : VALID or Not VALID
*  Description       : This Task Purpose is Commnicating with The Slave ECU to Ask it to Compare the Entered Password with the saved one
					
********************************************************************************************************************************************/ 
uint8 CheckPassword_EEPROM(uint8* TempPass);

/*******************************************************************************************************************************************
*  Task name         : Send_Wrong_Times
*  Syntax            : void Send_Wrong_Times(uint8 Wrong_Times_Counter)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : The nUmber of Wrong Times 
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Sending the Number of Wrong Times to the slave via UART Bus
					
********************************************************************************************************************************************/ 
void Send_Wrong_Times(uint8 Wrong_Times_Counter);


/*******************************************************************************************************************************************
*  Task name         : Clear_Wrong_Times
*  Syntax            : void  Clear_Wrong_Times()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is Clearing the number of wrong times
					
********************************************************************************************************************************************/ 
void Clear_Wrong_Times();






/************************************************************* OPEN LOCKER SOFTWARE COMPONENT *****************************************************************************************************************/


/*******************************************************************************************************************************************
*  Task name         : Open_Locker
*  Syntax            : void  Open_Locker()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task is responsiple about handling all the operations that being handled when the locker is opened
					  - Press C to Lock the Locker
					  - Press * to change the password or starting the change password process
					
********************************************************************************************************************************************/ 
void Open_Locker();

/*******************************************************************************************************************************************
*  Task name         : Open_Locker_DC
*  Syntax            : void  Open_Locker_DC()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task is the part two of Opening the locker process 
					   Here, we are communicating with the slave ECU to start controlling on the dc motor and moving it in the Opening direction
					
********************************************************************************************************************************************/ 
void Open_Locker_DC();


/*******************************************************************************************************************************************
*  Task name         : Close_Locker
*  Syntax            : void  Close_Locker()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task Purpose is to Close the Locker by Calling the Close Locker Dc Task and Free the Default Semaphore to return back
						to the Default Task.
					
********************************************************************************************************************************************/ 
void Close_Locker();


/*******************************************************************************************************************************************
*  Task name         : Close_Locker_DC
*  Syntax            : void  Close_Locker_DC()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task is the part two of closing the locker process 
					   Here, we are communicating with the slave ECU to start controlling on the dc motor and moving it in the closing direction
					
********************************************************************************************************************************************/ 
void Close_Locker_DC();

/*******************************************************************************************************************************************
*  Task name         : Change_Password_Check
*  Syntax            : uint8  Change_Password_Check()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : Valid Code or Not Valid Code 
*  Return value      : Vaid Code or Not Valid Code
*  Description       : This Task is responsiple on Checking on the Code that required for changing password while the system is opened
					
********************************************************************************************************************************************/ 
uint8 Change_Password_Check();


/*******************************************************************************************************************************************
*  Task name         : Change_Password
*  Syntax            : void  Change_Password()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : This Task is responsiple on Changing Password Process Starting from Taking The Password form Customer 
					   and Asking the Customer to enter the password again, Then Comparing the Two Passwords 
					   and if they are matching the password will be sentto hte Slave ECU to Save the new Password in the EEPROM
					
********************************************************************************************************************************************/ 
void Change_Password();


/*******************************************************************************************************************************************
*  Task name         : Send_Password_EEPROM
*  Syntax            : void  Send_Password_EEPROM(uint8* Password)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : The array that hold the new password
*  Parameters (inout): None
*  Parameters (out)  : None 
*  Return value      : None
*  Description       : This Task is responsiple on Sending the new Changed Password to the Slave ECU via UART BUS to Save it in the EEPROM
					
********************************************************************************************************************************************/ 
void Send_Password_EEPROM();





/************************************************************* RESET SOFTWARE COMPONENT *****************************************************************************************************************/

/*******************************************************************************************************************************************
*  Task name         : Wrong_Times_Error
*  Syntax            : void  Wrong_Times_Error()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None 
*  Return value      : None
*  Description       : This Task is responsiple on Checking on the Number of times that customer Entered wrong password
					   this is the Part one in the Reset Process 
					   Please Note that --> System will Keep you in this Task untill customer strting the Reset Process whic is
					   1- Pressing the Button to Create an interrupt and prevent any other task to interrupt The Reset Task
					   2- Entering the Reset Code 
					
********************************************************************************************************************************************/
void Wrong_Times_Error();


#endif /* LOCKERSYSTEM_SWCS_H_ */