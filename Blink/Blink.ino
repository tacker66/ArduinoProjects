
int pin_r = 12;
int pin_y = 9;
int pin_g = 6;

int wait = 200;

void setup() 
{      
  pinMode(pin_r, OUTPUT);     
  pinMode(pin_y, OUTPUT);     
  pinMode(pin_g, OUTPUT);     
  digitalWrite(pin_r, HIGH);  
  digitalWrite(pin_y, HIGH);  
  digitalWrite(pin_g, HIGH); 
  delay(5*wait);             
}

void loop() 
{
  digitalWrite(pin_r, LOW);  
  digitalWrite(pin_y, LOW);  
  digitalWrite(pin_g, LOW); 
  delay(wait);             
  digitalWrite(pin_r, HIGH); 
  digitalWrite(pin_y, LOW);  
  digitalWrite(pin_g, LOW); 
  delay(wait);             
  digitalWrite(pin_r, LOW); 
  digitalWrite(pin_y, HIGH); 
  digitalWrite(pin_g, LOW);  
  delay(wait);             
  digitalWrite(pin_r, LOW);  
  digitalWrite(pin_y, LOW);  
  digitalWrite(pin_g, HIGH); 
  delay(wait);             
}

