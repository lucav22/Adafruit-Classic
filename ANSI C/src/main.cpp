#include <Arduino.h>

void MyDelay (unsigned long mSecondsApx);
void setup ()
{
unsigned char *portDDRC;
portDDRC = (unsigned char *) 0x27;
*portDDRC |= 0x80;
}
void loop ()
{
unsigned char *portC;
portC = (unsigned char *) 0x28;
*portC |= 0x80;
MyDelay(1000);
*portC &= 0x7F;
MyDelay (1000);
}
void MyDelay (unsigned long mSecondsApx)
{
volatile unsigned long i;
 unsigned long endTime = 250 * mSecondsApx;

for (i = 0; i < endTime; i++);
}