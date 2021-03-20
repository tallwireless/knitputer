/*
 * Counter.h
 *
 * Declaration of a counter app
 *
 */


#ifndef KNITPUTER_COUTER
#define KNITPUTER_COUTER

#include "Button.h"
#include "Adafruit_ThinkInk.h"


class Counter {
    private:
        int _count;
        int _goal;

        ThinkInk_290_Grayscale4_T5* _display;
        void _writeCounter(const int, const int);
        void _writeGoal(const int, const int);
        void _writeButtonLabels();
        void _counterRefresh();
        void _goalRefresh();
        void _fullRefresh();
        void _toggleState() { _state = !_state; };
        void _incrementGoal_tens();
        void _incrementGoal_ones();
        bool _state = false;

    public:
        Counter(const int startValue, const int goal, ThinkInk_290_Grayscale4_T5* display);
        void updateCounter();
        static void callback_button1(void*);
        static void callback_button2(void*);
        static void callback_button3(void*);
        void incrementCounter();
        void resetCounter();
        const int getCount() { return _count; };
        const int getGoal() { return _goal; };
        void displayRefresh() { _fullRefresh(); };
        const bool getState() { return _state; };
};

#endif
