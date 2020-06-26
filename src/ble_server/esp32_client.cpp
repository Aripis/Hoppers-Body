#include "HTTPClient.h"
#include "WiFi.h"
#include <Arduino.h>

// Credentials
const char *ssid = "MyHopperServer";
const char *password = "rootisMyPass";

const char *serverNameWeight = "http://192.168.4.1/weight";

String weight;
unsigned long previousMillis = 0;
const long interval = 5000;

String httpGETRequest(const char *serverName) {
    HTTPClient http;

    // Your IP address with path or Domain name with URL path
    http.begin(serverName);

    // Send HTTP POST request
    int httpResponseCode = http.GET();

    String payload = "--";

    if (httpResponseCode > 0) {
        Serial.print("HTTP Response code: ");
        Serial.println(httpResponseCode);
        payload = http.getString();
    } else {
        Serial.print("Error code: ");
        Serial.println(httpResponseCode);
    }
    // Free resources
    http.end();

    return payload;
}

void setup(void) {
    Serial.begin(115200);

    WiFi.begin(ssid, password);
    Serial.print("Connecting to ");
    Serial.print(ssid);
    Serial.println("...");
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.println(".");
    }
    Serial.println();
    Serial.print("Connected to ");
    Serial.print(ssid);
    Serial.print(" with IP: ");
    Serial.println(WiFi.localIP());
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        if (WiFi.status() == WL_CONNECTED) {
            weight = httpGETRequest(serverNameWeight);
            Serial.println("Curr weight: " + weight);
            previousMillis = currentMillis;
        } else {
            Serial.println("WiFi disconnected");
        }
    }
}
