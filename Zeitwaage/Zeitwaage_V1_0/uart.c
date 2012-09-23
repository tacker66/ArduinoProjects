/*#######################################################################################
AVR Small Webserver 

#######################################################################################*/

#include "main.h"
#include "uart.h"

//############################################################################
//Routine für die Serielle Ausgabe
int uart_putchar (char c)
//############################################################################
{
	if (c == '\n')
		uart_putchar('\r');
	//Warten solange bis Zeichen gesendet wurde
	loop_until_bit_is_set(USR, UDRE);
	//Ausgabe des Zeichens
	UDR = c;
	
	return (0);
}

//############################################################################
//INstallation der Seriellen Schnittstelle
void UART_Init (void)
//############################################################################
{
	//Enable TXEN im Register UCR TX-Data Enable
	UCR=(1 << TXEN);
	//Teiler wird gesetzt 
	UBRR=(SYSCLK / (BAUD_RATE * 16L) - 1);
	//UBRR = 33;
	//öffnet einen Kanal für printf (STDOUT)
	fdevopen (uart_putchar, NULL, 0);
	sbi(PORTD,4);
}

