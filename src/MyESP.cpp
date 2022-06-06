#include "MyESP.hpp"
#include <ESP8266WiFi.h>

MyESP::MyESP()
{
  pinMode(LED_BUILTIN, OUTPUT);
  analogWrite(LED_BUILTIN, 1024);
  measuer5minuts.attach(300, goSleep);
  EEPROM.begin(EEPROM_SIZE);
  time_water = EEPROM.read(0);
  h_water = EEPROM.read(1);
  act_line = EEPROM.read(299);
  Serial.begin(115200);
  delay(100);
  pinMode(pushButton,  INPUT_PULLUP  );
  pinMode(zapatka,  INPUT_PULLUP);
  ticker.attach(0.6, tick);
  czas = "";
}


MyESP::~MyESP() {}

int MyESP::doesPushButtonPrest()
{
 return digitalRead(pushButton) == 0;
}

void MyESP::blinkFast()
{
	ticker.detach();
	ticker.attach(0.1, tick);
}

int MyESP::startWiFi()
{
  WiFi.begin(ssid, password);
  Serial.println("Connecting");
  while(WiFi.status() != WL_CONNECTED) { 
        delay(500);
        Serial.print(".");
  }
  Serial.println("");
  Serial.print("Connected to WiFi network with IP Address: ");
  Serial.println(WiFi.localIP());
  czas = getDateAndTime();
  return 1;
}

String MyESP::getDateAndTime()
{

    const char *host = "http://worldtimeapi.org/api/timezone/Europe/Warsaw";
    HTTPClient http; 
    http.begin(host);
  int httpCode = http.GET();            //Send the request
  String payload;
//  while (httpCode != 200)
//  {
         payload = http.getString();    //Get the response payload from server
  //       nCon++;
         delay(100);
  //       if (nCon > 10)
  //       {
   //     ESP.deepSleep(60*60e6);
    //         return -1;
    //     }
 // }
  if(httpCode == 200)
  {
        const size_t capacity = JSON_OBJECT_SIZE(15) + 350;
        DynamicJsonDocument doc(capacity);
        deserializeJson(doc, payload);
        String out = doc["datetime"]; // "2020-04-23T12:18:56.028849+02:00"
        return out;
  }
  String er = "-1";
  return er;
}

int MyESP::setStopWateringTime()
{
	ticker.detach();
	analogWrite(LED_BUILTIN, 1020);
	ticker.attach(time_water, motorStop);
	return 0;
}

void MyESP::watering()
{
	setStopWateringTime();
	startWatering();
			saveWateringTime();
			saveDataToThinkSpeak();
			writeLastWateringH();
	while(1)
	{
		if( !digitalRead(zapatka))
		{
			motorStop();
			break;
		}	
		delay(100);
	}
}


void MyESP::startWatering(){
	myMotor.startWatering();
}

void MyESP::saveWateringTime()
{
  for(int i = 0; i < 20; i++)
  {
    EEPROM.write(20*act_line + (i+2), czas[i]);
    //delay(10);
    EEPROM.commit();
  }
    act_line++;
    if (act_line > 9) act_line = 0;
  EEPROM.write(299, act_line);
      EEPROM.commit();
    
}

void MyESP::writeLastWateringH()
{

    EEPROM.write(230, getH());
      EEPROM.commit();
}

int MyESP::readLastWateringH()
{
   return EEPROM.read(230);
}

int MyESP::getH()
{
	int posTime = czas.indexOf("T");
 	return (czas[posTime + 1] - '0') * 10 + (czas[posTime+2] - '0');
}

int MyESP::checkIfWatering()
{
  int z[8];
 int czy_podlewac = 0;
for (int i = 0; i < 8; i++)
{
    z[i] = readEEPROM(350 + i);
    if (z[i] == getH() and z[i] != readLastWateringH()) czy_podlewac = 1;
}
return czy_podlewac;
}

int MyESP::readEEPROM(int place)
{
	return EEPROM.read(place);
}

void MyESP::startPage()
{
	page = load_page();
	server.on("/", [&](){
	    server.send(200, "text/html", page);
	});
server.on("/act", [&](){
     int r[8] = {100, 100, 100, 100, 100, 100, 100, 100};
     int k = 0;
     for (int i = 0 ; i < 25; i++)
     {
         if (k < 8)
         {
            if (server.arg("text" + String(i)) == String(i))
            {
                if (i == 24)
                {
                    r[k] = 0;
                } else
                {
                     r[k] = i;
                }
                k++;
            }
         }
     }
     int czy_commit = 0;
     if(r[0] != 100)
     {
            for (int i = 0; i < 8; i++)
            {
            EEPROM.write(350 + i, r[i]);
          }
	  czy_commit = 1;
     }
    String time_watering = server.arg("czas");
    int s =  time_watering.substring(0, 2).toInt();
    if (s > 0)
    {
        EEPROM.write(0, s);
	  czy_commit = 1;
    }
     if (czy_commit)
     {
       EEPROM.commit();
     }
     page = load_page();
     server.send(200, "text/html", page);
     //delay(1000);
    });
 server.on("/res", [&](){
     server.send(200, "text/html", page);
     //delay(1000);
     ESP.reset();
    });

server.begin();

}

void MyESP::handle()
{
	server.handleClient();
}

void MyESP::saveDataToThinkSpeak()
{

	WiFiClient  client;
	ThingSpeak.begin(client);
	 #define SECRET_CH_ID1 1111943                                 // replace 0000000 with your channel number
	 #define SECRET_WRITE_APIKEY1 "G59OSUJY626RRWWJ"                           // replace XYZ with your channel write API Key
	unsigned long myChannelNumber = SECRET_CH_ID1;
	const char * myWriteAPIKey = SECRET_WRITE_APIKEY1;

	int httpCode = ThingSpeak.writeField(myChannelNumber, 1,time_water , myWriteAPIKey);

	 if (httpCode == 200) {
	      Serial.println("Channel write successful.");
	 }
	 else {
	       Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
	 }
	client.stop();
}

void MyESP::saveTempToThinkSpeak(float temp)
{

	WiFiClient  client;
	ThingSpeak.begin(client);
	 #define SECRET_CH_ID 1189056                                 // replace 0000000 with your channel number
	 #define SECRET_WRITE_APIKEY "IHXD144KFX8UOY4B"                           // replace XYZ with your channel write API Key
	unsigned long myChannelNumber = SECRET_CH_ID;
	const char * myWriteAPIKey = SECRET_WRITE_APIKEY;

	int httpCode = ThingSpeak.writeField(myChannelNumber, 1, temp , myWriteAPIKey);

	 if (httpCode == 200) {
	      Serial.println("Temperatue write successful.");
	 }
	 else {
	       Serial.println("Problem writing to channel. HTTP error code " + String(httpCode));
	 }
	client.stop();
}

MyMotor::MyMotor(int STBY, int PWMA, int AIN1, int AIN2) 
	: STBY_(STBY), PWMA_(PWMA), AIN1_(AIN1), AIN2_(AIN2)
{
    pinMode(STBY_, OUTPUT);
    pinMode(PWMA_, OUTPUT);
    pinMode(AIN1_, OUTPUT);
    pinMode(AIN2_, OUTPUT);

    digitalWrite(AIN1_, HIGH);
    digitalWrite(AIN2_, LOW);
    analogWrite(PWMA_, 1023);
    digitalWrite(STBY_, LOW);
}

void MyMotor::startWatering()
{
    Serial.println("Start watering");
    digitalWrite(STBY_, HIGH);
}

void MyMotor::stopWatering()
{
    digitalWrite(STBY_, LOW);
    Serial.println("Stop watering");
}
