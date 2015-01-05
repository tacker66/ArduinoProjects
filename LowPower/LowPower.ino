
#include <Arduino.h>
#include <LowPower.h>

int builtin_led = 13;
int aux_led = 8;

// Results:
//  Arduino Nano (328):
//   powered with regulated 5V over VIN/GND: 12.8mA (builtin LED on), 14.6mA (LED off), 5.2mA powerDown mode
//   powered over 5V/GND: 24.2mA, 20.8mA, 7.7mA
//  Arduino Leonardo:
//   VIN/GND: 25.7mA, 27.4mA, 7.6mA
//   5V/GND: 36.3mA, 38.3mA, 9.5mA

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
