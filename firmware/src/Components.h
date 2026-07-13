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
    const byte _digits[11] = { 0x7E, 0x0C, 0xB6, 0x9E, 0xCC, 0xDA, 0xFA, 0x0E, 0xFE, 0xDE, 0x00 };
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