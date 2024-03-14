#include <Arduino.h>

// Function prototypes to organize code structure
void SetupLEDs();
void updateLEDs(uint8_t Percent);
void SetupTimerPWM();
void setupADC();
void SetPWMFreq(uint16_t freqInHz);
uint16_t translateADCtoFreq(uint16_t ADCval);

// Initializes LEDs as visual indicators of PWM frequency
void SetupLEDs() {
  // Configure pins as output for LEDs that indicate frequency range
  DDRB |= (1<<5) | (1<<6); // LEDs on PB5 and PB6 as outputs for lower frequencies
  DDRD |= (1<<7); // LED on PD7 as output for higher frequencies
  Serial.println("LEDs setup complete.");
}

// Updates LEDs based on the current PWM frequency as a percentage of the total range
void updateLEDs(uint8_t Percent) {
  // Clear all LED states before setting new state
  PORTB &= ~((1 << 5) | (1 << 6));
  PORTD &= ~(1 << 7);

  // Light up specific LEDs based on frequency percentage
  if (Percent < 50) {
    PORTB |= (1 << 5); // Lower half frequencies, turn on PB5
  } else {
    PORTB |= (1 << 6); // Upper half frequencies, turn on PB6
    PORTD |= (1 << 7); // Also turn on PD7 for frequencies above 50%
  }

  Serial.print("LED Update - Frequency Percent: ");
  Serial.println(Percent);
}

// Sets up Timer 1 for PWM output, using a 16-bit timer for high resolution frequency control
void SetupTimerPWM() {
  DDRB |= (1<<1); // Set PB1 (OC1A) as output for PWM
  // Configuring Timer 1 for Fast PWM mode through ICR1 for a clear top value
  TCCR1A = (1<<COM1A1) | (1<<WGM11); 
  TCCR1B = (1<<WGM13) | (1<<WGM12) | (1<<CS10); // No prescaling, start timer
  ICR1 = 16000; // Set initial TOP value for 1kHz at 16MHz CPU clock
  OCR1A = ICR1 / 2; // 50% duty cycle
  Serial.println("Timer PWM setup complete.");
}

// Configures ADC for continuous reading from a potentiometer
void setupADC() {
  ADMUX = (1<<REFS0); // AVcc as the reference
  // Enable ADC, auto trigger, prescaler of 128 for ADC clock
  ADCSRA = (1<<ADEN) | (1<<ADATE) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
  ADCSRA |= (1<<ADSC); // Start ADC conversions
  Serial.println("ADC setup complete.");
}

// Adjusts the PWM frequency while maintaining a 50% duty cycle
void SetPWMFreq(uint16_t freqInHz) {
  freqInHz = constrain(freqInHz, 1000, 4000); // Limit frequency to between 1kHz and 4kHz
  // Calculate ICR1 based on desired frequency. Adjust formula to consider integer division rounding
  uint32_t icr = 16000000 / (2 * freqInHz) - 1;
  ICR1 = (uint16_t)icr; // Cast to uint16_t to match register size
  OCR1A = ICR1 / 2; // Maintain 50% duty cycle
  Serial.print("PWM Frequency Set to: ");
  Serial.println(freqInHz);
}

// Translates the ADC value to a corresponding PWM frequency within the desired range
uint16_t translateADCtoFreq(uint16_t ADCval) {
  // ADC range (0-1023) linearly mapped to frequency range (1kHz-4kHz)
  return map(ADCval, 0, 1023, 1000, 4000);
}

void setup() {
  Serial.begin(9600);
  while (!Serial); // Necessary for certain boards like Leonardo or Micro
  SetupLEDs();
  SetupTimerPWM();
  setupADC();
}

void loop() {
  uint16_t ADCValue = analogRead(A0); // Read ADC value
  uint16_t Freq = translateADCtoFreq(ADCValue); // Convert to frequency
  SetPWMFreq(Freq); // Adjust PWM frequency
  uint8_t FreqPercent = map(Freq, 1000, 4000, 0, 100); // Calculate frequency percentage
  updateLEDs(FreqPercent); // Update LEDs based on frequency
  delay(100); // Maintain readability of LED changes
}
