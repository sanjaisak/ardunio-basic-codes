int a=1;
void setup() {
  // put your setup code here, to run once:
pinMode(A0,INPUT);
Serial.begin(9600);
}

void loop() {
  // put your main code here, to run repeatedly:
a=analogRead(A0);
 a = a * 0.48828125;
Serial.println(a);
delay(1000);
}
