#include <Wire.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include "ESP8266httpUpdate.h"



String firmwareVersion = "0.0.5";
String buildTimeStamp = String(BUILD_TIMESTAMP);

ESP8266WiFiMulti WiFiMulti;

void setup() {

    // put your setup code here, to run once:
    Serial.begin(115200);
    Serial.println("Now starting...");
    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();

    wifiManager.autoConnect("AutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();
    Serial.println("Started..");

    Serial.println("Unix time stamp: " + buildTimeStamp);
}

void loop() {
    // press nodemcu's flash button
    int result0 = digitalRead(0);
    if (result0 == LOW) {
      Serial.println("Current firmware: " + firmwareVersion);
      Serial.println("Unix time stamp: " + buildTimeStamp);
      Serial.println("Going to update firmware...");
      if((WiFiMulti.run() == WL_CONNECTED)) {

//          Serial.println("Update SPIFFS...");
//          t_httpUpdate_return ret = ESPhttpUpdate.updateSpiffs("https://github.com/squix78/esp8266-ci-ota/releases/download/0.0.6/firmware.bin");
//          if(ret == HTTP_UPDATE_OK) {
              Serial.println("Update sketch...");
              t_httpUpdate_return ret = ESPhttpUpdate.update("http://www.squix.org/blog/firmware.php?timestamp=" + String(BUILD_TIMESTAMP));

              switch(ret) {
                  case HTTP_UPDATE_FAILED:
                      Serial.printf("HTTP_UPDATE_FAILD Error (%d): %s", ESPhttpUpdate.getLastError(), ESPhttpUpdate.getLastErrorString().c_str());
                      break;

                  case HTTP_UPDATE_NO_UPDATES:
                      Serial.println("HTTP_UPDATE_NO_UPDATES");
                      break;

                  case HTTP_UPDATE_OK:
                      Serial.println("HTTP_UPDATE_OK");
                      break;
              }
          }
      }
//    }

}
