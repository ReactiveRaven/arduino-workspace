/***************************************************
  This is an example sketch for the Adafruit 2.2" SPI display.
  This library works with the Adafruit 2.2" TFT Breakout w/SD card
  ----> http://www.adafruit.com/products/1480
 
  Check out the links above for our tutorials and wiring diagrams
  These displays use SPI to communicate, 4 or 5 pins are required to
  interface (RST is optional)
  Adafruit invests time and resources providing this open source code,
  please support Adafruit and open-source hardware by purchasing
  products from Adafruit!

  Written by Limor Fried/Ladyada for Adafruit Industries.
  MIT license, all text above must be included in any redistribution
 ****************************************************/
 
#include "SPI.h"
#include "Adafruit_GFX.h"
#include "Adafruit_ILI9340.h"

#if defined(__SAM3X8E__)
    #undef __FlashStringHelper::F(string_literal)
    #define F(string_literal) string_literal
#endif

// These are the pins used for the UNO
// for Due/Mega/Leonardo use the hardware SPI pins (which are different)
#define _sclk 13
#define _miso 12
#define _mosi 11
#define _cs 10
#define _dc 9
#define _rst 8

// Using software SPI is really not suggested, its incredibly slow
//Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _mosi, _sclk, _rst, _miso);
// Use hardware SPI
Adafruit_ILI9340 tft = Adafruit_ILI9340(_cs, _dc, _rst);

int orange = tft.Color565(255,100,0);
int yellow = tft.Color565(255,153,0);

void lcarsBorderBits(int width, int height) {
  digitalWrite(3, LOW);
  tft.fillRect(30, 0, width-60, 5, orange);
  tft.fillRect(30, height-5, width-60, 5, orange);
  tft.fillRect(0, 30, 30, height-60, orange);
  tft.fillRect(width-30, 30, 30, height-60, orange);
  
  tft.fillRoundRect(0, 0, 70, 60, 30, orange);
  tft.fillRoundRect(30, 5, 60, 90, 30, ILI9340_BLACK);
  
  tft.fillRoundRect(width-70, 0, 70, 60, 30, orange);
  tft.fillRoundRect(width-90, 5, 60, 90, 30, ILI9340_BLACK);
  
  tft.fillRoundRect(0, height-60, 70, 60, 30, orange);
  tft.fillRoundRect(30, height-95, 60, 90, 30, ILI9340_BLACK);
  
  tft.fillRoundRect(width-70, height-60, 70, 60, 30, orange);
  tft.fillRoundRect(width-90, height-95, 60, 90, 30, ILI9340_BLACK);
  
  
  tft.fillRect(70, 0, 20, 5, ILI9340_BLACK);
  tft.fillRect(70, height-5, 20, 5, ILI9340_BLACK);

  tft.fillRect(0, 90, 30, 30, ILI9340_BLACK);
  tft.fillRect(width-30, height-90, 30, 30, ILI9340_BLACK);
  digitalWrite(3, HIGH);
}

void lcarsBorderBlob(int width, int height) {
  tft.fillRoundRect(0, 0, width, height, 30, orange);
  tft.fillRoundRect(30, 5, width-60, height-10, 30, ILI9340_BLACK);
  tft.fillRoundRect(30, 5, width-60, height-10, 30, ILI9340_BLACK);
}

void lcarsBorderCutouts(int width, int height) {
}

void setup() {
  
  pinMode(3, OUTPUT);
  pinMode(2, OUTPUT);
  
  int note = 1850;
  int pause = 150;
  int ps = 25;
  int ps_ = 15;
  int bips = 4;
  
  while (true) {
    delay(1000);
  }
  
  while (true) {
    tone(2, note);
    delay(pause);
    noTone(2);
    for (int i = 0; i < bips; i++) {
      tone(2, note);
      delay(ps);
      noTone(2);
      delay(ps_);
    }
    delay(pause * 1.5);
  }
  
  tone(2, 2000);
  delay(200);
  int pulse=25;
  int weight=60;
  int loops=2000/(pulse*2);
  for (int i = 0; i < loops; i++) {
    tone(2, 1170);
    delay((pulse*100)/weight);
    noTone(2);
    delay((pulse*100)/(100-weight));
  }
  
  digitalWrite(3, HIGH);
  
//  digitalWrite(3, LOW);
  tft.begin();
  tft.setRotation(3);
  tft.fillScreen(ILI9340_BLACK);
//  digitalWrite(3, HIGH);
  tft.setCursor(0, 0);
//  tft.setTextColor(ILI9340_WHITE);  tft.setTextSize(1);
//  tft.println("Hello World!");
  int width = tft.width();
  int height = tft.height();
  
//  tft.Color565(255, 153, 0)
  int orange = tft.Color565(255,100,0);
  
  // bigbox: 25500~
  // corners: ???

  int start = micros();
  
  lcarsBorderBits(width, height);
//  lcarsBorderBlob(width, height);
    
//    delay(1000);
//  tft.fillRoundRect(0, 0, width, height, 30, orange);

  
  int fin = micros() - start;
  lcarsBorderCutouts(width, height);
  tft.setCursor(60, 35);
  tft.println("Hello world");
  tft.println(fin);
//  tft.setTextColor(ILI9340_RED);  tft.setTextSize(5);
//  tft.println("Hello World!");

}

void loop(void) {
  delay(1000);
}
