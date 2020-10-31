int led = 9;
int brightness = 0;
int fadeout = 5;
void setup() {
  pinMode(led, OUTPUT);

}

void loop() {
  analogWrite(led, brightness) ;
  brightness = brightness + fadeout ;
  if(brightness== 0 || brightness ==120)
  {fadeout = -fadeout;
  }
 delay (30);
 

}
