# Hardware Design - Hygiene Hero 

Welcome to the hardware documentation for **Hygiene Hero**. This directory contains all Electronic Design Automation (EDA) files, chronicling the journey from initial proof-of-concept schematics to the final integrated Printed Circuit Board (PCB) ready for mass manufacturing.

## Hardware Architecture Overview
The Hygiene Hero hardware bridges standard microcontroller logic with custom analog and digital sub-systems. To optimize the Arduino Uno R3's (ATmega328P) processing load and pin count, the hardware specifically offloads tasks:
* **Hardware Triggering:** A 555 timer in astable mode continuously generates trigger pulses for the ultrasonic proximity sensors.
* **Serial-to-Parallel Conversion:** Daisy-chained 74HC595 shift registers drive the 2-digit 7-segment display using only 3 MCU pins.
* **Voltage Level Shifting:** A dedicated resistor network safely steps down the 5V TX logic to interface with the 3.3V RX line of the DFPlayer Mini.

## Directory Structure

| Directory | Description |
| :--- | :--- |
| `/main_board` | Contains the master KiCad project (`.pro`, `.sch`, `.kicad_pcb`). This is the final integrated custom PCB layout combining the MCU, audio, display, and sensor logic into a single, cohesive board. |
| `/subcircuits` | Holds the isolated schematics used during the breadboarding and prototyping phase (e.g., `Audio.kicad_sch`, `7 Seg Circuit.kicad_sch`, `Soap_water.kicad_sch`). These document the step-by-step engineering and debugging process. |
| `/production` | Contains the fabrication outputs required by PCB manufacturers. Includes Gerber files, NC Drill files, the Bill of Materials (BOM), and Component Placement Lists (CPL) for automated assembly. |

## Tools Used
* **EDA Software:** Designed and routed using [KiCad 10.0](https://www.kicad.org/).
* **Mechanical CAD:** The accompanying housing (found in the root `/enclosure` folder) was designed using Onshape.

## Viewing the Files
To open and edit the raw schematic and PCB files, you will need to install KiCad. Alternatively, PDF versions of the core schematics are provided within their respective folders for quick viewing without the EDA software.