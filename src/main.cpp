
#include "MyESP.hpp"
#include "ThingSpeak.h"
#include "Motor.hpp"

MyMotor MyESP::myMotor;
MyESP myESP;
int didPageStart = 0;

void setup() {
	myESP.startWiFi();

	if (myESP.doesPushButtonPrest())
	{
		myESP.startPage();
		myESP.blinkFast();
		didPageStart = 1;
	}
	else
	{
		if (myESP.checkIfWatering())
		{
			myESP.watering();
			myESP.saveWateringTime();
			myESP.saveDataToThinkSpeak();
			myESP.writeLastWateringH();
		} else
		{
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

