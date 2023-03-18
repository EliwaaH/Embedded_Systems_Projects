/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SysTick.h
 *       Module:  SysTick
 *
 *  Description:  header file for SysTick Peripheral    
 *  
 *********************************************************************************************************************/
#ifndef SYSTICK_H
#define SYSTICK_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
 
 
/* Datatype for holding the Values or Number of Counts that Reload Register will hold*/
typedef uint32   SysTick_Reload_Value;
 


/* Enum for SYSTICK Peripheral modes*/
typedef enum 
{
	SysTick_Disable,
	SysTick_Enable,
	
}SysTick_Mode;
 
 
/* Enum for SYSTICK Interrupt modes*/
typedef enum
{
	Interrupt_Disable,
	Interrupt_Enable,
	
}SysTick_Interrupt_Mode;


/* Enum for SYSTICK Clock Sources */
typedef enum
{
	Internal_Osc,
	System_Clock,
	
}SysTick_ClockSource;



/* Struct  to Hold the Configurations For User*/
typedef struct
{

	SysTick_Mode 							SysTickMode;
	SysTick_Interrupt_Mode 					InterruptMode;
	SysTick_ClockSource						ClockSource;
	
	
}SysTick_Config;


/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/

/* Create an Object of The Configurations Struct an Extern it to pass to other files*/
extern const SysTick_Config SysTick_Config_Modes;

 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



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
void SysTick_Set_ReloadValue(SysTick_Reload_Value ReloadValue);



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
uint8 SysTick_Set_Counts_Needed(uint8 Time_in_Sec);



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
void Clear_SysTick_Regs(void);



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
void SysTick_Init(const SysTick_Config* SysTickConfig_Ptr);




#endif  /* SYSTICK_H */

/**********************************************************************************************************************
 *  END OF FILE: SysTick.h
 *********************************************************************************************************************/
