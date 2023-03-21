/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Port_Regs.h
 *       Module:  Port
 *
 *  Description:  header file for port Registers definition    
 *  
 *********************************************************************************************************************/
#ifndef PORT_REGS_H
#define PORT_REGS_H

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
	

/*  GPIO REGISTERS   */

/*  #define  GPIO_AHB */

#define  GPIO_APB 
  

#ifdef  GPIO_APB
#define GPIO_OFFSET(x)                      (x<4?((0x40004000) + ((x)*0x1000)):((0x40024000) + ((x-4)*0x1000)))          

#define GPIO_PORT_A_OFFSET                   0x40004000
#define GPIO_PORT_B_OFFSET                   0x40005000
#define GPIO_PORT_C_OFFSET                   0x40006000
#define GPIO_PORT_D_OFFSET                   0x40007000
#define GPIO_PORT_E_OFFSET                   0x40024000
#define GPIO_PORT_F_OFFSET                   0x40025000

#define GPIODATA(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x3FC))
#define GPIODIR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0400))
#define GPIOIS(x)                            *((volatile uint32*)(GPIO_OFFSET(x) + 0x0404))
#define GPIOIBE(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0408))
#define GPIOIEV(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x040C))
#define GPIOIM(x)                          	 *((volatile uint32*)(GPIO_OFFSET(x) + 0x0410))
#define GPIORIS(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0414))
#define GPIOMIS(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0418))
#define GPIOICR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x041C))
#define GPIOAFSEL(x)                         *((volatile uint32*)(GPIO_OFFSET(x) + 0x0420))
#define GPIODR2R(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x0500))
#define GPIODR4R(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x0504))
#define GPIODR8R(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x0508))
#define GPIOODR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x050C))
#define GPIOPUR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0X0510))
#define GPIOPDR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0514))
#define GPIOSLR(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x0518))
#define GPIODEN(x)                           *((volatile uint32*)(GPIO_OFFSET(x) + 0x051C))
#define GPIOLOCK(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x0520))
#define GPIOCR(x)                            *((volatile uint32*)(GPIO_OFFSET(x) + 0x0524))
#define GPIOAMSEL(x)                         *((volatile uint32*)(GPIO_OFFSET(x) + 0x0528))
#define GPIOPCTL(x)                          *((volatile uint32*)(GPIO_OFFSET(x) + 0x052C))
#define GPIOADCCTL(x)                        *((volatile uint32*)(GPIO_OFFSET(x) + 0x0530))
#define GPIODMACTL(x)                        *((volatile uint32*)(GPIO_OFFSET(x) + 0x0534))
#define GPIOPeriphID4(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FD0))
#define GPIOPeriphID5(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FD4))
#define GPIOPeriphID6(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FD8))
#define GPIOPeriphID7(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FDC))
#define GPIOPeriphID0(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FE0))
#define GPIOPeriphID1(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FE4))
#define GPIOPeriphID2(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FE8))
#define GPIOPeriphID3(x)                     *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FEC))
#define GPIOPCellID0(x)                      *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FF0))
#define GPIOPCellID1(x)                      *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FF4))
#define GPIOPCellID2(x)                      *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FF8))
#define GPIOPCellID3(x)                      *((volatile uint32*)(GPIO_OFFSET(x) + 0x0FFC))


/*
#elif   GPIO_AHB
#define GPIO_PORT_A_OFFSET                   0x40058000
#define GPIO_PORT_B_OFFSET                   0x40059000
#define GPIO_PORT_C_OFFSET                   0x4005A000
#define GPIO_PORT_D_OFFSET                   0x4005B000
#define GPIO_PORT_E_OFFSET                   0x4005C000
#define GPIO_PORT_F_OFFSET                   0x4005D000
*/

#else
#error   "Please Check a Bus for GPIOs"
#endif

 

 
#endif  /* PORT_REGS_H */

/**********************************************************************************************************************
 *  END OF FILE: Port_Regs.h
 *********************************************************************************************************************/
