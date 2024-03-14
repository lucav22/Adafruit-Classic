#include <Arduino.h>

void MyDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80; // Set the highest bit of DDR to make pin 7 of port C an output
}

void loop() {
    // Pointer to the PORT register of port C
    unsigned char *portC;
    portC = (unsigned char *) 0x28;

    // Blink pattern
    for (int pattern = 1; pattern <= 3; pattern++) {
        for (int blink = 0; blink < pattern; blink++) {
            *portC |= 0x80; // Turn on the LED
            MyDelay(1000); // Delay for on-state
            *portC &= ~0x80; // Turn off the LED
            if (blink < pattern - 1) {
                MyDelay(500); // Shorter delay between blinks within a pattern
            }
        }
        MyDelay(1000); // Delay after each pattern before starting the next
    }
}

void MyDelay(unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 250 * mSecondsApx;
    for (i = 0; i < endTime; i++);
}
