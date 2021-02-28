/*
 * Button.cpp
 *
 * the meat of it all!
 *
 */


#include "Button.h"
#include "Arduino.h"


/*
 * Constructor
 *  
 *  Set the pin value, set the callbacks to NULL, setup the pin
 *
 */
Button::Button(const int pin){
    
    _push_callback = NULL;
    _release_callback = NULL;

    _pin = pin;
    _pinState = 0;
    _state = false;

    pinMode(_pin, INPUT_PULLDOWN);
}


// Set the _push_callback function pointer
void Button::set_push_callback(void (*func)() ) {
    _push_callback = func;
}

// set the _release_callback function pointer
void Button::set_release_callback(void (*func)() ) {
    _release_callback = func;
}

// return the pin number
const int Button::getPin() {
    return _pin;
}

// Update the state of the pin and run any nessicary callbacks if they are set
void Button::updateState() {
    // update the pin state
    _pinState = digitalRead(_pin);

    // When the button is pushed
    if ( _pinState && !_state) {
        _state = !_state;
        // If the callback is set, let's call it
        if ( _push_callback != NULL ){
            _push_callback();
        }
    } 
    // When the button is released
    else if ( !_pinState && _state ) {
        _state = !_state;
        // If the callback is set, let's call it
        if ( _release_callback != NULL ){
            _release_callback();
        }
    }
    
}
