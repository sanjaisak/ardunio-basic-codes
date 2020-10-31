 
#include <ESP8266WiFi.h>
#include <Servo.h>

Servo servo1;
Servo servo2;


void setup() {

    servo1.attach(0); 
    servo1.write(0);

   
     

  

}

void loop() {

    servo1.write(180);
  delay(50);

    servo1.write(0); 
  delay(50);
  
}
