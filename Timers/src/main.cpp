#include <Arduino.h>

#define MAX_DUTY_CYCLE 100
uint16_t dutyCycleA = 0; // Duty cycle for Pin 9 starts at 0%
uint16_t dutyCycleB = MAX_DUTY_CYCLE; // Duty cycle for Pin 10 starts at 100%
bool increasing = true; // Direction of change for dutyCycleA

void setup() {
  // Set OC1A (Pin 9) and OC1B (Pin 10) as outputs
  DDRB |= (1 << PB5) | (1 << PB6);

  // Configure Timer1 for Fast PWM mode 14 (ICR1 as TOP)
  TCCR1A = (1 << COM1A1) | (1 << COM1B1) | (1 << WGM11);
  TCCR1B = (1 << WGM13) | (1 << WGM12) | (1 << CS10);

  // Set the PWM frequency to 1kHz
  ICR1 = 8000;

  // Set initial duty cycle
  OCR1A = (ICR1 * dutyCycleA) / MAX_DUTY_CYCLE;
  OCR1B = (ICR1 * dutyCycleB) / MAX_DUTY_CYCLE;
}

void loop() {
  // Update the duty cycles
  if (increasing) {
    dutyCycleA++;
    dutyCycleB--;
  } else {
    dutyCycleA--;
    dutyCycleB++;
  }

  // Reverse the direction at the limits
  if (dutyCycleA == MAX_DUTY_CYCLE || dutyCycleA == 0) {
    increasing = !increasing;
  }

  // Update the OCR1A and OCR1B values to adjust the duty cycles
  OCR1A = (ICR1 * dutyCycleA) / MAX_DUTY_CYCLE;
  OCR1B = (ICR1 * dutyCycleB) / MAX_DUTY_CYCLE;

  // Delay to slow down the duty cycle change
  delay(100);
}
