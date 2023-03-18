/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  SCB.h
 *       Module:  System Control Block
 *
 *  Description:  header file for Registers definition  of the System Control Block Peripheral  
 *  
 *********************************************************************************************************************/
#ifndef SCB_H
#define SCB_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"

/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/




/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define CORTEXM4_PERI_BASE_ADDRESS             0xE000E000





#define ACTLR                                  *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0x008))
#define CPUID                                  *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0x008))
#define INTCTRL                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD04))
#define VTABLE                                 *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD08))
#define APINT                                  *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD0C)) 
#define SYSCTRL                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD10))
#define CFGCTRL                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD14))
#define SYSPRI1                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD18))
#define SYSPRI2                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD1C))
#define SYSPRI3                                *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD20))
#define SYSHNDCTRL                             *((volatile uint32*)(CORTEXM4_PERI_BASE_ADDRESS + 0xD24))




/****************************************** SYSHNDCTRL REGISTER BITS NUMBER **********************************************************/

#define MEMA                                   (uint8)(0U)
#define BUSA                                   (uint8)(1U)
#define USGA                                   (uint8)(3U)
#define SVCA                                   (uint8)(7U)
#define MON                                    (uint8)(8U)
#define PNDSV                                  (uint8)(10U)
#define TICK                                   (uint8)(11U)
#define USAGEP                                 (uint8)(12U)
#define MEMP                                   (uint8)(13U)
#define BUSP                                   (uint8)(14U)
#define SVC                                    (uint8)(15U)
#define MEM                                    (uint8)(16U)
#define BUS                                    (uint8)(17U)
#define USAGE                                  (uint8)(18U)


#endif  /* SCB_H */

/**********************************************************************************************************************
 *  END OF FILE: SCB.h
 *********************************************************************************************************************/
