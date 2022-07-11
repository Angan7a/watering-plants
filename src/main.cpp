
#include "MyESP.hpp"
#include <OneWire.h>
#include <DallasTemperature.h>
#include "ThingSpeak.h"


#define ONE_WIRE_BUS 0  // DS18B20 on arduino pin2 corresponds to D4 on physical board
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature DS18B20(&oneWire);
float prevTemp = 0;
const char* server = "api.thingspeak.com";
String apiKey = "IHXD144KFX8UOY4B";



MyMotor MyESP::myMotor;
MyESP myESP;
int didPageStart = 0;


void setup() {
  Serial.begin(115200);
delay(100);
	myESP.startWiFi();
 float temp;
  //char buffer[10];
  DS18B20.requestTemperatures(); 
  temp = DS18B20.getTempCByIndex(0);
 //String tempC = dtostrf(temp, 4, 1, buffer);//handled in sendTemp()
  Serial.print(" Temperature: ");
  Serial.println(temp);
  delay(800);
	myESP.saveTempToThinkSpeak(temp);
  //sendTeperatureTS(temp);

	if (myESP.doesPushButtonPrest())
	{
		myESP.startPage();
		Serial.println("Page started");
		myESP.blinkFast();
		didPageStart = 1;
	}
	else
	{
		if (myESP.checkIfWatering())
		{
			myESP.watering();
		} else
		{
			Serial.println("I'm going sleep to 20 min");
			ESP.deepSleep(20*60e6);
		}
	} 
}

void loop() {
	if( didPageStart )
	{
		myESP.handle();
	}
}

