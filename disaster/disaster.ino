#include <SoftwareSerial.h>
#include <stdlib.h>
#include <dht.h>

dht DHT;

#define DHT11_PIN 8
// LED 
// SensorInput analog input (A0)
byte statusLed    = 13;
byte sensorInterrupt = 0;
byte sensorPin       = 2;

const int vibration_Pin =7;
const int Gas_Pin =9;
int Fire_Pin=10;
float calibrationFactor = 4.5;
volatile byte pulseCount;
float flowRate;
unsigned int flowMilliLitres;
unsigned long totalMilliLitres;
unsigned long oldTime;
int Smoke;
int intensity;
int Motion;
int Fire;
// replace with your channel's thingspeak API key
String apiKey = "PWY6E74HG4A471AC";
int output_value;
int output_value1;
int output_value2;
int output_value3;
SoftwareSerial ser(2,3); // RX, TX

// this runs once
void setup() {                
  // initialize the digital pin as an output.
  pinMode(Gas_Pin, INPUT);    
  pinMode(vibration_Pin, INPUT); 
  pinMode(Fire_Pin, INPUT); 
  pinMode(statusLed, OUTPUT);  // Set up the status LED line as an output
  digitalWrite(statusLed, HIGH);  // We have an active-low LED attached
 
  pinMode(sensorPin, INPUT);
  digitalWrite(sensorPin, HIGH);
 
  pulseCount        = 0;
  flowRate          = 0.0;
  flowMilliLitres   = 0;
  totalMilliLitres  = 0;
  oldTime           = 0;
 
  // The Hall-effect sensor is connected to pin 2 which uses interrupt 0.
  // Configured to trigger on a FALLING state change (transition from HIGH
  // state to LOW state)
  attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  // enable debug serial
  Serial.begin(9600); 
  // enable software serial
  ser.begin(115200);
  
  // reset ESP8266
  ser.println("AT+RST");  
  delay (10000);
  ser.println("AT");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Sending AT command");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  delay (5000);
 ser.println("AT+CWMODE=1");
 delay (5000);
  
  ser.println("AT+CWMODE?");
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Setting mode");
  delay (5000);
  ser.println("AT+CWJAP=\"srvraj\",\"srvraj965\"");
  delay (15000);
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  Serial.println("Joining AP List");
  delay (8000);  
}

