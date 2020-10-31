#include <dht.h>


#include <ESP8266WiFi.h>
#include <Wire.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_BMP085_U.h>

Adafruit_BMP085_Unified bmp = Adafruit_BMP085_Unified(10085);

String apiKey = "1VKYEOE55WFL3TOM";                                     
const char* ssid = "Redmi";                                  
const char* password = "12345678";                             

const char* server = "api.thingspeak.com";
#define DHTPIN D8 

dht DHT;
WiFiClient client;

int sensorPin = A0;
int sensorValue = 0;  

void setup() {
pinMode(DHTPIN, INPUT);
pinMode(sensorPin, INPUT);

Serial.begin(115200);
delay(10);



WiFi.begin(ssid, password);

Serial.println();
Serial.println();
Serial.print("Connecting to ");
Serial.println(ssid);
Serial.print("..........");
Serial.println();
WiFi.begin(ssid, password);

while (WiFi.status() != WL_CONNECTED) {
delay(500);

}
Serial.println("WiFi connected");
Serial.println();

}


void loop() {



int dht_out = DHT.read22(DHTPIN);

Serial.print("Temperature: ");
Serial.print(DHT.temperature);
Serial.print(" degrees Celcius ");
Serial.println();

Serial.print("Humidity: ");
Serial.print(DHT.humidity);
Serial.print("%");
Serial.println();


//For Dew Point Temperature
double gamma = log(DHT.humidity/100) + ((17.62*DHT.temperature) / (243.5+DHT.temperature));
double dp = 243.5*gamma / (17.62-gamma);

Serial.print("Dew point: ");
Serial.print(dp);
Serial.print(" degrees Celcius ");
Serial.println();



if(!bmp.begin()) {
Serial.print("Failed to read from BMP sensor!!");
while(1);
}

sensors_event_t event;
bmp.getEvent(&event);

Serial.print("Pressure:         ");
Serial.print(event.pressure);
Serial.println(" hPa");

sensorValue = analogRead(sensorPin);
sensorValue = constrain(sensorValue, 150, 850); 
sensorValue = map(sensorValue, 150, 850, 0, 1023); 
Serial.print("Light intensity:  ");
Serial.println(sensorValue);
delay(100);




if (client.connect(server,80)) { // "184.106.153.149" or api.thingspeak.com
String postStr = apiKey;
postStr +="&field1=";
postStr += String(DHT.temperature);
postStr +="&field2=";
postStr += String(DHT.humidity);
postStr +="&field3=";
postStr += String(dp);
postStr +="&field4=";
postStr += String(event.pressure);
postStr +="&field5=";
postStr += String(sensorValue);
postStr += "\r\n\r\n\r\n\r\n\r\n\r\n\r\n\r\n";

client.print("POST /update HTTP/1.1\n");
client.print("Host: api.thingspeak.com\n");
client.print("Connection: close\n");
client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
client.print("Content-Type: application/x-www-form-urlencoded\n");
client.print("Content-Length: ");
client.print(postStr.length());
client.print("\n\n\n\n\n\n\n\n");
client.print(postStr);



}
client.stop();


delay(20000);
}
