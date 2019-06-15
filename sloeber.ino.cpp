#ifdef __IN_ECLIPSE__
//This is a automatic generated file
//Please do not modify this file
//If you touch this file your change will be overwritten during the next build
//This file has been generated on 2019-06-10 17:29:22

#include "Arduino.h"
#include "Arduino.h"
#include <WiFi.h>
#include <WiFiClient.h>
#include <WebServer.h>
#include <ESPmDNS.h>
#include "ArduinoJson.h"
#include "source_sensor/DHT.h"
#include "mqtt/PubSubClient.h"
#include "EEPROM.h"

void writeString(char add, String data) ;
String read_String(char add) ;
void callback(char* topic, byte* payload, unsigned int length) ;
void handleRoot() ;
void responseData() ;
void setupConfigure() ;
void setupWifi() ;
void handleNotFound() ;
void initGPIO() ;
void readParam() ;
void getConfigure();
void getDataSensor();
void setup(void) ;
void runLed() ;
int checkSensor() ;
int checkWifi() ;
void runStateMachine() ;
void runApp() ;
boolean reconnect() ;
void loop(void) ;

#include "web.ino"


#endif
