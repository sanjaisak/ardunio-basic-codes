float a;
void setup() {
  pinMode(A0,INPUT);
  Serial.begin(9600);

}

void loop() {
  a= analogRead(A0);
 // a= a*0.48828125;
  Serial.println(a);
delay(1000);
}
