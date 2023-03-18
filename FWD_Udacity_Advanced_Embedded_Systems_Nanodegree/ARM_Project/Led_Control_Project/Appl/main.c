#include "PORT.h"
#include "IntCtrl.h"
#include "SysTick.h"
#include "Bit_Math.h"


/* Global Static Variables to Save The Values of Number of Overflows Needed for Each Time*/
static uint8 on_overflows_needed;
static uint8 off_overflows_needed;


uint8 set_on_off_time(uint8 switch_PortNum, uint8 switch_PinNum, uint8 button_PortNum, uint8 button_PinNum);



/* SysTick Handler */
void Handle_SysTick_Driver_isr(void)
{
	/* Isr Counter to Count How Many Times Overflow Happens*/ 
	static uint8 Isr_Counter;
	
	/* Flag to be Used as an Indicator that ON time Condition is handeled and start handling the Off Time Condition*/
	static uint8  Isr_Flag;

	Isr_Counter++;	
	
	if(Dio_ReadChannel(Port_PinConfig[2].PortNum, Port_PinConfig[2].PortPinNum) == 0)
	{
		
		/* ON Time Condition -- When ON Time Finished TurnOff The Led and Raise The Flag, Also Clear the Counter*/
		if((Isr_Flag == 0) && (Isr_Counter == on_overflows_needed))
		{
			Dio_ClearChannel(Port_PinConfig[0].PortNum, Port_PinConfig[0].PortPinNum);
			Isr_Flag = 1;
			Isr_Counter = 0;
		}
	
		/* OFF Time Condition -- When Off Time Finished Turn on the Led and Clear The Number of Overflows To Start the
		 Period Again, ALso Clear the Counter and Flag*/
		else if((Isr_Flag == 1) && (Isr_Counter == off_overflows_needed))
		{
			Dio_WriteChannel(Port_PinConfig[0].PortNum, Port_PinConfig[0].PortPinNum);
			off_overflows_needed = 0 , on_overflows_needed = 0;
			Isr_Counter = 0;
			Isr_Flag = 0;
		}
		
	}
	
	else{
		Isr_Counter = 0;
		Isr_Flag = 0;
	}
}




int main(void)
{
	/* Suppose to Enable SYSTICK Peripheral but it's already Activated by Default */
	
	/*IntCrtl_Init(ExceptionsTypeConfig);*/
	
	
	/* Initialize The SysTick Module*/
	SysTick_Init(&SysTick_Config_Modes);
	
	/*Initialize Selected Pins With Ports*/
	Port_Init(Port_PinConfig);

	/* Pass The Address of the Handle_SysTick_Driver_isr to the Pointer to Function that being Handled in the
		 SysTick_Handler */
	Interrupt_CB(Handle_SysTick_Driver_isr);
	
	
	
	uint8 Led_PortNum = Port_PinConfig[0].PortNum;
	uint8 Led_PinNum  = Port_PinConfig[0].PortPinNum;
	
	uint8 PortNum_on_off  = Port_PinConfig[1].PortNum;
	uint8 PinNum_on_off   = Port_PinConfig[1].PortPinNum;
	
	uint8 PortNum_Switch = Port_PinConfig[2].PortNum;
	uint8 PinNum_Switch  = Port_PinConfig[2].PortPinNum;

	
	uint8 Counter_on = 0, Counter_off = 0;
	
	while(1){
		
		/* Close The Switch to Set ON Time by Pressing the Button with the Number of On Time Seconds
       Then Open the Switch to Set the ON Time	*/
		Counter_on = set_on_off_time(PortNum_Switch, PinNum_Switch, PortNum_on_off, PinNum_on_off);
		
		/* Close The Switch Again to Set OFF Time by Pressing the Button with the Number of OFF Time Seconds
     Then Open the Switch to Set the OFF Time	*/
		Counter_off = set_on_off_time(PortNum_Switch, PinNum_Switch, PortNum_on_off, PinNum_on_off);
		
		/* Turn on The Led to Start Period*/
		Dio_WriteChannel(Led_PortNum, Led_PinNum);
		
		
		/* Only will enter this loop whne first the switch is opened 
			Second - ON Time is not zero 
		  Third  - OFF Time is not Zero */
		while((Dio_ReadChannel(PortNum_Switch, PinNum_Switch) == 0) && (Counter_on > 0) && (Counter_off > 0))
		{
			on_overflows_needed = SysTick_Set_Counts_Needed(Counter_on);
			
			off_overflows_needed = SysTick_Set_Counts_Needed(Counter_off);
		}
		
	}
	
}



/**********************************************************************************************************************
*  Function name      : set_on_off_time
*  Syntax            : uint8 set_on_off_time( uint8 switch_PortNum, uint8 switch_PinNum
*                                             uint8 button_PortNum, uint8 button_PinNum )
*  Mode              : User Mode (Non-Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : uint8 switch_PortNum --  uint8 switch_PinNum 
											 uint8 button_PortNum -- uint8 button_PinNum        
*  Parameters (inout): None
*  Parameters (out)  : Counter
*  Return value      : None
*  Description       : Function That Using the Switch and Button to Set The ON and OFF Times To Control The Led.
*  *********************************************************************************************************************/

uint8 set_on_off_time(uint8 switch_PortNum, uint8 switch_PinNum, uint8 button_PortNum, uint8 button_PinNum)
{
	uint8 counter = 0;
	
	 /*Only Will Enter this Loop When the Switch is Closed  */
		while(Dio_ReadChannel(switch_PortNum, switch_PinNum) == 1)
		{
			if(Dio_ReadChannel(button_PortNum, button_PinNum) == 1)
			{
				counter++;
			}
		}
		return counter;
}



