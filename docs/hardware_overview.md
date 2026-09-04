# Hardware Overview

## Microcontroller

The system is built around an **ATmega4809 8-bit AVR microcontroller**. It manages the digital display, button inputs, ADC measurements, alarm buzzer, USB-C monitoring, and real-time clock functions.

A **32.768 kHz external crystal** provides the timing reference used by the microcontroller's real-time counter for accurate clock operation.

## Display and User Interface

The clock uses a **four-digit seven-segment LED display** for time and numerical measurements.

Additional user-interface hardware includes:

- Six individual LEDs for seconds indication
- USB status LED
- Alarm status LED
- Three tactile push buttons: **UP, DOWN, and OK**
- Piezoelectric buzzer for alarm output

## Analog Measurement Circuitry

The system uses the ATmega4809's ADC to monitor several analog signals:

- USB current
- Supply voltage
- USB-C CC1 voltage
- USB-C CC2 voltage

USB current is measured using a **current-sense resistor and an operational amplifier circuit**, which converts current into a measurable voltage for the ADC.

A resistor divider reduces the supply voltage to a level that can be safely measured by the microcontroller ADC.

## USB-C Interface

The USB-C interface uses the **CC1 and CC2 configuration channels** to detect when a device is connected.

The firmware monitors these voltages and enables the USB power path when a device is detected. Voltage and current measurements are then used to calculate the charging power and the energy delivered.

## Power Conditioning

The PCB includes several components used to stabilize and protect the system power supply, including:

- Bypass capacitors
- Bulk capacitors
- Ferrite bead filtering
- A 470 mF supercapacitor for short-duration power interruptions

These components help reduce supply noise and allow the clock to maintain timing during brief interruptions.

## PCB Assembly

The project was constructed on a custom PCB using both **through-hole and surface-mount components**.

My hands-on work included:

- Component placement
- Through-hole soldering
- Surface-mount LED soldering
- Continuity testing
- Hardware inspection
- Circuit troubleshooting
- Final enclosure assembly
