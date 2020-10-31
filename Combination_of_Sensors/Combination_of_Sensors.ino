#include <Adafruit_Sensor.h>

#include<ESP8266WiFi.h>

#include<MQ2.h>
#include<DHT.h>


int dht_pin = D2;
int gas_pin = A0;
int vib_pin = D4;

MQ2 mq2(gas_pin);
DHT dht(dht_pin, DHT11);
const char *ssid = "Redmi";
const char *password = "12345678";
String apiKey = "ACQD4UQFJWIL3O8O";

const char* server = "api.thingspeak.com";

WiFiClient client;

void setup() {
  // put your setup code here, to run once:
  pinMode(dht_pin,INPUT);
  pinMode(gas_pin, INPUT);
  pinMode(vib_pin, INPUT);
  Serial.begin(115200);
  
  delay(10);
 
  WiFi.begin(ssid,password);

  Serial.print("Connecting to: ");
  Serial.println(ssid);

  while(WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print("*");
  }

  Serial.println("");
  Serial.println("Connected to WiFi");
  Serial.println("");

}

void loop() {
  // put your main code here, to run repeatedly:
  int lpg = mq2.readLPG();
  int co = mq2.readCO();
  int smoke = mq2.readSmoke();

  int temp = dht.readTemperature(dht_pin);
  int hum = dht.readHumidity(dht_pin);

  int vib_value = digitalRead(vib_pin);

  int app_vib_value = !(vib_pin); 
  
  
  if (client.connect(server,80))
  {  
    String tsData = apiKey;
           tsData +="&field3=";
           tsData += String(lpg);
           tsData +="&field4=";
           tsData += String(co);
           tsData +="&field5=";
           tsData += String(smoke);
           tsData +="&field1=";
           tsData += String(temp);
           tsData +="&field2=";
           tsData += String(hum);
           tsData +="&field6=";
           tsData += String(app_vib_value);
           tsData += "\r\n\r\n";
 
    client.print("POST /update HTTP/1.1\n");
    client.print("Host: api.thingspeak.com\n");
    client.print("Connection: close\n");
    client.print("X-THINGSPEAKAPIKEY: "+apiKey+"\n");
    client.print("Content-Type: application/x-www-form-urlencoded\n");
    client.print("Content-Length: ");
    client.print(tsData.length());
    client.print("\n\n");
    client.print(tsData);
 
     Serial.print("LPG: ");
     Serial.print(lpg);
     Serial.print("  CO: ");
     Serial.print(co);
     Serial.print("  Smoke: ");
     Serial.println(smoke);
     Serial.print("  Temperature: ");
     Serial.print(temp);
     Serial.print("  Humidity: ");
     Serial.println(hum);
     Serial.print(" Vibration: ");
     Serial.println(!(vib_value));
     Serial.println("uploaded to Thingspeak server....");
  }
  client.stop();
 
  Serial.println("Waiting to upload next reading...");
  Serial.println();
  // thingspeak needs minimum 15 sec delay between updates
  delay(5000);
}
