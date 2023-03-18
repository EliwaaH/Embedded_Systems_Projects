/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  IntCrtl.h
 *       Module:  IntCrtl
 *
 *  Description:  header file for IntCrtl Module    
 *  
 *********************************************************************************************************************/
#ifndef IntCrtl_H
#define IntCrtl_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl_Types.h"
#include "IntCtrl_Cfg.h"


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/

/* Creating DataTyp of a Poitner to Function Refers to the Call Back Functionto */
typedef  void(*CB_type)(void);


/* Enum for Priorites to be use in the Configurations Struct*/
typedef enum 
{
    PRIORITY_0,
    PRIORITY_1,
    PRIORITY_2,
    PRIORITY_3,
    PRIORITY_4,
    PRIORITY_5,
    PRIORITY_6,
    PRIORITY_7,

}ExceptionPriority;


/* Struct that will hold the Configurations that User will enter */
typedef struct
{
    ExceptionType           Exception_type;
    ExceptionPriority       Exception_Priority;

}Exceptions_Config;

 
 
/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/


/* Creating an Array of Struts to Hold the Configurations that User will Enter*/
extern const Exceptions_Config ExceptionsTypeConfig[NUMBER_OF_EXCEPTIONS];


/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
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
void Interrupt_CB(CB_type ptr);



/******************************************************************************
* \Syntax          : void IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void IntCrtl_Init(const Exceptions_Config* ExceptionsConfigPtr);
 
#endif  /* IntCrtl_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCrtl.h
 *********************************************************************************************************************/
