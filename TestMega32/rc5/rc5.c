#include "rc5.h"
#include <avr/io.h>
#include "../Timer1/timer1.h"
#include <avr/interrupt.h>
#include "../application.h"


typedef enum{
	false = 0,
	true = 1
} bool;



volatile uint8_t _rcFlag_ = 0;
volatile RcData_t _rcData_;


typedef enum
{
	RcClear = 0,	//można odczytywać ramkę
	RcAdd = 1,		//dodaj bity
	RcStop = 2, 	//oczekuj na nowš ramkę
}RcState_e;

typedef struct
{
	RcState_e rcState;
	uint16_t u16RcData;
	//RcData_t rcDataDistribute;
	uint8_t bitCounter;// = 0;
	bool isFirstHalfBit;// = false;
	uint8_t firstHalfBit;// = 1;
}This_t;

static This_t this;

void init_INT2();


void przerwanieTimera(){

	Timer1_stop();
	Timer1_WriteTCNT1(0);

	this.rcState = RcClear;	//można odczytywać nowš ramkę
}




void rc5Init()
{
	this.rcState = RcClear;

	init_timer1(przerwanieTimera);
	init_INT2();


}

void parseHalfBit(uint8_t halfBit)
{
	if(this.rcState == RcStop)return;

	if(this.rcState == RcClear)
	{
		this.bitCounter = 14;
		this.u16RcData = 0;
		this.isFirstHalfBit = false;
		this.firstHalfBit = 1;	//zawsze pierwsza połowa bitu to 1
		this.rcState = RcAdd;
	}

	if(this.isFirstHalfBit == true)
	{
		this.firstHalfBit = halfBit;
		this.isFirstHalfBit = false;
	}
	else //jeli halfBit jest drugš połowš bitu
	{
		if(this.firstHalfBit != halfBit)
		{
			this.u16RcData |= this.firstHalfBit<<--this.bitCounter;
			this.isFirstHalfBit = true;

			if(this.bitCounter == 0)
			{//gitara, odczytano popawnie ramkę
				this.rcState = RcStop;
				*((uint16_t*)&_rcData_) = this.u16RcData;//rcDistribute();
				_rcFlag_ = 1;
			}
		}
		else
		{
			this.rcState = RcStop;	//błšd, zakończ odczytywanie tej ramki
		}
	}
}



void rc5Distribute()
{
	if(_rcFlag_ == 0){
		return ;
	}else{
		_rcFlag_ = 0;
	}
	static uint16_t lastData = 0;
	if(lastData == *((uint16_t*)&_rcData_))return;
	lastData = *((uint16_t*)&_rcData_);

	if(_rcData_.Addres != 0 || _rcData_.S1 == 0 || _rcData_.S2 == 0) return;
	//	sUiKFrameData->Frame.Weapon[1].ammoCount = RcData.Command;//6bit

	application_onRC5CodeReceived(_rcData_.Command);


}

void init_INT2(){
	DDRD &= ~(1<<PD2);  //PD2 as input
	PORTD &= ~(1<<PD2);  //turn off pullup

	MCUCR |= (1<<ISC00); // rising falling
	MCUCR &= ~(1<<ISC01); // rising falling
	GICR |= (1<<INT0); //enable INT0
}

inline uint8_t readPinInt2(){
   return ((PIND & (1 << PD2)) >> PD2);
}

ISR(INT0_vect)
{

	uint16_t tmpTime = Timer1_ReadTCNT1();
	uint8_t halfBit = readPinInt2();


	if(!Timer1_isRunning()){
		Timer1_start();
	}

	if(tmpTime < 1999) //1333us -> 3/4b	//zakładam, że piewszy bit to zawsze 1, więc (1333 / 0.667us)
	{
		parseHalfBit(halfBit);
		Timer1_WriteTCNT1(0);
	}
	else if(tmpTime < 3331) //2222us -> 5/4b (2222 / 0.667us)
	{
		if(halfBit == 1)
		{
			parseHalfBit(0);
			parseHalfBit(1);
		}
		else
		{
			parseHalfBit(1);
			parseHalfBit(0);
		}
		Timer1_WriteTCNT1(0);
	}
	else
	{
		this.rcState = RcStop;
		Timer1_WriteTCNT1(0);	//aby nie wyłšczyć timera do końca błędnej ramki
	}


}



