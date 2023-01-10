void handle_OnConnect() {
  Serial.println("GPIO4 Status: OFF | GPIO5 Status: OFF");
  server.send(200, "text/html", SendHTML(1,1)); 
}



String SendHTML(uint8_t led1stat,uint8_t led2stat){
  String ptr = "<!DOCTYPE html> <html>\n";
  ptr +="<head><meta name=\"viewport\" content=\"width=device-width, initial-scale=1.0, user-scalable=no\">\n";
  ptr +="<title>Rheinturm</title>\n";
  ptr +="<style>html { font-family: Helvetica; display: inline-block; margin: 0px auto; text-align: center;}\n";
  ptr +="body{margin-top: 50px;} h1 {color: #444444;margin: 50px auto 30px;} h3 {color: #444444;margin-bottom: 50px;}\n";
  ptr +=".button {display: block;width: 80px;background-color: #3498db;border: none;color: white;padding: 13px 30px;text-decoration: none;font-size: 25px;margin: 0px auto 35px;cursor: pointer;border-radius: 4px;}\n";
  ptr +=".button-on {background-color: #3498db;}\n";
  ptr +=".button-on:active {background-color: #2980b9;}\n";
  ptr +=".button-off {background-color: #34495e;}\n";
  ptr +=".button-off:active {background-color: #2c3e50;}\n";
  ptr +="p {font-size: 14px;color: #888;margin-bottom: 10px;}\n";
  ptr +="</style>\n";
  ptr +="</head>\n";
  ptr +="<body>\n";
  ptr +="<h1>Rheinturm</h1>\n";
  ptr +="<h3>Konfiguration</h3>\n";
  ptr +="<br>";
  char myHex[10] = "";
  ptr += "CLOCK_COLOR_SEKUNDEN_EINER: ";
  ptr += itoa(CLOCK_COLOR_SEKUNDEN_EINER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_SEKUNDEN_ZEHNER: ";
  ptr += itoa(CLOCK_COLOR_SEKUNDEN_ZEHNER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_MINUTEN_EINER: ";
  ptr += itoa(CLOCK_COLOR_MINUTEN_EINER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_MINUTEN_ZEHNER: ";
  ptr += itoa(CLOCK_COLOR_MINUTEN_ZEHNER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_STUNDEN_EINER: ";
  ptr += itoa(CLOCK_COLOR_STUNDEN_EINER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_STUNDEN_ZEHNER: ";
  ptr += itoa(CLOCK_COLOR_STUNDEN_ZEHNER,myHex,16);
  ptr += "<br>";
  ptr += "CLOCK_COLOR_OFF: ";
  ptr += itoa(CLOCK_COLOR_OFF,myHex,16);
  ptr += "<br>";


   
  ptr +="</body>\n";
  ptr +="</html>\n";
  return ptr;
}