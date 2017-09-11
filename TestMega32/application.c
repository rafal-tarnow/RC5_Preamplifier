/*
 * application.c
 *
 *  Created on: 25 sty 2017
 *      Author: rafal
 */
#include "application.h"
#include <avr/io.h>
#include "TDA8425/TDA8425.h"
#include <stdint.h>
#include "external_interrupt/int.h"
#include <avr/interrupt.h>
#include "buttons/buttons.h"






void application_onStartup(){
	DDRA |= 0b00000111;

	TDA8425_init();

	init_buttons();

	rc5Init();

	sei();

}

void application_onRC5CodeReceived(uint8_t code){
	switch(code)
	{
	case 1://przrładowanie	W0
		PORTA ^= (1<<PA0);
		break;
	case 2://zatrzymanie	W0
		PORTA ^= (1<<PA1);
		break;
	case 3://dojazd do K1	W0
		PORTA ^= (1<<PA2);
		break;
	case 17://V-
		TDA8425_volumeDown();
		break;
	case 16://V+
		TDA8425_volumeUp();
		break;
	}
}

void application_onButtonChanged(Button button, ButtonState event){

		switch(button){
		case BUTTON_0:
			if(event == PRESSED){

				TDA8425_volumeUp();

				PORTA |= (1<<PA0);
			}else{
				PORTA &= ~(1<<PA0);
			}
			break;
		case BUTTON_1:
			if(event == PRESSED){

				TDA8425_changeChannel();

				PORTA |= (1<<PA1);
			}else{
				PORTA &= ~(1<<PA1);
			}
			break;
		case BUTTON_2:
			if(event == PRESSED){

				TDA8425_volumeDown();

				PORTA |= (1<<PA2);
			}else{
				PORTA &= ~(1<<PA2);
			}
			break;
		}

}
