
//
// th.acker@arcor.de
//
// 30.12.2010
//

byte pin_g = 5;
byte pin_y = 6;
byte pin_r = 7;
byte btn_i = 13;
byte btn = 12;
byte btn_state = HIGH;
byte btn_last = HIGH;
byte state = HIGH;
int cycle = 1000;

volatile unsigned long lastTicks = 0;
volatile unsigned long sumTicks = 0;
volatile unsigned long numTicks = 0;

void countClockTicks(void)
{
  if(lastTicks == 0)
  {
    lastTicks = micros();
  }
  else
  {
    unsigned long curTicks = micros();
    if((curTicks - lastTicks) > 10000) // filter out noise
    {
      sumTicks += (curTicks - lastTicks);
      lastTicks = curTicks;
      numTicks++;
    }
  }
}

void setup(void) 
{
  // counting interrupt
  attachInterrupt(0, countClockTicks, RISING);
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
}

void loop(void)
{
  byte ser;
  byte col;
  byte col_state;

  btn_state = digitalRead(btn);
  if(btn_state == LOW && btn_last == HIGH)
  {
    digitalWrite(btn_i, state);
    if(state == HIGH) state = LOW;
    else state = HIGH;
  }
  btn_last = btn_state;

  if(numTicks > 0)
  {
    unsigned long avTicks = (double)sumTicks / (double)numTicks;
    int mulTicks = 1;
    if(((double)1000000 / (double)avTicks) > 3) mulTicks = 4;
    avTicks *= mulTicks;
    Serial.print(avTicks);
    Serial.print(" micros, ");
    Serial.print(mulTicks);
    Serial.print(" mult, ");
    long difTicks = avTicks - 1000000;
    double del = difTicks * 864 / 10000;
    Serial.print(del);
    Serial.println(" seconds per day");
  }
  
  if(Serial.available() > 0)
  {
    col = 0;
    ser = Serial.read();
    switch(ser)
    {
      case 'R': Serial.println("red ON");
                col_state = HIGH;
                col = pin_r;
                break;
      case 'Y': Serial.println("yellow ON");
                col_state = HIGH;
                col = pin_y;
                break;
      case 'G': Serial.println("green ON");
                col_state = HIGH;
                col = pin_g;
                break;
      case 'r': Serial.println("red OFF");
                col_state = LOW;
                col = pin_r;
                break;
      case 'y': Serial.println("yellow OFF");
                col_state = LOW;
                col = pin_y;
                break;
      case 'g': Serial.println("green OFF");
                col_state = LOW;
                col = pin_g;
                break;
      case 't': Serial.println("timer");
                break;
      default:  Serial.print("unknown command ");
                Serial.print("-"); Serial.print(ser, BYTE); Serial.print("-"); Serial.println();
                break;
    }
    if(col != 0)
    {
      digitalWrite(col, col_state);
    } 
   }

   delay(cycle);
}

