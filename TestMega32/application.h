/*
 * application.h
 *
 *  Created on: 25 sty 2017
 *      Author: rafal
 */

#ifndef APPLICATION_H_
#define APPLICATION_H_

#include "buttons/buttons_definitions.h"
#include <stdint.h>

void application_onStartup();

void application_onButtonChanged(Button button, ButtonState state);
void application_onRC5CodeReceived(uint8_t code);

#endif /* APPLICATION_H_ */
