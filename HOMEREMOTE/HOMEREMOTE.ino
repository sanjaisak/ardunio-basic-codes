#include <ESP8266WiFi.h>
#include <Arduino.h>
#include <IRremoteESP8266.h>
#include <IRsend.h>

WiFiClient client;
WiFiServer server(80);
const uint16_t kIrLed = 4;  // ESP8266 GPIO pin to use. Recommended: 4 (D2).

IRsend irsend(kIrLed);
const char* ssid = "sanjaisak";
const char* password = "sanjai@S";


String  data =""; 





void setup()
{



  Serial.begin(9600);
  connectWiFi();
  server.begin();
  irsend.begin();
  
}
void connectWiFi()
{
  Serial.println("Connecting to WIFI");
  WiFi.begin(ssid, password);
  while ((!(WiFi.status() == WL_CONNECTED)))
  {
    delay(300);
    Serial.print("..");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("NodeMCU Local IP is : ");
  Serial.print((WiFi.localIP()));
}

void loop()
{
   
    client = server.available();
    if (!client) return; 
    data = checkClient ();


   
    if (data == "up") 
    {
    up();
    data="";
    }
    
    
    if (data == "down") 
    {
    down();
    data="";
    }
    if (data == "left") 
    {
    left();
    data="";
    }
    if (data == "right") 
    {
    right();
    data="";
    }
    if (data == "onoff") 
    {
    onoff();
    data="";
    }
    if (data == "1") 
    {
    o1();
    data="";
    }
    if (data == "2") 
    {
    o2();
    data="";
    }
    if (data == "3") 
    {
    o3();
    data="";
    }
    if (data == "4") 
    {
    o4();
    data="";
    }
    if (data == "5") 
    {
    o5();
    data="";
    }

    if (data == "6") 
    {
    o6();
    data="";
    }
    if (data == "7") 
    {
    o7();
    data="";
    }
    if (data == "8") 
    {
    o8();
    data="";
    }
    if (data == "9") 
    {
    o9();
    data="";
    }
    if (data == "0") 
    {
    o0();
    data="";
    }
    
    if (data == "volup") 
    {
    volup();
    data="";
    }
    if (data == "voldown") 
    {
    voldown();
    data="";
    }
    if (data == "ok") 
    {
    ok();
    data="";
    }
    
    if (data == "menu") 
    {
    menu();
    data="";
    }
    if (data == "mute") 
    {
    mute();
    data="";
    }
    if (data == "exit1") 
    {
    exit1();
    data="";
    }
} 

void up(void)   
{
  Serial.println("up");
  irsend.sendNEC(0x14EBB04F);
}
void down(void)   
{
  Serial.println("down");
  irsend.sendNEC(0x14EB7887);
}
void right(void)   
{
  Serial.println("right");
  irsend.sendNEC(0x14EB6897);
}
void left(void)   
{
  Serial.println("left");
  irsend.sendNEC(0x14EBE817);
}
void ok(void)   
{
  Serial.println("ok");
  irsend.sendNEC(0x14EBE01F);
}
void o1(void)   
{
  Serial.println("01");
  irsend.sendNEC(0x14EB58A7);
}
void o2(void)   
{
  Serial.println("o2");
  irsend.sendNEC(0x14EB8877);
}
void o3(void)   
{
  Serial.println("o3");
  irsend.sendNEC(0x14EB906F);
}
void o4(void)   
{
  Serial.println("o4");
  irsend.sendNEC(0x14EBD827);
}
void o5(void)   
{
  Serial.println("o5");
  irsend.sendNEC(0x14EB48B7);
}
void o6(void)   
{
  Serial.println("o6");
  irsend.sendNEC(0x14EB50AF);
}
void o7(void)   
{
  Serial.println("o7");
  irsend.sendNEC(0x14EB38C7);
}
void o8(void)   
{
  Serial.println("o8");
  irsend.sendNEC(0x14EBC837);
}
void o9(void)   
{
  Serial.println("o9");
  irsend.sendNEC(0x14EBD02F);
}
void o0(void)   
{
  Serial.println("o0");
  irsend.sendNEC(0x14EB28D7);
}
void menu(void)   
{
  Serial.println("menu");
  irsend.sendNEC(0x14EB08F7);
}
void mute(void)   
{
  Serial.println("mute");
  irsend.sendNEC(0x14EBA857);
}
void exit1(void)   
{
  Serial.println("exit1");
  irsend.sendNEC(0x14EBF807);
}
void volup(void)   
{
  Serial.println("volup");
  irsend.sendNEC(0x14EBAA55);
}
void voldown(void)   
{
  Serial.println("voldown");
  irsend.sendNEC(0x14EBE817);
}

void onoff(void)   
{
  Serial.println("onoff");
  irsend.sendNEC(0x14EB18E7);
}


/***RECEIVE DATA FROM the APP ***/
String checkClient (void)
{
  while(!client.available()) delay(1); 
  String request = client.readStringUntil('\r');
  request.remove(0, 5);
  request.remove(request.length()-9,9);
  return request;
}
