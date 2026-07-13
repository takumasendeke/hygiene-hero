/*
Takudzwa Masendeke

This code is part of the hygiene-hero embedded systems project. 
It is used to interface the HC-SR04 ultrasonic sensors to ensure 
users apply soap and wash their hands for the reccomended time

no triggers were used because a physical clock in the form of a 
555 timer was used to save on SRAM usage
*/

// Echo pins
const int echoSoapPin = 2;
const int echoWaterPin = 3;

// setup
void setup() {
    Serial.begin(9600);

    pinMode(echoSoapPin,INPUT);
    pinMode(echoWaterPin,INPUT);

    Serial.println("Good to go ...");
} 

void loop() {
    // math
    const float SPEED_OF_SOUND_IN_AIR = 0.0343; // (cm/µs) assuming dry room at 20°C

    // Soap Sensor
    unsigned long durationSoap = pulseIn (echoSoapPin, HIGH, 120000); // timeout of 120ms 
    float soapDistance = -1; // sentinel value

    if (durationSoap != 0 ){
        soapDistance = (durationSoap * SPEED_OF_SOUND_IN_AIR) / 2; // distance is speed X time, x2 because it must go there and back
    }

    // water sensor 
    unsigned long durationWater = pulseIn (echoWaterPin, HIGH, 120000); // timeout of 120ms 
    float waterDistance = -1;

    if (durationWater != 0 ){
        waterDistance = (durationWater * SPEED_OF_SOUND_IN_AIR) /2; 
    }


    // logic

    // Soap logic, if hand is within 5cm
    if (soapDistance != -1 && soapDistance < 5){
        Serial.println("Soap has been dispensed");
    }

    // water logic, if hands are with 12cm
    if (soapDistance != -1 && waterDistance < 12){
        Serial.println("Hands are being washed");
    }

    delay(30);
}