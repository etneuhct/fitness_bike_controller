#include <ESP8266WiFi.h>
#include <WiFiUdp.h>
#include <ESP8266HTTPClient.h>

const char *ssid     = "****";
const char *password = "****";
const char *bike_url = "***";
int digitalPin = 16;
int count = 0;
int activated = 0;

WiFiClient client;

void setup(){
  Serial.begin(115200);
  pinMode(digitalPin, OUTPUT);

  WiFi.begin(ssid, password);

  while ( WiFi.status() != WL_CONNECTED ) {
    delay ( 500 );
    Serial.print ( "." );
  }
}

void loop() {

  int val = digitalRead(digitalPin);
  if (val == HIGH) {
    if (count == 3) {
      if (activated == 1) {
        sendSecondes();
        count = 0;
      }
      else {
        activated = 1;
        count = 0;
      }
    }
    else if (count > 0 & count < 3) {

      count += 1;
    }
  }
  else {
    count = 1;
    digitalWrite(digitalPin, HIGH);
  }
}

void sendSecondes() {
  HTTPClient http;
  http.begin(client, bike_url);
  http.addHeader("Content-Type", "application/json");
  http.POST("");
  http.end();
}
