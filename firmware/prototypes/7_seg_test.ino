/*
Takudzwa Masendeke

This code is part of the hygiene-hero embedded systems project. 
It is used to give the timer countdown for the recommended 20s 

It makes use of 2 74HC595 shift registers daisy chained together to 
*/

// Pin Definitions
const int DATA_PIN = 2;   
const int LATCH_PIN = 3;  
const int CLOCK_PIN = 4; 

byte digitMap[] = {
    0b00111111, // 0
    0b00000110, // 1
    0b01011011, // 2
    0b01001111, // 3
    0b01100110, // 4
    0b01101101, // 5
    0b01111101, // 6
    0b00000111, // 7
    0b01111111, // 8
    0b01101111  // 9
};

void setup() {
    pinMode(DATA_PIN, OUTPUT);
    pinMode(LATCH_PIN, OUTPUT);
    pinMode(CLOCK_PIN, OUTPUT);
}

void loop() {
  // Countdown from 20 to 0
    for (int i = 20; i >= 0; i--) {
        displayNumber(i);
        delay(1000); // wait 1 second
    }
    
    // flash at 00 to indicate done
    while(true) {
        displayNumber(0);
        delay(500);
        clearDisplay();
        delay(500);
    }
}

void displayNumber(int num) {
    int tens = num / 10; // split number into 2 numbers
    int ones = num % 10;

    digitalWrite(LATCH_PIN, LOW); // prepare to send data (prevent flickering)
    
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitMap[ones]); // Goes to Reg B
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, digitMap[tens]); // Goes to Reg A

    digitalWrite(LATCH_PIN, HIGH); // Latch data to outputs
}

void clearDisplay() {
    digitalWrite(LATCH_PIN, LOW);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0b00000000);
    shiftOut(DATA_PIN, CLOCK_PIN, MSBFIRST, 0b00000000);
    digitalWrite(LATCH_PIN, HIGH);
}