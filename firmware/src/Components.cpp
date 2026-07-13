#include "Components.h"

// ===========================================================
//  CLASS 1: SHIFT DISPLAY (7-SEGMENT DRIVER)
// ===========================================================

ShiftDisplay::ShiftDisplay(uint8_t latch, uint8_t clock, uint8_t data) {
  _latch = latch;
  _clock = clock;
  _data = data;
}

void ShiftDisplay::begin() {
  pinMode(_latch, OUTPUT);
  pinMode(_clock, OUTPUT);
  pinMode(_data, OUTPUT);
}

void ShiftDisplay::show(int num) {
  byte tens, units;

  // Find hex code values in decimal
  if (num < 0) {
    // display blank in num is negative (0x00)
    tens = _digits[10];
    units = _digits[10];
  } else {
    // future proofing the firmware to allow timer changes up to 99
    // limit to 99 (two 7 segs) 
    if (num > 99) num = 99;
    
    // extract digits
    tens = _digits[num / 10];
    units = _digits[num % 10];
  }

  // shift them out
  // tens first pushes through to Reg B, units stays in Reg A
  digitalWrite(_latch, LOW);
  shiftOut(_data, _clock, MSBFIRST, tens);
  shiftOut(_data, _clock, MSBFIRST, units);
  digitalWrite(_latch, HIGH);
}


// ===========================================================
//  CLASS 2: AUDIO DECK (DFPLAYER DRIVER)
// ===========================================================

AudioDeck::AudioDeck(uint8_t rx, uint8_t tx) {
  // dynamically create the serial object to save memory until needed
  _serial = new SoftwareSerial(rx, tx);
}

void AudioDeck::begin() {
  _serial->begin(9600);
  
  delay(2000); // 2s delay to allow DFPlayer to boot up

  if (_player.begin(*_serial)) {
    _player.volume(20);
    delay(500);
  }
}

void AudioDeck::playTrack(int track) {
  // disable loop mode 
  _player.disableLoop();
  delay(100);
  
  // play track
  _player.play(track);
}

void AudioDeck::loopTrack(int track) {
  // start playing the track
  _player.play(track);
  
  // DELAY: Wait 600ms for the file to actually start loading
  // Clones are slow. If we send "Loop" too fast, they ignore it.
  delay(600); 
  
  // FORCE "Repeat Current" mode
  _player.enableLoop(); 
  delay(50);
  _player.enableLoop(); 
}

void AudioDeck::loopAll() {
  _player.enableLoopAll();
}


// ===========================================================
//  CLASS 3: SONAR (ULTRASONIC SENSOR)
// ===========================================================

Sonar::Sonar(uint8_t trig, uint8_t echo, float thresh) {
  _trig = trig;
  _echo = echo;
  _thresh = thresh;
}

void Sonar::begin() {
  pinMode(_trig, OUTPUT);
  pinMode(_echo, INPUT);
}

bool Sonar::isTriggered() {
  // send 10us Pulse
  digitalWrite(_trig, LOW); 
  delayMicroseconds(2);
  digitalWrite(_trig, HIGH); 
  delayMicroseconds(10);
  digitalWrite(_trig, LOW);

  // read echo (timeout 25ms to prevent blocking)
  unsigned long duration = pulseIn(_echo, HIGH, 25000UL); 
  
  // handle timeout (no object)
  if (duration == 0) return false;

  // calculate distance (speed of sound = 343m/s -> ~58us/cm)
  float distance = duration / 58.0;

  // check threshold
  return (distance < _thresh);
}