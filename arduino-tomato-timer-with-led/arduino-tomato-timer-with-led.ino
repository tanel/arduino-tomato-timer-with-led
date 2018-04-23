#include "SevenSegmentTM1637.h"
#include "SevenSegmentExtended.h"

const byte PIN_CLK = 13;
const byte PIN_DIO = 12;
SevenSegmentExtended display(PIN_CLK, PIN_DIO);

const int MODE_BREAK = 0;
const int MODE_WORK = 1;
int mode = MODE_BREAK;

const unsigned long MILLISECONDS = 1;
const unsigned long SECONDS = 1000 * MILLISECONDS;
const unsigned long MINUTES = 60 * SECONDS;

const unsigned long TARGET_LONG = 25 * MINUTES;
const unsigned long TARGET_SHORT = 10 * MINUTES;

unsigned long currentTargetMillis = TARGET_LONG;

unsigned long targetStartedAt = 0;

void setup() {
  Serial.begin(9600);
  display.begin();
  display.setBacklight(100);
  delay(1000);

  targetStartedAt = millis();
}

void loop() {
  delay(1000);

  unsigned long spentMillis = millis() - targetStartedAt;
  unsigned long neededMillis = currentTargetMillis - spentMillis;

  unsigned long seconds = neededMillis / 1000;
  unsigned long minutes = 0;
  if (seconds > 0) {
    minutes = seconds / 60;
  }

  if (seconds > 60) {
    seconds = seconds - (minutes * 60);
  }

  display.printTime(minutes, seconds, false);
}
