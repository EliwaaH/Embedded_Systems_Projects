#ifndef SEVEN_SEGMENT_H
#define SEVEN_SEGMENT_H

#include "Platform_Types.h"
#include "PORT.h"

typedef enum {
	CATHOD = 0,
	ANODE
} seg_Type_T;

typedef enum {
	number_0 = 0,
	number_1,
	number_2,
	number_3,
	number_4,
	number_5,
	number_6,
	number_7,
	number_8,
	number_9,
}seg_number_T;

typedef struct
{
	Dio_PortType     PortID;
	seg_Type_T 		 seg_Type;
	seg_number_T 	 seg_number;

} sevenSegment_T;

extern const sevenSegment_T    SevenSegment_Config;

void segment_init(sevenSegment_T sevenSegment);
void segment_set_number(sevenSegment_T sevenSegment, uint8 Digit);

#endif /* SEVEN_SEGMENT_H */
