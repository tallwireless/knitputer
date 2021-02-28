/*
 * Button.cpp
 *
 * the meat of it all!
 *
 */


#include "Button.h"
#include "Arduino.h"


Button::Button(const int pin){
    
    _push_callback = NULL;
    _release_callback = NULL;

    _pin = pin;
    _pinState = 0;
    _state = false;

    pinMode(_pin, INPUT_PULLDOWN);
}


void Button::set_push_callback(void (*func)() ) {
    _push_callback = func;
}

void Button::set_release_callback(void (*func)() ) {
    _release_callback = func;
}

const int Button::getPin() {
    return _pin;
}

void Button::updateState() {
    _pinState = digitalRead(_pin);

    // When the button is pushed
    if ( _pinState && !_state) {
        _state = !_state;
        if ( _push_callback != NULL ){
            _push_callback();
        }
    } 
    // When the button is released
    else if ( !_pinState && _state ) {
        _state = !_state;
        if ( _release_callback != NULL ){
            _release_callback();
        }
    }
    
}
