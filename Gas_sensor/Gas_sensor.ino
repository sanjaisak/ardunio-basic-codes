#include <MQ2.h>
#define SENSOR A0
MQ2 mq2(SENSOR);
void setup() {
  // put your setup code here, to run once:
mq2.begin();
Serial.begin(9600);
}

float lpg,co,smoke;
void loop() {
  // put your main code here, to run repeatedly:

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
}
