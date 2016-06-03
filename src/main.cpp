
#include <ESP8266WiFi.h>
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>
#include <ESP8266WiFiMulti.h>
#include <ESP8266HTTPClient.h>
#include <ESP8266httpUpdate.h>
#include <Ticker.h>

#include "version.h"

ESP8266WiFiMulti WiFiMulti;
Ticker updateCheck;
boolean doUpdateCheck = false;

void enableUpdateCheck() {
  doUpdateCheck = true;
}

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
    Serial.println("BUILD_TAG: "+ String(BUILD_TAG));

    // don't wanna miss a thing... Check every 60 seconds
    updateCheck.attach(60, enableUpdateCheck);
}

void loop() {
    // press nodemcu's flash button
    int flashButtonState = digitalRead(0);
    if (flashButtonState == LOW || doUpdateCheck) {
      Serial.println("Going to update firmware...");
      if((WiFiMulti.run() == WL_CONNECTED)) {

              Serial.println("Update sketch...");
              t_httpUpdate_return ret = ESPhttpUpdate.update("http://www.squix.org/blog/firmware.php?tag=" + String(BUILD_TAG));

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
          doUpdateCheck = false;
      }


}
