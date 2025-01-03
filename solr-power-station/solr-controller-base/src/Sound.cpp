#include "Sound.h"

#define ARRAY_SIZE(x) (sizeof(x)/sizeof((x)[0]))

// Define durations for each note (in milliseconds)
static const uint32_t STARTUP_DURATIONS[] = {200, 200, 200, 400};
static const uint32_t STARTUP_NOTES[] = {NOTE_C4, NOTE_E4, NOTE_G4, NOTE_C5};

void playStartupSound(uint32_t buzzerPin) {
    for (uint32_t i = 0; i < ARRAY_SIZE(STARTUP_NOTES); i++) {
        tone(buzzerPin, STARTUP_NOTES[i], STARTUP_DURATIONS[i]);
        delay(STARTUP_DURATIONS[i] + 50); // Add a small delay between notes
    }
    noTone(buzzerPin); // Stop any remaining tone
}

void playErrorSound(uint32_t buzzerPin) {
    tone(buzzerPin, 1000); // Send 1KHz sound signal...
    delay(1000);        // ...for 1 sec
    noTone(buzzerPin);     // Stop sound...
    delay(1000);        // ...for 1sec
}
