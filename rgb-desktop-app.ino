/*
 * RGB custom controller for PC case with Arduino Nano
 * @author P.S.L.
 * @date 2024
 */


#include <Adafruit_NeoPixel.h>


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

}


void loop()
{
	
}
