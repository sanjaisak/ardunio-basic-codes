


#include<DHT.h>

int pin=D2;
int temp,hum;

DHT dht(pin,DHT11);
void setup() {
  // put your setup code here, to run once:
Serial.begin(115200);
pinMode(pin,INPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
temp = dht.readTemperature();
hum = dht.readHumidity();

Serial.print("Temerature: ");
Serial.println(temp);
Serial.print("Humidity: ");
Serial.println(hum);
delay(1000);
}
