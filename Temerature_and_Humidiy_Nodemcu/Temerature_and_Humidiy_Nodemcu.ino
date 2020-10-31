 #include<DHT.h>

int sensorPin = 8;
float temp,hum;
DHT dht(sensorPin,DHT22);
void setup() {
  // put your setup code here, to run once:
pinMode(sensorPin,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
temp = dht.readTemperature();
hum = dht.readHumidity();

Serial.print("Temperature: ");
Serial.print(temp);
Serial.println(" degree C");
Serial.print("Humidity: ");
Serial.print(hum);
Serial.println("%");
}
