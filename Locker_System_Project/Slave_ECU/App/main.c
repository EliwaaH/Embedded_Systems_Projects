/*
 * LockerSystem_With_Layers.c
 *
 * Created: 05/03/2023 16:28:46
 * Author : Ahmed_Eliwa
 */ 


#include "LockerSystem_SWCs_Slave.h"
#include "Comm_Manager.h"

int main(void)
{
	System_Init();
	
	//EEPROM_Write_Byte(FIRST_OPEN_WORD_ADDRESS, 0);
	//_delay_ms(50);
	//EEPROM_Write_Byte(WRONG_TIMES_WORD_ADDRESS, 0);
	
	while(1)	
	{
		/* Here we are in the Super Loop Receiving the Signal from UART and Send it to our Communication Manager to Choose whaich Task will excute based on the Message ID it receive*/
		uint8 Received_Comm = UART_Receive();
		
		Communications_Handler(Received_Comm);

	}
}