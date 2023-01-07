#define LED_SEKUNDEN_EINER_MIN 0
#define LED_SEKUNDEN_EINER_MAX 8
#define LED_SEKUNDEN_ZEHNER_MIN 9
#define LED_SEKUNDEN_ZEHNER_MAX 13

#define LED_MINUTEN_EINER_MIN 14
#define LED_MINUTEN_EINER_MAX 22
#define LED_MINUTEN_ZEHNER_MIN 23
#define LED_MINUTEN_ZEHNER_MAX 27

#define LED_STUNDEN_EINER_MIN 28
#define LED_STUNDEN_EINER_MAX 36
#define LED_STUNDEN_ZEHNER_MIN 37
#define LED_STUNDEN_ZEHNER_MAX 38

void display_clock() {
  for (int i = LED_SEKUNDEN_EINER_MIN; i <= LED_SEKUNDEN_EINER_MAX; i++) {
    if (i - LED_SEKUNDEN_EINER_MIN < sekunden.einer) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }

  for (int i = LED_SEKUNDEN_ZEHNER_MIN; i <= LED_SEKUNDEN_ZEHNER_MAX; i++) {
    if (i - LED_SEKUNDEN_ZEHNER_MIN < sekunden.zehner) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }

  for (int i = LED_MINUTEN_EINER_MIN; i <= LED_MINUTEN_EINER_MAX; i++) {
    if (i - LED_MINUTEN_EINER_MIN < minuten.einer) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }
  for (int i = LED_MINUTEN_ZEHNER_MIN; i <= LED_MINUTEN_ZEHNER_MAX; i++) {
    if (i - LED_MINUTEN_ZEHNER_MIN < minuten.zehner) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }
  for (int i = LED_STUNDEN_EINER_MIN; i <= LED_STUNDEN_EINER_MAX; i++) {
    if (i - LED_STUNDEN_EINER_MIN < stunden.einer) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }
  for (int i = LED_STUNDEN_ZEHNER_MIN; i <= LED_STUNDEN_ZEHNER_MAX; i++) {
    if (i - LED_STUNDEN_ZEHNER_MIN < stunden.zehner) {
      ClockLeds[i] = CLOCK_LED_ON;
    } else {
      ClockLeds[i] = CLOCK_LED_OFF;
    }
  }
  FastLED.show();
}
