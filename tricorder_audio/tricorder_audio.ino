// #include <Adafruit_GFX.h>    // Core graphics library
// #include "Adafruit_ILI9340.h" // Hardware-specific library =7372b
#include <SPI.h>
#include <SdFat.h>
#include <TMRpcm.h> // =5246b
// #include <Interruptions.h>
// #include <Lcars.h>
#include <avr/sleep.h>

SdFat sd;
TMRpcm tmrpcm;

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define SD_ChipSelectPin 4

void wakeUpNow() {
  // empty function
}

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  sleep_enable();
  attachInterrupt(0, wakeUpNow, CHANGE);
  sleep_mode();

  delay(20);

  sleep_disable();
  // detatchInterrupt(0);
}

void setup(void) {

  Serial.begin(115200); 
  while (!Serial) {
    ; // wait for serial port to connect. Needed for Leonardo only
  }

  // // Set up SD card
  sd.begin(SD_ChipSelectPin, SPI_FULL_SPEED);

  // Set up audio
  tmrpcm.speakerPin = 9;
  // tmrpcm.speakerPin2 = 5;
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  tmrpcm.setVolume(6);
  // tmrpcm.setVolume(6, 1);
  // Fix issue with multiple tracks
  tmrpcm.play("s1.wav");
  tmrpcm.stopPlayback();
  // Loop background track
  tmrpcm.play("s1.wav");
  tmrpcm.loop(true);
  // tmrpcm.play("s1.wav", 1);
  // tmrpcm.loop(true, 1);
}

void loop() {
  // Just playing music dudes...
}
