void Party(){ 
  static uint8_t hue;
  for(int i = 0; i < NUM_PIXELS_CLOCK/2; i++) {   
    // fade everything out
    //ClockLeds.fadeToBlackBy(40);

    // let's set an led value
    ClockLeds[i] = CHSV(hue++,255,255);

    // now, let's first 20 leds to the top 20 leds, 
    //ClockLeds(NUM_PIXELS_CLOCK/2,NUM_PIXELS_CLOCK-1) = leds(NUM_PIXELS_CLOCK/2 - 1 ,0);
    FastLED.delay(33);
  }
}
