/*
 *
 * StatusLED
 * 
 * Control the StatusLED
 *
 */
        
#include "StatusLED.h"


StatusLED::StatusLED(const int r, const int g, const int b) {
    // Store the pin numbers internally, set the mode, and turn off the pin
    _r_pin = r;
    pinMode(_r_pin,OUTPUT);
    _turnOff(_r_pin);

    _g_pin = g;
    pinMode(_g_pin,OUTPUT);
    _turnOff(_g_pin);

    _b_pin = b;
    pinMode(_b_pin,OUTPUT);
    _turnOff(_b_pin);
}
StatusLED::StatusLED(const int r, const int g, const int b, const int on, const int off) {
    // Set what it means to be on or off
    _on = on;
    _off = off;

    // Call the other constructor to set everything else up
    StatusLED(r,g,b);
}

void StatusLED::clearStatus() {
    // turn off all the LEDs
    _turnOff(_r_pin);
    _turnOff(_g_pin);
    _turnOff(_b_pin);
}
void StatusLED::setStatusBlue() {
    // clear the status
    clearStatus();

    // turn on the blue LED
    _turnOn(_b_pin);
}
void StatusLED::setStatusGreen() {
    // clear the status
    clearStatus();

    // turn on the green LED
    _turnOn(_g_pin);
}
void StatusLED::setStatusRed() {
    // clear the status
    clearStatus();

    // turn on the red LED
    _turnOn(_r_pin);
}
void StatusLED::setStatusYellow() {
    // clear the status
    clearStatus();

    //turn on the green and red LEDs
    _turnOn(_g_pin);
    _turnOn(_r_pin);
}

void StatusLED::setStatusPurple() {
    // clear the status
    clearStatus();

    //turn on the red and blue LEDs
    _turnOn(_r_pin);
    _turnOn(_b_pin);

}
