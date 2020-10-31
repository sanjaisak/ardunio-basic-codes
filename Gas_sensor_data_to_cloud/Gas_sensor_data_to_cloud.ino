#include <ESP8266WiFi.h>;
 
#include <WiFiClient.h>;
 
#include <ThingSpeak.h>;
#include <MQ2.h>
#define SENSOR A0
MQ2 mq2(SENSOR);
 
const char* ssid = "Redmi"; //Your Network SSID
 
const char* password = "12345678"; //Your Network Password
 
long sensorValue;
 

 
 
 
WiFiClient client;
 
unsigned long myChannelNumber = 797722; //Your Channel Number (Without Brackets)
 
const char * myWriteAPIKey = "PWY6E74HG4A471AC"; //Your Write API Key
 
void setup()
 
{
mq2.begin();
Serial.begin(115200);
 
delay(10);
 
// Connect to WiFi network
 
WiFi.begin(ssid, password);
while(WiFi.status()!= WL_CONNECTED)
{
  Serial.println("Connecting");
  Serial.print(".");
  Serial.println();
  delay(1000);
}
 
 
 
ThingSpeak.begin(client);
 
}
 

float lpg,co,smoke; 
 
void loop()
 
{
 
lpg = mq2.readLPG();
co = mq2.readCO();
smoke = mq2.readSmoke();

Serial.print("LPG = ");
Serial.print(lpg);
Serial.println("ppm");
Serial.print("CO = ");
Serial.print(co);
Serial.println("ppm");
Serial.print("Smoke = ");
Serial.print(smoke);
Serial.println("ppm");
Serial.println();
delay(100);
 
ThingSpeak.writeField(myChannelNumber, 1,lpg, myWriteAPIKey); //Update in ThingSpeak
ThingSpeak.writeField(myChannelNumber, 2,co, myWriteAPIKey); 
ThingSpeak.writeField(myChannelNumber, 3,smoke, myWriteAPIKey); 
 
delay(100);
 
}
