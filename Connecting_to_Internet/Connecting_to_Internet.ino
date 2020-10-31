#include<ESP8266WiFi.h>

const char* ssid = "Redmi";
const char* pass = "12345678";

const char* server = "api.thingspeak.com";
const char* getlink = "http://api.thingspeak.com/channels/797884/feeds/last.txt";
WiFiClient client;
 
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
delay(1000);
Serial.print("Connecting to ");
Serial.println(ssid);
WiFi.begin(ssid,pass);

while(WiFi.status() != WL_CONNECTED)
{
  delay(500);
  Serial.print("..");
}

Serial.println();
Serial.print("Connected to ");
Serial.println(ssid);
delay(1500);
}

void loop() {
  // put your main code here, to run repeatedly:

}
