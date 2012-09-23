#define LCD_PORT_w    PORTC
#define LCD_PORT_DDR  DDRC
#define DISPLAY_RS  (1<<0)
#define DISPLAY_EN  (1<<2)

void    _long_delay(void);
void    _lcd_write_command(unsigned char);
void    LCD_Write(unsigned char *);
void    LCD_Init(void);
char    LCD_Putchar(char);
#define LCD_Clear  {_lcd_write_command(0x01); _long_delay();}
void    LCD_Gotoxy(unsigned char  , unsigned char );
