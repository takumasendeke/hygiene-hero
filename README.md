# Hygiene Hero 🫧
> "Making Clean Hands the Norm, Not the Exception"

Welcome to the official repository for **Hygiene Hero**, an interactive, behavior-driven embedded system designed to guide users through a proper 20-second handwashing routine recommended by WHO.

## Overview
Hand hygiene is a critical aspect of public health, yet global compliance rates remain incredibly low, with the average wash time sitting at just 6 seconds. Built as an open-source Electrical and Computer Engineering project at the University of Cape Town, Hygiene Hero tackles this behavioral shortfall. It utilizes multi-sensory feedback—including a visual countdown, animated graphics, and audio cues—to encourage longer, proper handwashing and make the process engaging.

## Key Features
* **Touchless Activation:** Uses HC-SR04 ultrasonic sensors to monitor hand presence. 
* **Dynamic Visuals:** An ST7920 128x64 LCD plays custom, memory-optimized XBM animations directly from PROGMEM to save SRAM.
* **Clear Countdown:** A dual 7-segment display (driven by 74HC595 shift registers) provides an intuitive 20-second progress tracker.
* **Audio Nudges:** A DFPlayer Mini module plays background melodies and AI-generated vocal prompts over a UART interface.
* **Custom Enclosure:** A modular, 3D-printed housing designed in Onshape to protect the circuitry in a bathroom environment.

## Hardware Stack

| Component | Purpose |
| :--- | :--- |
| **Arduino Uno R3** | Master microcontroller orchestrating the state machine. |
| **ST7920 LCD (128x64)** | Renders handwashing animations and health facts via the U8g2 library. |
| **5161AS 7-Segment** | 2-digit display for the 20-second countdown. |
| **74HC595 Shift Registers** | Serial-to-parallel converters to drive the 7-segment display using minimal MCU pins. |
| **DFPlayer Mini + 8Ω Speaker** | Handles MP3 playback for background music and vocal cues. |
| **NE555D Timer** | Astable oscillator offloading the ultrasonic trigger pulse from the MCU. |
| **HC-SR04 / Tactile Button** | Inputs for proximity and soap detection. |

## Repository Structure

| Directory | Description |
| :--- | :--- |
| `/firmware` | Contains isolated subsystem prototypes and the final modular C++ source code (`src/` and `include/`). |
| `/hardware` | KiCad schematics, subcircuit experiments, and the final integrated PCB design. |
| `/enclosure` | CAD exports (STLs, STEPs) for the custom Bambu Lab 3D-printed housing. |
| `/docs` | Component datasheets, wiring diagrams, and project presentations. |

## Getting Started
1. Navigate to the `/firmware/prototypes` directory to view the isolated component tests for the display, audio, and sensors.
2. The final Object-Oriented system logic can be found in `/firmware/src/main.cpp`.
3. Ensure you have the `U8g2` and `DFRobotDFPlayerMini` libraries installed in your Arduino IDE or PlatformIO environment before compiling.

---
*Developed by Takudzwa Masendeke.*