# PIO-Based 10x Trigger Generator for Data Subsampling

## Overview
This repository contains a PIO (Programmable Input/Output) module for the Raspberry Pi Pico that generates a 10× frequency clock from an external trigger. This is useful for oversampling and averaging, where a 20 kHz input trigger is converted to a 200 kHz output signal for a DAQ system.

## Features

Uses PIO state machines for precise timing
Outputs a PWM signal for DAQ synchronization


## Hardware Requirements
Raspberry Pi Pico (rp2040,Raspberry Pi Foundation)
External 20 kHz trigger source

## Connections
| **Signal**     | **Source**           | **Destination**       |
|----------------|----------------------|-----------------------|
| 20 kHz Trigger  | External Source     | Pico (GP15)           |
| 200 kHz Output  | Pico (GP16)         | DAQ                   |

## Installation & Usage
1. **Download the pre-built UF2 file** and paste it into your Raspberry Pi Pico's storage.
   - Simply connect the Pico to your computer in bootloader mode (hold the **BOOTSEL** button while connecting via USB), and then drag and drop the UF2 file.

2. **Build from source** using Visual Studio Code with the Raspberry Pi Pico extension.
   - Please refer to the official manual for the setup and configuration.
   - Note: This test has been verified to work with **Raspberry Pi Pico (RP2040)** and **SDK 2.0.0**. Future versions of the SDK may not be guaranteed to work.
