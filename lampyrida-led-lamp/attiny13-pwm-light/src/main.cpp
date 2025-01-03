#include <Arduino.h>
#include <avr/power.h>
#include <avr/sleep.h>

// Wiring:
// -------
//                                   +-\/-+
//            RST ------- ADC0 PB5  1|°   |8  Vcc
//  VOLTAGE SENSE ------- ADC3 PB3  2|    |7  PB2 ADC1
// POWER_ON_SENSE ------- ADC2 PB4  3|    |6  PB1 AIN1 OC0B --- NC
//                             GND  4|    |5  PB0 AIN0 OC0A --- LED_LIGHT
//                                   +----+
//

// We don't even need an I/O pin, because it uses the reset line to toggle the processor between running and sleep
#define LED_LIGHT_PIN      PB0
#define POWER_ON_SENSE_PIN PB4  // The digital pin connected to the capacitor

typedef enum LedStatus {
    LED_POWER_OFF = 0,
    LED_MAX_POWER = 255,
    LED_HALF_POWER = 128,
    LED_MIN_POWER = 64
} LedStatus;

// The on/off state is stored in the variable. Usually all variables are initialized on reset, but we want this variable to retain its value
__attribute__((section(".noinit"))) volatile LedStatus ledMode;
static void powerDown();
static void setLedMode();


void setup() {
    pinMode(POWER_ON_SENSE_PIN, INPUT);
    boolean isPowerOnReset = digitalRead(POWER_ON_SENSE_PIN) == LOW;
    setLedMode();

    if (bit_is_set(MCUSR, BORF) || isPowerOnReset) { // Check the state of POWER_ON_SENSE_PIN to detect a power-on reset and don't turn on lights
        ledMode = LED_POWER_OFF;
    }
    MCUSR = 0;

    if (ledMode == LED_POWER_OFF) {
        powerDown();
    }

    pinMode(LED_LIGHT_PIN, OUTPUT);
    analogWrite(LED_LIGHT_PIN, ledMode);
}

void loop() {

}

static void setLedMode() {
    switch (ledMode) {
        case LED_POWER_OFF:
            ledMode = LED_MAX_POWER;
            break;
        case LED_MAX_POWER:
            ledMode = LED_HALF_POWER;
            break;
        case LED_HALF_POWER:
            ledMode = LED_MIN_POWER;
            break;
        case LED_MIN_POWER:
            ledMode = LED_POWER_OFF;
            break;
        default:
            ledMode = LED_POWER_OFF;
    }
}

static void powerDown() {
    // Don't leave unused pins floating
    pinMode(PB1, INPUT_PULLUP);
    pinMode(PB2, INPUT_PULLUP);
    pinMode(PB3, INPUT_PULLUP);

    set_sleep_mode(SLEEP_MODE_PWR_DOWN);
    ADCSRA &= ~(1 << ADEN);       // Turn off ADC to save power
    sleep_enable();
    sleep_cpu();
}
