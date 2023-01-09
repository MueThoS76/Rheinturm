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
#include <FastLED.h>
#define NUM_PIXELS_CLOCK 39 // Anzahl LEDs
#define LED_PIN_CLOCK    16 // LED Pin
#define NUM_PIXELS_AUX   3  // Anzahl LEDs
#define LED_PIN_AUX      17 // LED Pin
#define BRIGHTNESS  64
#define CLOCK_LED_ON CRGB::Yellow;
#define CLOCK_LED_OFF CRGB::Black;


CRGB ClockLeds[NUM_PIXELS_CLOCK];
CRGB AuxLeds[NUM_PIXELS_AUX];

#define Touch_PIN 14 // Touchsensor
#define Touch_Threshold 20
#define DEBUG 1
struct ziffern {
  byte einer;
  byte zehner;
} sekunden, minuten, stunden;

bool fadein = 1;
int fadeValue = 0;


int Modus = 1;
int Touch_Value = 0;
bool Touched = 0;
unsigned long Old_Millis = 0;
int Long_Touch = 0;
unsigned long Press_Time;


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
    //Serial.println("Time not set");
    ESP.restart();
  }

  FastLED.addLeds<PL9823, LED_PIN_CLOCK>(ClockLeds, NUM_PIXELS_CLOCK);
  FastLED.addLeds<PL9823, LED_PIN_AUX>(AuxLeds, NUM_PIXELS_AUX);
  FastLED.setMaxPowerInMilliWatts(1000);
  FastLED.setBrightness(  BRIGHTNESS );
  FastLED.clear();
  FastLED.show();
}

void loop() {
  ArduinoOTA.handle();  // If you also want the OTA during regular execution
  // Your loop code here
  getNTPtime(1);
  display_clock();
  display_aux();

  Touch_Value = touchRead(Touch_PIN);
  if (Touch_Value < Touch_Threshold && Touched == 0) {
    Old_Millis = millis();
    Touched = 1;
  } else if (Touch_Value > Touch_Threshold && Touched == 1) {
    Press_Time  = millis() - Old_Millis;
    if (Press_Time > 200 && Press_Time < 1500) {
      Modus++;
      Touched = 0;
    } else if (Press_Time > 1500) {
      Long_Touch++;
      Touched = 0;
    } else {
      Touched = 0;
    }
  }
  if (Modus == 3 ) Modus = 1;


#ifdef DEBUG
  //Serial.print(Modus);
  //Serial.print(" ");
  //Serial.print(Long_Touch);
  //Serial.print(" ");
  //Serial.print(Touched);
  //Serial.print(" ");
  //Serial.print(Press_Time);
  //Serial.print(" ");
  //Serial.println(Touch_Value);
#endif
}
