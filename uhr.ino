#define TIMEINFO_INVALID (timeinfo.tm_year <= (2016 - 1900))

bool getNTPtime(int sec) {
  uint32_t start = millis();
  do {
    time(&now);
    localtime_r(&now, &timeinfo);
    //Serial.print(".");
    delay(10);
  } while (((millis() - start) <= (1000 * sec)) && TIMEINFO_INVALID);
  if (TIMEINFO_INVALID) return false;  // the NTP call was not successful
  //Serial.print("now ");  Serial.println(now);
  char time_output[30];
  //strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
  //Serial.println(time_output);
  //Serial.println();
  sekunden.einer  = timeinfo.tm_sec  % 10;
  sekunden.zehner = timeinfo.tm_sec  / 10;
  minuten.einer   = timeinfo.tm_min  % 10;
  minuten.zehner  = timeinfo.tm_min  / 10;
  stunden.einer   = timeinfo.tm_hour % 10;
  stunden.zehner  = timeinfo.tm_hour / 10;
#ifdef DEBUG
  // Uhr Ausgabe:
  Serial.print(stunden.zehner);
  Serial.print(" ");
  Serial.print(stunden.einer);
  Serial.print(" - ");
  Serial.print(minuten.zehner);
  Serial.print(" ");
  Serial.print(minuten.einer);
  Serial.print(" - ");
  Serial.print(sekunden.zehner);
  Serial.print(" ");
  Serial.print(sekunden.einer);
  Serial.println(" ");
#endif
  return true;
}


void showTime(tm localTime) {
  Serial.print(localTime.tm_mday);
  Serial.print('-');
  Serial.print(localTime.tm_mon + 1);
  Serial.print('-');
  Serial.print(localTime.tm_year - 100);
  Serial.print('_');
  Serial.print(localTime.tm_hour);
  Serial.print(':');
  Serial.print(localTime.tm_min);
  Serial.print(':');
  Serial.print(localTime.tm_sec);
  Serial.print(" Day of Week ");
  if (localTime.tm_wday == 0)   Serial.println(7);
  else Serial.println(localTime.tm_wday);
}
