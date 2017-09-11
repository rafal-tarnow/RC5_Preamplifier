#pragma once
#include <inttypes.h>

typedef struct
{
    uint16_t Command:6;	//biy rozkazu służšce do okrelenia funkcji
    uint16_t Addres:5; //bity służšce do identyfikacji urzšdzenia docelowego,
    uint16_t T:1;	//bit Toogle (ponowne wcinięcie powoduje jego zmianę na przeciwny)
    uint16_t S2:1;	//bit startu (zawsze logiczne "1")
    uint16_t S1:1;	//bit startu (zawsze logiczne "1")
    uint16_t blank:2;
}RcData_t;

/*
 * Jeli zdefiniujemy _RC_SUPPORT_ (plik main_config.h) będziemy mieli włšczonš dodatkowš funkcjonalnoć sterownika
 * Będzie można sterować przeładowaniem oraz bezpiecznikiem (gdy elektrospust jest nieaktywny) poprzez pilot RC5
 * pod warunkiem podłšczenia fotodiody 36KHz (np TSOP4836) do złšcza "J5" sterownika (jest to złšcze służšce so programowania sterownika)
 *
 * Konfiguracja połšczenia fotodiody do złšcza J5 (6 pinowe):
 * 		Pin1 - Vs
 * 		Pin2 - no connect
 * 		Pin3 - GND
 * 		Pin4 - no connect
 * 		Pin5 - no connect
 *		Pin6 - OUT (DATA)
 *
 * Opis funkcjonalnoci przycisków pilota:
 * - Kołyska główna	(WEAPON_0):
 * 		- przycisk "1"		przeładowanie
 * 		- przycisk "2"		zatrzymanie silnika przeładowania
 * 		- przycisk "3"		dojazd do czujnika K1
 * 		- przycisk "4"		dojazd do czujnika K2
 * 		- przycisk "Menu"	zabezpieczenie
 * 		- przycisk "P+"		zatrzymanie silnika bezpiecznika
 * 		- przycisk "P->P"	odbezpieczenie
 * - Kołyska prawa (WEAPON_1):
 * 		- przycisk "5"		przeładowanie
 * 		- przycisk "6"		zatrzymanie silnika przeładowania
 * 		- przycisk "7"		dojazd do czujnika K1
 * 		- przycisk "8"		dojazd do czujnika K2
 * 		- przycisk "<"		zabezpieczenie
 * 		- przycisk "P-"		zatrzymanie silnika bezpiecznika
 * 		- przycisk ">"		odbezpieczenie
 * */



void rc5Init();
void rc5Distribute();
