#include <Arduino.h>

void NewDelay(unsigned int mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80; // Set the highest bit of DDR to make pin 7 of port C an output
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80; // Corrected to use 0x80 to turn on the LED
    NewDelay(1000); // Adjusted for a rough 1-second delay
    *portC &= ~0x80; // Corrected to properly turn off the LED
    NewDelay(1000); // Adjusted for another rough 1-second delay
}

void NewDelay(unsigned int mSecondsApx) {
    volatile unsigned int i;
    unsigned long endTime = 4 * mSecondsApx; // Adjusted multiplier for a more accurate delay
    for (i = 0; i < endTime; i++);
}
