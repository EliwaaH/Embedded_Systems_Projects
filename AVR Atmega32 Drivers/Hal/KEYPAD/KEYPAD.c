
#include "KEYPAD.h"
#include <util/delay.h>


#define ROWS 4
#define COLS 4

uint8 KEYPAD_Matrix[ROWS][COLS] = {
		{7 , 8 , 9 ,'/'},
		{4 , 5 , 6 ,'*'},
		{1 , 2 , 3 ,'-'},
		{'C' , 0 , '=' ,'+'},
};



void KEYPAD_Init(KEYPAD_Config_T KEYPAD_Config)
{
	/*
	 First Set Port Pins Directions as 4 pins as Input PullUp  and another 4 pins as Output pins
	*/

	Dio_SetPortDirection(KEYPAD_Config.KEYPAD_PORT, 0b11110000);

	/*

	Second Write Logical One on all KEYPAD Port Pins as Vcc

	*/

	//Dio_WritePort(KEYPAD_Config.KEYPAD_PORT, 0b11111111);
}



uint8 KEYPAD_getPressedkey(KEYPAD_Config_T KEYPAD_Config)
{
	uint8 col,row;
	

	/* Super Loop to keep in this Function until A key Get Pressed By User*/
	while(1)
	{

		/*This For Loop for Looping over every Row and Column to get the Pressed Key */
		for (row = 0 ; row < KEYPAD_Config.N_ROWS ; row++)
		{
			/* Here we are Making Every Row as Input Every Iteration to Check if any Column Putton Get Pressed or not*/
			Dio_WritePort(KEYPAD_Config.KEYPAD_PORT ,
								(~(0b00010000 << row )));  // internal pull up

			/* Looping over Columns for Every Single Row */
			for ( col = 0 ; col < KEYPAD_Config.N_COLS ; col++)
			{
				/* Checking if any key pressed or not */
				if (!(Dio_ReadChannel(KEYPAD_Config.KEYPAD_PORT , col)))
				{
					/* This delay is very important because of the Depouncing Issues*/
					_delay_ms(50);
					
					/* Here we are keeping our system here until any key pressed */
					while(!(Dio_ReadChannel(KEYPAD_Config.KEYPAD_PORT , col)));
					
					/* Return this Key Value */
					return KEYPAD_Matrix[row][col];
				}
			}
			
		}
		
	}
	
}
