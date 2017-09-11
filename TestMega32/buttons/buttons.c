#include <avr/io.h>
#include "buttons.h"

#include "buttons_definitions.h"
#include "button_filter.h"
#include "../application.h"

void init_gpios();
void init_bit_filters();

//	PP = 0,
//	PL,
//	PK,



static BitFilterInstance Button_0_filter; //W1
static BitFilterInstance Button_1_filter; //W2
static BitFilterInstance Button_2_filter; //W3


void Button0_filtered(BitEvent bitEvent);
void Button1_filtered(BitEvent bitEvent);
void Button2_filtered(BitEvent bitEvent);



void init_buttons(){
		init_bit_filters();
		init_gpios();
}

/*
PP = 0,
PL,
PK,
TG,
TD,
SPUST_1,
SPUST_2,
BLOKADA
 */



void init_bit_filters(){
		initBitFilter(&Button_0_filter, 5);
		bitFilter_setOnBitChangeListener_signal(&Button_0_filter,Button0_filtered);

		initBitFilter(&Button_1_filter, 5);
		bitFilter_setOnBitChangeListener_signal(&Button_1_filter,Button1_filtered);

		initBitFilter(&Button_2_filter, 5);
		bitFilter_setOnBitChangeListener_signal(&Button_2_filter,Button2_filtered);

}

void init_gpios(){
	//input
	DDRC |= (1<<PC6); //button0
	DDRC |= (1<<PC5); //button1
	DDRC |= (1<<PC4); //button2

	//input type
	PORTC |= (1<<PC6); //button0
	PORTC |= (1<<PC5); //button1
	PORTC |= (1<<PC4); //button2

	SFIOR &= ~(1<<PUD); //enable pullups

}

ButtonState button_0_state = RELEASED;
ButtonState button_1_state = RELEASED;
ButtonState button_2_state = RELEASED;



void Button0_filtered(BitEvent bitEvent){
	switch(bitEvent){
	case ACTION_UP:
		application_onButtonChanged(BUTTON_0,RELEASED);
		button_0_state = RELEASED;
		break;
	case ACTION_DOWN:
		application_onButtonChanged(BUTTON_0,PRESSED);
		button_0_state = PRESSED;
		break;
	}
}
void Button1_filtered(BitEvent bitEvent){
	switch(bitEvent){
	case ACTION_UP:
		application_onButtonChanged(BUTTON_1,RELEASED);
		button_1_state = RELEASED;
		break;
	case ACTION_DOWN:
		application_onButtonChanged(BUTTON_1,PRESSED);
		button_1_state = PRESSED;
		break;
	}
}
void Button2_filtered(BitEvent bitEvent){
	switch(bitEvent){
	case ACTION_UP:
		application_onButtonChanged(BUTTON_2,RELEASED);
		button_2_state = RELEASED;
		break;
	case ACTION_DOWN:
		application_onButtonChanged(BUTTON_2,PRESSED);
		button_2_state = PRESSED;
		break;
	}
}




ButtonState getButtonState(Button button){
	switch(button){
	case BUTTON_0:
		return button_0_state;
		break;
	case BUTTON_1:
		return button_1_state;
		break;
	case BUTTON_2:
		return button_2_state;
		break;
	}
}


void scan_buttons(){
	//0
	if(PINC & (1<<PC6)){
		przyciskIsReleasedNotFiltered(&Button_0_filter);
	}else{
		przciskIsPressedNotFiltered(&Button_0_filter);
	}
	//1
	if(PINC & (1<<PC5)){
		przyciskIsReleasedNotFiltered(&Button_1_filter);
	}else{
		przciskIsPressedNotFiltered(&Button_1_filter);
	}
	//2
	if(PINC & (1<<PC4)){
		przyciskIsReleasedNotFiltered(&Button_2_filter);
	}else{
		przciskIsPressedNotFiltered(&Button_2_filter);
	}
}


