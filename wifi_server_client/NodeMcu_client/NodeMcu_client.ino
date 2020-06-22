// Henry's Bench
//Checking to ensure you can connect ESP-12E to a router
#include <WiFi.h>
    
const char* ssid     = "Hoppy";
const char* password = " ";     

int wifiStatus;

void blink(){
  for (int i = 0; i < 10; ++i){
    digitalWrite(LED_BUILTIN, HIGH);
    delay(100);
    digitalWrite(LED_BUILTIN, LOW);
    delay(100);
  }
}

void setup() {
    
    Serial.begin(115200);\
    delay(200);
    
    // We start by connecting to a WiFi network
//    while (WiFi.status() != WL_CONNECTED) {
    blink();
    Serial.println();
    Serial.println();
    Serial.print("Your are connecting to: ");
    Serial.println(ssid);
    Serial.print("With: ");
    Serial.println(password);

    WiFi.begin(ssid, password);
    
    for (int i = 0; WiFi.status() != WL_CONNECTED; ++i) {
        delay(500);
        Serial.print(".");
        if (i == 10) {
            break;
        } 
    }
//    }
}   
    
void loop() {
    wifiStatus = WiFi.status();

    if(wifiStatus == WL_CONNECTED){
        blink();
        Serial.println("");
        Serial.println("Your ESP is connected!");  
        Serial.println("Your IP address is: ");
        Serial.println(WiFi.localIP());  
    }
    else{
        Serial.println("");
        Serial.println("WiFi not connected");
    }
    delay(1000); // check for connection every once a second

}
