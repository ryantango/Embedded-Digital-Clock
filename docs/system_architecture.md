# System Architecture

## Overview

The completed project is centered around an **ATmega4809 microcontroller**, which coordinates the clock, display, user controls, analog measurements, alarm, and USB-C power-monitoring functions.

The system combines digital timing, analog sensing, user-interface hardware, and power-control circuitry into one embedded platform.

```mermaid
flowchart TD

    Crystal[32.768 kHz Crystal]
    Buttons[UP / DOWN / OK Buttons]
    USB[USB-C Device]
    CurrentSense[Current-Sense + Op-Amp Circuit]
    VoltageDivider[Supply Voltage Divider]
    CC[CC1 / CC2 Lines]

    MCU[ATmega4809 Microcontroller]

    RTC[Real-Time Counter]
    ADC[10-bit ADC]
    Display[4-Digit 7-Segment Display]
    LEDs[Seconds / Status LEDs]
    Buzzer[Alarm Buzzer]
    USBControl[USB Power Control]

    Crystal --> RTC
    RTC --> MCU

    Buttons --> MCU

    USB --> CC
    CC --> ADC

    CurrentSense --> ADC
    VoltageDivider --> ADC
    ADC --> MCU

    MCU --> Display
    MCU --> LEDs
    MCU --> Buzzer
    MCU --> USBControl
    USBControl --> USB
