#ifndef TIMER0_HW_H
#define TIMER0_HW_H



/* TIMER/COUNTER CONTROL REGISTER BITS (TCCR0) */
#define        CS00        (0U)
#define        CS01        (1U)
#define        CS02        (2U)
#define        WGM01       (3U)
#define        COM00       (4U)
#define        COM01       (5U)
#define        WGM00       (6U)
#define        FOC0        (7U)



/* TIMER/COUNTER INTERRUPT MASK REGISTER BITS (TIMSK) */
#define        TOIE0       (0U)
#define        OCIE0       (1U)


/* TIMER/COUNTER INTERRUPT FLAG REGISTER BITS (TIFR) */
#define        TOV0        (0U)
#define        OCF0        (1U)

/* Global Interrupts Enable BIT (SERG) */
#define          I         (7U)


#endif // !TIMER0_HW_H