# Embedded-Digital-Clock
ATmega4809-based embedded digital clock project featuring PCB assembly, real-time timing, seven-segment display control, ADC measurement, and USB-C power monitoring.
# ATmega4809 Digital Clock & USB-C Power Monitor

Embedded systems project completed for ESE 123 at Stony Brook University.

The project involved assembling, programming, testing, and debugging an
ATmega4809-based digital clock built on a custom PCB. The completed system
used a four-digit seven-segment display, real-time clock functionality,
tactile controls, an alarm buzzer, LED indicators, ADC-based analog
measurement, and USB-C charging circuitry.

## Project Overview

Throughout the semester, I developed experience with both hardware and
firmware development by progressively assembling and testing the digital
clock system.

My work included:

- Programming the ATmega4809 using Embedded C in MPLAB X
- Working with GPIO, ADCs, timing, and microcontroller peripherals
- Assembling and soldering through-hole and surface-mount components
- Testing circuits using a DMM, oscilloscope, and function generator
- Simulating circuits using LTspice
- Measuring USB voltage and current using the microcontroller ADC
- Detecting USB-C device connections through the CC1 and CC2 lines
- Calculating charging power and total delivered energy
- Debugging hardware and firmware throughout system integration

## My Firmware Contribution

The source code included in this repository represents my Lab 12 firmware
work for USB-C detection and power monitoring.

The firmware:

1. Samples USB-C CC1 and CC2 voltages using the ADC
2. Detects when a USB-C device is connected
3. Measures supply voltage and USB current
4. Applies hardware calibration factors
5. Calculates real-time charging power

   Power = Voltage × Current

6. Accumulates energy delivered during the charging session
7. Displays measured values using the project's seven-segment display
8. Detects device removal and disables the USB output

## Hardware

- ATmega4809 8-bit AVR microcontroller
- Four-digit seven-segment LED display
- Custom printed circuit board
- USB-C interface
- Current-sensing circuitry
- Operational amplifier circuitry
- Tactile push buttons
- Alarm buzzer
- Indicator LEDs
- Resistors and capacitors
- Power-supply filtering circuitry

## Software & Tools

- Embedded C
- MPLAB X IDE
- XC8 Compiler
- LTspice
- Digital Multimeter
- Oscilloscope
- Function Generator
- Soldering and PCB Assembly

## System Architecture

```mermaid
flowchart LR
    USB[USB-C Device] --> CC[CC1 / CC2 Detection]
    CC --> ADC[ATmega4809 ADC]

    Current[Current Sense Circuit] --> ADC
    Supply[Supply Voltage] --> ADC

    ADC --> MCU[ATmega4809]

    MCU --> Power[Power Calculation]
    Power --> Energy[Energy Accumulation]

    MCU --> Display[7-Segment Display]
    MCU --> USBCTRL[USB Power Control]
