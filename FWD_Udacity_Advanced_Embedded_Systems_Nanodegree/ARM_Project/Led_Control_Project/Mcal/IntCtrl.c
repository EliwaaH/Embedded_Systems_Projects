/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCrtl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"
#include "IntCtrl.h"
#include "SCB_Regs.h"
#include "Bit_Math.h"


/**********************************************************************************************************************
 *  LOCAL DATA Types
 *********************************************************************************************************************/

/* Cretaing a Varibale of the DataType CB_type*/
CB_type Callback_ptr = NULL_PTR;


/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/



/*  The IRQ Handler of SYSTICK Peripheral */
void SysTick_Handler(void);



/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/**************************************************************************************
* \Syntax          : void Interrupt_CB(CB_type ptr)                                      
* \Description     : Function thar Act as a Protector or Guared for Entering the ISR
					 SYSTICK Handler
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : CB_type -- ptr                    
* \Parameters (out): None                                                      
* \Return value:   : None
*****************************************************************************************/
void Interrupt_CB(CB_type ptr)
{
	if (NULL_PTR != ptr)
	{
		Callback_ptr = ptr;
	}
}



/**************************************************************************************
* \Syntax          : void IntCrtl_Init(const Exceptions_Config* ExceptionsConfigPtr)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : const Exceptions_Config* -- ExceptionsConfigPtr                     
* \Parameters (out): None                                                      
* \Return value:   : None
*****************************************************************************************/
void IntCrtl_Init(const Exceptions_Config* ExceptionsConfigPtr)
{

		
	  uint8 u8_ptrcount=0;
    for(u8_ptrcount=0; u8_ptrcount<NUMBER_OF_EXCEPTIONS; u8_ptrcount++)
    {
        if(SysTick == ExceptionsConfigPtr[u8_ptrcount].Exception_type)
        {
           /*SET_BIT(SYSHNDCTRL, TICK);*/
        }
    }	
}




/*  The IRQ Handler of SYSTICK Peripheral */
void SysTick_Handler(void)
{
	if(NULL_PTR != Callback_ptr)
	{
		Callback_ptr();
	}
}


/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.c
 *********************************************************************************************************************/
