#include "HTTPClient.h"
#include "WiFi.h"
#include <Arduino.h>
#include <string>

// Credentials
const char *ssid = "MyHopperServer";
const char *password = "rootisMyPass";

const char *serverNameWeight = "http://192.168.4.1/weight";

const long interval = 5000;

String otherWeight, myWeight;

double messured_weight = 0;

unsigned long previousMillis = 0;

unsigned long steps = 0;

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

String getWeight() {
    // get weight;

    for (int i = 0; i < 5; ++i) {
        digitalWrite(LED_BUILTIN, HIGH);
        delay(100);
        digitalWrite(LED_BUILTIN, LOW);
        delay(100);
    }
    messured_weight += 0.5;
    return String(messured_weight);
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

bool isWalkingDualMode() {
    return true;
}

bool isWalkingSingleMode() {
    return false;
}

void loop() {
    unsigned long currentMillis = millis();

    if (currentMillis - previousMillis >= interval) {
        Serial.println("--------------------------------");
        if (WiFi.status() == WL_CONNECTED) {
            Serial.println("Connected to WiFi - dual mode");
            otherWeight = httpGETRequest(serverNameWeight);
            myWeight = getWeight();
            double oW = atof(otherWeight.c_str());
            double mW = atof(myWeight.c_str());
            double currW = oW + mW;
            Serial.print("Curr weight: ");
            Serial.println(currW);

            if (isWalkingDualMode()) {
                steps++;
                Serial.print("Incremented Steps => ");
                Serial.println(steps);
            }

            previousMillis = currentMillis;
        } else {
            Serial.println("WiFi disconnected - switching to single mode");

            previousMillis = currentMillis;
        }
        Serial.println();
        Serial.println("Sending data to Android app...");
    }
}
