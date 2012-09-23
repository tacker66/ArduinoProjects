
#define _TASTE1       (PINA & (1<<7))
#define _TASTE2       (PINA & (1<<6))
#define _TASTE3       (PINA & (1<<5))
#define _TASTE4       (PINA & (1<<4))
#define _TASTE5       (PINA & (1<<3))
#define CNT_TASTE     10 // mindestens 3
#define KEY_DELAY_MS  50

#define KEY1  (1<<0)
#define KEY2  (1<<1)
#define KEY3  (1<<2)
#define KEY4  (1<<3)
#define KEY5  (1<<4)


void Keyboard_Init(void);
unsigned char GetKeyboard(void);
