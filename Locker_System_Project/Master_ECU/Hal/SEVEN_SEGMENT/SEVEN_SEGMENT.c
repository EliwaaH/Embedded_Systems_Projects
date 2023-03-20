

#include "SEVEN_SEGMENT.h"


static uint8 auint8segmentIndex[10] =
{		
		0b00111111, /* 0 */
		0b00000110, /* 1 */
		0b01011011, /* 2 */
		0b01001111, /* 3 */
		0b01100110, /* 4 */
		0b01101101, /* 5 */
		0b01111101, /* 6 */
		0b00000111, /* 7 */
		0b01111111, /* 8 */
		0b01101111  /* 9 */
};

void segment_init(sevenSegment_T sevenSegment)
{
	Dio_SetPortDirection(sevenSegment.PortID, 0xFF);

	if( sevenSegment.seg_Type == ANODE)
	{

		Dio_WritePort(sevenSegment.PortID,
				~auint8segmentIndex[sevenSegment.seg_number]);
	}
	else if(sevenSegment.seg_Type  == CATHOD)
	{


		Dio_WritePort(sevenSegment.PortID,
				auint8segmentIndex[sevenSegment.seg_number]);
	}
	else
	{

	}
}
void segment_set_number(sevenSegment_T sevenSegment, uint8 Digit)
{
	
	if(sevenSegment.seg_Type == ANODE)
	{
		Dio_WritePort(sevenSegment.PortID,
			   ~auint8segmentIndex[Digit]);

	}
	else if(sevenSegment.seg_Type  == CATHOD)
	{
		Dio_WritePort(sevenSegment.PortID,
				auint8segmentIndex[Digit]);
	}
	else{

	}
}

