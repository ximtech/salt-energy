#include <Arduino.h>

#include "Sound.h"
#include "ACS712.h"

#define BUILD_IN_LED_PIN    13
#define BUZZER_PIN          5
#define AC_OUT_PIN          7
#define DC_OUT_PIN          6
#define COOLING_FAN_PIN     9
#define SOURCE_VOLTAGE_PIN  A0
#define AC_AMPS_SENSOR_PIN  A1
#define DC_AMPS_SENSOR_PIN  A2

#define VOLTAGE_READ_COUNT 4
#define MIN_CURRENT_THRESHOLD_VALUE 0.9f
#define CURRENT_CORRECTION_COEFFICIENT 3.0f
#define MAX_AC_LOAD_CURRENT 28.0f
#define MAX_DC_LOAD_CURRENT 15.0f
#define MAX_TOTAL_LOAD_CURRENT 30.0f
#define MIN_BATTERY_VOLTAGE 9.9f    // 3.3V * 3 -> 0%
#define BATTERY_RECOVERY_VOLTAGE 11.6f  // 3.61V * 3 -> 10%
#define CURRENT_OVERLOAD_TIMEOUT_MS 5000

/*
 * Two resistors divider of 30K and 7.5K
 *
 * Vbat     Vin      GND
 *  |        |        |
 *  +--[R1]--+--[R2]--+
 *
 *  R1 = 30kOhms
 *  R2 = 7.5kOhms
*/
static const float R1 = 30000;
static const float R2 = 7500;
static const float correctionFactor = .1;

//  Arduino NANO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 30A uses 66 mV per A
static ACS712 ACS712_AC_LOAD_SENSOR(AC_AMPS_SENSOR_PIN, 5.0, 1023, 66);
static ACS712 ACS712_DC_LOAD_SENSOR(DC_AMPS_SENSOR_PIN, 5.0, 1023, 66);

static uint32_t acLoadEnableTimeout = 0;
static uint32_t dcLoadEnableTimeout = 0;

static float getPowerSupplyVoltage();
static float getLoadAmps(ACS712 acs);

static inline void ledOn();
static inline void ledOff();
static inline void setCoolingFanSpeed(int16_t adcValue);
static inline void acOutputRelayOn();
static inline void acOutputRelayOff();
static inline void dcOutputRelayOn();
static inline void dcOutputRelayOff();


