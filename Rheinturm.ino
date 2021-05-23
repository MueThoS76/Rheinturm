/*
    WiFi-Settings: https://github.com/Juerd/ESP-WiFiSettings
    NTP-Server: https://www.pool.ntp.org/zone/europe
    time zone settings: (https://remotemonitoringsystems.ca/time-zone-abbreviations.php)
     See https://github.com/nayarsystems/posix_tz_db/blob/master/zones.csv for Timezone codes for your region
*/

#include <SPIFFS.h>
#include <WiFiSettings.h>
#include <ArduinoOTA.h>
#include <time.h>
#include <Adafruit_NeoPixel.h>
#define NUMPIXELS 60 // Anzahl LEDs
#define PIN        12 // LED Pin
struct ziffern {
  byte einer;
  byte zehner;
} sekunden, minuten, stunden;




Adafruit_NeoPixel pixels(NUMPIXELS, PIN, NEO_GRB + NEO_KHZ800);

const char* NTP_SERVER = "de.pool.ntp.org";
const char* TZ_INFO    = "CET-1CEST-2,M3.5.0/02:00:00,M10.5.0/03:00:00";
tm timeinfo;
time_t now;




// Start ArduinoOTA via WiFiSettings with the same hostname and password
void setup_ota() {
  ArduinoOTA.setHostname(WiFiSettings.hostname.c_str());
  ArduinoOTA.setPassword(WiFiSettings.password.c_str());
  ArduinoOTA.begin();
}

void setup() {
  Serial.begin(115200);
  SPIFFS.begin(true);  // Will format on the first run after failing to mount

  // Force WPA secured WiFi for the software access point.
  // Because OTA is remote code execution (RCE) by definition, the password
  // should be kept secret. By default, WiFiSettings will become an insecure
  // WiFi access point and happily tell anyone the password. The password
  // will instead be provided on the Serial connection, which is a bit safer.
  WiFiSettings.secure = true;

  // Set callbacks to start OTA when the portal is active
  WiFiSettings.onPortal = []() {
    setup_ota();
  };
  WiFiSettings.onPortalWaitLoop = []() {
    ArduinoOTA.handle();
  };

  // Use stored credentials to connect to your WiFi access point.
  // If no credentials are stored or if the access point is out of reach,
  // an access point will be started with a captive portal to configure WiFi.
  WiFiSettings.connect();

  Serial.print("Password: ");
  Serial.println(WiFiSettings.password);

  setup_ota();  // If you also want the OTA during regular execution

  configTime(0, 0, NTP_SERVER);
  setenv("TZ", TZ_INFO, 1);

  if (getNTPtime(10)) {  // wait up to 10sec to sync
  } else {
    Serial.println("Time not set");
    ESP.restart();
  }

  pixels.begin(); // INITIALIZE NeoPixel strip object (REQUIRED)


}

void loop() {
  ArduinoOTA.handle();  // If you also want the OTA during regular execution

  // Your loop code here

  //   pixels.clear(); // Set all pixel colors to 'off'
  getNTPtime(1);
  //showTime(timeinfo);


  //  for (int i = 0; i < NUMPIXELS; i++) { // For each pixel...
  //    pixels.setPixelColor(i, pixels.Color(50, 0, 50));
  //    pixels.show();   // Send the updated pixel colors to the hardware.
  //    delay(100); // Pause before next pass through loop
  //}



  // Uhr Berechnungen:
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

  for (int i = 0; i <= 8; i++) {
    if (i + 1 <= sekunden.einer) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }

  for (int i = 9; i <= 13; i++) {
    if (i - 8 <= sekunden.zehner) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }

  for (int i = 14; i <= 22; i++) {
    if (i - 13 <= minuten.einer) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  for (int i = 23; i <= 27; i++) {
    if (i - 22 <= minuten.zehner) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  for (int i = 28; i <= 36; i++) {
    if (i - 27 <= stunden.einer) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  for (int i = 37; i <= 38; i++) {
    if (i - 36 <= stunden.zehner) {
      pixels.setPixelColor(i, pixels.Color(50, 0, 50));
    } else {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
    }
  }
  pixels.show();
}




bool getNTPtime(int sec) {
  {
    uint32_t start = millis();
    do {
      time(&now);
      localtime_r(&now, &timeinfo);
      //Serial.print(".");
      delay(10);
    } while (((millis() - start) <= (1000 * sec)) && (timeinfo.tm_year < (2016 - 1900)));
    if (timeinfo.tm_year <= (2016 - 1900)) return false;  // the NTP call was not successful
    //Serial.print("now ");  Serial.println(now);
    char time_output[30];
    //strftime(time_output, 30, "%a  %d-%m-%y %T", localtime(&now));
    //Serial.println(time_output);
    //Serial.println();
    sekunden.einer = timeinfo.tm_sec % 10;
    sekunden.zehner = (timeinfo.tm_sec / 10) % 10;
    minuten.einer = timeinfo.tm_min % 10;
    minuten.zehner = (timeinfo.tm_min / 10) % 10;
    stunden.einer = timeinfo.tm_hour % 10;
    stunden.zehner = (timeinfo.tm_hour / 10) % 10;
  }
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
