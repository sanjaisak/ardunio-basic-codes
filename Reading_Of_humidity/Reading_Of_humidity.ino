#include <LiquidCrystal.h>
#include "dht.h"

dht DHT;
int sensorPin = 8;
int sensorValue;
int LDRPin = A0;
int sensorValue1 = 0;
const int rs = 12, en = 11, d4 = 5, d5 = 4, d6 = 3, d7 = 2;
LiquidCrystal lcd(rs, en, d4, d5, d6, d7);
void setup() {
  // put your setup code here, to run once:
  pinMode(sensorPin,INPUT);
  pinMode(LDRPin, INPUT);
  Serial.begin(9600);
  lcd.begin(16, 2);
}

void loop() {
  // put your main code here, to run repeatedly:
  sensorValue = DHT.read22(sensorPin);
  Serial.print("Humidity Value: ");
  Serial.println(DHT.humidity);
  
  Serial.print("Temperature Value: ");
  Serial.println(DHT.temperature);
  
  lcd.setCursor(0,0);
  lcd.print("Temp: ");
  lcd.print(DHT.temperature);
  lcd.print("C");
  delay(2000);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("Hum: ");
  lcd.print(DHT.humidity);
  lcd.print("%");
  delay(2000);
  lcd.clear();
  double gamma = log(DHT.humidity/100) + ((17.62*DHT.temperature) / (243.5+DHT.temperature));
  double dp = 243.5*gamma / (17.62-gamma);
  lcd.setCursor(0,0);
  lcd.print("DP Temp: ");
  lcd.print(dp);
  lcd.print("C");
  delay(2000);
  lcd.clear();
  Serial.print("Dew point: ");
  Serial.print(dp);
  Serial.println(" degrees Celcius ");

sensorValue1 = analogRead(LDRPin);
sensorValue1 = constrain(sensorValue1, 150, 1500); 
sensorValue1 = map(sensorValue1, 150, 1500, 0, 1023); 
Serial.print("Light intensity:  ");
Serial.println(sensorValue1);
lcd.setCursor(0,0);
  lcd.print("L.Int.: ");
  lcd.print(sensorValue1);
  lcd.print(" lux");
 
  lcd.setCursor(0,1);
if(sensorValue1<=150)
{
  Serial.println("You should avoid doing work in such conditions.");
}
if(sensorValue1>=150 && sensorValue1<=250)
{
  Serial.println("It is only good for Warehouses, Homes, Theaters, Archives.");
}
if(sensorValue1>=250 && sensorValue1<=500)
{
  Serial.println("It is only good for Easy Office Work, Classes.");
}
if(sensorValue1>=500 && sensorValue1<=750)
{
  Serial.println("It is only good for Normal Office Work, PC Work, Study Library, Groceries, Show Rooms,Laboratories.");
}
if(sensorValue1>=750 && sensorValue1<=1000)
{
  Serial.println("It is only good for Supermarkets, Mechanical Workshops, Office Landscapes.");
}
if(sensorValue1>=1000 && sensorValue1<=1500)
{
  Serial.println("It is only good for Normal Drawing Work, Detailed Mechanical Workshops, Operation  Theatres.");
}
Serial.println("");
delay(2000);
lcd.clear();




}
