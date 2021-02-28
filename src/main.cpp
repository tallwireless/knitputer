#include <Adafruit_ThinkInk.h>

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

const int yellowButton = 17; 
const int redButton = 21;
const int orangeButton = 34;
const int statusLED = 14;

int yellowButtonState = 0;
int yellowState = 0;
int redButtonState = 0;
int redState = 0;
int orangeButtonState = 0;
int orangeState = 0;


void setup() {
  pinMode(redButton, INPUT_PULLDOWN);
  pinMode(yellowButton, INPUT_PULLDOWN);
  pinMode(orangeButton, INPUT_PULLUP);
  pinMode(statusLED, OUTPUT);
  
  Serial.begin(115200);
  while (!Serial) {
    delay(10);
  }
}
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
  bool full_update = false;
  bool update_screen = false;
  yellowButtonState = digitalRead(yellowButton);
  redButtonState = digitalRead(redButton);
  orangeButtonState = digitalRead(orangeButton);
  // The button goes from open to close
  if(yellowButtonState && !yellowState) {
    Serial.println("Yellow button Pushed");
    yellowState = !yellowState;
    counter += 1;
    update_screen = true;
  }
  // Button goes from closed to open
  else if (!yellowButtonState && yellowState){
    Serial.println("Yellow button released");
    yellowState = !yellowState;
  }
  if(redButtonState && !redState) {
    Serial.println("Red button Pushed");
    redState = !redState;
    counter = 0;
    update_screen = true;
  }
  // Button goes from closed to open
  else if (!redButtonState && redState){
    Serial.println("Red button Released");
    redState = !redState;
  }  
 if(orangeButtonState && !orangeState) {
    Serial.println("Orange button Pushed");
    orangeState = !orangeState;
    full_update = true;
  }
  // Button goes from closed to open
  else if (!orangeButtonState && orangeState){
    Serial.println("Orange button Released");
    orangeState = !orangeState;
  }

  if (update_screen && counter % 5 != 0){
    writeCounter("Count:",counter,0,0);
    partialDisplayUpdate(0,0,150,150);
  }
  else if (update_screen || full_update ) {
    writeCounter("Goal:", goal, 0 , 140);
    writeCounter("Count:",counter,0,0);
    fullDisplayUpdate();
  }
} 
