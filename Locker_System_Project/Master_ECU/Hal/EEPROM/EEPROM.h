#ifndef EEPROM_H
#define EEPROM_H

#include "Platform_Types.h"
#include "EEPROM_Cfg.h"



void EEPROM_Write_Byte(uint8 Word_Address, uint8 Data);
uint8 EEPROM_Read_Byte(uint8 Word_Address);

uint8* EEPROM_Read_Data(uint8 Word_Address, uint16 Data_Lentgh);
void EEPROM_Write_Data(uint8 Word_Address, uint8* Data, uint16 Data_Lentgh);

#endif