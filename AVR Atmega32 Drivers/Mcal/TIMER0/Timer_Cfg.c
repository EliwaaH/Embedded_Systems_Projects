

#include "Timer0.h"





/***********************************************************************************************************************************************

***************************************************** Timer0  Configurations File ***************************************************************

    1- First Argument is the mode Of the Timer (Normal_Mode ,  CTC_Mode, FAST_PWM_Mode, Phase_Correct_PWM_MODE)
    
    2- Second Argument is the Mode of the PWM (Inverting or Non Inverting)

    3- The Third Argument is The CTC Mode If CTC mode Selected Thsi Option Will be Put in Consideration 

    4- The Fourth Argument is the Prescaler 

***********************************************************************************************************************************************/





const Timer0_Config_Type    Timer0Config = 
{
    Fast_PWM_Mode,
    PWM_NonInverting_Mode,
    CTC_Set,
    Prescaler_64_,

};