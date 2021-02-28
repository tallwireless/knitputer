/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_ThinkInk.h"
#include "Button.h"
#include "Counter.h"

//   --- EPD Display Setup ---
#define EPD_DC      33  // can be any pin, but required!
#define EPD_CS      15  // can be any pin, but required!
#define EPD_BUSY    23  // can set to -1 to not use a pin (will wait a fixed delay)
#define SRAM_CS     -1  // can set to -1 to not use a pin (uses a lot of RAM!)
#define EPD_RESET   -1  // can set to -1 and share with chip Reset (can't deep sleep)
#define SPI_SCK   5      /* hardware SPI SCK pin      */
#define SPI_MOSI  18      /* hardware SPI SID/MOSI pin   */
#define SPI_MISO  19       /* hardware SPI MISO pin   */

#define BUTTON_A 27
#define BUTTON_B 12a
#define BUTTON_C 13

ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

#define COLOR1 EPD_BLACK
#define COLOR2 EPD_LIGHT
#define COLOR3 EPD_DARK

Button yellowButton = NULL;
Button redButton = NULL;
Button orangeButton = NULL;
const int statusLED = 14;

bool gray = false;

Counter counter = Counter(0,10,&display);

void setup() {
    yellowButton = Button(17); 
    redButton = Button(21);
    orangeButton = Button(34);
 
    yellowButton.set_push_callback(counter.callback_incrementCounter,&counter);
    redButton.set_push_callback(counter.callback_resetCounter,&counter);

    counter.displayRefresh();

    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
}

void loop() {
    yellowButton.updateState();
    redButton.updateState();
}
