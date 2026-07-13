/*
Takudzwa Masendeke

This code is the main firmware for the Hygiene Hero Project.
It combines all the code from the prototyping to create the 
final system altogether.

HYGENIE HERO - v6.0

updates:
-added voice ques for actions
*/

#include "Components.h"
#include "Bitmaps.h"

// CONFIGURATION
const unsigned long IDLE_TRACK_MS  = 139000; // 2m 19s Song
const unsigned long SCRUB_MUSIC_MS = 25000; 
const unsigned long COME_BACK_MS   = 5000;  
const unsigned long ABANDON_TIMEOUT = 10000; 
const unsigned long SOAP_TIMEOUT    = 5000;  

// INSTANTIATE OBJECTS 
U8G2_ST7920_128X64_1_SW_SPI u8g2(U8G2_R0, 13, 11, 10, 12);
ShiftDisplay timer(5, 6, 7);   
AudioDeck voice(8, 9);         
Sonar hands(3, 4, 20.0);       

const uint8_t BTN_PIN = 2;

// VARIABLES
enum State { IDLE, WET, SOAP, SCRUB };
State currentState = IDLE;

// Animation
const uint8_t frames_per_step[] = { 8, 8, 67, 30, 30, 8 };
const int NUM_STEPS = 6;
int current_anim_step = 0;
int frame_idx = 0;
unsigned long lastTime = 0;

// Audio & Logic
unsigned long lastAudioTrigger = 0;
unsigned long currentTrackDuration = 4000;

// TIMERS
unsigned long handsLostTimer = 0;
unsigned long handsFoundTimer = 0;
unsigned long cooldownTimer = 0;
unsigned long soapPhaseStart = 0; 

bool isPaused = false;
bool hasPlayedPauseAudio = false;

// HELPER FUNCTIONS
void setTrackDuration(int trackNum) {

    switch(trackNum) {
        case 1: currentTrackDuration = IDLE_TRACK_MS; break;
        case 2: currentTrackDuration = 3000; break;
        case 3: currentTrackDuration = 3000; break;
        case 4: currentTrackDuration = SCRUB_MUSIC_MS; break;
        case 8: currentTrackDuration = COME_BACK_MS; break;
        default: currentTrackDuration = 4000; break;
    }
}

void playTrackSafe(int trackNum) {
    voice.playTrack(trackNum);
    setTrackDuration(trackNum);
    lastAudioTrigger = millis();
}

void resetToIdle() {
    // clear timer immediately
    timer.show(-1); 

    // short delay to let the last "Clean" audio finish slightly
    delay(2000);

    // reset state variables
    currentState = IDLE;
    timer.show(20);
    playTrackSafe(1); // Start Main Song
    cooldownTimer = millis(); 
    isPaused = false;
    handsLostTimer = 0;
    handsFoundTimer = 0;
    
    // force a screen update immediately so "Please Wash" appears now
    drawScreen(0, 0); 
}

// SETUP
void setup() {
  timer.begin();
  voice.begin();
  hands.begin();
  pinMode(BTN_PIN, INPUT_PULLUP);
  
  u8g2.begin();
  
  timer.show(20); 
  playTrackSafe(1); 
  cooldownTimer = millis(); 
}

