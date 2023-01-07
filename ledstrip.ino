void display_clock() {

  for (int i = 0; i <= 8; i++) {
    if (i + 1 <= sekunden.einer) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(0, 0, 0));
    }
  }

  for (int i = 9; i <= 13; i++) {
    if (i - 8 <= sekunden.zehner) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(aus.r, aus.g, aus.b));
    }
  }

  for (int i = 14; i <= 22; i++) {
    if (i - 13 <= minuten.einer) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(aus.r, aus.g, aus.b));
    }
  }
  for (int i = 23; i <= 27; i++) {
    if (i - 22 <= minuten.zehner) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(aus.r, aus.g, aus.b));
    }
  }
  for (int i = 28; i <= 36; i++) {
    if (i - 27 <= stunden.einer) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(aus.r, aus.g, aus.b));
    }
  }
  for (int i = 37; i <= 38; i++) {
    if (i - 36 <= stunden.zehner) {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(uhr.r, uhr.g, uhr.b));
    } else {
      PIXELS_CLOCK.setPixelColor(i, PIXELS_CLOCK.Color(aus.r, aus.g, aus.b));
    }
  }
  PIXELS_CLOCK.show();
}
