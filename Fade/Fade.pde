
int brightness = 0;    // how bright the LED is
int fadeAmount = 5;    // how many points to fade the LED by
int pin = 4;

void setup()  
{ 
  pinMode(pin, OUTPUT);
} 

void loop()  
{ 
  analogWrite(pin, brightness);    

  brightness = brightness + fadeAmount;

  if (brightness == 0 || brightness == 255) {
    fadeAmount = -fadeAmount ; 
  }     

  delay(30);                            
}

