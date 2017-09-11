/*
 * timer_1.c
 *
 *  Created on: 3 lut 2017
 *      Author: rafal
 */
#include "timer1.h"
#include <avr/interrupt.h>
#include <stdlib.h>

static void (*funkcjaObslugiPrzerwania)() = NULL;

/* Timer/Counter1 Capture Event */
ISR(TIMER1_CAPT_vect)
{

}

/* Timer/Counter1 Compare Match A */
ISR(TIMER1_COMPA_vect)
{
	funkcjaObslugiPrzerwania();

}

/* Timer/Counter1 Compare Match B */
ISR(TIMER1_COMPB_vect)
{

}

/* Timer/Counter1 Overflow */
ISR(TIMER1_OVF_vect)
{
	PORTA ^= (1<<PA0);
}





void init_timer1(void (*przerwanie)()){

		funkcjaObslugiPrzerwania = przerwanie;

		TCCR1A &= ~(1<<COM1A1); //Normal port operation, OC1A disconnected
		TCCR1A &= ~(1<<COM1A0); //Normal port operation, OC1A disconnected

		TCCR1A &= ~(1<<COM1B1); //Normal port operation, OC1B disconnected
		TCCR1A &= ~(1<<COM1B0); //Normal port operation, OC1B disconnected


		Timer1_WriteOCR1A(14992);

		//MODE 4 , clear timer on compate match OCR1A
		TCCR1B &= ~(1<<WGM13);
		TCCR1B |= (1<<WGM12);
		TCCR1A &= ~(1<<WGM11);
		TCCR1A &= ~(1<<WGM10);


		TIMSK |= (1<<OCF1A); //Output Compare A Match Interrupt Enable
		TIMSK |= (1<<TOIE1); //Overflow Interrupt Enable

		//TCCR1B &= (~(1<<CS12)) & (~(1<<CS11)) & (~(1<< CS10)); //Stop timer
		//TCCR1B |= (1<<CS11); //start timer clk/8
}

void Timer1_stop(){
	TCCR1B &= (~(1<<CS12)) & (~(1<<CS11)) & (~(1<< CS10)); //Stop timer
}

void Timer1_start(){
	TCCR1B |= (1<<CS11); //start timer clk/8
}
uint8_t Timer1_isRunning(){
	return TCCR1B & (1<<CS11);
}

uint16_t Timer1_ReadTCNT1()
{
	uint8_t sreg;
	uint16_t i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Read TCNT1 into i */
	i = TCNT1;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}

void Timer1_WriteTCNT1(uint16_t i )
{
	uint8_t sreg;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Set TCNT1 to i */
	TCNT1 = i;
	/* Restore global interrupt flag */
	SREG = sreg;
}

uint16_t Timer1_ReadOCR1A()
{
	uint8_t sreg;
	uint16_t i;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Read OCR1A into i */
	i = OCR1A;
	/* Restore global interrupt flag */
	SREG = sreg;
	return i;
}

void Timer1_WriteOCR1A(uint16_t i )
{
	uint8_t sreg;
	/* Save global interrupt flag */
	sreg = SREG;
	/* Disable interrupts */
	cli();
	/* Set OCR1A to i */
	OCR1A = i;
	/* Restore global interrupt flag */
	SREG = sreg;
}
