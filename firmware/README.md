# Firmware - Hygiene Hero 

Welcome to the firmware documentation for **Hygiene Hero**. This directory houses the embedded C/C++ code that powers the system's state machine, audio handling, visual rendering, and sensor polling. 

## Software Architecture
The firmware for Hygiene Hero is built with a focus on memory optimization and modularity to operate efficiently on the 2KB SRAM constraint of the ATmega328P. 
* **Memory Management:** High-resolution display frames are converted to XBM format and stored entirely in Flash memory (`PROGMEM`) to prevent SRAM overflow.
* **Non-Blocking Logic:** The final system utilizes time-delta polling (`millis()`) rather than blocking `delay()` calls, allowing the MCU to multitask audio playback, display updates, and sensor reading simultaneously.
* **Object-Oriented Design:** The core logic is encapsulated into distinct C++ classes (`ShiftDisplay`, `AudioDeck`, `Sonar`) to ensure clean hardware abstraction and prevent variable scope conflicts.

## Directory Structure

| Directory | Description |
| :--- | :--- |
| `/prototypes` | Contains isolated "board bring-up" tests (e.g., `ultrasonic_test.ino`, `audio_Test.ino`). These standalone scripts were used to validate individual hardware subsystems and debug communication protocols prior to full system integration. |
| `/src` | Contains the final integrated C++ implementation files (`.cpp`), including the master state machine orchestrator (`main.cpp`). |
| `/include` | Contains the architectural blueprint headers (`.h`) for the OOP classes, defining the public interfaces and private hardware bindings. |

## Core Dependencies
To compile this firmware, ensure the following libraries are installed in your Arduino IDE or PlatformIO environment:
* **[U8g2](https://github.com/olikraus/u8g2):** For driving the ST7920 128x64 graphical display.
* **[DFRobotDFPlayerMini](https://github.com/DFRobot/DFRobotDFPlayerMini):** For UART control of the MP3 audio module.
* **SoftwareSerial:** Standard Arduino library used for virtual serial communication with the audio module.

## Compilation & Flashing
The final integrated code within `/src` is designed to be compiled using standard GCC toolchains or PlatformIO. If using the standard Arduino IDE, ensure the `.cpp` and `.h` files are located in a sketch folder named to match the primary `.ino` or `.cpp` file.