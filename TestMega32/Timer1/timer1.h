/*
 * timer_1.h
 *
 *  Created on: 3 lut 2017
 *      Author: rafal
 */

#pragma once

#include <stdint.h>

void init_timer1(void (*przerwanie)());

void Timer1_start();
void Timer1_stop();
uint8_t Timer1_isRunning();

uint16_t Timer1_ReadTCNT1();
void Timer1_WriteTCNT1(uint16_t i );

uint16_t Timer1_ReadOCR1A();
void Timer1_WriteOCR1A(uint16_t i );
