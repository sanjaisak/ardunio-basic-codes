#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>

const char* ssid = "sanjaisak";
const char* password = "sanjai@S";

ESP8266WebServer server(80);

void handleRoot()
{
  char temp[400];

  snprintf(temp, 400,
    "<html>\    
  <head>\
  </head>\
    <body>\
    <center>\
    <h1>WELCOME</h1></br>\
    </center>\
    <center>\
    <a href =\"/0\"><button >[ON-fan] </button> </a>\
    <br>\
    <br>\
     </center>\
    <center>\
      <a href =\"/5\"><button>[ON-light]</button>_________</a>\
    <a href =\"/4\"> <button>[OFF-light]</button> </a>\
    </cenetr>\
    <center>\
    <br>\
   <a href =\"/1\"><button>[OFF-fan]</button></a>\
    </center>\
  </body>\
</html>");
  server.send(200, "text/html", temp);
//  server.send(200, "text/plain", "I'm an awasome webServer!!!");

}

void ledOn() {
 server.send(200, "text/plain", "Moving forward");

  digitalWrite(D0, HIGH);
 
}

void ledOff() {
 server.send(200, "text/plain", "Moving backward");
    digitalWrite(D0, LOW);
  
}
void left()
{
  server.send(200, "text/plain", "Moving rigth");

  digitalWrite(D1, LOW);
}
void Right()
{
 server.send(200, "text/plain", "Moving left");

  digitalWrite(D1, HIGH);
}

void Flash() {

  server.send(200, "text/plain", "LED flashing");

  pinMode(D0, OUTPUT);
  digitalWrite(D0, HIGH);
  delay(500);
  digitalWrite(D0, LOW);
  delay(500);
  digitalWrite(D0, HIGH);
  delay(500);
  digitalWrite(D0, LOW);
  delay(500);
  digitalWrite(D0, HIGH);
  delay(500);
  digitalWrite(D0, LOW);
  delay(500);
  digitalWrite(D0, HIGH);
  delay(500);
  digitalWrite(D0, LOW);
  delay(500);
}

void LEDdim()
{
  pinMode(D0, OUTPUT);
  analogWrite(D0, 200);
}
void setup(void) {
  pinMode(D0, OUTPUT);
    pinMode(D1, OUTPUT);
  pinMode(D3,OUTPUT);
  pinMode(D4,OUTPUT);
  Serial.begin(115200);
  Serial.print("Connecting to network");
  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);   // Connect to WiFi network

  while (WiFi.status() != WL_CONNECTED) {    // Wait for connection
    delay(500);
    Serial.print(".");
  }

  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  server.on("/", handleRoot);
  server.on("/1", ledOff);
  server.on("/0", ledOn);
  server.on("/2", Flash);
  server.on("/3", LEDdim);
  server.on("/4", left);
  server.on("/5", Right);

  server.begin();
  Serial.println("HTTP server started");
}

void loop(void)
{
  server.handleClient();
}