// LOOP
void loop() {
  unsigned long now = millis();
  bool sensorActive = hands.isTriggered(); 

  // AUDIO WATCHDOG 
  if (!isPaused && (now - lastAudioTrigger > currentTrackDuration)) {
      if (currentState == IDLE) playTrackSafe(1); 
      else if (currentState == WET) playTrackSafe(2);
      else if (currentState == SOAP) playTrackSafe(3); 
      else if (currentState == SCRUB && current_anim_step == 2) playTrackSafe(4); 
  }

  // STATE MACHINE
  switch (currentState) {
    case IDLE:
      drawScreen(0, 0); 
      
      // cooldown check
      if (now - cooldownTimer < 2000) { 
          break; 
      }

      // easy trigger
      if (sensorActive) {
          currentState = WET;
          current_anim_step = 0; frame_idx = 0;
          playTrackSafe(2); 
      }
      break;

    case WET:
      runAnimation();
      if (frame_idx >= frames_per_step[0]) {
        currentState = SOAP;
        current_anim_step = 1; frame_idx = 0;
        playTrackSafe(3); 
        soapPhaseStart = now; 
      }
      break;

    case SOAP:
      runAnimation();
      if (frame_idx >= frames_per_step[1]) frame_idx = 0; 
      
      // soap timeout (5s)
      if (now - soapPhaseStart > SOAP_TIMEOUT) {
          resetToIdle();
          return;
      }

      // button wait (1.5s)
      if (now - soapPhaseStart > 1500) {
          if (digitalRead(BTN_PIN) == LOW) {
            currentState = SCRUB;
            current_anim_step = 2; frame_idx = 0;
            isPaused = false;
            handsLostTimer = 0;
            playTrackSafe(4); 
          }
      }
      break;

    case SCRUB:
      if (current_anim_step == 2) { 
          if (!sensorActive) {
              handsFoundTimer = 0;
              if (handsLostTimer == 0) handsLostTimer = now;
              
              // abandon timeout (10s)
              if (now - handsLostTimer > ABANDON_TIMEOUT) {
                  resetToIdle(); 
                  return;
              }

              // pause logic (1.5s)
              if (now - handsLostTimer > 1500) { 
                  isPaused = true;
                  if (!hasPlayedPauseAudio) {
                      playTrackSafe(8); 
                      hasPlayedPauseAudio = true;
                  }
                  drawScreen(0, 0); 
                  return; 
              }
          } else {
              handsLostTimer = 0;
              if (isPaused) {
                  if (handsFoundTimer == 0) handsFoundTimer = now;
                  if (now - handsFoundTimer > 500) { 
                      isPaused = false;
                      hasPlayedPauseAudio = false;
                      playTrackSafe(4); 
                  } else {
                      drawScreen(0, 0);
                      return; 
                  }
              }
          }
      }
      
      runAnimation();
      
      if (current_anim_step == 2) {
         int total = frames_per_step[2];
         int timeLeft = ((total - frame_idx) * 300) / 1000;
         if (timeLeft < 0) timeLeft = 0;
         timer.show(timeLeft); 
      } else {
         timer.show(-1);
      }

      if (frame_idx >= frames_per_step[current_anim_step]) {
        frame_idx = 0;
        current_anim_step++;
        
        if (current_anim_step == 3) playTrackSafe(5); 
        else if (current_anim_step == 4) playTrackSafe(6); 
        else if (current_anim_step == 5) playTrackSafe(7); 
        
        if (current_anim_step >= NUM_STEPS) {
          resetToIdle(); // trigger idle screen
        }
      }
      break;
  }
}

void runAnimation() {
  if (millis() - lastTime > 300) {
    lastTime = millis();
    u8g2.firstPage();
    do {
      if (current_anim_step < NUM_STEPS) {
          u8g2.drawXBMP(0, 0, 128, 64, bitmapSteps[current_anim_step][frame_idx % 2]);
      }
    } while (u8g2.nextPage());
    frame_idx++;
  }
}

void drawScreen(int step, int frame) {
  u8g2.firstPage();
  do {
    u8g2.setFont(u8g2_font_ncenB10_tr);
    u8g2.setDrawColor(1);
    u8g2.setFontPosTop();

    if (currentState == IDLE) {
        u8g2.drawStr(10, 0, "Please Wash");
        u8g2.drawStr(15, 16, "Your Hands");
        u8g2.setFont(u8g2_font_6x10_tf);
        u8g2.drawStr(0, 38, "80% of diseases");
        u8g2.drawStr(0, 50, "spread by touch");
    } 
    else if (currentState == SCRUB && isPaused) {
        u8g2.drawStr(10, 20, "Come Back!");
        u8g2.drawStr(5, 40, "Finish Scrub");
    }
  } while (u8g2.nextPage());
}