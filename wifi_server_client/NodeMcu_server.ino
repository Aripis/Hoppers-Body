#include <WiFi.h>
#include <WebServer.h>

// SSID & Password

const char* ssid = "Hoppy32_1";
const char* password = "parjola33";

// IP Address

IPAddress local_ip(192,168,1,1);
IPAddress gateway(198,168,1,1);
IPAddress subnet(255,255,255,0);

WebServer server(80);


void setup() {
  Serial.begin(115200);

  
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);
  
  server.begin();
  Serial.println("HTTP server started");
  
  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  server.handleClient();
  digitalWrite(LED_BUILTIN, HIGH);
  delay(200);
  digitalWrite(LED_BUILTIN, LOW);

  
}