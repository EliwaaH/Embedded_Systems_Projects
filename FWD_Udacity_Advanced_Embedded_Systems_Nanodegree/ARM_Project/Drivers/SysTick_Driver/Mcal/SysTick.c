/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  SysTick.c
 *        \brief  
 *
 *      \details  
 *
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "SysTick.h"
#include "SysTick_Regs.h"
#include "Bit_Math.h"


/*SysTick Overflow Counts for one Second*/
#define SYSTICK_OVERFLOW_COUNTS                       (0x00FFFFFF)

/* Time in Seconds for SYSTICK to Overflow*/
#define SYSTICK_OVERFLOW_TIME                         (uint8)(1U)

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 **********************************************************************************************************************/



/**********************************************************************************************************************
*  Service name      : SysTick_Set_ReloadValue
*  Syntax            : void SysTick_Set_ReloadValue( SysTick_Reload_Value ReloadValue)
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : SysTick_Reload_Value - Reload Value 
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Put The Reload Value in SYSTICK RELOAD REGISTER.
*  *********************************************************************************************************************/

void SysTick_Set_ReloadValue(SysTick_Reload_Value ReloadValue)
{
	STRELOAD  = ReloadValue;
}


/**********************************************************************************************************************
*  Service name      : SysTick_Set_Counts_Needed
*  Syntax            : uint8 SysTick_Set_Counts_Needed(uint8 Time_in_Sec)
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : uint8 -  Time_in_Sec
*  Parameters (inout): None
*  Parameters (out)  : Number of Overflows Needed
*  Return value      : None
*  Description       : Service to Return The Number of The Overflows Needed Based on the Input Time in Seconds.
*  *********************************************************************************************************************/
uint8 SysTick_Set_Counts_Needed(uint8 Time_in_Sec)
{
	
	float32 NUMBER_OF_COUNTS_NEEDED=0 , NUMBER_OF_OVERFLOWS_NEEDED=0;
	
	if (Time_in_Sec == SYSTICK_OVERFLOW_TIME)
	{
		
		SysTick_Set_ReloadValue(SYSTICK_OVERFLOW_COUNTS);
		
		return 1;
		
	}
	
	else if(Time_in_Sec > SYSTICK_OVERFLOW_TIME)
	{
		NUMBER_OF_OVERFLOWS_NEEDED = Time_in_Sec / SYSTICK_OVERFLOW_TIME;
		
		SysTick_Set_ReloadValue(SYSTICK_OVERFLOW_COUNTS);
		
		return NUMBER_OF_OVERFLOWS_NEEDED;
	}
	
	return 0;
}


/**********************************************************************************************************************
*  Service name      : Clear_SysTick_Regs
*  Syntax            : void Clear_SysTick_Regs(void)
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Reentrant
*  Parameters (in)   : None
*  Parameters (inout): None
*  Parameters (out)  : None
*  Return value      : None
*  Description       : Service to Clear The Register of SYSTICK 
*  *********************************************************************************************************************/
void Clear_SysTick_Regs(void)
{
	STRELOAD = 0x0;
	STCURRENT = 0x0;
}



/**********************************************************************************************************************
*  Service name      : SysTick_Init
*  Syntax            : void SysTick_Init(const SysTick_Config* SysTickConfig_Ptr)
*  Mode              : Supervisor Mode (Privileged Mode)
*  Sync/Async        : Synchronous
*  Reentrancy        : Non Reentrant
*  Parameters (in)   : const SysTick_Config*  --  SysTickConfig_Ptr
*  Parameters (inout): None
*  Parameters (out)  : Number of Overflows Needed
*  Return value      : None
*  Description       : Service to Initialize the SYSTICK Peripheral
*  *********************************************************************************************************************/
void SysTick_Init(const SysTick_Config* SysTickConfig_Ptr)
{
	/* Check if the SysTick Peripheral is Enabled or not */
	if(SysTick_Enable == SysTickConfig_Ptr->SysTickMode)
	{
		SET_BIT(STCTRL, ENABLE_BIT);
	
	}
	
	/*If SysTick Peripheral is Disabled Exit the Initilization Function */
	else if(SysTick_Disable == SysTickConfig_Ptr->SysTickMode)
	{
		return;
	}
	
	/* Check if the SysTick Interrupt is Enabled or not */
	if(Interrupt_Enable == SysTickConfig_Ptr->InterruptMode)
	{
		SET_BIT(STCTRL, INTERRUPT_BIT);
	}

		
	/* Check if the SysTick Clock Source is System CLock */
	if(System_Clock == SysTickConfig_Ptr->ClockSource)
	{
		SET_BIT(STCTRL, CLOCK_SOURCE_BIT);
	}
		
	/* Check if the SysTick Clock Source is Internal Oscillator */
	else if(Internal_Osc == SysTickConfig_Ptr->ClockSource)
	{
		CLEAR_BIT(STCTRL, CLOCK_SOURCE_BIT);
	}
	
	/* Put The Value of Counts You Want Timer to Start at in the RELOAD Register */
	/* STRELOAD  = ReloadValue; */
}


/**********************************************************************************************************************
 *  END OF FILE: SysTick.c
 *********************************************************************************************************************/
