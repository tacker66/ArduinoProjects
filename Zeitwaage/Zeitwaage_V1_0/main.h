#ifndef _MAIN_H
 #define _MAIN_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <avr/io.h>
#include <avr/pgmspace.h>
#include <avr/interrupt.h>
#include <avr/signal.h>
#include <avr/eeprom.h>

#include "uart.h"
#include "lcd.h"
#include "printf_P.h"
#include "timer0.h"
#include "keyboard.h"
#include "menu.h"
#include "old_macros.h"

extern unsigned char Sekunde,Minute,Stunde;

//Hier die Quarz Frequenz einstellen
#define SYSCLK	8000000L	//Quarz Frequenz in Hz

	
#if defined (__AVR_ATmega32__)	
//	#define Networkcard_INT_Enable()	enable_external_int (1<<INT0);
#endif	


#endif //_MAIN_H






