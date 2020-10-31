int ledPin = 12;
int buttonPin = 8;
void setup() {
  // put your setup code here, to run once:
  pinMode(ledPin,OUTPUT);
  pinMode(buttonPin,INPUT);
}

int buttonState = 0;
void loop() {
  // put your main code here, to run repeatedly:
  buttonState = digitalRead(buttonPin);
  if(buttonState == 1)
  {
    digitalWrite(ledPin,HIGH);
    delay(100);
  }
  if(buttonState == 0)
  {
    digitalWrite(ledPin,LOW);
    delay(100);
  }
  
}
