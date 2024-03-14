#include <Arduino.h>


void NewDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x24;
    *portDDRC |= 0x20; // Set pin 5 of port D as output
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x25;
    *portC |= 0x20; // Turn on LED by setting pin 5 high
    NewDelay(1000); // Delay for approximately 1000 milliseconds
    *portC &= ~0x20; // Turn off LED by clearing pin 5
    NewDelay(1000); // Delay for approximately 1000 milliseconds
}

void NewDelay(unsigned long mSecondsApx) {
    volatile unsigned long i = 0;
    unsigned long endTime = 100 * mSecondsApx;
    while (i < endTime) {
        i++;
    }
}

