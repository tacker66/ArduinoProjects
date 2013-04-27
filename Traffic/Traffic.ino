
byte pin_g = 9;
byte pin_y = 6;
byte pin_r = 12;
byte btn_i = 11;
byte btn = 4;
byte btn_state = HIGH;
byte btn_last = HIGH;
byte state = HIGH;
byte demo = 1;
byte demo_state = 0;
byte demo_timer;
int demo_cycle = 500;
unsigned long demo_last_state_change = 0;
int cycle = 100;

void setup() 
{
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

void loop() 
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
      case 'd': Serial.println("demo");
                demo = 1;
                break;
      case 't': Serial.println("timer");
                break;
      default:  Serial.print("unknown command ");
                Serial.print("-"); Serial.print(ser); Serial.print("-"); Serial.println();
                break;
    }
    
    if(col != 0)
    {
      if(demo == 1)
      {
        digitalWrite(pin_r, LOW); 
        digitalWrite(pin_y, LOW);  
        digitalWrite(pin_g, LOW); 
        demo = 0;
      }
      digitalWrite(col, col_state);
    } 
   }
   
   if(demo == 0)
   {
     delay(cycle);
     return;
   }
    
   if(demo_state == 0)
   {
    digitalWrite(pin_r, HIGH); 
    digitalWrite(pin_y, LOW);  
    digitalWrite(pin_g, LOW); 
   }
   
   if(demo_state == 1)
   {
    digitalWrite(pin_r, HIGH); 
    digitalWrite(pin_y, HIGH); 
    digitalWrite(pin_g, LOW);  
   }    
   
   if(demo_state == 2)
   {
    digitalWrite(pin_r, LOW);  
    digitalWrite(pin_y, LOW);  
    digitalWrite(pin_g, HIGH); 
   }
   
   if(demo_state == 3)
   {
    digitalWrite(pin_r, LOW);  
    digitalWrite(pin_y, HIGH);  
    digitalWrite(pin_g, LOW); 
   }

   if(millis() > (demo_last_state_change + demo_cycle))
   {
     demo_last_state_change = millis();
     demo_state++;
     demo_state%=4;
   }
   
   delay(cycle);
}

