#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>
                          
#define FIREBASE_HOST "testrun-5f68a-default-rtdb.firebaseio.com"
#define FIREBASE_AUTH "Sfb0tDGKi5SnpOIlxEuXAISbfYCLdchvB9HdxLIe"
#define WIFI_SSID "sanjaisak"
#define WIFI_PASSWORD "sanjai@S"                                 //Password of your wifi network 
 
  
// Declare the Firebase Data object in the global scope
FirebaseData firebaseData;

// Declare global variable to store value
String val="0";



void setup() {

  Serial.begin(9600);                                                      // Select the same baud rate if you want to see the datas on Serial Monitor

  Serial.println("Serial communication started\n\n");  
           
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);                                     //try to connect with wifi
  Serial.print("Connecting to ");
  Serial.print(WIFI_SSID);


  
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print(".");
    delay(500);
  }

  
  Serial.println();
  Serial.print("Connected to ");
  Serial.println(WIFI_SSID);
  Serial.print("IP Address is : ");
  Serial.println(WiFi.localIP());//print local IP address
  pinMode(D5,OUTPUT);
  Firebase.begin(FIREBASE_HOST, FIREBASE_AUTH);   // connect to firebase

  Firebase.reconnectWiFi(true);
  delay(1000);
}

void loop() {




  if (Firebase.getString(firebaseData, "/data")) {                           

    if (firebaseData.dataType() == "int") {                            

      val = firebaseData.stringData();
      Serial.println(val);
      delay(1000);
      if(val=="1")
      {
        digitalWrite(D5,HIGH);
        Serial.println("on");
      }
      else 
      
      {
        digitalWrite(D5,LOW);
        Serial.println("off");
      }
      
      
    }

  } else {
    Serial.println(firebaseData.errorReason());
  }
 }