void setup() {
    Serial.begin(9600);
    pinMode(BUILD_IN_LED_PIN, OUTPUT);
    pinMode(AC_OUT_PIN, OUTPUT);
    pinMode(DC_OUT_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(COOLING_FAN_PIN, OUTPUT);
    pinMode(SOURCE_VOLTAGE_PIN, INPUT);

    digitalWrite(AC_OUT_PIN, HIGH);
    digitalWrite(DC_OUT_PIN, HIGH);

    Serial.print("ACS712_LIB_VERSION: ");
    Serial.println(ACS712_LIB_VERSION);
    delay(100);

    ACS712_AC_LOAD_SENSOR.autoMidPointDC(10);
    ACS712_AC_LOAD_SENSOR.incMidPoint();
    ACS712_AC_LOAD_SENSOR.incMidPoint();
    ACS712_AC_LOAD_SENSOR.suppressNoise(true);

    ACS712_DC_LOAD_SENSOR.autoMidPointDC(10);
    ACS712_DC_LOAD_SENSOR.incMidPoint();
    ACS712_DC_LOAD_SENSOR.incMidPoint();
    ACS712_DC_LOAD_SENSOR.suppressNoise(true);

    Serial.print("ACS AC MidPoint= ");
    Serial.print(ACS712_AC_LOAD_SENSOR.getMidPoint());
    Serial.print(" ACS DC MidPoint= ");
    Serial.println(ACS712_DC_LOAD_SENSOR.getMidPoint());

    // stabilize values
    ACS712_AC_LOAD_SENSOR.mA_DC(150);
    ACS712_DC_LOAD_SENSOR.mA_DC(150);

    playStartupSound(BUZZER_PIN);
}

void loop() {

    float batteryVoltage = getPowerSupplyVoltage();
    bool isLoadEnabled = digitalRead(AC_OUT_PIN) == LOW && digitalRead(DC_OUT_PIN) == LOW;
    if (isLoadEnabled && batteryVoltage <= MIN_BATTERY_VOLTAGE) {
        acOutputRelayOff();
        dcOutputRelayOff();
        return;
    }

    if (!isLoadEnabled && batteryVoltage < BATTERY_RECOVERY_VOLTAGE) {
        delay(1000);
        return;
    }

    float acLoadAmps = 0.0f;
    if (acLoadEnableTimeout == 0) {
        acOutputRelayOn();
        acLoadAmps = getLoadAmps(ACS712_AC_LOAD_SENSOR);

        if (acLoadAmps > MAX_AC_LOAD_CURRENT) {
            acOutputRelayOff();
            acLoadEnableTimeout = millis();
        }
    }

    float dcLoadAmps = 0.0f;
    if (dcLoadEnableTimeout == 0) {
        dcOutputRelayOn();
        dcLoadAmps = getLoadAmps(ACS712_DC_LOAD_SENSOR);

        if (dcLoadAmps > MAX_DC_LOAD_CURRENT) {
            dcOutputRelayOff();
            dcLoadEnableTimeout = millis();
        }
    }

    uint32_t currentMillis = millis();
    bool isACLoadEnabled = digitalRead(AC_OUT_PIN) == LOW;
    if (!isACLoadEnabled && (currentMillis - acLoadEnableTimeout) >= CURRENT_OVERLOAD_TIMEOUT_MS) {
        acLoadEnableTimeout = 0;
    }

    bool isDCLoadEnabled = digitalRead(DC_OUT_PIN) == LOW;
    if (!isDCLoadEnabled && (currentMillis - dcLoadEnableTimeout) >= CURRENT_OVERLOAD_TIMEOUT_MS) {
        dcLoadEnableTimeout = 0;
    }

    if ((acLoadAmps + dcLoadAmps) >= MAX_TOTAL_LOAD_CURRENT) {
        acOutputRelayOff();
        dcOutputRelayOff();
        acLoadEnableTimeout = millis();
        dcLoadEnableTimeout = millis();
    }

    // TODO: Cooling fan impl


    Serial.print("Battery V= ");
    Serial.print(batteryVoltage, 4);
    Serial.print(" AC amps= ");
    Serial.print(acLoadAmps, 3);
    Serial.print(" DC amps= ");
    Serial.print(dcLoadAmps, 3);
    Serial.println();
    delay(2000);


}

static float getPowerSupplyVoltage() {
    float accumulatedValue = 0;
    for (uint8_t i = 0; i < VOLTAGE_READ_COUNT; i++) {
        float adcValue = analogRead(SOURCE_VOLTAGE_PIN);
        float outVoltage = (adcValue * 5.0f) / 1023.0f;
        float dividerVoltage = outVoltage / (R2 / (R1 + R2));
        accumulatedValue += dividerVoltage + correctionFactor;
        delay(10); // Sampling delay
    }
    return accumulatedValue / VOLTAGE_READ_COUNT;
}

static float getLoadAmps(ACS712 acs) {
    float amps = acs.mA_DC(10) / 1000;
    return (amps > MIN_CURRENT_THRESHOLD_VALUE) ? (amps / CURRENT_CORRECTION_COEFFICIENT) : 0.0f;
}

static inline void ledOn() {
    digitalWrite(BUILD_IN_LED_PIN, HIGH);
}

static inline void ledOff() {
    digitalWrite(BUILD_IN_LED_PIN, LOW);
}

static inline void setCoolingFanSpeed(int16_t adcValue) {
    analogWrite(COOLING_FAN_PIN, adcValue);
}

static inline void acOutputRelayOn() {
    digitalWrite(AC_OUT_PIN, LOW);
}

static inline void acOutputRelayOff() {
    digitalWrite(AC_OUT_PIN, HIGH);
}

static inline void dcOutputRelayOn() {
    digitalWrite(DC_OUT_PIN, LOW);
}

static inline void dcOutputRelayOff() {
    digitalWrite(DC_OUT_PIN, HIGH);
}