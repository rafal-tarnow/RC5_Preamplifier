#ifndef _BUTTONS_H_

#define _BUTTONS_H_

#include "buttons_definitions.h"

void init_buttons();
void scan_buttons();
ButtonState getButtonState(Button button);

#endif
