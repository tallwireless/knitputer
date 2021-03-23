/*
 * Display.h
 *
 * Wrapper around the other display to be able to add features like the
 * StatusLED
 */


#include "Adafruit_ThinkInk.h"
#include "StatusLED.h"

#ifndef KNITPUTER_DISPLAY
#define KNITPUTER_DISPLAY

class Display: public ThinkInk_290_Grayscale4_T5 {
    private:
        StatusLED* _statusLED = NULL;

    public:
        Display(StatusLED* s,int8_t SID, int8_t SCLK, int8_t DC, int8_t RST,
                             int8_t CS, int8_t SRCS, int8_t MISO,
                             int8_t BUSY = -1)
          : ThinkInk_290_Grayscale4_T5( SID, SCLK, DC, RST, CS, SRCS, MISO, BUSY){_statusLED = s;};

        Display(StatusLED* s, int8_t DC, int8_t RST, int8_t CS, int8_t SRCS, int8_t MISO,
                             int8_t BUSY = -1, SPIClass *spi = &SPI)
          : ThinkInk_290_Grayscale4_T5( DC, RST, CS, SRCS, BUSY, spi){_statusLED = s;};

        void display(bool sleep = false) {
            _statusLED->setStatusBlue();
            Serial.println("full update");
            ThinkInk_290_Grayscale4_T5::display();
            _statusLED->clearStatus();
        };
        void displayPartial(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2) {
            _statusLED->setStatusBlue();
            Serial.println("partial update");
            ThinkInk_290_Grayscale4_T5::displayPartial(x1, y1, x2, y2);
            _statusLED->clearStatus();
        };
};
#endif
