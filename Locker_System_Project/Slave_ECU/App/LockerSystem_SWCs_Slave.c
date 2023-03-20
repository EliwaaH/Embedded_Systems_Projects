/*
 * LockerSystem_SWCs_Slave.c
 *
 * Created: 13/03/2023 22:39:43
 *  Author: Ahmed_Eliwa
 */ 

#include "LockerSystem_SWCs_Slave.h"




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
void System_Init()
{
	Port_Init(Port_Config_Pins);
	UART_Init(UARTConfig, BAUD_RATE);
	TIMER0_Init(Timer0Config);
	I2C_Init(I2C_Config, ECU_ADDRESS);

}



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
void Check_First_Open()
{
	/* Cchek the first open  activate or not then then the checking status to the master via UART Bus*/
	UART_Transmit(EEPROM_Read_Byte(FIRST_OPEN_WORD_ADDRESS));
}


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
void Activate_First_Open()
{
	/* Write one on the First Open Word Address in EEPROM*/
	EEPROM_Write_Byte(FIRST_OPEN_WORD_ADDRESS, 1);
}



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
void Deactivate_First_Open()
{

	/* Write Zero on the First Open Word Address in EEPROM*/
	EEPROM_Write_Byte(FIRST_OPEN_WORD_ADDRESS, 0);
}









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
void ReceivePassword_EEPROM()
{
	uint8 u8Counter = 0;
	
	/* Receving the Password From Master ECU*/
	for(; u8Counter < PASWWORD_DIGITS ;)
	{
		/* Write the Password Digits or Data in the EEPROM*/
		EEPROM_Write_Byte(u8Counter, UART_Receive());
		
		u8Counter++;
	}
}



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
void Check_Password()
{
	uint8 u8Counter = 0;
	
	/* Receving the Password and Compare it with the Data Saved in the EEPROM*/
	for(; u8Counter < PASWWORD_DIGITS ;)
	{
		if(UART_Receive() == EEPROM_Read_Byte(u8Counter))
		{
			u8Counter++;
			
			continue;
		}
		
		else
		{
			break;
		}
	}
	
	/* If matched send Valid*/
	if(u8Counter == PASWWORD_DIGITS)
	{
		UART_Transmit(VALID_CODE);
		
		
	}
	
	/* If not send not valid*/
	else
	{
		UART_Transmit(NOT_VALID_CODE);
		
	}
}








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
void Open_Lock()
{
	DC_Motor_on(DC_Motor_Config, 50, RIGHT);
	
	_delay_ms(5000);
	
	DC_Motor_off(DC_Motor_Config);
}


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
void Close_Lock()
{
	DC_Motor_on(DC_Motor_Config, 50, LEFT);
	
	_delay_ms(5000);
	
	DC_Motor_off(DC_Motor_Config);	
}




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
void Wrong_Times_Save()
{
	EEPROM_Write_Byte(WRONG_TIMES_WORD_ADDRESS, UART_Receive());
}


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
void Wrong_Times_Clear()
{
	EEPROM_Write_Byte(WRONG_TIMES_WORD_ADDRESS, 0);
}


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
void Wrong_Times_Send()
{
	UART_Transmit(EEPROM_Read_Byte(WRONG_TIMES_WORD_ADDRESS));
}