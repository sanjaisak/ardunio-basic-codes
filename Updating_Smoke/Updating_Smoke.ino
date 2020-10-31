#define SEN 7
int sensorValue;
void setup()
{
  pinMode(SEN,INPUT);
  Serial.begin(9600);
}

void loop()
{
  sensorValue = digitalRead(SEN);
  Serial.println(sensorValue);
  delay(1000);
}
