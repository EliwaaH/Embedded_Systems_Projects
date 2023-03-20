#ifndef I2C_HW_H
#define I2C_HW_H


/* I2C --> TWBR Register Bits*/

#define   TWBR0                  (0U)
#define   TWBR1                  (1U)
#define   TWBR2                  (2U)
#define   TWBR3                  (3U)
#define   TWBR4                  (4U)
#define   TWBR5                  (5U)
#define   TWBR6                  (6U)
#define   TWBR7                  (7U)



/* I2C --> TWCR Register Bits*/

#define   TWIE                   (0U)
#define   TWEN                   (2U)
#define   TWWC                   (3U)
#define   TWSTO                  (4U)
#define   TWSTA                  (5U)
#define   TWEA                   (6U)
#define   TWINT                  (7U)



/* I2C --> TWSR Register Bits*/

#define   TWPS0                  (0U)
#define   TWPS1                  (1U)
#define   TWS3                   (3U)
#define   TWS4                   (4U)
#define   TWS5                   (5U)
#define   TWS6                   (6U)
#define   TWS7                   (7U)

/* I2C --> TWAR Register Bits*/

#define   TWGCE                  (0U)
#define   TWA0                   (1U)
#define   TWA1                   (2U)
#define   TWA2                   (3U)
#define   TWA3                   (4U)
#define   TWA4                   (5U)
#define   TWA5                   (6U)
#define   TWA6                   (7U)


/* READ -- WRITE BIT*/
#define   TWD0                   (0U)

#endif // I2C_HW_H