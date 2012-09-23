/*#######################################################################################
AVR Small Webserver 

Copyright (C) 2004 Ulrich Radig

#######################################################################################*/

#ifndef _UART_H
 #define _UART_H

extern void UART_Init (void);
extern int uart_putchar (char c);

//Die Baud_Rate der Seriellen Schnittstelle ist 9600 Baud
//#define BAUD_RATE 9600		//Baud Rate für die Serielle Schnittstelle	
//#define BAUD_RATE 14400		//Baud Rate für die Serielle Schnittstelle	
//#define BAUD_RATE 28800		//Baud Rate für die Serielle Schnittstelle	
#define BAUD_RATE 38400		//Baud Rate für die Serielle Schnittstelle	
//#define BAUD_RATE 57600		//Baud Rate für die Serielle Schnittstelle	

//Anpassen der seriellen Schnittstellen Register wenn ein ATMega128 benutzt wird
#if defined (__AVR_ATmega128__)
#	define USR UCSR0A
#	define UCR UCSR0B
#	define UDR UDR0
#	define UBRR UBRR0L
#	define EICR EICRB
#endif

#if defined (__AVR_ATmega32__)
#	define USR UCSRA
#	define UCR UCSRB
#	define UBRR UBRRL
#	define EICR EICRB
#endif

#endif //_UART_H
