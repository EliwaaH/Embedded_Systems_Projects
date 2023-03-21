/*
 * LockerSystem_SWCs.c
 *
 * Created: 12/03/2023 16:31:18
 *  Author: Ahmed_Eliwa
 */

#include "LockerSystem_SWCs.h"


/* Prototype of The Reset Function Which be Passed to The ISR of The INT0 Function Callback */ 
static void Reset_Handler();


/* Macros To Get The Call the Right Led Number*/
#define  YELLOW_LED          (0U)
#define  RED_LED             (1U)
#define  GREEN_LED           (2U)

/* Global Variables which are Used as Semaphores or Mutexes to Protect Every Task to be Called unless It's Mutex is Free*/
uint8 FirstTime_Open_Semaphore ;
uint8 Change_Password_Semaphore;
uint8 Default_Semaphore;
uint8 Open_Locker_Semaphore;

static uint8 Wrong_Times_Error_Semphore = 0;
static uint8 Open_Locker_DC_Semaphore = 0;


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
void Init_System()
{
	Port_Init(Port_Config_Pins);
	UART_Init(UARTConfig, 9600);
	ExtInt_Init(ExtIntConfigType);
	KEYPAD_Init(KEYPAD_Config);
	LCD_Init(LCD_Config);
	LEDs_Init(LEDs_Config);
	segment_init(SevenSegment_Config);
	
	INT0_CB(Reset_Handler);
	
	
	Default_Semaphore = 1;
	FirstTime_Open_Semaphore = 0;
	Change_Password_Semaphore = 0;
	Open_Locker_Semaphore = 0;
	Wrong_Times_Error_Semphore = 0;

	
}



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
void FirstTime_Open()
{
	/* Show on 7Segment weather if this is the first time open or not*/
	segment_set_number(SevenSegment_Config, First_Open_Check());
	
	/* This is the array which hold the FTO Code it's a constant array no one can change in it except the developer of the system*/
	const uint8 First_Time_Pass[PASWWORD_DIGITS] = {5, 5, 5, 5};
	
	uint8 Pass_[PASWWORD_DIGITS]={0};
		
	uint8 u8Counter = 0;
	
	uint8 Digit = 0;
	
	
		
	LCD_Clear(LCD_Config);
	
	LCD_WriteString(LCD_Config, "Please Enter First Time Password");
	
	//_delay_ms(1000);
	
	//LCD_Clear(LCD_Config);
	
	
	/* Taking the Code from the customer and save it in an array called Pass_ */
	for( ; u8Counter < PASWWORD_DIGITS ; )
	{
		Pass_[u8Counter] =KEYPAD_getPressedkey(KEYPAD_Config);
			
		Gotoxy(LCD_Config, 1, u8Counter);
						
		LCD_WriteCharctar(LCD_Config, '*');
			
		u8Counter++;
			
	}
	
	u8Counter = 0;
	
	/* Comparing the entered code with the saved one*/
	for(u8Counter = 0; u8Counter < PASWWORD_DIGITS; u8Counter++)
	{
		if(Pass_[u8Counter] == First_Time_Pass[u8Counter])
		{
			continue;
		}
		
		else
		{
			LCD_Clear(LCD_Config);
			
			LCD_WriteString(LCD_Config, "Wrong Pass");
			_delay_ms(1000);
			
			break;
		}
	}
	
	/* Checking if the Code Entered is correct or not 
	If Correct --> Deactivate the First Open Check and Set the Cahnge Password Semaphore to Enter the Change Password Task
	
	If Not Correct --> Keep in First Open Task 
	*/
	if(u8Counter  == PASWWORD_DIGITS)
	{
		First_Open_Deactivate();
		Clear_Wrong_Times();
		
		FirstTime_Open_Semaphore = 0;
		Default_Semaphore = 1;
		Change_Password_Semaphore = 1;
		
		return;
	}
	
	else 
	{
		First_Open_Activate();
		
		FirstTime_Open_Semaphore = 1;
		
		Change_Password_Semaphore = 0;
		
	}
		
}


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
uint8 First_Open_Check()
{
	uint8 Check = 0;
	
	/* Sending The Correct Code on UART BUS to The Slave ECU to checking on the Required Address*/
	UART_Transmit(FIRST_OPEN_CHECK_COMM);
	
	//_delay_ms(50);
	
	/* Waiting for The UART to Send the Data of the Checking Process*/
	Check = UART_Receive();
	
	return Check;
}


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
void First_Open_Activate()
{
	/* Sending the Communication Code for Activating the FTO (FIRST_OPEN_ACTIVATE_COMM)*/
	UART_Transmit(FIRST_OPEN_ACTIVATE_COMM);
}


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
void First_Open_Deactivate()
{
	/* Sending the Communication Code for deactivating the FTO (FIRST_OPEN_DEACTIVATE_COMM)*/
	UART_Transmit(FIRST_OPEN_DEACTIVATE_COMM);
}




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
void Default()
{
	
	/* Checking for the First Open Check is Passed or Not*/
	if(First_Open_Check() == 1)
	{
		FirstTime_Open();
		
		return;
	}
	
	
	else
	{
		while(Default_Semaphore == 1)
		{
			/* Light the Yellow Led */
			LED_Off(LEDs_Config, GREEN_LED);
			LED_Off(LEDs_Config, RED_LED);
			LED_On(LEDs_Config, YELLOW_LED);
			
			uint8 TempPass[PASWWORD_DIGITS]= {0};
			uint8 u8Counter = 0;
			uint8 LcdClearFlag = 0;
			uint8 Check = 0;
	
			/* Getting the Number of Wrong Times Entered y Calling Get_Wrong_Times()*/
			uint8 Wrong_Times_Counter = Get_Wrong_Times();
	
			segment_set_number(SevenSegment_Config, Wrong_Times_Counter);
	
			/* Check If the Wrong Times is Excedded or not*/
			Check_Wrong_Times();
			
			/* This is an important Condititon to Make Sure that Task will Stop if the Wrong Times Excedded*/
			if(FirstTime_Open_Semaphore == 1)
			{
				return;
			}
		
			LCD_Clear(LCD_Config);
			LCD_WriteString(LCD_Config, "Welcome, Please Enter Your Password");
	
	
			/*Saving the Password Entered by Customer */
			while((u8Counter < PASWWORD_DIGITS) && (Default_Semaphore == 1))
			{
				TempPass[u8Counter] = KEYPAD_getPressedkey(KEYPAD_Config);
		
				Gotoxy(LCD_Config, 1, u8Counter);
				LCD_WriteNumber(LCD_Config, TempPass[u8Counter]);
		
				u8Counter++;
			}
	

			if(Default_Semaphore == 1)
			{
				/* Check if the pass entered is correct or not*/
				Check = CheckPassword(TempPass);
	
				/* If Correct --> System will open and wrong times will be cleared*/
				if(Check == VALID_CODE)
				{
					LCD_Clear(LCD_Config);
					LCD_WriteString(LCD_Config, "Password Correct, Locker Opening");
					_delay_ms(1000);

					Clear_Wrong_Times();
					Default_Semaphore = 0;
					Open_Locker_Semaphore = 1;
		
					return;
				}
	
				/* If not System will not open and Number of Wrong times will increment */
				else 
				{
					LCD_Clear(LCD_Config);
					LCD_WriteString(LCD_Config, "Password isn't Correct, Enter it again");
					_delay_ms(1000);
				
					Send_Wrong_Times(++Wrong_Times_Counter);
				}
			}
		}
	}
			
		
}


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
uint8 Get_Wrong_Times()
{
	uint8 Wrong_Times = 0;
	
	/* Sending the Communication code vi UART BUS to The Slave ECU*/
	UART_Transmit(CHECK_WRONG_TIMES_COMM);
	
	_delay_ms(100);
	
	/* Waiting until Slave Sending the Correct Data */
	Wrong_Times = UART_Receive();
	
	return Wrong_Times;
	
}


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
void Check_Wrong_Times()
{	
	/* If the Number of Wrong Times Excedded Program will call Wrong_Times_Error() which under The RESET SWC*/
	while(Get_Wrong_Times() >= 3)
	{
		Wrong_Times_Error();
	}
	
	return;
}

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
uint8 CheckPassword(uint8* TempPass)
{
	uint8 Check = 0;
	
	/* Calling The CheckPassword_EEPROM */
	Check = CheckPassword_EEPROM(TempPass);
	
	return Check;
	
}

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
uint8 CheckPassword_EEPROM(uint8* TempPass)
{
	uint8 Check = 0;
	uint8 u8Counter = 0;
	
	/* Sending te The Right Communication Code or Message Code on the UART BUS to The slave to Ask him to send the Required data*/
	UART_Transmit(CHECK_PASSWORD);
	
	/* Now the Slave is waiting for the password to be send to compare it with the password saved in the EEPROM*/
	for(;u8Counter < PASWWORD_DIGITS;)
	{
		/* Sending the Password to the Slave*/
		UART_Transmit(TempPass[u8Counter]);
		u8Counter++;
	}
	
	/* Slave will Compaer the Two Passwords and Retrun a Code that Indicate weather this password is correct or not*/
	Check = UART_Receive();
	
	if(Check == VALID_CODE)
	{
		return Check;
	}
	
	else if(Check == NOT_VALID_CODE)
	{
		return Check;
	}
	
}


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
void Send_Wrong_Times(uint8 Wrong_Times_Counter)
{
	/* First Send the Correct Code to the slave*/
	UART_Transmit(SEND_WRONG_TIMES_COMM);
	_delay_ms(50);

	/* then send the Number of wrong times*/
	UART_Transmit(Wrong_Times_Counter);
}

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
void Clear_Wrong_Times()
{
	/* Sending the right code to the slave via UART BUS to clear the address of the wrong times in the EEPROM*/
	UART_Transmit(CLEAR_WRONG_TIMES_COMM);
}





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
void Open_Locker()
{
	uint8 Digit = 0;
	
	Open_Locker_DC_Semaphore  = 0;
	
	/* First we have to wiat untill the door of the locker is opened */
	while (Open_Locker_DC_Semaphore == 0)
	{
		Open_Locker_DC();	
	}
		
	while(Open_Locker_Semaphore == 1)
	{
		LED_Off(LEDs_Config, YELLOW_LED);
		LED_Off(LEDs_Config, RED_LED);
		LED_On(LEDs_Config, GREEN_LED);
		
		LCD_Clear(LCD_Config);
		LCD_WriteString(LCD_Config, "Welcome, Locker Opened");
		
		/* 
		Keep Waiting in this task until customer decide to take an action
		Press C to close the system 
		press * to change password
		*/
		
		Digit = KEYPAD_getPressedkey(KEYPAD_Config);
		
		if(Digit == CLOSE_LOCK_SYMBOL)
		{
			LCD_Clear(LCD_Config);
			
			/* If C presses Close Locker by calling Close_Locker Task and free the Open_Locker_Semaphore*/
			Close_Locker();
			
			Open_Locker_Semaphore = 0;
			
			break;
		}
		
		else if(Digit == CHANGE_PASSWORD_SYMBOL)
		{
			LCD_Clear(LCD_Config);
			
			/*
			 If * prssed the system will start hte changing password process, which begin with checking the code first 
			 then go to change_password task if the code was coorect
			*/
			uint8 Check = Change_Password_Check();
			
			/*  We are always Check if an interrupt happen during the process or not (Interrupt or Reset Handler Clear The Open Locker Semaphore )*/
			if(Open_Locker_Semaphore == 1)
			{
				if(Check == VALID_CODE)
				{
					LCD_Clear(LCD_Config);
					LCD_WriteString(LCD_Config, "Password Changed Successfully");
					_delay_ms(2000);
				
					continue;
				}
			
				else 
				{
					LCD_Clear(LCD_Config);
					LCD_WriteString(LCD_Config, "Failed, incorrect Code");
					_delay_ms(2000);
				
					continue;
				}
			}
			
			else { break; }
		}
		
		else { continue; }
	}
	
}



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
void Open_Locker_DC()
{
	/* Sending the Right Communication Code to the ECU slave to Take an Specific Action on Motor*/
	UART_Transmit(OPEN_LOCKER);

	/*wait until locker Opens */
	_delay_ms(5000);

	/* Take the Open Locker Dc Semaphore to tell the system that Locker is Openend now */
	Open_Locker_DC_Semaphore = 1;
}



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
void Close_Locker()
{
	LCD_Clear(LCD_Config);
	LCD_WriteString(LCD_Config, "Locker Closed");
	
	Close_Locker_DC();
	
	Default_Semaphore = 1;
	
}



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
void Close_Locker_DC()
{
	/* Sending the Right Communication Code to the ECU slave to Take an Specific Action on Motor*/
	UART_Transmit(CLOSE_LOCKER);
	
	/*wait until locker Close */
	_delay_ms(5000);
}




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
uint8 Change_Password_Check()
{
	while(Open_Locker_Semaphore == 1)
	{
		uint8 u8Counter = 0;
		uint8 u8CorrecteCounter = 0;
		uint8 LcdClearFlag = 0;
		uint8 Digit = 0;
	
		/* This is the array that hold the code that must be entered to change the password*/
		const uint8 Change_Pass[CHANGE_PASSWORD_DIGITS] = {'*', '*', '*', '*'};
		
		LCD_Clear(LCD_Config);
		LCD_WriteString(LCD_Config, "Please Enter The Code to Change Pass");
	
		_delay_ms(1000);
	
		u8Counter = 0;
		u8CorrecteCounter = 0;

		/* Comparing the Entered Code with the Saved one */
	

		while((u8Counter < CHANGE_PASSWORD_DIGITS)  && (Open_Locker_Semaphore == 1))
		{
		
			if(KEYPAD_getPressedkey(KEYPAD_Config) == Change_Pass[u8Counter])
			{
				u8CorrecteCounter++;
				u8Counter++;
			}
		
			else
			{
				u8Counter++;
			
			}
		
			Gotoxy(LCD_Config, 1, u8Counter-1);
			LCD_WriteCharctar(LCD_Config, '*');
		}
		
		if(Open_Locker_Semaphore == 1)
		{	
			/* if code is correct so the system will free the Change Password Semaphore and Got to Change_Password Task*/
			if(u8CorrecteCounter == 4)
			{
				LCD_Clear(LCD_Config);
				LCD_WriteString(LCD_Config, "Correct Code");
				_delay_ms(1000);
		
				Change_Password_Semaphore = 1;
				Change_Password();
		
				return VALID_CODE;
		
			}
	
			/*if code isn't correct so system will return not valid code and password will not change*/
			else 
			{
				LCD_Clear(LCD_Config);
				LCD_WriteString(LCD_Config, "Wrong Code");
				_delay_ms(1000);
		
				return NOT_VALID_CODE;
			}
		}
	}
	
	return;
}





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
void Change_Password()
{
	Clear_Wrong_Times();
	segment_set_number(SevenSegment_Config, Get_Wrong_Times());
	
	while(Change_Password_Semaphore == 1)
	{
		/* Creating two Arrays to Hold the entered two passwords*/
		uint8 Password[4] = {0};
		uint8 Temp_Pass[4] = {0};
	
		uint8 u8Counter = 0;
	
		uint8 u8CorrectCounter = 0;
	
		uint8 Digit = 0;
		
	
		LCD_Clear(LCD_Config);
	
		LCD_WriteString(LCD_Config, "Write a Four Digits Pass");
	
		/* Start taking the Password form the customer */
		for(; u8Counter < PASWWORD_DIGITS ; )
		{
			Password[u8Counter] = KEYPAD_getPressedkey(KEYPAD_Config);
		
			Gotoxy(LCD_Config, 1, u8Counter);
		
			LCD_WriteCharctar(LCD_Config, '*');
		
			u8Counter++;
		}
	
		u8Counter = 0;
	
		LCD_Clear(LCD_Config);
	
		LCD_WriteString(LCD_Config, "Please Write your Pass Again");
		
		
		/* Taking the Password again from customer */
		for(; u8Counter < PASWWORD_DIGITS ;)
		{
			Temp_Pass[u8Counter] = KEYPAD_getPressedkey(KEYPAD_Config);
			
			Gotoxy(LCD_Config, 1, u8Counter);
			
			LCD_WriteCharctar(LCD_Config, '*');
			
			u8Counter++;
		}
		
		u8Counter = 0;
	
		/* Comparing the two passwords to make sure that customer entered the same password in the first and second time*/
		for(; u8Counter < PASWWORD_DIGITS ;)
		{
			
			if(Password[u8Counter] == Temp_Pass[u8Counter])
			{
				u8CorrectCounter++;
				
				u8Counter++;
			}
			
			else
			{
				u8Counter++;
			}
			
			
		}

		/* if the two passwords match, the system will call the task that send the password to the slave to save in the EEPROM*/
		if(u8CorrectCounter == 4)
		{
			LCD_Clear(LCD_Config);
			LCD_WriteString(LCD_Config, "Congrats Your New Pass is Set Now");
			_delay_ms(1000);
			
			Send_Password_EEPROM(Password);
			
			Change_Password_Semaphore = 0;
			return ;
		}

		/* if the two passwords don't match, the system will remain in the Change Password task and ask customer to try again*/
		else
		{
			LCD_Clear(LCD_Config);
			LCD_WriteString(LCD_Config, "Sorry, Your Passwords don't match");
			_delay_ms(1000);

			Change_Password_Semaphore = 1;
		
		}
	}
	
	
}



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

