// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
// + (c) 3.2006 Holger Buss
// + Nur für den privaten Gebrauch
// + Kommerzielle Nutzung nur nach Rücksprache
// + www.mikrocontroller.com
// ++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
#include "main.h"

unsigned int  TestInt = 0;
#define ARRAYGROESSE 10
signed int FehlerSekundenProTag = 0,KurzFehlerSekundenProTag = 0;
double uSekProSekunde = 0,uSekKurzmittel = 0;
 
void FehlerProTag(void)
{
 double tmp_dbl;
  
 tmp_dbl  = (double)TimeSumme;
 tmp_dbl += TimeSummeUeberlauf * (65535.0 * 65535.0);
 tmp_dbl *= 86400.0;
 tmp_dbl *= 4; 
 tmp_dbl *= (double)TicksProSekunde;
 tmp_dbl /= 3125;
 tmp_dbl /= SekundenFuerTicks;
 tmp_dbl /= (double)Ticks;
 tmp_dbl = 864000.0 - tmp_dbl;
 FehlerSekundenProTag = (FehlerSekundenProTag * 3 + tmp_dbl) / 4;

 if(Ticks < 5) FehlerSekundenProTag = 0;
// if(FehlerSekundenProTag < tmp_dbl) FehlerSekundenProTag++;
// else if(FehlerSekundenProTag < tmp_dbl) FehlerSekundenProTag++;

//SekundenProTag = tmp_float;
 // TimeSumme/ Ticks;
}

void BerechneKurzmittel(void)
{
 double tmp_dbl;
           tmp_dbl  = (double)KurzzeitMittel;
//           tmp_dbl *= TicksProSekunde;
           tmp_dbl *= 100000.0;
           tmp_dbl *= 4;
           tmp_dbl /= 3125;
           tmp_dbl /= SekundenFuerTicks;
//           tmp_dbl /= (double)Ticks;
           uSekKurzmittel = tmp_dbl;
}

void FehlerProTagKurz(void)
{
 double tmp_dbl;
 
 tmp_dbl  = (double)KurzzeitMittel;
 tmp_dbl *= 86400.0;
 tmp_dbl *= 4; 
// tmp_dbl *= (double)TicksProSekunde;
 tmp_dbl /= 3125;
 tmp_dbl /= SekundenFuerTicks;
// tmp_dbl /= (double)Ticks;
 tmp_dbl = 864000.0 - tmp_dbl;
 KurzFehlerSekundenProTag = (KurzFehlerSekundenProTag + tmp_dbl) / 2;
}

void RechneToleranz(void)
{
 unsigned long tmp_l;
//tmp_l = 31250;
 tmp_l = 7812;
 tmp_l *= SekundenFuerTicks;
 tmp_l /= TicksProSekunde;
 MinDiffTime = tmp_l - (tmp_l * (long)Toleranz) / 1000;
 MaxDiffTime = tmp_l + (tmp_l * (long)Toleranz) / 1000;
}

void RechneSekunde(void)
{
 double tmp_dbl;
           tmp_dbl  = (double)TimeSumme;
           tmp_dbl += TimeSummeUeberlauf * (65535.0 * 65535.0);
           tmp_dbl *= TicksProSekunde;
           tmp_dbl *= 100000.0;
           tmp_dbl *= 4;
           tmp_dbl /= 3125;
           tmp_dbl /= SekundenFuerTicks;
           tmp_dbl /= (double)Ticks;
           uSekProSekunde = tmp_dbl;
}


void Reset(void)
{
 t_high = 0;
 t_low = 0;
 g_ticks=0;
 g_overflow=0;	// Anzahl der Überläufe aus dem Interrupt 
 DiffTime = 0;	
 MessTime = 0;	
 OldTime = 0;	
 Ticks=0;
 TimeSumme = 0;
 TimeSummeUeberlauf = 0;
 Minute = 0;
 Sekunde = 0;
 Stunde = 0;
 FehlerTicks = 0;
 CntOkay = 0;
}

