#include <Arduino.h>

void MyDelay(unsigned long mSecondsApx);

void setup() {
    unsigned char *portDDRC;
    portDDRC = (unsigned char *) 0x27;
    *portDDRC |= 0x80; // Configure pin as output
}

void loop() {
    unsigned char *portC;
    portC = (unsigned char *) 0x28;
    *portC |= 0x80; // Turn on LED
    MyDelay(1000); // Corrected syntax here
    *portC &= ~0x80; // Turn off LED; corrected to use bitwise NOT for 0x80 and fixed variable name
    MyDelay(1000); // Corrected syntax here
}

void MyDelay(unsigned long mSecondsApx) {
    volatile unsigned long i;
    unsigned long endTime = 1000 * mSecondsApx;
    for (i = 0; i < endTime; i++); // Delay loop
}
