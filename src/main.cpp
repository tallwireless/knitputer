/***************************************************
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/

#include "Adafruit_ThinkInk.h"
#include "Button.h"
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
int counter = 0;
bool first = true;
int goal = 10;



void writeCounter(const char* label, const int counter, const int x, const int y) {
    display.setTextColor(EPD_BLACK);
    display.setTextSize(3);
    display.setCursor(10+y,5+x);
    display.begin(THINKINK_MONO);
    display.print(label);
    display.setCursor(10+y,45+x);
    display.setTextSize(10);
    display.print(counter);

}

void partialDisplayUpdate(const int x1, const int y1, const int x2, const int y2) {
    Serial.println("Partially updating the display");
    digitalWrite(statusLED, HIGH);
    display.displayPartial(x1,y1,x2,y2);
    display.clearBuffer();
    digitalWrite(statusLED, LOW);
}

void fullDisplayUpdate() {
    Serial.println("Updating the full display");
    digitalWrite(statusLED, HIGH);
    display.display();
    display.clearBuffer();
    digitalWrite(statusLED, LOW);
}

void clearDisplay() {
    Serial.println("Clearing Display");
    digitalWrite(statusLED, HIGH);
    display.clearDisplay();
    digitalWrite(statusLED, LOW);
}

void incrementCounter() {
    counter +=1;
    if (counter % 5 != 0){
        writeCounter("Count:",counter,0,0);
        partialDisplayUpdate(0,0,150,150);
    }
    else {
        writeCounter("Goal:", goal, 0 , 140);
        writeCounter("Count:",counter,0,0);
        fullDisplayUpdate();
    }
}

void resetCounter() {
    counter = 0;
    writeCounter("Goal:", goal, 0 , 140);
    writeCounter("Count:",counter,0,0);
    fullDisplayUpdate();
}

void refreshDisplay() {
    writeCounter("Goal:", goal, 0 , 140);
    writeCounter("Count:",counter,0,0);
    fullDisplayUpdate();
}
void setup() {
    yellowButton = Button(17); 
    yellowButton.set_release_callback(incrementCounter);
    redButton = Button(21);
    redButton.set_push_callback(resetCounter);
    orangeButton = Button(34);
    orangeButton.set_push_callback(refreshDisplay);
  
    Serial.begin(115200);
    while (!Serial) {
        delay(10);
    }
}

void loop() {
  if (first) {
    for( int i=0; i< 10; i++){
      Serial.println("");
    }


  Serial.println("STARTING!");

    
   // clearDisplay();
    writeCounter("Goal:", goal, 0,140);
    writeCounter("Count:",counter,0,0);
    fullDisplayUpdate();
    first = false;
  }
    yellowButton.updateState();
    redButton.updateState();
    orangeButton.updateState();
  
}
