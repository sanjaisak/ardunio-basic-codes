#include<ESP8266WiFi.h>
#include<FirebaseArduino.h>
#define WiFi_SSID"sanjaisak"
#define WiFi_PASSWORD"sanjai@S"
#define FIREBASE_HOST"https://camcheck-7e9e2.firebaseio.com/"
#define FIREBASE_AUTH"AIzaSyDVhQIHtqycmNDb0dvsOQyfqHwCixCi5Kc"
void setup() 
{
  Serial.begin(9600);
  WiFi.begin(WiFi_SSID,WiFi_PASSWORD);
  delay(9600);
  Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH);
 

}

void loop()
{
  Firebase.set("STATUS",123);
}
String a=Firebase.get("LED");
if(a=="1")
{
  digitalWrite(D0,HIGH);
  Serial.println("1");
  
}
else{
  digitalWrite(D0,LOW);
   Serial.println("2");}
