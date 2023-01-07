void display_clock() {

  for (int i = 0; i <= 8; i++) {
    if (i + 1 <= sekunden.einer) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }

  for (int i = 9; i <= 13; i++) {
    if (i - 8 <= sekunden.zehner) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }

  for (int i = 14; i <= 22; i++) {
    if (i - 13 <= minuten.einer) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }
  for (int i = 23; i <= 27; i++) {
    if (i - 22 <= minuten.zehner) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }
  for (int i = 28; i <= 36; i++) {
    if (i - 27 <= stunden.einer) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }
  for (int i = 37; i <= 38; i++) {
    if (i - 36 <= stunden.zehner) {
      ClockLeds[i] = CRGB::Red;
    } else {
      ClockLeds[i] = CRGB::Black;
    }
  }
  FastLED.show();
}
