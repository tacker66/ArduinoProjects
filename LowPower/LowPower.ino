
#include <Arduino.h>
#include <LowPower.h>

int builtin_led = 13;
int aux_led = 8;

void setup()
{
	pinMode(builtin_led, OUTPUT);
	pinMode(aux_led, OUTPUT);
}

void loop()
{
	digitalWrite(aux_led, HIGH);
	delay(8000);
	digitalWrite(aux_led, LOW);
	delay(8000);
	digitalWrite(builtin_led, HIGH);
	delay(8000);
	digitalWrite(builtin_led, LOW);
	LowPower.powerDown(SLEEP_8S, ADC_OFF, BOD_OFF);
}
