/*
Takudzwa Masendeke

This code is part of the hygiene-hero embedded systems project. 
It is used to count down 20 LEDs of varying colour to indicate the 
amount of time left to the user. 

In the final code this idea was rejected over the 7 segment for it
readability, power consumption and cost. 

This code makes use of 3 daisy cahined CD4015 shift registers to drive transistors 
that act as switches for the LEDs
*/

const int RESET_PIN = 5; 
const int CLOCK_PIN = 6;
const int DATA_PIN  = 7;

const int TOTAL_LEDS = 20; 

void setup() {
  pinMode(RESET_PIN, OUTPUT);
  pinMode(CLOCK_PIN, OUTPUT);
  pinMode(DATA_PIN,  OUTPUT);

  resetChain();
}

void loop() {

  resetChain(); // turn of all LEDs

  digitalWrite(DATA_PIN, HIGH); // set to ON state
  
  for(int i = 0; i < TOTAL_LEDS; i++) {
    pulseClock();
    delay(1000); // wait 1 second per LED (Total 20 seconds)
  }
}

void pulseClock() {
  digitalWrite(CLOCK_PIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(CLOCK_PIN, LOW);
}

void resetChain() {
  digitalWrite(RESET_PIN, HIGH);
  delay(10);
  digitalWrite(RESET_PIN, LOW);
}