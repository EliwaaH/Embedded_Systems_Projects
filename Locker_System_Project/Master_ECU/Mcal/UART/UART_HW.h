#ifndef UART_HW_H
#define UART_HW_H




/* UART CONTROL REGISTER A BITS (UCSRA) */
#define     RXC                  (7U)
#define     TXC                  (6U)
#define     UDRE                 (5U)
#define     FE                   (4U)
#define     DOR                  (3U)
#define     PE                   (2U)
#define     U2X                  (1U)
#define     MPCM                 (0U)


/* UART CONTROL REGISTER B BITS (UCSRB) */
#define     RXCIE                (7U)
#define     TXCIE                (6U)
#define     UDRIE                (5U)
#define     RXEN                 (4U)
#define     TXEN                 (3U)
#define     UCSZ2                (2U)
#define     RXB8                 (1U)
#define     TXB8                 (0U)


/* UART CONTROL REGISTER B BITS  (UCSRC) */
#define     URSEL                 (7U)
#define     UMSEL                 (6U)
#define     UPM1                  (5U)
#define     UPM0                  (4U)
#define     USBS                  (3U)
#define     UCSZ1                 (2U)
#define     UCSZ0                 (1U)
#define     UCPOL                 (0U)


/*The Required Bit in the UBRRH Register and UCSRC Register*/
#define    URSEL                  (7U)



#endif // !UART_HW_H