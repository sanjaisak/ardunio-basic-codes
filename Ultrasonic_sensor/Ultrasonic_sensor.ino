
#define TRIG D6
#define ECHO D7
void setup() {
  // put your setup code here, to run once:
  pinMode(TRIG,OUTPUT);
  pinMode(ECHO,INPUT);
  Serial.begin(115200);
}

void loop() {
  // put your main code here, to run repeatedly:
  int dur=0;
  digitalWrite(TRIG,LOW);
  delayMicroseconds(2);
  digitalWrite(TRIG,HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIG,LOW);
  dur = pulseIn(ECHO,HIGH);
  float dist = (dur * 0.0343)/2; 
  Serial.print("Distance: ");
  Serial.println(dist);
  delay(1000);
}
