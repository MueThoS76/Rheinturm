void display_aux(){
  if (fadein) {
    fadeValue+=3;
    if (fadeValue >= 200){fadein = 0;}
  }else{
    fadeValue-=6;
    if (fadeValue <= 0){fadein = 1;}
  }
  PIXELS_AUX.setPixelColor(0, PIXELS_AUX.Color(warning.g, fadeValue, warning.b));

  PIXELS_AUX.show();
  
}
