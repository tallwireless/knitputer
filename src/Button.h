/*
 * button.h
 *
 * This is a class for containing all of the fun code for handling a button.
 *
 */
#ifndef KNITPUTER_BUTTON
#define KNITPUTER_BUTTON

class Button {
private:
  // Somewhere to store the callback functions for different state
  // changes
  void (*_push_callback_func)(void*);
  void (*_release_callback_func)(void*);
  void (*_push_callback_obj_func)(void*);
  void (*_release_callback_obj_func)(void*);
  void* _push_callback_obj;
  void* _release_callback_obj;

  // Some internal properties
  int _pin;
  int _pinState;
  bool _state;

public:
  Button(const int);
  void set_push_callback(void (*)(void*));
  void set_push_callback(void (*)(void*),void*);
  void set_release_callback(void (*)(void*));
  void set_release_callback(void (*)(void*),void*);
  void updateState();
  const int getPin();
};

#endif
