/*
 * Comm_Manager.h
 *
 * Created: 20/03/2023 20:13:11
 *  Author: Ahmed_Eliwa
 */ 


#ifndef COMM_MANAGER_H_
#define COMM_MANAGER_H_


#include "LockerSystem_SWCs_Slave.h"

typedef uint8 Comm_Type;

void Communications_Handler(Comm_Type uart_comm);


#endif /* COMM_MANAGER_H_ */