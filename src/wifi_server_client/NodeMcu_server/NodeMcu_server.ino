#include <WiFi.h>
#include <WebServer.h>

// SSID & Password
const char* ssid = "Hoppy";
const char* password = " ";

// IP Address
IPAddress local_ip(192,168,1,1);
IPAddress gateway(198,168,1,1);
IPAddress subnet(255,255,255,0);
WebServer server(80);

void blink(){
  for (int i = 0; i < 10; ++i){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void setup() {
  Serial.begin(115200);
  blink();
  WiFi.softAP(ssid, password);
  WiFi.softAPConfig(local_ip, gateway, subnet);
  delay(100);

  server.begin();
  Serial.println("HTTP server started");

  pinMode(LED_BUILTIN, OUTPUT);
}


void loop() {
  server.handleClient();

}
