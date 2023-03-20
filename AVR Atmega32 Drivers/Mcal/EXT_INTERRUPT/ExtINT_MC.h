
#ifndef EXTINT_MC_H
#define EXTINT_MC_H


/* Global Interrupts Enable BIT (SERG) */
#define  I                             (7U)

/* Interrupt0 Enable BIT (GICR) */
#define  INT0                          (6U)

/* Interrupt1 Enable BIT (GICR) */
#define  INT1                          (7U)

/* Interrupt2 Enable BIT (GICR) */
#define  INT2                          (5U)

/* Interrupt0 Flag BIT (GIFR) */
#define  INTF0                         (6U)

/* Interrupt1 Flag BIT (GIFR) */
#define  INTF1                         (7U)

/* Interrupt2 Flag BIT (GIFR) */
#define  INTF2                         (5U)



/* Interrupt0 Sense Control BTIs (MCUCR) */
#define  ISC00                         (0U)
#define  ISC01                         (1U)


/* Interrupt1 Sense Control BTIs (MCUCR) */
#define  ISC10                         (2U)
#define  ISC11                         (3U)


/* Interrupt2 Sense Control BTI (MCUCSR) */
#define  ISC2                          (6U)



#endif // !EXTINT_MC_H