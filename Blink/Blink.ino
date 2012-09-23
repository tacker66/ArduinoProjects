
int pin_g = 2;
int pin_y = 3;
int pin_r = 4;

int wait = 1000;

void setup() 
{        xx        
  pinMode(pin_g, OUTPUT);     
  pinMode(pin_y, OUTPUT);     
  pinMode(pin_r, OUTPUT);     
}

void loop() 
{
  digitalWrite(pin_r, HIGH); 
  digitalWrite(pin_y, LOW);  
  digitalWrite(pin_g, LOW); 
  delay(3*wait);             
  digitalWrite(pin_r, LOW); 
  digitalWrite(pin_y, HIGH); 
  digitalWrite(pin_g, LOW);  
  delay(wait);             
  digitalWrite(pin_r, LOW);  
  digitalWrite(pin_y, LOW);  
  digitalWrite(pin_g, HIGH); 
  delay(3*wait);             
  digitalWrite(pin_r, LOW);  
  digitalWrite(pin_y, HIGH);  
  digitalWrite(pin_g, HIGH); 
  delay(wait);             
}

