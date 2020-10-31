

int IN1 = 5;
int IN2 = 6;
int IN3 = 10;
int IN4 = 11;
char state;
String voice;

void setup() {
  // put your setup code here, to run once:

pinMode(IN1, OUTPUT);
pinMode(IN2, OUTPUT);
pinMode(IN3, OUTPUT);
pinMode(IN4, OUTPUT);
Serial.begin(9600);


}

void loop() {
  // put your main code here, to run repeatedly:
while(Serial.available()>0)
{
  delay(10);
  state = Serial.read();
 
  if (state =='#' )
  {
    break;
    }
   voice += state;
}
   if(voice.length()>0){
    Serial.println(voice);
    if(voice=="*forward"){
   
   
        analogWrite(IN1, 255);
        analogWrite(IN2, 0); 
        analogWrite(IN3, 255);
        analogWrite(IN4, 0);
   }
   if(voice=="*left"){
   
   
        analogWrite(IN1, 0);
        analogWrite(IN2, 0); 
        analogWrite(IN3, 255);
        analogWrite(IN4, 0);
   }
   if(voice=="*right"){
   
   
        analogWrite(IN1, 255);
        analogWrite(IN2, 0); 
        analogWrite(IN3, 0);
        analogWrite(IN4, 0);
   }
   if(voice=="*backward"){
   
   
        analogWrite(IN1, 0);
        analogWrite(IN2, 255); 
        analogWrite(IN3, 0);
        analogWrite(IN4, 255);
   }
   if(voice=="*stop"){
   
   
        analogWrite(IN1, 0);
        analogWrite(IN2, 0); 
        analogWrite(IN3, 0);
        analogWrite(IN4, 0);
   }
   voice="";  
  }
}
