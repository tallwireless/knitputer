/*
 *  StatusLED
 *
 *  This is a wrapper to control the StatusLED.
 *
 */

#ifndef KNITPUTER_STATUSLED
#define KNITPUTER_STATUSLED


#include "Arduino.h"

class StatusLED {
    private:
        int _r_pin = -1;
        int _g_pin = -1;
        int _b_pin = -1;
        int _on = LOW;
        int _off = HIGH;
        void _turnOff(const int pin) { digitalWrite(pin, _off); };
        void _turnOn(const int pin ) { digitalWrite(pin, _on); };
    public:
        StatusLED(const int r, const int g, const int b);
        StatusLED(const int r, const int g, const int b, const int on, const int off); 
        void clearStatus();
        void setStatusBlue();
        void setStatusGreen();
        void setStatusRed();
        void setStatusYellow();
        void setStatusPurple();
};


#endif
