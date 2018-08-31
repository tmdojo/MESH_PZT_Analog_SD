/*
 Hardware required :
 * Arduino shield with a SD card on CS4
 * A sound file named "test.wav" in the root directory of the SD card
*/

#include <Wire.h> //Include arduino Wire Library to enable to I2C
#include "Yurikleb_DRV2667.h"
#include <SD.h>
#include <SPI.h>
#include <AudioZero.h>

int switch_AS;

Yurikleb_DRV2667 drv;

void setup()
{
  switch_AS=0;
  
  // debug output at 115200 baud
  Serial.begin(115200);
  
  // setup SD-card
  Serial.print("Initializing SD card...");
  if (SD.begin(4)) {
    Serial.println("read SDcard.");
    
    // 44100kHz stereo => 88200 sample rate
    AudioZero.begin(44100*2);

    // setup SD-card for loop
    switch_AS=1;
  }

  drv.begin();  
  drv.setToAnalogInput();  //Swithch To Analog

}

void loop(){

  if (switch_AS==1) {
    File myFile = SD.open("test.wav");
    Serial.print("Play test.wav");
    AudioZero.play(myFile);
  }

}
