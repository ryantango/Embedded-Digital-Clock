 #define F_CPU 20000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "functions.h"

// Hardware calibration constants measured for this project 
#define ADC_REF_VOLTAGE        4.3f
#define ADC_MAX_COUNT          1023.0f
#define ADC_ACCUMULATIONS      64.0f
#define CURRENT_DIVIDER_TOP    150000.0f
#define CURRENT_DIVIDER_BOTTOM 4750.0f
#define TRANSIMPEDANCE_GAIN    2.27f
#define CC_CONNECTED_THRESHOLD 2.3f

#define AVDD_CALIBRATION       1.00180036f
#define CURRENT_CALIBRATION    0.9227554943f

// Experimentally measured loop duration used for energy accumulation
#define CHARGE_LOOP_TIME_S     1.276f

/* --------------------------------------------------------------------------
 * Measure USB current
 *
 * Reads ADC channel AIN12, converts the accumulated ADC result to voltage,
 * compensates for the resistor-divider network, then converts the measured
 * voltage to USB current using the transimpedance gain.
 * -------------------------------------------------------------------------- */
static float measure_current(void)
{
    float sense_voltage;

    ADC0_CTRLC = 0b01000011;   // small cap, Vref reference, prescale 16 
    ADC0_MUXPOS = 0b00001100;  // AIN12 
    ADC0_COMMAND = 0b00000001; // start conversion

    while (ADC0_COMMAND)
    {
        // wait for ADC conversion 
    }

    sense_voltage =
        (ADC_REF_VOLTAGE * ADC0_RES) /
        (ADC_MAX_COUNT * ADC_ACCUMULATIONS);

    sense_voltage *=
        (CURRENT_DIVIDER_TOP + CURRENT_DIVIDER_BOTTOM) /
        CURRENT_DIVIDER_TOP;

    return sense_voltage / TRANSIMPEDANCE_GAIN;
}

// Measure USB-C configuration channel CC1 on AIN14. 
static float measure_cc1(void)
{
    ADC0_CTRLC = 0b01010011;   // small cap, VDD reference, prescale 16 
    ADC0_MUXPOS = 0b00001110;  // AIN14 
    ADC0_COMMAND = 0b00000001; // start conversion 

    while (ADC0_COMMAND)
    {
        // wait for ADC conversion 
    }

    return (5.0f * ADC0_RES) / (ADC_MAX_COUNT * ADC_ACCUMULATIONS);
}

// Measure USB-C configuration channel CC2 on AIN15.
static float measure_cc2(void)
{
    ADC0_CTRLC = 0b01010011;   // small cap, VDD reference, prescale 16 
    ADC0_MUXPOS = 0b00001111;  // AIN15 
    ADC0_COMMAND = 0b00000001; // start conversion 

    while (ADC0_COMMAND)
    {
        // wait for ADC conversion 
    }

    return (5.0f * ADC0_RES) / (ADC_MAX_COUNT * ADC_ACCUMULATIONS);
}

// Returns nonzero while a USB-C device is detected on either CC line. 
static unsigned char usb_device_connected(float cc1, float cc2)
{
    return (cc1 < CC_CONNECTED_THRESHOLD) ||
           (cc2 < CC_CONNECTED_THRESHOLD);
}

int main(void)
{
    float vcc1 = 0.0f;
    float vcc2 = 0.0f;
    float energy = 0.0f;
    float power = 0.0f;
    float current = 0.0f;
    float avdd = 0.0f;
    float delta_energy = 0.0f;

    // Configure the ATmega4809 and project hardware. 
    setup();

    while (1)
    {
        /*
         * Wait for a USB-C device.
         * A device is considered disconnected while both CC voltages are
         * above the 2.3 V threshold.
         */
        do
        {
            vcc1 = measure_cc1();
            for (int i = 0; i < 200; i++)
            {
                disp_float(vcc1);
            }
            _delay_ms(100);

            vcc2 = measure_cc2();
            for (int i = 0; i < 200; i++)
            {
                disp_float(vcc2);
            }
            _delay_ms(100);

        } while (!usb_device_connected(vcc1, vcc2));

        // Start a new charging session. 
        energy = 0.0f;

        /*
         * Enable the USB output / USB indicator according to the original
         * Lab 12 hardware mapping.
         */
        PORTC_OUT = 0b00011111;

        /*
         * Continue monitoring voltage, current, power, and energy until the
         * USB-C device is removed.
         */
        do
        {
            avdd = AVDD_CALIBRATION * measure_AVDD();
            current = CURRENT_CALIBRATION * measure_current();

            power = avdd * current;

            for (int i = 0; i < 200; i++)
            {
                disp_float(power);
            }

            _delay_ms(100);

            /*
             * Energy for one loop:
             *     E = P * Δt
             *
             * The 1.276 s loop duration was measured experimentally in the
             * original Lab 12 implementation.
             */
            delta_energy = power * CHARGE_LOOP_TIME_S;
            energy += delta_energy;

            // Toggle the diagnostic/indicator output used in the lab. 
            PORTE_OUT ^= 0b00001000;

            vcc1 = measure_cc1();
            vcc2 = measure_cc2();

        } while (usb_device_connected(vcc1, vcc2));

        // Disable the USB output / USB indicator after disconnect. 
        PORTC_OUT = 0b00111111;

        // Display total delivered energy in kJ. 
        for (int i = 0; i < 200; i++)
        {
            disp_float(energy / 1000.0f);
        }

        _delay_ms(100);
    }
}
