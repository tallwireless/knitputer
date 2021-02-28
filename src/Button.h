/*
 * button.h
 *
 * This is a class for containing all of the fun code for handling a button.
 *
 */
class Button {
private:
  // Somewhere to store the callback functions for different state
  // changes
  void (*_push_callback)();
  void (*_release_callback)();

  // Some internal properties
  int _pin;
  int _pinState;
  bool _state;

public:
  Button(const int);
  void set_push_callback(void (*func)());
  void set_release_callback(void (*func)());
  void updateState();
  const int getPin();
};