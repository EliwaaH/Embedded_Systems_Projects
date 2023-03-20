#include "TIMER0_HW.h"
#include "REGISTERS.h"
#include "Bit_Math.h"
#include "PORT.h"
#include "Timer0.h"
#include <avr/interrupt.h>



Call_Back Callback_ptr_OVF  = NULL;

Call_Back Callback_ptr_COMP = NULL;



void Timer0_OVF_CB(Call_Back ptr)
{
    if(ptr != NULL)
    {
        Callback_ptr_OVF = ptr;
    }
}



void Timer0_COMP_CB(Call_Back ptr)
{
    if(ptr != NULL)
    {
        Callback_ptr_COMP = ptr;
    }
}


void TIMER0_Init(const Timer0_Config_Type ConfigCont)
{
    uint8 TimerMode     = ConfigCont.Timer0_mode;
    uint8 PrescalerVal  = ConfigCont.PrescalerMode;
    uint8 PWMmode       = ConfigCont.PWM_mode;
    uint8 CTCmode       = ConfigCont.CTC_mode;


    if(TimerMode == Normal_Mode)
    {   
        // Enable Normal Mode
        TCCR0 = (0 << WGM00) | (0 << WGM01) | (0 << COM00) | (0 << COM01);

        // Enable Interrupt Mode
        SET_BIT(TIMSK, TOIE0);

        // Enable Global Interrupts
        SET_BIT(SREG, I);
    }

    else if(TimerMode == CTC_Mode)
    {
        switch (CTCmode)
        {
            case CTC_Toggle:

                TCCR0 = (0 << WGM00) | (1 << WGM01) | (1 << COM00) | (0 << COM01);
                break;
        
            case CTC_Set:
                TCCR0 = (0 << WGM00) | (1 << WGM01) | (1 << COM00) | (1 << COM01);
                break;

            case CTC_Clear:
                TCCR0 = (0 << WGM00) | (1 << WGM01) | (0 << COM00) | (1 << COM01);
        }
 
    }

    else if (TimerMode == Fast_PWM_Mode)
    {   
        switch(PWMmode)
        {
            case PWM_Inverting_Mode:
                TCCR0 = (1 << WGM00) | (1 << WGM01) | (1 << COM00) | (1 << COM01);
                break;

            case PWM_NonInverting_Mode:
                TCCR0 = (1 << WGM00) | (1 << WGM01) | (0 << COM00) | (1 << COM01);
        }
    }
    

    else if (TimerMode == PhaseCorrect_PWM_Mode)
    {   
        switch(PWMmode)
        {
            case PWM_Inverting_Mode:
                TCCR0 = (1 << WGM00) | (0 << WGM01) | (1 << COM00) | (1 << COM01);
                break;

            case PWM_NonInverting_Mode:
                TCCR0 = (1 << WGM00) | (0 << WGM01) | (0 << COM00) | (1 << COM01);
        }
    }



    switch (PrescalerVal)
    {
        case Prescaler_OFF_:
            TCCR0 |= (1 << CS00) | (0 << CS01) | (0 << CS02);       
            break;
    
        case Prescaler_8_:
            TCCR0 |= (0 << CS00) | (1 << CS01) | (0 << CS02);
            break;

        case Prescaler_64_:
            TCCR0 |= (1 << CS00) | (1 << CS01) | (0 << CS02);
            break;
        
        case Prescaler_256_:
            TCCR0 |= (0 << CS00) | (0 << CS01) | (1 << CS02);
            break;

        case Prescaler_1024_:
            TCCR0 |= (1 << CS00) | (0 << CS01) | (0 << CS02);
    }
}


void CTC_Mode_ON(uint8 Data_Counts)
{
	/* Set The Direction of OC0 PIN in ATmega32 MicroController As Output Pin */
	Dio_SetChannelDirection(PORT_B, PIN3, OUTPUT);
	
    /* Load the Compare Value into The Compare Register*/
    OCR0 = Data_Counts;

    /* Enable The CTC Interrupt*/
    SET_BIT(TIMSK, OCIE0);

    /* Enable the Global Interrupt*/
    SET_BIT(SREG, I);
}



void PWM_ON(uint8 DutyCycle_Counts)
{
	/* Set The Direction of OC0 PIN in ATmega32 MicroController As Output Pin */
	Dio_SetChannelDirection(PORT_B, PIN3, OUTPUT);
	
    /* Load the Compare Value into The Compare Register*/
    OCR0 = DutyCycle_Counts;

    /* Enable The CTC Interrupt*/
    SET_BIT(TIMSK, OCIE0);

    /* Enable the Global Interrupt*/
    SET_BIT(SREG, I);
}






ISR (TIMER0_OVF_vect)
{
    if(NULL != Callback_ptr_OVF)
    {
        Callback_ptr_OVF();
    }
    

}

ISR (TIMER0_COMP_vect)
{

    if(NULL != Callback_ptr_COMP)
    {
        Callback_ptr_COMP();
    }

}


