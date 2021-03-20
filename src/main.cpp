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
#define EPD_BUSY    22  // can set to -1 to not use a pin (will wait a fixed delay)
#define SRAM_CS     -1  // can set to -1 to not use a pin (uses a lot of RAM!)
#define EPD_RESET   -1  // can set to -1 and share with chip Reset (can't deep sleep)
#define SPI_SCK   18      /* hardware SPI SCK pin      */
#define SPI_MOSI  23      /* hardware SPI SID/MOSI pin   */
#define SPI_MISO  19       /* hardware SPI MISO pin   */

ThinkInk_290_Grayscale4_T5 display(EPD_DC, EPD_RESET, EPD_CS, SRAM_CS, EPD_BUSY);

#define COLOR1 EPD_BLACK
#define COLOR2 EPD_LIGHT
#define COLOR3 EPD_DARK

Button* yellowButton = NULL;
Button* redButton = NULL;
Button* orangeButton = NULL;

Counter* counter = NULL;

#define RED_LED 5
#define BLUE_LED 0
#define GREEN_LED 17

void refresh(void * hold) {
    counter->displayRefresh();
}

void setup() {
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
    counter = new Counter(0,0,&display);

    Serial.println("Setting up the buttons!");
    yellowButton = new Button(16,INPUT); 
    redButton = new Button(25,INPUT);
    orangeButton =  new Button(26,INPUT);

    Serial.println("Setting up the callbacks!");
    yellowButton->set_push_callback(counter->callback_button3,counter);
    orangeButton->set_release_callback(counter->callback_button2,counter);
    redButton->set_push_callback(counter->callback_button1,counter);

    Serial.println("Updating the display!");
    Serial.println("Counter Refresh: Clearing the buffer");
    display.clearBuffer();
    display.begin(THINKINK_MONO);        
    display.setCursor(10,40);
    display.setTextSize(6);
    display.print("LOADING");
    display.display();
    //delay(3000);
    counter->displayRefresh();
    Serial.println("done with setup!");
}
int i = 3000000;
int c = i;

void loop() {
    yellowButton->updateState();
    redButton->updateState();
    orangeButton->updateState();
}
