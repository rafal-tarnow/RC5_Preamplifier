#ifndef _BUTTON_FILTER_H_
#define _BUTTON_FILTER_H_

#include <stdint.h>


typedef enum{
	ACTION_DOWN,
	ACTION_UP
} BitEvent;


typedef struct{
	volatile	uint8_t previousNotFilteredState;
	volatile	uint8_t count;
	uint8_t previousFilteredKeyState;
	uint8_t numberOfCorrectProbes;
	void (*callback)(BitEvent);
}BitFilterInstance;

void initBitFilter(BitFilterInstance *bitFilterInstance, uint8_t numberOfCorrectProbes);
void bitFilter_setOnBitChangeListener_signal(BitFilterInstance *bitFilterInstance, void (*nCallback)(BitEvent));


void przciskIsPressedNotFiltered(BitFilterInstance *bitFilterInstance);
void przyciskIsReleasedNotFiltered(BitFilterInstance *bitFilterInstance);


#endif
