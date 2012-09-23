#include "main.h"
unsigned int KeyTimer = 0;

void Keyboard_Init(void)
{
 KeyTimer = SetDelay(KEY_DELAY_MS);
}

unsigned char GetKeyboard(void)
{
 static char taste1 = 0, taste2 = 0,taste3 = 0,taste4 = 0,taste5 = 0;
 unsigned char ret = 0;
 if(CheckDelay(KeyTimer))
 {
  if(_TASTE1) { if(taste1++ == 0 || taste1 == CNT_TASTE) ret |= KEY1;  if(taste1 == CNT_TASTE) taste1 = CNT_TASTE-CNT_TASTE/3;} else taste1 = 0;
  if(_TASTE2) { if(taste2++ == 0 || taste2 == CNT_TASTE) ret |= KEY2;  if(taste2 == CNT_TASTE) taste2 = CNT_TASTE-CNT_TASTE/3;} else taste2 = 0; 
  if(_TASTE3) { if(taste3++ == 0 || taste3 == CNT_TASTE) ret |= KEY3;  if(taste3 == CNT_TASTE) taste3 = CNT_TASTE-CNT_TASTE/3;} else taste3 = 0; 
  if(_TASTE4) { if(taste4++ == 0 || taste4 == CNT_TASTE) ret |= KEY4;  if(taste4 == CNT_TASTE) taste4 = CNT_TASTE-CNT_TASTE/3;} else taste4 = 0; 
  if(_TASTE5) { if(taste5++ == 0 || taste5 == CNT_TASTE) ret |= KEY5;  if(taste5 == CNT_TASTE) taste5 = CNT_TASTE-CNT_TASTE/3;} else taste5 = 0; 
  KeyTimer = SetDelay(KEY_DELAY_MS);
 } 
 return(ret);
}                   
