#pragma once 
//#include "Arduino.h"
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <time.h>
#include <EEPROM.h>
#include <Wire.h>
#include <Ticker.h>
#include <DNSServer.h>
//#include <WiFiManager.h>
#include <ESP8266HTTPClient.h>
#include <ArduinoJson.h>
#include "html.h"
#include "ThingSpeak.h"

#define EEPROM_SIZE 512
class MyMotor {
	int STBY_ = 12; //standby
	//Motor A
	int PWMA_ = 5; //Speed control
	int AIN1_ = 14; //Direction
	int AIN2_ = 4; //Direction
	int time_wait = 0;
	Ticker d;
	static void wait()
	{
		static int time_elaps = 0;
		time_elaps++;
	}
public:
	MyMotor(int STBY = 12, int PWMA = 5, int AIN1 = 14, int AIN2 = 4);
	void startWatering();
	void stopWatering();
};

class MyESP {
protected:
	char akt_czas[10];
	int time_water;
	int h_water;
	String page = "";
	String pageIP = "";
	//int ledPin = 2; // onboard LED
	int pushButton = 13; // push button
	int IPButton = 14; // button to show IP
	int act_line;
const char* ssid = "Vectra-WiFi-260244";//type your ssid
const char* password = "vnet278750378";//type your password
//const char* ssid = "TFO-WiFi";//type your ssid
//const char* password = "accessok";//type your password
	ESP8266WebServer server{80};
	Ticker measuer5minuts;
	Ticker ticker;
	String czas;
        //WiFiManager wifiManager;
	static void motorStop()
	{
		analogWrite(LED_BUILTIN, 1024);
		myMotor.stopWatering();
		Serial.println("I'm going sleep to 1h");
        	//ESP.deepSleep(60*60e6);
		goSleep();
	}
	static void tick()
	{
		static int state = 1;
	  if (state)
	  {
		  analogWrite(LED_BUILTIN, 1010);
	  } else
	  {
		  analogWrite(LED_BUILTIN, 1024);
	  }
	  state = !state;

	}
	static void goSleep()
	{
	   Serial.println("I going to sleep for 20 min");
	   ESP.deepSleep(20*60e6);
	}
    String getDateAndTime();
public:
    void blinkFast();
    static MyMotor myMotor;
    virtual int readEEPROM(int);
    int getH();
    int doesPushButtonPrest();
    virtual int startWiFi();
    MyESP();
    int returnZero();
    void watering();
    virtual int setStopWateringTime();
    void startWatering();
    void saveWateringTime();
    int checkIfWatering();
    void startPage();
    void handle();
void saveDataToThinkSpeak();
void saveTempToThinkSpeak(float temp);
void writeLastWateringH();
int readLastWateringH();
    virtual ~MyESP();
};


