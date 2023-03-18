/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  Bit_Math.h
 *    Component:  -
 *       Module:  -
 *
 *  Description:  Provision of The Required Operations on Specific Bits in Registers
 *
 *********************************************************************************************************************/



#ifndef BIT_MATH_H
#define BIT_MATH_H


/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/

/* Set a Certain Bit in Any Rgister */
#define SET_BIT(REG, BIT)                   (REG|=(1<<BIT))

/* Clear a Certain Bit in Any Rgister */
#define CLEAR_BIT(REG, BIT)                 (REG&=(~(1<<BIT)))

/* Toggle a Certain Bit in Any Rgister */
#define TOGGLE_BIT(REG, BIT)                (REG^=(1<<BIT))

/* Rotate right the register value with a specific value of rotates */
#define ROR(REG, num)                       (REG = (REG>>num) | (REG << ((sizeof(REG) * 8)-num)) )
	
/* Rotate left the register value with a specific value of rotates */
#define ROL(REG, num)                       (REG = (REG<<num) | (REG >> ((sizeof(REG) * 8)-num)) )

/*Chech If a specific bit is set in any register and return its value */
#define BIT_IS_SET(REG, BIT)                ( (REG & (1 << BIT)) >> BIT)

/*Chech If a specific bit is clear in any register and return its value */
#define BIT_IS_CLEAR(REG, BIT)              ( !(REG & (1 << BIT)) >> BIT) 



#endif /* BIT_MATH_H */
/**********************************************************************************************************************
 *  END OF FILE: Bit_Math.h
 *********************************************************************************************************************/