// the loop 
void loop() {  
  // blink LED on board
  DHT.read11(DHT11_PIN);
    
    Serial.print("Current humidity = ");
    Serial.print(DHT.humidity);
    Serial.print("%  ");
    Serial.print("temperature = ");
    Serial.print(DHT.temperature); 
    Serial.println("C  ");
    
    delay(500);

    //Read light sensor data
    Fire =digitalRead(Fire_Pin);
    Serial.println("Light fire2");  
    Serial.println(Fire);
    output_value = Fire;
     if (Fire == HIGH) {
    // turn LED on:
    digitalWrite(statusLed, HIGH);
    } else {
    // turn LED off:
    digitalWrite(statusLed, LOW);
     }
    Motion =digitalRead(vibration_Pin);
    Serial.print("Vibration detected :");
    Serial.println(Motion);
    output_value1 = Motion;
    
    if (Motion == HIGH) {
    // turn LED on:
    digitalWrite(statusLed, HIGH);
    } else {
    // turn LED off:
    digitalWrite(statusLed, LOW);
     }
    Smoke =digitalRead(Gas_Pin);
    Serial.print("Smoke detected :");
    Serial.println(Smoke);
    output_value2 = Smoke;
    if (Smoke == HIGH) {
    // turn LED on:
    digitalWrite(statusLed, HIGH);
    } else {
    // turn LED off:
    digitalWrite(statusLed, LOW);
     }
    if ((millis() - oldTime) > 1000)   // Only process counters once per second
  {
    // Disable the interrupt while calculating flow rate and sending the value to
    // the host
    detachInterrupt(sensorInterrupt);
 
    // Because this loop may not complete in exactly 1 second intervals we calculate
    // the number of milliseconds that have passed since the last execution and use
    // that to scale the output. We also apply the calibrationFactor to scale the output
    // based on the number of pulses per second per units of measure (litres/minute in
    // this case) coming from the sensor.
    flowRate = ((1000.0 / (millis() - oldTime)) * pulseCount) / calibrationFactor;
 
    // Note the time this processing pass was executed. Note that because we've
    // disabled interrupts the millis() function won't actually be incrementing right
    // at this point, but it will still return the value it was set to just before
    // interrupts went away.
    oldTime = millis();
 
    // Divide the flow rate in litres/minute by 60 to determine how many litres have
    // passed through the sensor in this 1 second interval, then multiply by 1000 to
    // convert to millilitres.
    flowMilliLitres = (flowRate / 60) * 1000;
 
    // Add the millilitres passed in this second to the cumulative total
    totalMilliLitres += flowMilliLitres;
 
    unsigned int frac;
 
    // Print the flow rate for this second in litres / minute
    Serial.print("Flow rate: ");
    Serial.print(int(flowRate));  // Print the integer part of the variable
    Serial.print("L/min");
    Serial.print("\t");       // Print tab space
 
    // Print the cumulative total of litres flowed since starting
    Serial.print("Output Liquid Quantity: ");
    Serial.print(totalMilliLitres);
    Serial.println("mL");
    Serial.print("\t");       // Print tab space
    Serial.print(totalMilliLitres / 1000);
    Serial.print("L");
    output_value3 = totalMilliLitres / 1000;
 
    // Reset the pulse counter so we can start incrementing again
    pulseCount = 0;
 
    // Enable the interrupt again now that we've finished sending output
    attachInterrupt(sensorInterrupt, pulseCounter, FALLING);
  }

   delay(1000);
  
  // read the value from SensorInput.
  // read 10 values for averaging.
  int val = 0;
  int val1 = 0;
  int val2 = 0;
  int val3 = 0;
  int val4 = 0;
  int val5 = 0;
  
  val = DHT.temperature;
  Serial.println("Analog reading");
  // convert to string
  char buf[16];
  String strTemp = String(val, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strTemp);
  
    val1 = DHT.humidity;
  Serial.println("Analog reading");
  // convert to string

  String strHum = String(val1, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strHum);

    val2 = output_value;
  
  String strFire = String(val2, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strFire);

   val3 = output_value1;
  
  String strMotion = String(val3, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strMotion);


   val4 = output_value2;
  String strSmoke = String(val4, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strSmoke);

   val5 = output_value3;
   String strFlow = String(val5, DEC); 
  Serial.println("Printing parameter");
  Serial.println(strFlow);
  
   
  // TCP connection
  String cmd = "AT+CIPSTART=\"TCP\",\"";
  cmd += "184.106.153.149"; // api.thingspeak.com
  cmd += "\",80";
  ser.println(cmd);
  Serial.println(cmd); 
  while(ser.available())
  {
    Serial.write(ser.read());
  }
  
  Serial.println("TCP connection");
  
  if(ser.find("Error")){
    Serial.println("AT+CIPSTART error");
    return;
  }
  
  // prepare GET string
  String getStr = "GET /update?api_key=";
  getStr += apiKey;
  getStr +="&field1=";
  getStr += String(strTemp);
  getStr +="&field2=";
  getStr += String(strHum);
  getStr +="&field3=";
  getStr += String(strFire);
  getStr +="&field4=";
  getStr += String(strMotion);
  getStr +="&field5=";
  getStr += String(strSmoke);
  getStr +="&field6=";
  getStr += String(strFlow);

  
  getStr += "\r\n\r\n";

  Serial.println("Got string");

  // send data length
  cmd = "AT+CIPSEND=";
  cmd += String(getStr.length());
  ser.println(cmd);
  while(ser.available())
  {
    Serial.write(ser.read());
  }

  if(ser.find(">")){
    ser.print(getStr);
  }
  else{
    ser.println("AT+CIPCLOSE");
    // alert user
    Serial.println("AT+CIPCLOSE");
  }
 delay(20000);  
}

void pulseCounter()
{
  // Increment the pulse counter
  pulseCount++;
}
