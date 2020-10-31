#include <Time.h>


int sensorPin = A0;    // select the input pin for the potentiometer
float sensorValue = 0;  // variable to store the value coming from the sensor
int count=9;
int starttime = 0;
int heartrate = 0; 
boolean counted = false;


void setup() {
  // declare the ledPin as an OUTPUT:
  pinMode(sensorPin, INPUT); 
  Serial.begin(9600);
}


void loop() {
  // read the value from the sensor:

starttime = millis();
while (millis()<starttime+10000)                          // so i'm reading the pulse for 10 seconds
{ 
  sensorValue = analogRead(sensorPin);
  if (sensorValue >550 && counted == false)         // counting the pulse, and making sure I dont count 
  {                                                                // each peak more than once
    count++;
    counted = true;  
  }
  else if (sensorValue < 500)
  {
    counted = false; 
  } 
}

    heartrate = count*6;                                    // multiplying by six to get pulse per minute 
 Serial.println(heartrate);                                   // printing to serial screen 

  heartrate=0;
  count =0;
}


