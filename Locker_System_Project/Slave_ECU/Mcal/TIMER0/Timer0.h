#ifndef TIMER0_H
#define TIMER0_H
 

#include "Platform_Types.h"


typedef void(*Call_Back)(void);


typedef enum
{
    Normal_Mode,
    CTC_Mode,
    Fast_PWM_Mode,
    PhaseCorrect_PWM_Mode,

}TIMER0_Modes;



typedef enum
{
    PWM_OFF,
    PWM_Inverting_Mode,
    PWM_NonInverting_Mode,

}PWM_Oper_Modes;

typedef enum 
{
    CTC_Toggle,
    CTC_Set,
    CTC_Clear,

}CTC_Modes;


typedef enum
{
    Prescaler_OFF_,
    Prescaler_8_,
    Prescaler_64_,
    Prescaler_256_,
    Prescaler_1024_,

}Prescaler_Mode_;


typedef struct 
{   
    TIMER0_Modes        Timer0_mode;
    PWM_Oper_Modes      PWM_mode;
    CTC_Modes           CTC_mode;
    Prescaler_Mode_      PrescalerMode;
    
}Timer0_Config_Type;


extern const Timer0_Config_Type    Timer0Config;

void Timer0_OVF_CB(Call_Back ptr);
void Timer0_COMP_CB(Call_Back ptr);

void TIMER0_Init(const Timer0_Config_Type ConfigCont);
void CTC_Mode_ON(uint8 Data_Counts);
void PWM_ON(uint8 DutyCycle_Counts);


#endif 