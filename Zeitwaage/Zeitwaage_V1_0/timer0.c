// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + (c) 3.2006 Holger Buss
// + Nur für den privaten Gebrauch
// + Kommerzielle Nutzung nur nach Rücksprache
// + www.mikrocontroller.com
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "main.h"
volatile unsigned int CountMilliseconds = 0;

volatile char t_high = 0;
volatile char t_low = 0;
volatile unsigned char g_ticks=0;
volatile unsigned char g_overflow=0;	// Anzahl der Überläufe aus dem Interrupt 
volatile unsigned int DiffTime = 0;	
volatile unsigned int MessTime = 0;	
volatile unsigned int OldTime = 0;	
//unsigned int MinDiffTime = 19000;
//unsigned int MaxDiffTime = 21000;
unsigned int MinDiffTime = 5000;
unsigned int MaxDiffTime = 5400;
volatile unsigned long Ticks=0;
volatile unsigned long TimeSumme = 0;
volatile unsigned int  TimeSummeUeberlauf = 0;
unsigned int SekundenFuerTicks = 1;
unsigned int TicksProSekunde = 6;
unsigned int Toleranz = 20;
volatile unsigned long FehlerTicks = 0;
unsigned char NeuerMesswert = 0;
unsigned char CntOkay = 0;
volatile unsigned int  KurzzeitMittel = 0;

SIGNAL (SIG_INPUT_CAPTURE1)
{
unsigned int tmp_t,tmp_d;
static unsigned int OldTime, kurzmittel;
static unsigned char kurzcnt = 0;
unsigned long vorher;
 
		tmp_t = ICR1;
        tmp_d = tmp_t - OldTime;

        
      if(tmp_d > MinDiffTime)  // kein Spike
       {
//        MessTime = (MessTime * 3 + (((long)tmp_d * 6L * 4) / 125L)) / 4;
        OldTime  = tmp_t;
        DiffTime = tmp_d;
        if(tmp_d < MaxDiffTime)     // Messwert korrekt
         {
           vorher = TimeSumme;
           TimeSumme += tmp_d;
           if(vorher > TimeSumme) TimeSummeUeberlauf++;
           Ticks++;
           NeuerMesswert = 1;
           CntOkay++;
           kurzmittel += tmp_d;
           if(++kurzcnt == TicksProSekunde)
            {
             KurzzeitMittel = kurzmittel;
             kurzmittel = 0;
             kurzcnt = 0;
            }
           PORTB &= ~128;
         } 
         else 
          {
           FehlerTicks++;
           PORTB |= 128;
          } 
       } 
       else 
        {
//         DiffTime = tmp_t;
         MessTime = tmp_d;
        } 
}

SIGNAL (SIG_OVERFLOW1)
        {
		 g_overflow++;
		}


SIGNAL (SIG_OVERFLOW0)
{
 TCNT0 -= 125;
 CountMilliseconds++;
// if(!(PIND & (1<<6))) PORTB |= 32; else PORTB &= ~32;
}

enum {
  STOP             = 0,
  CK               = 1,
  CK8              = 2,
  CK64             = 3,
  CK256            = 4,
  CK1024           = 5,
  T0_FALLING_EDGE  = 6,
  T0_RISING_EDGE   = 7
};

void Timer0_Init(void)
{
// Timer/Counter 0 initialization
// (for system Clock = 8.000.000)
// Clock source: System Clock
// Mode: Normal top=FFh
// OC0 output: Disconnected
 TCCR0 = CK64;
 TCNT0 = -125;  // reload
 OCR0  = 0x00;
// Timer(s)/Counter(s) Interrupt(s) initialization
 TIMSK |= 0x01;
}

void Timer1_Init(void)
{
  ACSR |= (1<<ACD);					//Analog Comperator aus!
  TCCR1B =  (1<<ICES1) | (1<<ICNC1) | (1<<CS12) | (0<<CS11) | (1<<CS10) ; //| Input Capture Edge = steigende Flanke, Timer Prescaler = 1024
  TIMSK |= (1<<TICIE1) | (1<<TOIE1);
}

unsigned int SetDelay (unsigned int t)
{
  return(CountMilliseconds + t);                                             
}

char CheckDelay (unsigned int t)
{
  return(((t - CountMilliseconds) & 0x8000) >> 8);
}

void Delay_ms(unsigned int w)
{
 unsigned int akt;
 akt = SetDelay(w);
 while (!CheckDelay(akt));
}
