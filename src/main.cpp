#include <Wire.h>
#include <ESP8266WiFi.h>          //https://github.com/esp8266/Arduino
//needed for library
#include <DNSServer.h>
#include <ESP8266WebServer.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager


#include <ESP8266WiFiMulti.h>

#include <ESP8266HTTPClient.h>
#include "ESP8266httpUpdate.h"
#include <SSD1306.h>
#include "SSD1306Ui.h"

const char TEST_PROGMEM[] PROGMEM = {
  0x00, 0xFC, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0x1F, 0x00, 0x00, 0x04, 0x00
};

SSD1306   display(0x3c, D3, D4);
String firmwareVersion = "0.0.5";
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

    display.init();
    display.flipScreenVertically();
    display.clear();
    display.setFont(ArialMT_Plain_10);

    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
    pinMode(0, INPUT);
    pinMode(2, INPUT);
}

void loop() {
    // press nodemcu's flash button
    int result0 = digitalRead(0);
    if (result0 == LOW) {
      Serial.println("Current firmware: " + firmwareVersion);
      Serial.println("Going to update firmware...");
      if((WiFiMulti.run() == WL_CONNECTED)) {

//          Serial.println("Update SPIFFS...");
//          t_httpUpdate_return ret = ESPhttpUpdate.updateSpiffs("https://github.com/squix78/esp8266-ci-ota/releases/download/0.0.6/firmware.bin");
//          if(ret == HTTP_UPDATE_OK) {
              Serial.println("Update sketch...");
              t_httpUpdate_return ret = ESPhttpUpdate.update("http://www.squix.org/blog/firmware2.php");

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
