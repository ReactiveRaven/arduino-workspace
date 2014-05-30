#include <Adafruit_GFX.h>    // Core graphics library
#include "Adafruit_ILI9340.h" // Hardware-specific library =7372b
#include <SPI.h>
// #include <SdFat.h>
// #include <TMRpcm.h> // =5246b
#include <Interruptions.h>
#include <Lcars.h>
#include <avr/sleep.h>

// SdFat sd;
// TMRpcm tmrpcm;

Interruptions interruptions = Interruptions();

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

#define TFT_RST 8
#define TFT_DC 11
#define TFT_CS 12
#define SD_CS 4
#define TFT_BL 3
#define SD_ChipSelectPin 4

Adafruit_ILI9340 tft = Adafruit_ILI9340(TFT_CS, TFT_DC, TFT_RST);
Lcars _lcars = Lcars(&tft);

long previousMillis = 0;        // will store last time LED was updated

// the follow variables is a long because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long interval = 10;           // interval at which to blink (milliseconds)

void wakeUpNow() {
  // empty function
}

void sleepNow() {
  set_sleep_mode(SLEEP_MODE_PWR_DOWN);

  tft.writecommand(ILI9340_DISPOFF);    //Display on 
  tft.writecommand(ILI9340_SLPIN);    //Exit Sleep 
  digitalWrite(TFT_BL, LOW);


  sleep_enable();
  attachInterrupt(0, wakeUpNow, CHANGE);
  sleep_mode();

  tft.writecommand(ILI9340_SLPOUT);    //Exit Sleep
  delay(20);    
  tft.writecommand(ILI9340_DISPON);    //Display on 
  digitalWrite(TFT_BL, HIGH);

  sleep_disable();
  // detatchInterrupt(0);
}

void setup(void) {
  pinMode(2, INPUT);

  //   Serial.begin(115200); 
  // while (!Serial) {
  //   ; // wait for serial port to connect. Needed for Leonardo only
  // }

  // // Set up SD card
  // sd.begin(SD_ChipSelectPin, SPI_FULL_SPEED);

  // // Set up audio
  // tmrpcm.speakerPin = 9;
  // tmrpcm.speakerPin2 = 5;
  // pinMode(9, OUTPUT);
  // pinMode(10, OUTPUT);
  // tmrpcm.setVolume(6);
  // tmrpcm.setVolume(6, 1);
  // // Fix issue with multiple tracks
  // tmrpcm.play("1.wav");
  // tmrpcm.stopPlayback();
  // // Loop background track
  // tmrpcm.loop(true);

  // Set up screen
  pinMode(TFT_BL, OUTPUT);
  digitalWrite(TFT_BL, LOW);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(Lcars_Color_Black);
  digitalWrite(TFT_BL, HIGH);
  // Lcars lcars = Lcars(&tft);
  _lcars.begin();
  sleepNow();
}

void loop() {
  unsigned long currentMillis = millis();
  unsigned long diff = currentMillis - previousMillis;
 
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;
    // Serial.println("Tick");
    _lcars.tick(currentMillis);
  } else {
    // Serial.println("No tick");
  }
}
