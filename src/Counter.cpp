/*
 * Counter app
 *
 * Basically a counter system
 */

#include "Button.h"
#include "Counter.h"
#include "Display.h"
//int _count;
//int _goal;
//struct CounterButtons _buttons;
//void* _display;

Counter::Counter(const int startValue, const int goal, Display* display) {
    // Let's set some things up!
    _count = startValue;
    _goal = goal;
    _display=display;
}

void Counter::callback_button1(void *obj) {
    Counter* This = (Counter*) obj;
    Serial.println("callback_button1");
    bool state = This->getState(); 
    // If we in a counting state
    if ( state == false ) {
        Serial.println("callback_button1: State is false");
        This->incrementCounter();
    } else if (state == true ) {
        // edit the goal count
        Serial.println("callback_button1: State is true");
        This->_incrementGoal_tens();
    }
}

void Counter::incrementCounter() {
    _count += 1;
    if (_count % 20) {
        _counterRefresh();
    }
    else {
        _fullRefresh();
    }
}

void Counter::callback_button2(void *obj) {
    Serial.println("callback_button2");
    Counter* This = (Counter*) obj;
    bool state = This->getState(); 
    if ( state == 0 ) {
        // Reset the counter in counting mode
        This->resetCounter();
    } else if ( state == 1 ) {
        // increment the ones space
        This->_incrementGoal_ones();
    }
}

void Counter::resetCounter() {
    Serial.println("Resetting the counter for");
    _count = 0;
    _fullRefresh();
}

void Counter::callback_button3(void *obj) {
    Serial.println("callback_button3");
    Counter* This = (Counter*) obj;
    This->_toggleState();
    This->_fullRefresh();
}

void Counter::_incrementGoal_tens() {
    // Increase the goal by ten
    _goal += 10;
    // If the goal exceeds 100 then we are going to roll it back
    if ( _goal >= 100 ) {
        _goal -= 100;
    }
    _goalRefresh();
}

void Counter::_incrementGoal_ones() {
    //increase the goal by one
    _goal += 1;
    // rollback by 10 if increase from 9
    if ( _goal % 10  == 0 ) {
        _goal -= 10;
    }
    _goalRefresh();
}

void Counter::_writeCounter(const int x, const int y) {
    _display->setTextColor(EPD_BLACK);
    _display->setTextSize(2);
    _display->setCursor(10+y,5+x);
    _display->print("Count:");              
    _display->setCursor(10+y,40+x);
    _display->setTextSize(6);
    _display->print(_count);
}
void Counter::_writeGoal(const int x, const int y) {
    _display->setTextColor(EPD_BLACK);
    _display->setTextSize(2);
    _display->setCursor(10+y,5+x);
    if ( _state ) {
        // When we are in the edit state
        _display->setTextColor(EPD_BLACK,EPD_RED);
        _display->print("Edit Goal:");              
        _display->setTextColor(EPD_BLACK);
    } else {
        _display->print("Goal:");              
    }
    _display->setCursor(10+y,40+x);
    _display->setTextSize(6);
    _display->print(_goal);
}

void  Counter::_counterRefresh() {
    Serial.println("Counter Refresh: Clearing the buffer");
    _display->clearBuffer();
    _display->begin(THINKINK_MONO);        
    Serial.println("Counter Refresh: writing counter");
    _writeCounter(0,0);
    Serial.println("Counter Refresh: Updating the screen");
    _display->displayPartial(0,45,
            _display->width()/2-30,_display->height()-27);
    Serial.println("Counter Refresh: Completed updating the screen. delaying");
    //delay(500);
    Serial.println("Counter Refresh: clearing buffer again");
    _display->clearBuffer();
}
void  Counter::_goalRefresh() {
    Serial.println("Goal Refresh: clearing the buffer");
    _display->clearBuffer();
    _display->begin(THINKINK_MONO);        
    Serial.println("Goal Refresh");
    _writeGoal(0,_display->width()/2);
    Serial.println("Goal Refresh: updating the display");
    _display->displayPartial(_display->width()/2,45,
            _display->width()-30,_display->height()-27);
    Serial.println("GoallRefresh: Pausing");
    //delay(500);
    Serial.println("Goal Refresh: clearing the buffer");
    _display->clearBuffer();
}
void Counter::_writeButtonLabels() {
    int margin = 10;
    int interval = (_display->width()-margin*2)/3;
    int pos_x = margin;
    int pos_y = _display->height()-10;
    _display->setTextColor(EPD_BLACK);
    _display->setCursor(pos_x,pos_y);
    _display->setTextSize(1);
    
    if (_state) {
        _display->print("Tens");
        pos_x += interval;
        _display->setCursor(pos_x, pos_y);
        _display->print("Ones");
        pos_x += interval;
        _display->setCursor(pos_x, pos_y);
        _display->print("Done");
    } else {
        _display->print("Add one");
        pos_x += interval;
        _display->setCursor(pos_x, pos_y);
        _display->print("Reset");
        pos_x += interval;
        _display->setCursor(pos_x, pos_y);
        _display->print("Edit Goal");
    }

}


void Counter::_fullRefresh() {
    Serial.println("FullRefresh: Clearing buffer");
    _display->clearBuffer();
    if( _state ) {
    _display->begin(THINKINK_GRAYSCALE4);        
    } else {
    _display->begin(THINKINK_MONO);        
    }
    Serial.println("FullRefresh: Writing the counter to the buffer");
    _writeCounter(0,0);
    Serial.println("FullRefresh: Writing the goal to the buffer");
    _writeGoal(0, _display->width()/2);
    Serial.println("FullRefresh: Writing the button labels to the buffer");
    _writeButtonLabels();
    Serial.println("FullRefresh: Displaying");
    _display->display();
    Serial.println("FullRefresh: Pausing");
    //delay(2000);
    Serial.println("FullRefresh: Clearing buffer again");
    _display->clearBuffer();
}

