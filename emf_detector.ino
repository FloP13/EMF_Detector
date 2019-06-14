/****Includes****/
#include <ESP8266WiFi.h>          // https://github.com/esp8266/Arduino
#include <WiFiClient.h>
#include <DNSServer.h>            // Local DNS Server used for redirecting all requests to the &onfiguration portal
#include <ESP8266WebServer.h>     // Local WebServer used to serve the configuration portal
#include <WiFiManager.h>          // https://github.com/tzapu/WiFiManager WiFi Configuration Magic
#include <ESP8266mDNS.h>          // Allow custom URL
#include <Adafruit_NeoPixel.h>
#include "pitches.h"


// typedef enum color_e {RED, GREEN, YELLOW, OFF} color_t;
// const int RGBpins[] = {D7, D5, D6};
const int ledsPin = D6;
const int buzerPin = D1;
int senseLimit = 15; // raise this number to decrease sensitivity (up to 1023 max)
// notes for the buzzer:
// notes in the melody:
int melody[] = { NOTE_C1, NOTE_C2, NOTE_C3, NOTE_C4, NOTE_C5, NOTE_C6, NOTE_C7, NOTE_C8 };

/*****Initialization*****/
ESP8266WebServer server(80);
const char *ssid = "EMFSensor";
Adafruit_NeoPixel strip = Adafruit_NeoPixel(8, ledsPin, NEO_GRB + NEO_KHZ800);


/****Utils****/
void colorWipe(uint32_t color, int wait) {
  for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, color);         //  Set pixel's color (in RAM)
    strip.show();                          //  Update strip to match
    delay(wait);                           //  Pause for a moment
  }
}


/*****WebPage*****/
// Warning: only use simple quotes in the html (no double)
String rootHTML = "\
<!doctype html> <html> <head> <title> EMF Sensor </title> </head> <body>\
<br> <br> <span>EMF : <b id=\"ev\">emf_val<b/></span> <br> <br> </body>\
<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.4.1/jquery.min.js\"></script>\
<script>setInterval( () => { $.ajax('/emf_val', { success: (d, ts, j) => { $('#ev').html(d.emf) } }) }, 900);</script>\
</html>\
";


void getEmfVal() {
  int meanGet = 20;
  int emf_val = 0;
  for (int i=0; i<meanGet; i++) emf_val += analogRead(A0);
  emf_val = emf_val / meanGet;
  emf_val = constrain(emf_val, 1, senseLimit);  // turn any reading higher than the senseLimit value into the senseLimit value
  emf_val = map(emf_val, 1, senseLimit, 1, 1023);  // remap the constrained value within a 1 to 1023 range
  ledsHandling(emf_val);
  // for (int i=0; i<3; i++) digitalWrite(RGBpins[i], LOW);
  // if (emf_val <= 342) digitalWrite(RGBpins[1], HIGH);
  // if (emf_val > 342 && emf_val <= 684) digitalWrite(RGBpins[2], HIGH);
  // if (emf_val > 684) digitalWrite(RGBpins[0], HIGH);
  Serial.println(emf_val);
  String answer = "{\"emf\": \"" + String(emf_val) + "\"}";
  server.send(200, "application/json", answer);
  int buzzer_sound = map(emf_val, 1, 1023, 0, 7);
  tone(buzerPin, melody[buzzer_sound], 100);
}


String getHTML() {
  return rootHTML;
}


void handleRoot() {
    server.send(200, "text/html", getHTML());
}



/****LEDs****/
void ledsHandling (int emf_val) {
  colorWipe(strip.Color(0, 0, 0) , 0);
  if (emf_val <= 128) {
    strip.setPixelColor(0, 0, 255, 0);
  }
  if (emf_val > 128 && emf_val <= 256) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
  }
  if (emf_val > 256 && emf_val <= 384) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
  }
  if (emf_val > 384 && emf_val <= 512) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
    strip.setPixelColor(3, 255, 255, 0);
  }
  if (emf_val > 512 && emf_val <= 640) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
    strip.setPixelColor(3, 255, 255, 0);
    strip.setPixelColor(4, 255, 223, 0);
  }
  if (emf_val > 640 && emf_val <= 768) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
    strip.setPixelColor(3, 255, 255, 0);
    strip.setPixelColor(4, 255, 223, 0);
    strip.setPixelColor(5, 255, 167, 0);
  }
  if (emf_val > 768 && emf_val <= 896) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
    strip.setPixelColor(3, 255, 255, 0);
    strip.setPixelColor(4, 255, 223, 0);
    strip.setPixelColor(5, 255, 167, 0);
    strip.setPixelColor(6, 255, 80, 0);

  }if (emf_val > 896) {
    strip.setPixelColor(0, 0, 255, 0);
    strip.setPixelColor(1, 167, 255, 0);
    strip.setPixelColor(2, 223, 255, 0);
    strip.setPixelColor(3, 255, 255, 0);
    strip.setPixelColor(4, 255, 223, 0);
    strip.setPixelColor(5, 255, 167, 0);
    strip.setPixelColor(6, 255, 80, 0);
    strip.setPixelColor(7, 255, 0, 0);  
  }
  strip.show(); // on affiche
  strip.setBrightness(50); 
}


/****Setups****/
void setupWifi() {
    // WiFiManager
    WiFiManager wifiManager;

    // reset saved settings -- Flush flash
    // wifiManager.resetSettings();

    // set callback that gets called when connecting to previous WiFi fails, and enters Access Point mode
    // wifiManager.setAPCallback(configModeCallback);

    // fetches ssid and pass from eeprom and tries to connect
    // if it does not connect it starts an access point with the specified name
    // and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect(ssid);

    // might seem redundant but it's not printed the 1st time:
    Serial.println("local ip");
    Serial.println(WiFi.localIP());
}


void setupServer() {
    server.on("/", handleRoot);
    server.on("/emf_val", getEmfVal);
    server.begin();
    Serial.println("HTTP server started");
}


void setupMDNS() {
    // Add service to MDNS-SD to access the ESP with the URL http://<ssid>.local
    if (MDNS.begin(ssid)) {
        Serial.print("MDNS responder started as http://");
        Serial.print(ssid);
        Serial.println(".local");
    }
    MDNS.addService("http", "tcp", 8080);
}


/****MAIN CODE****/
void setup() {
  pinMode(buzerPin, OUTPUT);
  strip.begin();
  strip.show(); // Initialise toute les led à 'off'
  // for (int i=0; i<3; i++) pinMode(RGBpins[i], OUTPUT);
  Serial.begin(115200);
  Serial.println("Starting WiFi.");
  setupWifi();
  setupServer();
  setupMDNS();
  Serial.println("Setup OK.");
}


void loop() {
  server.handleClient();
}
