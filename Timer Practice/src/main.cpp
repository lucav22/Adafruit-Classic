#include <Arduino.h>

// Timers  Example
// Requesting Timer 0/8 (8 Bit), which is Pin #3, SCl on my board
// PWM/ 1ms

void setup() {
  // put set up code here
  TCCR0A = 0b00100011;
      // 00 Channel A Disconnected since im using for TOP
      // 10 - Channel B Clears on a match
      // 00 - Not used
      // 11 - Bit 0 and 1 of WGM (111) - Fast PWm up to ORC0A

  TCCR0B = 0b00001011;
      // 0000 - Don't care
      // 1 - MSC of WGM (111)
      // 011 Prescale by 64 so new clocl frequency is 8M/64 = 125k
  
  OCR0A = 125;
  // 125 Bus ticks = 1ms
  OCR0B = 0; 
  // Hald of OCR0A which gives 50% duty cycle


}

void loop() {
  delay(200);
  OCR0B++;
  if (OCR0B > OCR0A)
    OCR0B = 0;




}