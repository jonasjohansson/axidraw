#include <Adafruit_NeoPixel.h>
#include <Smoothed.h>

Adafruit_NeoPixel pixels(10, 6, NEO_GRB + NEO_KHZ800);

Smoothed <float> mySensor;

bool ledOn = false;

int MIN_DIST = 485;
int MAX_DIST = 490;

bool DEBUG = false;

void setup() {
  pixels.begin();
  pixels.clear();
  pixels.setBrightness(20);
  pixels.show();
  mySensor.begin(SMOOTHED_EXPONENTIAL, 5);
  mySensor.clear();
  Serial.begin(9600);
  delay(1000);
}

// 477-489 (DOWN)
// 488-500 (UP)

void loop() {
  
  mySensor.add(analogRead(0));
  float dist = mySensor.get();
  
  if (DEBUG) Serial.println(dist);

  if (dist > MAX_DIST && ledOn == true) {
    pixels.setPixelColor(0, pixels.Color(0, 0, 0));
    pixels.show();
    ledOn = false;
  }

  if (dist < MIN_DIST && ledOn == false) {
    pixels.setPixelColor(0, pixels.Color(255, 255, 255));
    pixels.show();
    ledOn = true;
  }
  
  delay(1);
}
