#include "core/powerSave.h"
#include <interface.h>

/***************************************************************************************
** Function name: _setup_gpio()
** Location: main.cpp
** Description:   initial setup for the device
***************************************************************************************/
void _setup_gpio() {
    pinMode(SEL_BTN, INPUT_PULLUP);
    pinMode(UP_BTN, INPUT_PULLUP);
    pinMode(DW_BTN, INPUT_PULLUP);
}

/***************************************************************************************
** Function name: _post_setup_gpio()
** Location: main.cpp
** Description:   second stage gpio setup to make a few functions work
***************************************************************************************/
void _post_setup_gpio() { pinMode(TFT_BL, OUTPUT); }

/***************************************************************************************
** Function name: getBattery()
** location: display.cpp
** Description:   Delivers the battery value from 1-100
** Reads GPIO34 through a 2x (100k/100k) voltage divider wired to the 18650's
** BMS output, so the ADC only ever sees up to ~2.1V from a max 4.2V cell.
***************************************************************************************/
int getBattery() {
    static bool adcInitialized = false;
    if (!adcInitialized) {
        pinMode(ANALOG_BAT_PIN, INPUT);
        analogSetAttenuation(ADC_11db); // Full range for 0-3.3V input
        adcInitialized = true;
    }

    // Read ADC and convert to actual battery voltage (with x2 divider)
    uint32_t adcReading = analogReadMilliVolts(ANALOG_BAT_PIN);
    float actualVoltage = (float)adcReading * 2.0f; // x2 voltage divider

    // Single-cell Li-ion range: 3000mV (cutoff/empty) to 4200mV (fully charged)
    const float MIN_VOLTAGE = 3000.0f;
    const float MAX_VOLTAGE = 4200.0f;

    int percent = (int)(((actualVoltage - MIN_VOLTAGE) / (MAX_VOLTAGE - MIN_VOLTAGE)) * 100.0f);

    if (percent < 0) percent = 0;
    if (percent > 100) percent = 100;

    return percent;
}

/*********************************************************************
** Function: setBrightness
** location: settings.cpp
** set brightness value
** This board's backlight pin (GPIO32) is a plain on/off line, not PWM-driven
** in the base config, so we just toggle it fully on above a threshold.
**********************************************************************/
void _setBrightness(uint8_t brightval) {
    pinMode(TFT_BL, OUTPUT);
    digitalWrite(TFT_BL, brightval > 0 ? HIGH : LOW);
}

/*********************************************************************
** Function: InputHandler
** Handles the variables PrevPress, NextPress, SelPress, AnyKeyPress and EscPress
** 3-button scheme: SEL_BTN = select, UP_BTN = previous/esc (long-press = esc),
** DW_BTN = next
**********************************************************************/
void InputHandler(void) {
    static unsigned long tm = millis();
    static unsigned long esc_tm = millis();
    static bool esc_armed = false;
    if (!(millis() - tm > 200 || LongPress)) return;

    bool s = (digitalRead(SEL_BTN) == LOW);
    bool u = (digitalRead(UP_BTN) == LOW);
    bool d = (digitalRead(DW_BTN) == LOW);

    if (s || u || d) {
        tm = millis();
        if (!wakeUpScreen()) AnyKeyPress = true;
        else return;
    }

    if (u) {
        PrevPress = true;
        if (!esc_armed) {
            esc_tm = millis();
            esc_armed = true;
        }
    } else {
        esc_armed = false;
    }
    if (esc_armed && millis() - esc_tm > 1000) {
        esc_armed = false;
        PrevPress = false;
        EscPress = true;
    }
    if (d) NextPress = true;
    if (s) SelPress = true;
}

/*********************************************************************
** Function: powerOff
** location: mykeyboard.cpp
** Turns off the device (or try to)
** No power-management chip on this board, so this is a no-op.
**********************************************************************/
void powerOff() {}

/*********************************************************************
** Function: checkReboot
** location: mykeyboard.cpp
** Btn logic to turn off the device (name is odd btw)
** No power/reboot button wired, so this is a no-op.
**********************************************************************/
void checkReboot() {}
