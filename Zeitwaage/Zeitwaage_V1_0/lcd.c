// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + LCD-Funktionen für den M16C62
// +++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

void _long_delay(void)
{
//long t = 5000;
//while (t--);
Delay_ms(5);
}

void _short_delay(void)
{
int t = 500;
while (t--);
}


void _lcd_write_command(unsigned char data)
{
  LCD_PORT_w = (data & 0xf0) | DISPLAY_EN;
  LCD_PORT_w = (data & 0xf0) | DISPLAY_EN;
  LCD_PORT_w = (data & 0xf0);
  LCD_PORT_w = (data & 0xf0);
  LCD_PORT_w = (data << 4) | DISPLAY_EN;
  LCD_PORT_w = (data << 4) | DISPLAY_EN;
  LCD_PORT_w = (data << 4);
}

void _lcd_write_4bit(unsigned char data)
{
  LCD_PORT_w = (data << 4) | DISPLAY_EN;
  LCD_PORT_w = (data << 4) | DISPLAY_EN;
  LCD_PORT_w = (data << 4);
}

void lcd_write_byte(unsigned char data)
{
  LCD_PORT_w = (data & 0xf0) | DISPLAY_EN | DISPLAY_RS;
  LCD_PORT_w = (data & 0xf0) | DISPLAY_RS;
  LCD_PORT_w = (data << 4)   | DISPLAY_EN | DISPLAY_RS;
  LCD_PORT_w = (data << 4)   | DISPLAY_RS;
}


int my_pput(int zeichen)
{
 lcd_write_byte((char) zeichen);
 return(1);
}

// initialize the LCD controller
void LCD_Init(void)
{
LCD_PORT_DDR = 0xff;//0xf0 | DISPLAY_RS | DISPLAY_EN;
_long_delay();
_long_delay();
_long_delay();
_lcd_write_4bit(0x03);	   // noch 8 Bit
_long_delay();
_lcd_write_4bit(0x03);	   // noch 8 Bit
_long_delay();
_lcd_write_4bit(0x03);	   // noch 8 Bit
_long_delay();
_lcd_write_4bit(0x02);	   // jetzt 4 Bit
_long_delay();
_lcd_write_command(0x28);     // 4 Bit Zweizeilig
_long_delay();
_lcd_write_command(0x08);     // Display aus
_long_delay();
_lcd_write_command(0x01);     // Clear
_long_delay();
_lcd_write_command(0x06);     //Entry mode
_long_delay();
_lcd_write_command(0x08 + 4); // Display an
_long_delay();
}


void LCD_Gotoxy(unsigned char x , unsigned char y)
 {
  _short_delay();
  switch(y)
  { case 0 : _lcd_write_command(x + 0x80); break;
    case 1 : _lcd_write_command(x + 0xC0); break;
    case 2 : _lcd_write_command(x + (0x80 + 20)); break;
    case 3 : _lcd_write_command(x + (0xC0 + 20)); break;
  }
 }


void LCD_Write(unsigned char *this_text)
{
 unsigned char i = 0;
 while(this_text[i] != 0) 
  {
   lcd_write_byte(this_text[i++]);
   _long_delay();
  }
}


char LCD_Putchar(char zeichen)
{
_short_delay();
 lcd_write_byte((char) zeichen);
 return(1);
}


