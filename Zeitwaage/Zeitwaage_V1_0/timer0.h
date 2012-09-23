
extern volatile unsigned int CountMilliseconds;
void Timer0_Init(void);
void Delay_ms(unsigned int);
unsigned int SetDelay (unsigned int t);
char CheckDelay (unsigned int t);

extern volatile char t_high;
extern volatile char t_low;
extern volatile unsigned char g_ticks;
extern volatile unsigned char g_overflow;	// Anzahl der Überläufe aus dem Interrupt 
extern volatile unsigned int  DiffTime;	
extern volatile unsigned int  AktTime;	
extern volatile unsigned long Ticks;
extern volatile unsigned long FehlerTicks;
extern volatile unsigned int  MessTime;
extern volatile unsigned long TimeSumme;
extern volatile unsigned int  TimeSummeUeberlauf;
extern volatile unsigned int  OldTime;
extern unsigned int SekundenFuerTicks;
extern unsigned int TicksProSekunde;
extern unsigned int MinDiffTime;
extern unsigned int MaxDiffTime;
extern unsigned int Toleranz;
extern unsigned char NeuerMesswert;
extern unsigned char CntOkay;
extern volatile unsigned int  KurzzeitMittel;