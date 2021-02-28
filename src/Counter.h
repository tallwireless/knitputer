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
        void _writeCounter(const char*, const int, const int,  const int);
        void _counterRefresh();
        void _fullRefresh();

    public:
        Counter(const int startValue, const int goal, ThinkInk_290_Grayscale4_T5* display);
        void updateCounter();
        static void callback_incrementCounter(void*);
        void incrementCounter();
        static void callback_resetCounter(void*);
        void resetCounter();
        const int getCount() { return _count; };
        const int getGoal() { return _goal; };
        void displayRefresh() { _fullRefresh(); };

};

#endif
