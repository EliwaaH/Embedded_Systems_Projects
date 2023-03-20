
#ifndef KEYPAD_H
#define KEYPAD_H

#include "PORT.h"
#include "Platform_Types.h"

typedef struct {

    Dio_PortType    KEYPAD_PORT;
    uint8           N_COLS;
    uint8           N_ROWS; 

}KEYPAD_Config_T;

extern const KEYPAD_Config_T  KEYPAD_Config;

void KEYPAD_Init(KEYPAD_Config_T KEYPAD_Config);
uint8 KEYPAD_getPressedkey(KEYPAD_Config_T KEYPAD_Config);

#endif /* KEYPAD_H */
