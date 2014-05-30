
/*
This sketch demonstrates playing 2 audio tracks simultaneously using a single timer.

Steps:
1. Edit pcmConfig.h
    a: Uncomment #define buffSize 128
    b: Uncomment #define ENABLE_MULTI

2. Usage is as below. See https://github.com/TMRh20/TMRpcm/wiki/Advanced-Features#wiki-multi-mode for
   additional informaiton.

*/

#include <SD.h>
#include <SPI.h>
#include <TMRpcm.h>

//#define SD_ChipSelectPin 53  //example uses hardware SS pin 53 on Mega2560
#define SD_ChipSelectPin 4  //using digital pin 4 on arduino nano 328, can use other pins

TMRpcm audio;   // create an object for use in this sketch 

void setup() {
  
  audio.speakerPin = 9; //5,6,11 or 46 on Mega, 9 on Uno, Nano, etc
  pinMode(10,OUTPUT);  //Pin pairs: 9,10 Mega: 5-2,6-7,11-12,46-45
  
  Serial.begin(9600);
  
  if (!SD.begin(SD_ChipSelectPin)) {  
    return;
  }else{
    // Serial.println("SD OK");
  }

  audio.setVolume(6);
  audio.play("tr1.wav", 0);
  delay(100);
  audio.stopPlayback();
  audio.play("tr1.wav", 0);
  audio.loop(0);
  audio.loop(1);

  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(A4, OUTPUT);
  pinMode(A2, OUTPUT);
  pinMode(A1, OUTPUT);
  pinMode(A0, OUTPUT);
  pinMode(A5, OUTPUT);
  pinMode(A6, OUTPUT);
  pinMode(A3, OUTPUT);
  pinMode(A7, OUTPUT);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(13, HIGH);
  digitalWrite(5, HIGH);
  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(A4, HIGH);
  digitalWrite(A2, HIGH);
  digitalWrite(A1, HIGH);
  digitalWrite(A0, HIGH);
  digitalWrite(A5, HIGH);
  digitalWrite(A6, HIGH);
  digitalWrite(A3, HIGH);
  digitalWrite(A7, HIGH);

  // digitalWrite(11, LOW);
  // digitalWrite(12, LOW);
  // digitalWrite(13, LOW);
  // digitalWrite(A4, LOW);
  // digitalWrite(A5, LOW);
  // digitalWrite(A6, LOW);

}

uint32_t i = 0;


void loop() {

    uint8_t mod = i % 6;

  

    // switch (mod) {
    //   case 0:
    //     digitalWrite(11, HIGH); break;
    //   case 1:
    //     digitalWrite(12, HIGH); break;
    //   case 2:
    //     digitalWrite(13, HIGH); break;
    //   case 3:
    //     digitalWrite(A4, HIGH); break;
    //   case 4:
    //     digitalWrite(A5, HIGH); break;
    //   case 5:
    //     digitalWrite(A6, HIGH); break;
    // }

    i = i + 1;

    Serial.println(mod);
  
    // if(Serial.available()){                          //Send commands over serial to play
    //   switch(Serial.read()){
    //     case '2': audio.play("tr1.wav",0); break;    //Play tr1.wav on pin 11 (9 on Uno)
    //     case '3': audio.play("tr1.wav",1); break;    //Play tr1.wav on pin 12 (10 on Uno)
    //     case '4': audio.play("tr2.wav",0); break;    //Play tr2.wav on pin 11
    //     case '5': audio.play("tr2.wav",1); break;    //Play tr2.wav on pin 12
    //     case '6': audio.play("tr1.wav",15,0); break; //Play tr1.wav starting at 15 seconds on pin 11
    //     case '7': audio.play("tr1.wav",30,1); break; //Play tr1.wav starting at 30 seconds, pin 12
    //     case '=': audio.volume(1); break;            //Increase volume by 1
    //     case '-': audio.volume(0); break;            //Decrease volume by 1
    //     case 's': audio.stopPlayback(0); break;      //Stop playback on pin 11
    //     case 'S': audio.stopPlayback(1); break;      //Stop playback on pin 12
    //     case 'x': audio.stopPlayback(); break;       //Stop all playback
        
    //   }
    // }
}