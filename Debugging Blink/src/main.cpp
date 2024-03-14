#include <Arduino.h>

int ledPin = 13;
void setup ()
{
Serial.begin(9600);
pinMode(ledPin, OUTPUT);
}
void loop()
{
 digitalWrite(13, HIGH);
 Serial.println("LED ON");
 delay(1000);
 digitalWrite(13, LOW);
 Serial.println("LED OFF");
 delay(1000);
}