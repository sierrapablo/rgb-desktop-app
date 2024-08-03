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
  // Hacer la transición de colores LED a LED
  colorWheel();
}

void colorWheel() {
  // Recorrer 256 valores para crear una rueda cromática completa
  for (int j = 0; j < 256; j++) {
    for (int i = 0; i < NUM_LEDS; i++) {
      // Calcular el color basado en la posición en la rueda
      strip.setPixelColor(i, wheel((i * 256 / NUM_LEDS + j) & 255));
    }
    strip.show();
    delay(20);  // Ajustar la velocidad de la transición
  }
}

// Función para generar colores en una rueda cromática
uint32_t wheel(byte wheelPos) {
  wheelPos = 255 - wheelPos;
  if (wheelPos < 85) {
    return strip.Color(255 - wheelPos * 3, 0, wheelPos * 3);
  }
  if (wheelPos < 170) {
    wheelPos -= 85;
    return strip.Color(0, wheelPos * 3, 255 - wheelPos * 3);
  }
  wheelPos -= 170;
  return strip.Color(wheelPos * 3, 255 - wheelPos * 3, 0);
}
