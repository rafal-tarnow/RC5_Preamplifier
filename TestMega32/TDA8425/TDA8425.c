/*
 * TDA8425.c
 *
 *  Created on: 30 sty 2017
 *      Author: rafal
 */
#include "TDA8425.h"
#include "../i2cbase/I2CBase.h"

#define TDA8425ADDR 0x82

uint8_t VL,VR,BA,TR,S1;
uint8_t VL_SADDR, VR_SADDR, BA_SADDR, TR_SADDR, S1_SADDR;

void update(){
	do
	{
		I2C_SendStartAndSelect(TDA8425ADDR);
	}while(I2C_Error==I2C_NoACK);
	I2C_SendByte(VL_SADDR);
	I2C_SendByte(VL);

	do
	{
		I2C_SendStartAndSelect(TDA8425ADDR);
	}while(I2C_Error==I2C_NoACK);
	I2C_SendByte(VR_SADDR);
	I2C_SendByte(VR);

	do
	{
		I2C_SendStartAndSelect(TDA8425ADDR);
	}while(I2C_Error==I2C_NoACK);
	I2C_SendByte(BA_SADDR);
	I2C_SendByte(BA);

	do
	{
		I2C_SendStartAndSelect(TDA8425ADDR);
	}while(I2C_Error==I2C_NoACK);
	I2C_SendByte(TR_SADDR);
	I2C_SendByte(TR);

	do
	{
		I2C_SendStartAndSelect(TDA8425ADDR);
	}while(I2C_Error==I2C_NoACK);
	I2C_SendByte(S1_SADDR);
	I2C_SendByte(S1);

	I2C_Stop();
}


void TDA8425_init(){
	//init for TDA8425
	VL_SADDR = 0b00000000;
	VR_SADDR = 0b00000001;
	BA_SADDR = 0b00000010;
	TR_SADDR = 0b00000011;
	S1_SADDR = 0b00001000;

	VL = 0b11111100; //0dB
	VR = 0b11111100; //0dB
	BA = 0b11110110; //0dB
	TR = 0b11110110; //0dB

	S1 = 0b11001110;

	I2C_Init();

	update();
}

void TDA8425_changeChannel(){
	if(S1 & 0b000000001){
		S1 &= 0b11111110;
	}else{
		S1 |= 0b00000001;
	}

	update();
}

void TDA8425_volumeUp(){
	if(VL < 255){
		VL++;
	}

	if(VR < 255){
		VR++;
	}

	update();
}

void TDA8425_volumeDown(){
	if(VL > 0){
		VL--;
	}

	if(VR > 0){
		VR--;
	}

	update();
}
