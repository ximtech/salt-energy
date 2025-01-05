#include <Arduino.h>

#include "Sound.h"
#include "ACS712.h"

#define BUILD_IN_LED_PIN    13
#define BUZZER_PIN          5
#define LOAD_OUT_PIN        7
#define COOLING_FAN_PIN     9
#define SOURCE_VOLTAGE_PIN  A0
#define ACS_SENSOR_PIN      A1

#define MCU_SUPPLY_VOLTAGE              4.61f
#define ADC_RESOLUTION                  1023.0f

#define VOLTAGE_READ_COUNT              4
#define MIN_CURRENT_THRESHOLD_VALUE     0.1f
#define CURRENT_CORRECTION_COEFFICIENT  0.4f
#define MAX_LOAD_CURRENT                1.5f    // 30.0f
#define MIN_BATTERY_VOLTAGE             9.9f    // 3.3V * 3 -> 0%
#define BATTERY_RECOVERY_VOLTAGE       (10.8f - 0.4f)  // 3.61V * 3 -> 10% with correction
#define CURRENT_OVERLOAD_TIMEOUT_MS     5000
#define LOW_BATTERY_SIGNAL_COUNT        10

#define CURRENT_VALUE_FOR_FAN_MAX_SPEED 1.0f    // 10.0f
#define CURRENT_VALUE_FOR_FAN_MID_SPEED 0.5f    // 5.0f
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
static const float correctionFactor = 0.2f;

static uint8_t lowBatterySignalCounter = 0;

//  Arduino NANO has 5.0 volt with a max ADC value of 1023 steps
//  ACS712 30A uses 66mV per A
static ACS712 ACS712_CURRENT_SENSOR(ACS_SENSOR_PIN, MCU_SUPPLY_VOLTAGE, ADC_RESOLUTION, 66);

static uint32_t loadEnableTimeout = 0;

static float getPowerSupplyVoltage(uint16_t samplingCount);
static float getLoadAmps(ACS712 acs);

static inline void ledToggle();
static inline void ledOff();
static inline void setCoolingFanSpeed(int16_t adcValue);
static inline void outputRelayOn();
static inline void outputRelayOff();


void setup() {
    Serial.begin(9600);
    pinMode(BUILD_IN_LED_PIN, OUTPUT);
    pinMode(LOAD_OUT_PIN, OUTPUT);
    pinMode(BUZZER_PIN, OUTPUT);
    pinMode(COOLING_FAN_PIN, OUTPUT);
    pinMode(SOURCE_VOLTAGE_PIN, INPUT);

    digitalWrite(LOAD_OUT_PIN, HIGH);   // disable output at startup
    outputRelayOff();

    Serial.print("ACS712_LIB_VERSION: ");
    Serial.println(ACS712_LIB_VERSION);
    delay(100);

    ACS712_CURRENT_SENSOR.autoMidPointDC(10);
    ACS712_CURRENT_SENSOR.incMidPoint();
    ACS712_CURRENT_SENSOR.incMidPoint();
    ACS712_CURRENT_SENSOR.suppressNoise(true);

    Serial.print("ACS MidPoint= ");
    Serial.println(ACS712_CURRENT_SENSOR.getMidPoint());

    // stabilize values
    ACS712_CURRENT_SENSOR.mA_DC(150);
    getPowerSupplyVoltage(100);
    playStartupSound(BUZZER_PIN);
}

void loop() {

    float batteryVoltage = getPowerSupplyVoltage(VOLTAGE_READ_COUNT);
    Serial.print("Battery V= ");
    Serial.println(batteryVoltage, 3);

    bool isLoadEnabled = digitalRead(LOAD_OUT_PIN) == LOW;
    if (isLoadEnabled && batteryVoltage <= MIN_BATTERY_VOLTAGE) {
        outputRelayOff();
        return;
    }

    if (!isLoadEnabled && batteryVoltage < BATTERY_RECOVERY_VOLTAGE) {
        if (lowBatterySignalCounter < LOW_BATTERY_SIGNAL_COUNT) {
            signalLowBattery(BUZZER_PIN);
            lowBatterySignalCounter++;
        }
        ledToggle();
        delay(500);    // battery is not charged yet, wait some time and return
        return;
    }
    lowBatterySignalCounter = 0;


    float loadAmps = 0.0f;
    if (loadEnableTimeout == 0) {
        loadAmps = getLoadAmps(ACS712_CURRENT_SENSOR);
        Serial.print("Load Amps= ");
        Serial.println(loadAmps, 3);

        if (loadAmps > MAX_LOAD_CURRENT) {
            outputRelayOff();
            setCoolingFanSpeed(0);
            loadEnableTimeout = millis();
            return;
        }
        outputRelayOn();
    }

    uint32_t currentMillis = millis();
    bool isACLoadEnabled = digitalRead(LOAD_OUT_PIN) == LOW;
    if (!isACLoadEnabled && ((currentMillis - loadEnableTimeout) < CURRENT_OVERLOAD_TIMEOUT_MS)) {
        signalCurrentTooHigh(BUZZER_PIN);
        ledToggle();
        delay(500);    // wait some time before the next check
        return;
    }

    loadEnableTimeout = 0;
    ledOff();

    if (loadAmps >= CURRENT_VALUE_FOR_FAN_MAX_SPEED) {
        setCoolingFanSpeed(255);

    } else if (loadAmps >= CURRENT_VALUE_FOR_FAN_MID_SPEED) {
        setCoolingFanSpeed(128);

    } else {
        setCoolingFanSpeed(0);
    }
}

static float getPowerSupplyVoltage(uint16_t samplingCount) {
    float accumulatedValue = 0;
    for (uint16_t i = 0; i < samplingCount; i++) {
        float adcValue = analogRead(SOURCE_VOLTAGE_PIN);
        float outVoltage = (adcValue * MCU_SUPPLY_VOLTAGE) / ADC_RESOLUTION;
        float dividerVoltage = outVoltage / (R2 / (R1 + R2));
        accumulatedValue += (dividerVoltage - correctionFactor);
        delay(10); // Sampling delay
    }
    return accumulatedValue / samplingCount;
}

static float getLoadAmps(ACS712 acs) {
    float amps = (acs.mA_DC(10) / 1000) + CURRENT_CORRECTION_COEFFICIENT;
    return (amps > MIN_CURRENT_THRESHOLD_VALUE) ? amps : 0.0f;
}

static inline void ledToggle() {
    digitalWrite(BUILD_IN_LED_PIN, !digitalRead(BUILD_IN_LED_PIN));
}

static inline void ledOff() {
    digitalWrite(BUILD_IN_LED_PIN, LOW);
}

static inline void setCoolingFanSpeed(int16_t adcValue) {
    analogWrite(COOLING_FAN_PIN, adcValue);
}

static inline void outputRelayOn() {
    digitalWrite(LOAD_OUT_PIN, LOW);
}

static inline void outputRelayOff() {
    digitalWrite(LOAD_OUT_PIN, HIGH);
}