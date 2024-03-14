#include <Arduino.h>

void NewDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80; // Set pin 7 of port C as output
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80; // Turn on LED by setting pin 7 high
    NewDelay(1000); // Adjusted for roughly a 1-second delay
    *portC &= ~0x80; // Turn off LED by clearing pin 7
    NewDelay(1000); // Adjusted for roughly a 1-second delay
}

void NewDelay(unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 1000 * mSecondsApx; // Adjust based on clock speed and required accuracy
    for (i = 0; i < endTime; i++);
}
