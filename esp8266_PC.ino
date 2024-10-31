#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <ArduinoJson.h>
#include "config.h"


ESP8266WebServer server(80);

void setup() {

  Serial.begin(115200);
  // Connect to Wi-Fi
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  while (WiFi.status() != WL_CONNECTED) {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");
  Serial.println(WiFi.localIP().toString());
  // Define HTTP endpoints
  server.on("/discover", HTTP_GET, handleDiscover);
  server.on("/toggle_state", HTTP_GET, handleToggle);
  server.on("/forceOff", HTTP_GET, handleForceOff);
  
  // Start server
  server.begin();
  Serial.println("HTTP server started");

  pinMode(buttonPin, OUTPUT);
  
}

void loop() {

  server.handleClient();
}

void handleDiscover() {
  StaticJsonDocument<200> doc;
  doc["name"] = "ESP8266 PC";
  doc["ip_address"] = WiFi.localIP().toString(); // Add the IP address
  doc["mac_address"] = WiFi.macAddress(); // Add the MAC address
  
  JsonArray endpoints = doc.createNestedArray("endpoints");
  endpoints.add("/toggle_state");
  endpoints.add("/forceOff");

  String response;
  serializeJson(doc, response);

  server.send(200, "application/json", response);
}

void handleToggle() {
  digitalWrite(buttonPin, HIGH);
  delay(1000);
  digitalWrite(buttonPin, LOW);
  server.send(200, "text/plain", "PC button has been toggled");
}


void handleForceOff() {
  digitalWrite(buttonPin, HIGH);
  delay(5000);
  digitalWrite(buttonPin, LOW);
  server.send(200, "text/plain", "PC forced OFF");
}
