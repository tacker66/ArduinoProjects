// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + (c) 3.2006 Holger Buss
// + Nur für den privaten Gebrauch
// + Kommerzielle Nutzung nur nach Rücksprache
// + www.mikrocontroller.com
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++

#include "main.h"
unsigned int _SekTimer = 0,_TastTimer = 0;
unsigned char Sekunde = 0,Minute = 0,Stunde = 0;

void Sekundentakt_Init(void)
{
  _SekTimer = SetDelay(1000);
}

void Sekundentakt(void)
{
 if(CheckDelay(_SekTimer))  
 {
  _SekTimer += 1000;
//  PORTB++;
  if(++Sekunde == 60) 
   {
    Sekunde = 0;
    if(++Minute == 60) { Stunde++; Minute = 0;};
   } 
 }   
}

void SetzeLEDs(void)
{
 unsigned char tmp;
 tmp = PORTB & 0x80;
 if(CntOkay % TicksProSekunde == 0) tmp |= 32;
 tmp += CntOkay % 4;
 PORTB = tmp;
}

void ShowGraph(void)
{
unsigned char z, tmp;

             if(KurzFehlerSekundenProTag/50 > 400) tmp = 80;
             else if(KurzFehlerSekundenProTag/50 < -400) tmp = 0;
             else tmp = 40 + KurzFehlerSekundenProTag/50;
             printf("\r+");
             for(z = 0; z < 80; z++) 
             {
              if(z == 40)
                 { 
                   if(tmp == 40)  printf("*");
                   else  printf("|");
                  }
               else 
               if(z == tmp) printf("*"); else printf(" ");
             } 
             printf("+");
             printf(" %4i",KurzFehlerSekundenProTag/10);

}
//############################################################################
//Hauptprogramm
int main (void)
//############################################################################
{
 char z,txt[]= {"Moin"},key,cntSek = 0;
 int test = 0;
 unsigned int _MessTimer;
	UART_Init();
    UART_Init();
    Timer0_Init();
    Timer1_Init();
    Keyboard_Init();
    Sekundentakt_Init();
    _MessTimer = SetDelay(3000);
	//Globale Interrupts Einschalten
	sei ();
DDRB = 0xff;
PORTB = 0x00;

Delay_ms(400);
    LCD_Init();
Delay_ms(100);
    LCD_Clear;
    RechneToleranz();
	while (1)
		{
         key = GetKeyboard();
         Menu(key);
         Delay_ms(5);      
         SetzeLEDs();
         Sekundentakt();
         if(CheckDelay(_MessTimer))  
          {
           _MessTimer = SetDelay(1000);
             FehlerProTag();
             RechneSekunde();
             if(++cntSek >= SekundenFuerTicks)
              {
               BerechneKurzmittel();
               FehlerProTagKurz();
               ShowGraph();
               cntSek = 0;
              } 
          } 
           if(NeuerMesswert)
            {
             NeuerMesswert = 0;
            } 
        }
return (1);
}
