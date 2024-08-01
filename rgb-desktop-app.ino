#include <Adafruit_NeoPixel.h>

// Pin al que está conectado el controlador ARGB
#define LED_PIN    6

// Número de LEDs en el ventilador (ajusta este número según sea necesario)
#define NUM_LEDS   12  // Ajusta según el número de LEDs en tu ventilador

// Crear un objeto Adafruit_NeoPixel
Adafruit_NeoPixel strip = Adafruit_NeoPixel(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

void setup() {
  // Inicializar la biblioteca de NeoPixel
  strip.begin();
  // Apagar todos los LEDs al inicio
  strip.setBrightness(128);
  strip.show();
}

void loop() {
  // Parpadeo aleatorio en todos los LEDs
  randomBlink();
}

void randomBlink() {
  // Aleatorizar la duración del encendido y apagado
  int onTime = random(200, 2500);   // Duración aleatoria entre 50 y 200 ms
  int offTime = random(200, 1000);  // Duración aleatoria entre 50 y 200 ms
  
  // Encender todos los LEDs en blanco
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(255, 250, 200));
  }
  strip.show();
  delay(onTime);
  
  // Apagar todos los LEDs
  for(int i = 0; i < NUM_LEDS; i++) {
    strip.setPixelColor(i, strip.Color(0, 0, 0));
  }
  strip.show();
  delay(offTime);
}