void Send_Password_EEPROM(uint8* Password)
{
	uint8 u8Counter = 0;
	
	/* Send the Correct Communication code for the ECU Slave to Start Receving the Password and Save it*/
	UART_Transmit(SEND_PASSWORD);
	
	for( ; u8Counter < PASWWORD_DIGITS ; )
	{
		/* Send the Password */
		UART_Transmit(Password[u8Counter]);
		
		u8Counter++;
	}
}









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

void Wrong_Times_Error()
{
	/* Turn On the Red Led to Indicate that you excedded the number off allowed times*/
	LED_Off(LEDs_Config, GREEN_LED);
	LED_Off(LEDs_Config, YELLOW_LED);
	LED_On(LEDs_Config, RED_LED);
	
	LCD_Clear(LCD_Config);
	Gotoxy(LCD_Config, 0, 0);
	LCD_WriteString(LCD_Config, "You Exceeded The Allowed Number of Tries");
	_delay_ms(2000);
		
	LCD_Clear(LCD_Config);
	Gotoxy(LCD_Config, 0, 0);
	LCD_WriteString(LCD_Config, "Please, Contact Your Manufacture");
		
	Gotoxy(LCD_Config, 1, 0);
	LCD_WriteString(LCD_Config, "Or Start Reset Process");
		
	/* Free the wrong times semaphore */
	Wrong_Times_Error_Semphore = 1 ;
		
	/* Keep in this Task until the Button is pressed */
	while((Dio_ReadChannel(ExtIntConfigType[0].PortID, ExtIntConfigType[0].ChannelID)))
	{
			/* Wait Until the Push Button Pressed To continue the Reset Process*/

			/*
			Check if the Reset Process is done Correctly or not
			if yes, Go out from this task and system will take you to the First Open Task
			if not, System will remain in this Task
			*/
			if(Wrong_Times_Error_Semphore == 1)
			{
				continue;
			}
							
			else { break; }	
	}
	
}



