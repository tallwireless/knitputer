/*
 * Counter app
 *
 * Basically a counter system
 */

#include "Button.h"
#include "Counter.h"
#include "Adafruit_ThinkInk.h"
//int _count;
//int _goal;
//struct CounterButtons _buttons;
//void* _display;

Counter::Counter(const int startValue, const int goal, ThinkInk_290_Grayscale4_T5* display) {
    // Let's set some things up!
    _count = startValue;
    _goal = goal;
    _display=display;
}

void Counter::callback_incrementCounter(void *obj) {
    Counter* This = (Counter*) obj;
    This->incrementCounter();
}

void Counter::incrementCounter() {
    _count += 1;
    if (_count % 10) {
        _counterRefresh();
    }
    else {
        _fullRefresh();
    }
}

void Counter::callback_resetCounter(void *obj) {
    Counter* This = (Counter*) obj;
    This->resetCounter();
}

void Counter::resetCounter() {
    _count = 0;
    _fullRefresh();
}

void Counter::_writeCounter(const char* label, const int counter, const int x, const int y) {
    _display->setTextColor(EPD_BLACK);
    _display->setTextSize(3);
    _display->setCursor(10+y,5+x);
    _display->begin(THINKINK_MONO);        
    _display->print(label);              
    _display->setCursor(10+y,45+x);
    _display->setTextSize(10);
    _display->print(counter);
}

void  Counter::_counterRefresh() {
    _writeCounter("Count:", _count, 0,0);
    _display->displayPartial(0,0,_display->width()/2,_display->height());
    _display->clearBuffer();
}

void Counter::_fullRefresh() {
    _writeCounter("Count:", _count, 0,0);
    _writeCounter("Goal: ", _goal, 0, _display->width()/2);
    _display->display();
    _display->clearBuffer();
}

