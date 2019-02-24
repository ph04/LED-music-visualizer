#include <Adafruit_NeoPixel.h>
#ifdef __AVR__
  #include <avr/power.h>
#endif

#define PIN 7
#define LEDS 60
Adafruit_NeoPixel strip = Adafruit_NeoPixel(LEDS, PIN, NEO_GRB + NEO_KHZ800);

const int sensorPin = A1;
const int FTVPin = A2;
const int invertedPin = A0;
const int buttonPin = 9;
int sensorState = 0;
int FTVValue = 0;
int buttonValue = 0;
uint32_t leds[LEDS];
uint32_t leds2[LEDS];

void setup() {
  // This is for Trinket 5V 16MHz, you can remove these three lines if you are not using a Trinket
  #if defined (__AVR_ATtiny85__)
    if (F_CPU == 16000000) clock_prescale_set(clock_div_1);
  #endif
  // End of trinket special code

  strip.begin();
  strip.show();
}

uint32_t evalColor(int p) {
  if (p < 100) {
    return strip.Color(255, 0, 0);
  }
  else if (p >= 100 && p <= 200) {
    int b = (p - 40) * (255/37.0000);
    return strip.Color(255, 0, b);
  }
  else if (p > 200 && p <= 300) {
    int r = 255 - ((p - 78) * 2);
    return strip.Color(r, 0, 255);
  }
  else if (p >= 300 && p <= 400) {
    int g = (p - 206) * (255/32.0000);
    return strip.Color(0, g, 255);
  }
  else if (p <= 400 && p <= 500) {
    int r = (p - 239) * (255/11.0000);
    return strip.Color(r, 255, 255);
  }
  else if (p >= 500 && p <= 600) {
    return strip.Color(255, 255, 255);
  }
  else if (p >= 600 && p <= 700) {
    int rb = 255-((p-271)*2);
    return strip.Color(rb, 255, rb);
  }
  else if (p >= 700 && p <= 800) {
    return strip.Color(0, 255-(p-398), (p-398));
  }
  else return strip.Color(0, 0, 0);
}

int s = 1;

void loop() {
  sensorState = analogRead(sensorPin);
  buttonValue = digitalRead(buttonPin);

  if (buttonValue == LOW && s == 0) s = 1;
  else if (buttonValue == LOW && s == 1) s = 0;

  if (s == 0) FTVValue = analogRead(FTVPin);
  else FTVValue = analogRead(invertedPin);

  //begin of led shift
  for (int i = 0; i < LEDS; i++)
    leds[i] = strip.getPixelColor(i);

  for (int i = 1; i < LEDS; i++)
    leds2[i] = leds[i - 1];

  for (int i = 1; i < LEDS; i++)
    strip.setPixelColor(i, leds2[i]);
  //end of led shift

  strip.setPixelColor(0, evalColor(FTVValue - 200));
  strip.show();

  delay(sensorState / 12);
}