/*******************************************************************************************************************************************
*  Task name         : Reset_Handler
*  Syntax            : static void  Reset_Handler()
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None 
*  Return value      : None
*  Description       : This is The Task that Will be Excuted in The ISR of the EXT_INT0 
					   This is the Part Two in the Reset Process 
					   Here, The Program Will Ask The Customer to Enter the RESET Code 
					   IF the Reset Code is Correct hte System will Go to the First Open Task to make sure that Customer 
					   has The Original Manufactured Code, then Will go to The Change Password Task
********************************************************************************************************************************************/

static void Reset_Handler()
{
	
	/* Creating a Constannt Array that Hold the Reset Code */
	const uint8 Reset_Handler_Code[6] = {1, 5, 9, 3, 5, 7};
	uint8 Temp_Code[6]={0};
			
	uint8 u8CorrectCounter=0;
	uint8 u8Counter = 0;	
	
	LED_Off(LEDs_Config, GREEN_LED);
	LED_Off(LEDs_Config, YELLOW_LED);
	LED_On(LEDs_Config, RED_LED);
	
	
	LCD_Clear(LCD_Config);
	LCD_WriteString(LCD_Config, "Welcome to Reset Mode");
	_delay_ms(1000);
	
	/* Take the Wrong Times Semaphore to Enter the Task*/
	Wrong_Times_Error_Semphore = 1;
	
	/* Keep here until hte Wrong times Semaphore Released*/
	while(Wrong_Times_Error_Semphore == 1)
	{
		LCD_Clear(LCD_Config);
		LCD_WriteString(LCD_Config, "Please Enter the Reset Code");
		
		u8Counter = 0;
		u8CorrectCounter = 0;
		
		/* Taking the Code from the Customer and Comparing it with the Saved one*/
		for(; u8Counter < 6 ;)
		{
			if(KEYPAD_getPressedkey(KEYPAD_Config) == Reset_Handler_Code[u8Counter])
			{

				u8CorrectCounter++;
				u8Counter++;
			}
		
			else { u8Counter++; }
				
			Gotoxy(LCD_Config, 1, u8Counter-1);
			LCD_WriteCharctar(LCD_Config, '*');
		}
	
		/* if Code is Correct the system will Free the First Open Semapore and Clear the Number of Wrong times*/
		if(u8CorrectCounter == 6)
		{
			LCD_Clear(LCD_Config);
			LCD_WriteString(LCD_Config, "Correct Code");
			_delay_ms(1000);
			
			FirstTime_Open_Semaphore = 1;
			Default_Semaphore = 0;
			Change_Password_Semaphore = 0;
			Open_Locker_Semaphore = 0;
						
			Wrong_Times_Error_Semphore = 0;
			
			/* Write 1 on the First Time Open Word Address in EEPROM*/
			First_Open_Activate();
		
			/* Clear The Wrong Times Location In EEPROM*/
			Clear_Wrong_Times();
			
			segment_set_number(SevenSegment_Config, Get_Wrong_Times());
		
			return;
		
		}
		/* if the code isn't correct, the system will remain here*/
		else
		{
			LCD_Clear(LCD_Config);
			LCD_WriteString(LCD_Config, "Wrong Code,Please Try Again");
			
			_delay_ms(1000);
			Wrong_Times_Error_Semphore = 1;
			continue;
		}
		
	}
	
	
}


