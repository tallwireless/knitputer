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
    
    _push_callback_obj = NULL;
    _push_callback_obj_func = NULL;
    _release_callback_obj = NULL;
    _release_callback_obj_func = NULL;
    _push_callback_func = NULL;
    _release_callback_func = NULL;

    _pin = pin;
    _pinState = 0;
    _state = false;

    pinMode(_pin, INPUT_PULLDOWN);
}


// Set the _push_callback function pointer when there is no object
void Button::set_push_callback(void (*func)(void*) ) {
    _push_callback_func = func;
    _push_callback_obj = NULL;
    _push_callback_obj_func = NULL;
}

// set the _release_callback function pointer when there is no object
void Button::set_release_callback(void (*func)(void*) ) {
    _release_callback_func = func;
    _release_callback_obj = NULL;
    _release_callback_obj_func = NULL;
}
//
// Set the _push_callback function pointer when there is no object
void Button::set_push_callback(void (*func)(void*) , void* obj) {
    _push_callback_func = NULL;
    _push_callback_obj = obj;
    _push_callback_obj_func = func;
}
// Set the _release_callback function pointer when there is no object
void Button::set_release_callback(void (*func)(void*) , void* obj) {
    _release_callback_func = NULL;
    _release_callback_obj = obj;
    _release_callback_obj_func = func;
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
        if ( _push_callback_func == NULL && _push_callback_obj != NULL && _push_callback_obj_func != NULL ){
            _push_callback_obj_func(_push_callback_obj);
        }
        else if ( _push_callback_func != NULL && _push_callback_obj == NULL && _push_callback_obj_func == NULL ){
            _push_callback_func(NULL);
        }
    } 
    // When the button is released
    else if ( !_pinState && _state ) {
        _state = !_state;
        // If the callback is set, let's call it
        if ( _release_callback_func == NULL && _release_callback_obj != NULL && _release_callback_obj_func != NULL ){
            _release_callback_obj_func(_release_callback_obj);
        }
        else if ( _release_callback_func != NULL && _release_callback_obj == NULL && _release_callback_obj_func == NULL ){
            _release_callback_func(NULL);
        }
    }
    
}
