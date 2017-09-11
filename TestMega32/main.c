


#define F_CPU 12000000UL
#include <util/delay.h>

#include "buttons/buttons.h"
#include "i2cbase/I2CBase.h"
#include "application.h"
#include <avr/interrupt.h>
#include "external_interrupt/int.h"
#include "Timer1/timer1.h"
#include "rc5/rc5.h"




int main(){



	application_onStartup();


	while(1){
		_delay_ms(1);
		scan_buttons();

		rc5Distribute();

	}

	return 0;
}
