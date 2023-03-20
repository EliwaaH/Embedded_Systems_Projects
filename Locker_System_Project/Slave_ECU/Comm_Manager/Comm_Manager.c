/*
 * Comm_Manager.c
 *
 * Created: 20/03/2023 20:12:50
 *  Author: Ahmed_Eliwa
 */ 

#include "Comm_Manager.h"


void Communications_Handler(Comm_Type Received_Comm)
{
	switch(Received_Comm)
	{
		case RECEIVE_PASSWORD_COMM:
		ReceivePassword_EEPROM();
		break;
		
		case CHECK_PASSWORD_COMM:
		Check_Password();
		break;
		
		case OPEN_LOCKER_COMM:
		Open_Lock();
		break;
		
		case CLOSE_LOCKER_COMM:
		Close_Lock();
		break;
		
		case CHECK_WRONG_TIMES_COMM:
		Wrong_Times_Send();
		break;
		
		case CLEAR_WRONG_TIMES_COMM:
		Wrong_Times_Clear();
		break;
		
		case RECEIVE_WRONG_TIMES_COMM:
		Wrong_Times_Save();
		break;
		
		case FIRST_OPEN_CHECK_COMM:
		Check_First_Open();
		break;
		
		case FIRST_OPEN_ACTIVATE_COMM:
		Activate_First_Open();
		break;
		
		case FIRST_OPEN_DEACTIVATE_COMM:
		Deactivate_First_Open();
		break;
	}
}