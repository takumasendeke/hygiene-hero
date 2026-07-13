/*
Takudzwa Masendeke

This code is part of the hygiene-hero embedded systems project. 
It is used to play a cool retro beat in the bathroom as the user 
washes thier hands to make the process more enticing

I used the DFPlayer mini (DFR0299 DFPlayer) to play the audio to play 
1 song indefinetly at max volume.
*/

#include "SoftwareSerial.h"
#include "DFRobotDFPlayerMini.h"

SoftwareSerial mySoftwareSerial(8, 9); // Rx pin 8 and Tx pin
DFRobotDFPlayerMini myDFPlayer; 

void setup() {
  mySoftwareSerial.begin(9600); // simulate serial port on standard pins to prevent collion with USB
  Serial.begin(9600);
  
  Serial.println(F("Turning ON"));
  Serial.println(F("Waiting 3 seconds for Capacitor to charge..."));
  
  delay(3000); // allowing capacitors to charge up 

  Serial.println(F("Connecting to DFPlayer..."));
  
  if (myDFPlayer.begin(mySoftwareSerial)) {
    Serial.println(F("DFPlayer Online!"));

    myDFPlayer.volume(30); // set max volume
    delay(500); // give volume tie to adjust

    Serial.println(F("Playing Track 1..."));
    myDFPlayer.play(1); // play first track
    
    //myDFPlayer.loop(1); // loop track
    
  } else {
    Serial.println(F("Error: DFPlayer not responding. Check wiring."));
    // something went wrong
  }
}

void loop() {
  // blink LED to ensure Arduino is functional
  digitalWrite(13, HIGH);
  delay(500);
  digitalWrite(13, LOW);
  delay(500);
}