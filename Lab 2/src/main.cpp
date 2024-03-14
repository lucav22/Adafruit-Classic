#include <Arduino.h>

void setup() {
  // Initialize serial communication
  Serial.begin(9600);
  
  // Set D3 (OC4B) as an output pin
  DDRD |= (1 << 0); // DDD3 is the bit position for pin D3 in the DDRD register
  
  DDRD &= ~(1<<6);


  ADMUX |= (1<< REFS0) & ~(1 << ADLAR) | (1<<MUX0);
  ADCSRA |= (1<< ADEN) | (1 << ADSC) | (1 << ADATE) | (1 << ADPS2);
  ADCSRB |= (1 << MUX5);
  DIDR2 |= (1 << ADC9D);

  // Configure Timer 4 for Fast PWM mode
  TCCR0A = (1 << COM0B1) | (1 << WGM01) | (1<<WGM00); // Set non-inverting mode for OC4B and enable PWM for OC4B
  TCCR4B = (1 << WGM02) | (1 << CS01) | (1 << CS00); // Set prescaler to 64 (CS42 is the bit position for a prescaler of 64)
  
  // Set the PWM frequency to 1kHz
  OCR0A = 124; // Set the top value for the counter which determines the PWM frequency
  
  // Set the duty cycle to 50% initially
  OCR0B = 0; // Set the duty cycle for OC4B (50% of 249)
}

void loop() {
  float aval;
  long x;
  x = millis();
  aval = abs(3 * sin(2 * 3.141592654 * x / 1000));
  delay(1);
  Serial.println(aval);
  OCR0B= aval/3*OCR0A;


  unsigned short ADCval;
  ADCval = (ADC & 0x3FF);

  float fADCval;
  fADCval = ((float)ADCval)/1023*3;

  Serial.print(abs(aval));
  Serial.print(" ");
  Serial.print(fADCval);
}


