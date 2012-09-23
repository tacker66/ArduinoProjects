
//
// th.acker@arcor.de
//

byte pin_g = 5;
byte pin_y = 6;
byte pin_r = 7;
byte btn = 12;
byte btn_i = 13;
byte state = HIGH;

// cycle time for main loop()
int cycle = 1000;

volatile unsigned long lastTicks = 0;
volatile unsigned long lastCountedTicks = 0;

// correction for onboard timer
// correctionFactor * onboard time = real time 
// hh:mm:ss 13:17:00 vs. 13:17:30 (i.e. 47820s / 47820s)
volatile double correctionFactor = 0.99937304;

// count number of measurements in intervals of 50ms=50000us
// to get a good mute value (in us) for filtering
volatile unsigned int filterValue = 50000;
volatile unsigned long statInterval = 50000;
volatile unsigned int numStatistics = 25; 
volatile unsigned int statistics[25];

// number of values to count before computing a time span
volatile unsigned int numValues = 5;
volatile unsigned int actValue = 0;

// moving average for measured values
volatile unsigned int numAvValues = 3;
volatile double avValues[3];
volatile unsigned int actAvValue = 0;

// best average value
volatile unsigned long bestValue = 1000000;

void resetData(void)
{
  unsigned int i;
  lastTicks = 0;
  lastCountedTicks = 0;
  for(i=0; i<numStatistics; i++)  statistics[i] = 0;
  actAvValue = 0;
  for(i=0; i<numAvValues; i++)  avValues[i] = 0;
  bestValue = 1000000;
  actValue = 0;
}

void countClockTicks(void)
{
  if(lastTicks == 0)
  {
    lastTicks = micros();
    lastCountedTicks = lastTicks;
  }
  else
  {
    unsigned long curTicks = micros();
    if((curTicks - lastTicks) > filterValue) // filter out noise
    {
      statistics[(((curTicks - lastTicks) / statInterval) % numStatistics)]++;
      actValue++;
      if(actValue > numValues)
      {
        avValues[actAvValue] = (double)(curTicks - lastCountedTicks) / numValues;
        actAvValue++;
        actAvValue %= numAvValues;
        lastCountedTicks = curTicks;
        actValue = 0;
      }
      lastTicks = curTicks;
    }
  }
  // life beat ...
  digitalWrite(pin_g, state);
  if(state == HIGH)  state = LOW;
  else state = HIGH;
  digitalWrite(pin_r, state);
}

void showStatistics(void)
{
  unsigned int i;
  
  for(i=0; i<numStatistics; i++)
  {
    Serial.print("count for up to ");
    Serial.print((i + 1) * statInterval / 1000);
    Serial.print(" ms is ");
    Serial.println(statistics[i]);
  }
}

void checkClock(void)
{
  for(;;)
  {
    digitalWrite(pin_y, LOW);
    delay(500);
    digitalWrite(pin_y, HIGH);
    unsigned long hours, minutes, seconds, uptime = millis();
    hours = uptime / 3600000;
    uptime = uptime % 3600000;
    minutes = uptime / 60000;
    uptime = uptime % 60000;
    seconds = uptime / 1000;
    Serial.print("uptime hh:mm:ss "); 
    Serial.print(hours); 
    Serial.print(":"); 
    Serial.print(minutes); 
    Serial.print(":"); 
    Serial.print(seconds); 
    Serial.println(""); 
  }
}

void showTime(void)
{
  unsigned int i;
  double mulTicks = 1;
  double avTicks = 0;
  
  for(i=0; i<numAvValues; i++)
  {
    avTicks += avValues[i];  
  }
  avTicks /= numAvValues;
  
  if(avTicks < filterValue)
  {
    Serial.println("waiting for more data ...");
    return;
  }
  
  if((1000000 / avTicks) > 3) mulTicks = 4;
  avTicks *= mulTicks;
  
  if(avTicks < 800000)
  {
    Serial.println("waiting for more data ...");
    return;
  }

  Serial.print(avTicks);
  Serial.print(" micros, ");
  Serial.print(mulTicks);
  Serial.print(" mult, ");
  double difTicks = avTicks - 1000000;
  double del = difTicks * 864 / 10000;
  Serial.print(del);
  Serial.println(" seconds per day");
}

void setup(void) 
{
  // need more GND lines on the breadboard ;-)  
  pinMode(4, INPUT);
  pinMode(8, INPUT);
  digitalWrite(4, HIGH); // pullup
  digitalWrite(8, HIGH); // pullup
  // input button
  pinMode(btn, INPUT);
  digitalWrite(btn, HIGH); // pullup
  // mode LED
  pinMode(btn_i, OUTPUT);
  // traffic light LEDs  
  pinMode(pin_g, OUTPUT);     
  pinMode(pin_y, OUTPUT);     
  pinMode(pin_r, OUTPUT);
  // start serial communication
  Serial.begin(9600);
  // reset data
  resetData();
  // install counting interrupt
  attachInterrupt(0, countClockTicks, RISING);
}

void loop(void)
{
  byte ser;

  // ready :-) 
  digitalWrite(pin_y, HIGH);

  if(Serial.available() > 0)
  {
    ser = Serial.read();
    switch(ser)
    {
      case 't': Serial.println("time");
                showTime();
                break;
      case 's': Serial.println("statistics");
                showStatistics();
                break;
      case 'r': Serial.println("reset");
                resetData();
                break;
      case 'c': Serial.println("check clock");
                checkClock();
                break;
      default:  Serial.print("unknown command ");
                Serial.print("-"); Serial.print(ser, BYTE); Serial.print("-"); Serial.println();
                break;
    }
   }
   
   showTime();

   delay(cycle);
}

