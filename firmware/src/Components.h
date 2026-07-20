#ifndef COMPONENTS_H
#define COMPONENTS_H

#include <Arduino.h>
#include <U8g2lib.h>
#include <SoftwareSerial.h>
#include <DFRobotDFPlayerMini.h>

// 7 Segment display
class ShiftDisplay {
  private:
    uint8_t _latch, _clock, _data;
    
    // UPDATED: Hex values recalculated for [A, G, F, E, D, C, B, DP] wiring
    const byte _digits[11] = { 0xBE, 0x06, 0xDA, 0xCE, 0x66, 0xEC, 0xFC, 0x86, 0xFE, 0xEE, 0x00 };
    
  public:
    ShiftDisplay(uint8_t latch, uint8_t clock, uint8_t data);
    void begin();
    void show(int num);
};

// Audio Sensor
class AudioDeck {
  private:
    SoftwareSerial* _serial;
    DFRobotDFPlayerMini _player;
  public:
    AudioDeck(uint8_t rx, uint8_t tx);
    void begin();
    void playTrack(int track);
    void loopTrack(int track); // <--- ADD THIS LINE
    void loopAll();
};

// Ultrasonic sensor
class Sonar {
  private:
    uint8_t _trig, _echo;
    float _thresh;
  public:
    Sonar(uint8_t trig, uint8_t echo, float thresh);
    void begin();
    bool isTriggered();
};

#endif