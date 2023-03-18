/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCtrl_Types.h
 *       Module:  -
 *
 *  Description:  <Write File DESCRIPTION here>     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_TYPES_H
#define INTCTRL_TYPES_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/




/*Enum for Handling Exceptions Types of The Arm Cortex M4 Proccessor */
typedef enum
{
    Reset=1,
    Non_Maskable_Interrupt,
    Hard_Faut,
    Memory_Management,
    Bus_Fault,
    Usage_Fault,
    SVCall = 11,
    Debug_Monitor,
    PendSV = 14,
    SysTick,

}ExceptionType;




/*Enum for Handling Interrupts Types of The Arm Cortex M4 Proccessor */
typedef enum
{
    GPIO_Port_A,
    GPIO_Port_B,
    GPIO_Port_C,
    GPIO_Port_D,
    GPIO_Port_E,
    UART0,
    UART1,
    SSI0,
    I2C0,
    PWM0_Fault,
    PWM0_Generator_0,
    PWM0_Generator_1,
    PWM0_Generator_2,
    QEI0,
    ADC0_Sequence_0,
    ADC0_Sequence_1,
    ADC0_Sequence_2,
    ADC0_Sequence_3,
    Watchdog_Timer,
    Timer_0A_16_32,
    Timer_0B_16_32,
    Timer_1A_16_32,
    Timer_1B_16_32,
    Timer_2A_16_32,
    Timer_2B_16_32,
    Analog_Comparator_0,
    Analog_Comparator_1,
    System_Control =28,
    Flash_EEPROM_Control,
    GPIO_Port_F,
    UART2 = 33,
    SSI1,
    Timer_3A_16_32,
    Timer_3B_16_32,
    I2C1,
    QEI1,
    CAN0,
    CAN1,
    Hibernation_Module = 43,
    USB,
    PWM_Generator_3,
    μDMA_Software,
    μDMA_Error,
    ADC1_Sequence_0,
    ADC1_Sequence_1,
    ADC1_Sequence_2,
    ADC1_Sequence_3,
    SSI2 = 57,
    SSI3,
    UART3,
    UART4,
    UART5,
    UART6,
    UART7,
    I2C2 = 68,
    I2C3,
    Timer_4A_16_32,
    Timer_4B_16_32,
    Timer_5A_16_32 = 92,
    Timer_5B_16_32,
    Timer_0A_32_64,
    Timer_0B_32_64,
    Timer_1A_32_64,
    Timer_1B_32_64,
    Timer_2A_32_64,
    Timer_2B_32_64,
    Timer_3A_32_64,
    Timer_3B_32_64,
    Timer_4A_32_64,
    Timer_4B_32_64,
    Timer_5A_32_64,
    Timer_5B_32_64,
    System_Exception,
    PWM1_Generator_0 = 134,
    PWM1_Generator_1,
    PWM1_Generator_2,
    PWM1_Generator_3,
    PWM1_Fault

}InterruptType;

 
#endif  /* INTCTRL_TYPES_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Types.h
 *********************************************************************************************************************/
