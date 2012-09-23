#ifndef _PRINTF_P_H_
#define _PRINTF_P_H_

#include <avr/pgmspace.h>

extern void _printf_P (char const *fmt0, ...);

#define LCD_printf(format, args...)   _printf_P(PSTR(format) , ## args)
#define LCD_printfxy(x,y,format, args...)  { LCD_Gotoxy(x,y);_printf_P(PSTR(format) , ## args);}

#endif
