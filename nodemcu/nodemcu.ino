#include <MQ2.h>
#include<WiFi.h>
#include <ESP8266WiFi.h>
int sensor = A0;
MQ2 mq2(sensor);
float lpg,co,smoke;


String apiWritekey = "8QDL8CJU6A6VI4PN"; // replace with your THINGSPEAK WRITEAPI key here
const char* ssid = "Redmi"; // your wHifi SSID name
const char* password = "12345678" ;// wifi pasword
 
const char* server = "api.thingspeak.com";
WiFiClient client;
 
void setup() {
   pinMode(sensor,INPUT);
  Serial.begin(115200);
  WiFi.disconnect();
  delay(10);
  WiFi.begin(ssid, password);
 
  Serial.println();
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
 
  WiFi.begin(ssid, password);
 
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("NodeMcu connected to wifi...");
  Serial.println(ssid);
  Serial.println();
}
 
void loop() {
 
  lpg = mq2.readLPG();
  co = mq2.readCO();
  smoke = mq2.readSmoke();
  
  
  if (client.connect(server,80))
  {  
    String tsData = apiWritekey;
           tsData +="&field1=";
           tsData += String(lpg);
           tsData +="&field2=";
           tsData += String(co);
           tsData +="&field3=";
           tsData += String(smoke);
           tsData += "\r\n\r\n";
 
     client.print("POST /update HTTP/1.1\n");
     client.print("Host: api.thingspeak.com\n");
     client.print("Connection: close\n");
     client.print("X-THINGSPEAKAPIKEY: "+apiWritekey+"\n");
     client.print("Content-Type: application/x-www-form-urlencoded\n");
     client.print("Content-Length: ");
     client.print(tsData.length());
     client.print("\n\n");  // the 2 carriage returns indicate closing of Header fields & starting of data
     client.print(tsData);
 
     Serial.print("LPG: ");
     Serial.print(lpg);
     Serial.print("  CO: ");
     Serial.print(co);
     Serial.print("  Smoke: ");
     Serial.println(smoke);
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(15000);
}
