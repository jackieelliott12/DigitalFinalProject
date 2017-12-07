#include <Audio.h>
#include <Wire.h>
#include <SPI.h>
#include <SD.h>
#include <SerialFlash.h>
#include <Adafruit_NeoPixel.h>


// GUItool: begin automatically generated code
AudioInputAnalog         adc1;           //xy=164,95
AudioAnalyzePeak         peak1;          //xy=317,123
AudioConnection          patchCord1(adc1, peak1);
// GUItool: end automatically generated code

int mic = A2;

int potPin1 = A16;
int potVal1 = 0;
int mappedPotVal1 = 0;
int potPin2 = A17;
int potVal2 = 0;
int mappedPotVal2 = 0;
int potPin3 = A18;
int potVal3 = 0;
int mappedPotVal3 = 0;

int slideSwitch = 30;
int buttonPin = 31;


Adafruit_NeoPixel strip = Adafruit_NeoPixel(30, 6, NEO_GRB + NEO_KHZ800);

elapsedMillis fps;
int vol = 0;

void setup() {
  Serial.begin(9600);
  AudioMemory(12);
  pinMode (mic, INPUT);
  pinMode (slideSwitch, INPUT);
  pinMode (buttonPin, INPUT);
  strip.begin();
  strip.show();

  //  analogReadResolution(10);
}

void loop() {
  switchMode();
}


void vuMeter() {
  potVal1 = analogRead(potPin1);
  potVal2 = analogRead(potPin2);
  potVal3 = analogRead(potPin3);

  mappedPotVal1 = map(potVal1, 0, 65535, 0, 255);
  mappedPotVal2 = map(potVal2, 0, 65535, 0, 255);
  mappedPotVal3 = map(potVal3, 0, 65535, 0, 255);

  Serial.println(potVal1);
  for (int i = 0; i < 30; i++) {
    if (i < vol) {
      strip.setPixelColor(i, 0, 0, 255);
      }
    if (i >= vol) {
      strip.setPixelColor(i, mappedPotVal1, mappedPotVal2, mappedPotVal3);
    }
  strip.show();
}
}

void checkMic() {
  if (fps > 24) {
    if (peak1.available()) {
      fps = 0;
      vol = peak1.read() * 30.0;

      Serial.print("|");
      for (int cnt = 0; cnt < vol; cnt++) {
        Serial.print(">");
      }
      Serial.println();
    }
  }
}

void ampMode() {
  vuMeter();
  checkMic();
}

void rainbow() {
  for (int i = 0; i < 30; i++) {
    if (i < vol) {
      strip.setPixelColor(0, 255, 0, 0); //RED
      strip.setPixelColor(6, 255, 0, 0);
      strip.setPixelColor(12, 255, 0, 0);
      strip.setPixelColor(18, 255, 0, 0);
      strip.setPixelColor(24, 255, 0, 0);
      strip.setPixelColor(30, 255, 0, 0);
      strip.setPixelColor(1, 0, 255, 0); //GREEN
      strip.setPixelColor(7, 0, 255, 0);
      strip.setPixelColor(13, 0, 255, 0);
      strip.setPixelColor(19, 0, 255, 0);
      strip.setPixelColor(25, 0, 255, 0);
      strip.setPixelColor(2, 0, 0, 255); //BLUE
      strip.setPixelColor(8, 0, 0, 255);
      strip.setPixelColor(14, 0, 0, 255);
      strip.setPixelColor(20, 0, 0, 255);
      strip.setPixelColor(26, 0, 0, 255);
      strip.setPixelColor(3, 255, 255, 0); //YELLOW
      strip.setPixelColor(9, 255, 255, 0);
      strip.setPixelColor(15, 255, 255, 0);
      strip.setPixelColor(21, 255, 255, 0);
      strip.setPixelColor(27, 255, 255, 0);
      strip.setPixelColor(4, 0, 255, 255);  //CYAN
      strip.setPixelColor(10, 0, 255, 255);
      strip.setPixelColor(16, 0, 255, 255);
      strip.setPixelColor(22, 0, 255, 255);
      strip.setPixelColor(28, 0, 255, 255);
      strip.setPixelColor(5, 255, 0, 255); //MAGENTA
      strip.setPixelColor(11, 255, 0, 255);
      strip.setPixelColor(17, 255, 0, 255);
      strip.setPixelColor(23, 255, 0, 255);
      strip.setPixelColor(29, 255, 0, 255);
    }
    if (i >= vol) {
      strip.setPixelColor(i, 0, 0, 0);
    }
  }
  strip.show();
  delay(50); //delay so light stays longer
}

void rainbowMode() {
  rainbow();
  checkMic();
}

void switchMode() {
  if (digitalRead(slideSwitch) == HIGH) {
    ampMode();
  } else {
    rainbowMode();
  }
}