void Menu(unsigned char key)
 {
  static unsigned int  arr = 0;
  static unsigned char MaxMenue = 10,MenuePunkt = 4;       
  double tmp_dbl;
 
  if(key & KEY1) { if(MenuePunkt) MenuePunkt--; else MenuePunkt = MaxMenue; LCD_Clear; }
  if(key & KEY2) { MenuePunkt++; LCD_Clear; }
  if((key & KEY1) && (key & KEY2)) MenuePunkt = 0;
//  LCD_printfxy(13,0,"[%i]",MenuePunkt);
  switch(MenuePunkt)
   {
    case 0: 
           LCD_printfxy(0,0,"Zeitwaage");
           LCD_printfxy(0,1,"Holger Buss");
           break;
    case 1: 
            LCD_printfxy(0,0,"Messzeit");
            LCD_printfxy(0,1,"%3i:%02i:%02i ",Stunde,Minute,Sekunde);
           if(key & KEY5) Reset();
           break;
    case 2: 
          
           LCD_printfxy(0,0,"Ticks:%5lu",Ticks);
           LCD_printfxy(0,1,"sek=%9luus",(unsigned long) uSekProSekunde);
           if(key & KEY5) Reset();
           break;
    case 3: 
           LCD_printfxy(0,0,"Kurzmittel");
           LCD_printfxy(0,1,"sek=%9luus",(unsigned long) uSekKurzmittel);
           break;
    case 4: 
          LCD_printfxy(0,0,"Ticks:%5lu",Ticks);
          LCD_printfxy(0,1,"%4i.%i sek/Tag ",FehlerSekundenProTag / 10,abs(FehlerSekundenProTag) % 10);
           if(key & KEY5) Reset();
           break;
    case 5: 
          LCD_printfxy(0,0,"Kurzmittel");
          LCD_printfxy(0,1,"%4i sek/Tag ",KurzFehlerSekundenProTag / 10);
           if(key & KEY5) Reset();
           break;
    case 6: 
           LCD_printfxy(0,0,"Okay:%5lu Ticks",Ticks);
           LCD_printfxy(0,1,"Fehler:%4lu ",FehlerTicks);
           if(key & KEY5) Reset();
           break;
    case 7: 
           LCD_printfxy(0,0,"Anzahl Ticks");
           LCD_printfxy(0,1,"%2i pro %2isek",TicksProSekunde,SekundenFuerTicks);
           if(key & KEY3) if(TicksProSekunde > 1) TicksProSekunde--; 
           if(key & KEY4) TicksProSekunde++;
           if(key) RechneToleranz();
           break;
    case 8: 
           LCD_printfxy(0,0,"Ticks Zeitbasis");
           LCD_printfxy(0,1,"%2i pro %2isek",TicksProSekunde,SekundenFuerTicks);
           if(key & KEY3) if(SekundenFuerTicks > 1) SekundenFuerTicks--; 
           if(key & KEY4) SekundenFuerTicks++;
           if(key) RechneToleranz();
           break;
    case 9: 
           LCD_printfxy(0,0,"Sensortoleranz");
//           LCD_printfxy(0,0,"%5i - %5i",MinDiffTime,MaxDiffTime);
           LCD_printfxy(0,1,"  %2u/1000 ",Toleranz);
           if(key & KEY3) if(Toleranz > 1) Toleranz--; 
           if(key & KEY4) if(Toleranz < 999)Toleranz++;
           if(key) RechneToleranz();
           break;
    case 10: 
           LCD_printfxy(0,0,"Diff:%5u ",DiffTime);
           LCD_printfxy(0,1,"Mittel:%5u ",KurzzeitMittel);
           break;
 

  default: MaxMenue = MenuePunkt - 1;
             MenuePunkt = 0; 
           break;
    }
}