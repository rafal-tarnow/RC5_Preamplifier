#include "button_filter.h"
#include <stdint.h>



static void nullCallback(BitEvent bitEvent){}



void initBitFilter(BitFilterInstance *bitFilterInstance, uint8_t numberOfCorrectProbes){
	bitFilterInstance->callback = nullCallback;
	bitFilterInstance->previousFilteredKeyState = 2; // 2 - not defined, used for first scan
	bitFilterInstance->previousNotFilteredState = 0;
	bitFilterInstance->count = 0;
	bitFilterInstance->numberOfCorrectProbes = numberOfCorrectProbes;
}

void bitFilter_setOnBitChangeListener_signal(BitFilterInstance *bitFilterInstance, void (*nCallback)(BitEvent)){
	bitFilterInstance->callback = nCallback;
}


void callbackEventPressed(BitFilterInstance *bitFilterInstance){
	bitFilterInstance->callback(ACTION_DOWN);
}

void callbackEventReleased(BitFilterInstance *bitFilterInstance){
	bitFilterInstance->callback(ACTION_UP);
}

void przciskIsPressedFiltered(BitFilterInstance *bitFilterInstance){
	if(bitFilterInstance->previousFilteredKeyState != 1){
		bitFilterInstance->previousFilteredKeyState = 1;
		callbackEventPressed(bitFilterInstance);
	}
}

void przyciskIsReleasedFiltered(BitFilterInstance *bitFilterInstance){
	if(bitFilterInstance->previousFilteredKeyState != 0){
		bitFilterInstance->previousFilteredKeyState = 0;
		callbackEventReleased(bitFilterInstance);
	}
}


void incrementPressedProbe(BitFilterInstance *bitFilterInstance){

	if(bitFilterInstance->previousNotFilteredState == 1){
		bitFilterInstance->count++;
		if(bitFilterInstance->count == bitFilterInstance->numberOfCorrectProbes){
			przciskIsPressedFiltered(bitFilterInstance);
			bitFilterInstance->count = 1;
		}
	}else{
		bitFilterInstance->previousNotFilteredState = 1;
		bitFilterInstance->count = 1;
	}
}

void incrementReleasedProbe(BitFilterInstance *bitFilterInstance){
	if(bitFilterInstance->previousNotFilteredState == 0){
		bitFilterInstance->count++;
		if(bitFilterInstance->count == bitFilterInstance->numberOfCorrectProbes){
			przyciskIsReleasedFiltered(bitFilterInstance);
			bitFilterInstance->count = 1;
		}
	}else{
		bitFilterInstance->previousNotFilteredState = 0;
		bitFilterInstance->count = 1;
	}
}

void przciskIsPressedNotFiltered(BitFilterInstance *bitFilterInstance){
	incrementPressedProbe(bitFilterInstance);
}

void przyciskIsReleasedNotFiltered(BitFilterInstance *bitFilterInstance){
	incrementReleasedProbe(bitFilterInstance);
}
