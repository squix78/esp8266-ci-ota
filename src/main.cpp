#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>

String firmwareVersion = "0.0.5";

void setup() {

    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Now starting...");
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();

    //set custom ip for portal
    //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();


    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    Serial.println("Now downloading artefact...");

    Serial.println("Downloaded new version....");
    pinMode(0, INPUT);
    pinMode(2, INPUT);
}

void loop() {
    // press nodemcu's flash button
    int result0 = digitalRead(0);
    if (result0 == LOW) {
      Serial.println("Current firmware: " + firmwareVersion);
      Serial.println("Going to update firmware...");
      delay(2000);
      ESPhttpUpdate.update("github.com", 80, "/squix78/esp8266-ci-ota/releases/download/0.0.5/firmware.bin");
      Serial.println("Updated firmware....");
    }

}
