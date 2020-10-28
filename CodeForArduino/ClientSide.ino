#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <Arduino.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>

#ifndef STASSID
#define STASSID "ESPap"
#define STAPSK  "thereisnospoon"
#endif

const char* ssid     = STASSID;
const char* password = STAPSK;

IPAddress staticIP(192,168,4,22);
//
IPAddress gateway(192,168,4,9);
//
IPAddress subnet(255,255,255,0);

const char* host = "192.168.4.1";
const uint16_t port = 80;

void setup() {
  Serial.begin(115200);

	//Connect to WiFi
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void loop() {
  Serial.print("connecting to ");
  Serial.print(host);
  Serial.print(':');
  Serial.println(port);

 HTTPClient http;
   WiFiClient client;
   String str;
   str="data=Sample%20Data%20Print";
    Serial.print("[HTTP] begin...\n");
    if (http.begin(client, "http://192.168.4.1/data?"+str)) {  


      Serial.print("[HTTP] GET...\n");
      int httpCode = http.GET();

      if (httpCode > 0) {
        Serial.printf("[HTTP] GET... code: %d\n", httpCode);

        if (httpCode == HTTP_CODE_OK || httpCode == HTTP_CODE_MOVED_PERMANENTLY) {
          String payload = http.getString();
          Serial.println(payload);
        }
      } else {
        Serial.printf("[HTTP] GET... failed, error: %s\n", http.errorToString(httpCode).c_str());
      }

      http.end();  
}
  
}
