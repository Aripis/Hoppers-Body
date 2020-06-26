#include "ESPAsyncWebServer.h"
#include "WiFi.h"
#include <Arduino.h>

// Credentials
const char *ssid = "MyHopperServer";
const char *password = "rootisMyPass";

// AsyncWebServer port 80
AsyncWebServer server(80);

// HTTP request
String header;
double messured_weight = 0;

String getWeight() {
    // get weight;

    for (int i = 0; i < 5; ++i) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
    messured_weight++;
    return String(messured_weight);
}

void setup() {
    // debugging stuff [DS]
    Serial.begin(115200);
    Serial.println();

    // DS
    Serial.println("Setting Access Point...");

    WiFi.softAP(ssid, password);

    IPAddress IP = WiFi.softAPIP();

    // DS
    Serial.print("AP IPAddress: ");
    Serial.println(IP);

    server.on("/weight", HTTP_GET, [](AsyncWebServerRequest *request) {
        request->send_P(200, "text/plain", getWeight().c_str());
    });

    // server start
    server.begin();
}

void loop() {
    //
}