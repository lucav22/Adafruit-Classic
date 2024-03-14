#include <Arduino.h>

int ledPin = 13; // LED connected to digital pin 13

void setup() {
  pinMode(ledPin, OUTPUT); // Initialize the digital pin as an output
}

void loop() {
  int blinkCount = 1; // Start with one blink
  while(true) { // Infinite loop
    for (int j = 0; j < blinkCount; j++) { // Blink for blinkCount times
      digitalWrite(ledPin, HIGH); // Turn the LED on
      delay(500); // Keep it on for 500 milliseconds
      digitalWrite(ledPin, LOW); // Turn the LED off
      if (j < blinkCount - 1) { // If not the last blink in the sequence, wait before the next blink
        delay(500); // Wait for 500 milliseconds
      }
    }
    delay(1000); // After completing the blinks, wait for a second
    
    blinkCount++; // Increase the number of blinks for the next cycle
    if (blinkCount > 3) { // If the sequence completes one, two, and three blinks,
      blinkCount = 1; // Reset the blink count to start over
    }
  }
}





