#include "Sound.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))
#define LOW_BATTERY_TONE_DURATION_MS 300
#define LOW_BATTERY_PAUSE_DURATION_MS 200
#define HIGH_CURRENT_TONE_DURATION_MS 300
#define HIGH_CURRENT_PAUSE_DURATION_MS 200

// Define durations for each note (in milliseconds)
static const uint32_t STARTUP_DURATIONS[] = {200, 200, 200, 400};
static const uint32_t STARTUP_NOTES[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};

void playStartupSound(uint8_t buzzerPin) {
    for (uint32_t i = 0; i < ARRAY_SIZE(STARTUP_NOTES); i++) {
        tone(buzzerPin, STARTUP_NOTES[i], STARTUP_DURATIONS[i]);
        delay(STARTUP_DURATIONS[i] + 50); // Add a small delay between notes
    }
    noTone(buzzerPin); // Stop any remaining tone
}

void signalLowBattery(uint8_t buzzerPin) {
    tone(buzzerPin, NOTE_A4, LOW_BATTERY_TONE_DURATION_MS);
    delay(LOW_BATTERY_TONE_DURATION_MS + LOW_BATTERY_PAUSE_DURATION_MS);
    tone(buzzerPin, NOTE_A5, LOW_BATTERY_TONE_DURATION_MS);
    delay(LOW_BATTERY_TONE_DURATION_MS + LOW_BATTERY_PAUSE_DURATION_MS);
}

void signalCurrentTooHigh(uint8_t buzzerPin) {
    tone(buzzerPin, NOTE_B4, HIGH_CURRENT_TONE_DURATION_MS);
    delay(HIGH_CURRENT_TONE_DURATION_MS + HIGH_CURRENT_PAUSE_DURATION_MS);
    tone(buzzerPin, NOTE_B5, HIGH_CURRENT_TONE_DURATION_MS);
    delay(HIGH_CURRENT_TONE_DURATION_MS + HIGH_CURRENT_PAUSE_DURATION_MS);
}

void playErrorSound(uint8_t buzzerPin) {
    tone(buzzerPin, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzerPin);     // Stop sound...
    delay(1000);        // ...for 1sec
}
