/*
 * RGB custom controller for PC case with Arduino Nano
 * @author P.S.L.
 * @date 2024
 */


#include <Adafruit_NeoPixel.h>
#include <EEPROM.h>


/* Define pins */

// D13: LED output
const int LED_ON_OFF = 13;

// D1, D10, D11, D12: Push buttons
const int BUTTON_ON_OFF = 1;
const int BUTTON_FRONT = 10;
const int BUTTON_REAR = 11;
const int BUTTON_INSIDE = 12;

// Pins for different WS2812 RGB LEDs stripes
const int LED_FRONT_BOTTOM = 2;
const int LED_FRONT_MID = 3;
const int LED_FRONT_TOP = 4;
const int LED_REAR = 5;
const int LED_TOP_FRONT = 6;
const int LED_TOP_BACK = 7;
const int LED_INSIDE = 8;
const int LED_GPU = 9;

// Number of WS2812 LEDs per strip
const int numFanLeds = 8;
const int numInsideStripLeds = 16;
const int numGPUStripLeds = 12;

// Create Adafruit_NeoPixel objects for each strip
Adafruit_NeoPixel frontBottomFan(
  numFanLeds,
  LED_FRONT_BOTTOM,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel frontMidFan(
  numFanLeds,
  LED_FRONT_MID,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel frontTopFan(
  numFanLeds,
  LED_FRONT_TOP,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel rearFan(
  numFanLeds,
  LED_REAR,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel topFrontFan(
  numFanLeds,
  LED_TOP_FRONT,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel topBackFan(
  numFanLeds,
  LED_TOP_BACK,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel insideStrip(
  numInsideStripLeds,
  LED_INSIDE,
  NEO_GRB + NEO_KHZ800
);
Adafruit_NeoPixel gpuStrip(
  numGPUStripLeds,
  LED_GPU,
  NEO_GRB + NEO_KHZ800
);

// A0-A5: Analog Input potentiometers
const int POT_FRONT_INTENSITY = A0;
const int POT_FRONT_CHROMATIC = A1;
const int POT_REAR_INTENSITY = A2;
const int POT_REAR_CHROMATIC = A3;
const int POT_INSIDE_INTENSITY = A4;
const int POT_INSIDE_CHROMATIC = A5;

// Default configurations for memory
/*
 * ledState -> boolean. Controls if the LEDs are ON/OFF
 * (front/rear/inside)ModeState -> int (1-4). Controls different modes:
 * 1: Static
 * 2: Pulse
 * 3: "Knight Rider"
 * 4: Industrial Cracked
 */
bool ledState = true;
int frontModeState = 1;
int rearModeState = 1;
int insideModeState = 1;

unsigned long lastDebounceTime = 0;
const unsigned long debounceDelay = 50;


void setup() {
  // Initialize digital pin LED_BUILTIN as an output.
  pinMode(LED_ON_OFF, OUTPUT);

  // Initialize button pins as inputs
  pinMode(BUTTON_ON_OFF, INPUT);
  pinMode(BUTTON_FRONT, INPUT);
  pinMode(BUTTON_REAR, INPUT);
  pinMode(BUTTON_INSIDE, INPUT);

  // Initialize each WS2812 RGB LED strip
  frontBottomFan.begin();
  frontMidFan.begin();
  frontTopFan.begin();
  rearFan.begin();
  topFrontFan.begin();
  topBackFan.begin();
  insideStrip.begin();
  gpuStrip.begin();
  
  // Turn off all pixels at the start
  frontBottomFan.show();
  frontMidFan.show();
  frontTopFan.show();
  rearFan.show();
  topFrontFan.show();
  topBackFan.show();
  insideStrip.show();
  gpuStrip.show();

  // Array to store the addresses in EEPROM
  int states[4] = {1, 2, 3, 4};
  int* statePointers[3] = {
    &frontModeState, &rearModeState, &insideModeState
  };

  // Read values from EEPROM
  ledState = EEPROM.read(0);
  for (int i = 0; i < 4; i++) {
    *statePointers[i] = EEPROM.read(states[i]);
  }

}


void loop() {
  int buttonState = digitalRead(BUTTON_ON_OFF);
  if (buttonState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      ledState = !ledState;
      EEPROM.write(0, ledState);
      lastDebounceTime = millis();
    }
  }

  handleButton(BUTTON_FRONT, frontModeState, 1);
  handleButton(BUTTON_REAR, rearModeState, 2);
  handleButton(BUTTON_INSIDE, insideModeState, 3);

  if (ledState) {
    int frontIntensity = analogRead(POT_FRONT_INTENSITY) / 4;
    int frontColor = analogRead(POT_FRONT_CHROMATIC);
    int rearIntensity = analogRead(POT_REAR_INTENSITY) / 4;
    int rearColor = analogRead(POT_REAR_CHROMATIC);
    int insideIntensity = analogRead(POT_INSIDE_INTENSITY) / 4;
    int insideColor = analogRead(POT_INSIDE_CHROMATIC);

    setStripColor(frontBottomFan, frontIntensity, frontColor);
    setStripColor(frontMidFan, frontIntensity, frontColor);
    setStripColor(frontTopFan, frontIntensity, frontColor);

    setStripColor(rearFan, rearIntensity, rearColor);
    setStripColor(topFrontFan, rearIntensity, rearColor);
    setStripColor(topBackFan, rearIntensity, rearColor);

    setStripColor(insideStrip, insideIntensity, insideColor);
    setStripColor(gpuStrip, insideIntensity, insideColor);
  } else {
    frontBottomFan.clear();
    frontMidFan.clear();
    frontTopFan.clear();
    rearFan.clear();
    topFrontFan.clear();
    topBackFan.clear();
    insideStrip.clear();
    gpuStrip.clear();

    frontBottomFan.show();
    frontMidFan.show();
    frontTopFan.show();
    rearFan.show();
    topFrontFan.show();
    topBackFan.show();
    insideStrip.show();
    gpuStrip.show();
  }
}


void handleButton(int buttonPin, int &modeState, int eepromAddress) {
  int buttonState = digitalRead(buttonPin);
  if (buttonState == HIGH) {
    if (millis() - lastDebounceTime > debounceDelay) {
      modeState++;
      if (modeState > 4) {
        modeState = 1;
      }
      EEPROM.write(eepromAddress, modeState);
      lastDebounceTime = millis();
    }
  }
}


void setStripColor(Adafruit_NeoPixel& strip, int intensity, int chromatic) {
  // Map potentiometer value to color wheel
  uint32_t color = wheel(chromatic % 1024);
  for (int i = 0; i < strip.numPixels(); i++) {
    strip.setPixelColor(i, strip.Color(
      (intensity * (color >> 16 & 0xFF)) / 255,
      (intensity * (color >> 8 & 0xFF)) / 255,
      (intensity * (color & 0xFF)) / 255
    ));
  }
  strip.show();
}


uint32_t wheel(int pos) {
  pos = 1023 - pos;
  if (pos < 341) {
    return (255 - pos * 255 / 341) << 16 | (pos * 255 / 341) << 8;
  } else if (pos < 682) {
    pos -= 341;
    return (255 - pos * 255 / 341) << 8 | pos * 255 / 341;
  } else {
    pos -= 682;
    return (pos * 255 / 341) << 16 | (255 - pos * 255 / 341);
  }
}
