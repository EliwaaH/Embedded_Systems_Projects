
#ifndef  BIT_MATH_H
#define  BIT_MATH_H


#define  SET_BIT(PORT, BIT)             (PORT |= (1 << BIT))
#define  CLEAR_BIT(PORT, BIT)           (PORT = PORT & (~(1<<BIT)))
#define  TOGGLE_BIT(PORT, BIT)          (PORT ^= (1 << BIT))
#define  READ_BIT(PORT, BIT)            ((PORT >> BIT) & 1)
#define  BIT_IS_SET(PORT, BIT)          ((PORT & (1 << BIT)) >> BIT)
#define  BIT_IS_CLEAR(PORT, BIT)        (!(PORT & (1 << BIT)) >> BIT)


#endif