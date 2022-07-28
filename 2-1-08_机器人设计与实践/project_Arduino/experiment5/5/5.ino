const int TrigPin = 2; 
const int EchoPin = 3; 
float cm; 
void setup() 
{ 
  Serial.begin(9600); 
  pinMode(TrigPin, OUTPUT); 
  pinMode(EchoPin, INPUT); 
} 
void loop() 
{ 
  digitalWrite(TrigPin, LOW); //低高低电平发一个短时间脉冲去 TrigPin 
  delayMicroseconds(2); 
  digitalWrite(TrigPin, HIGH); 
  delayMicroseconds(10); 
  digitalWrite(TrigPin, LOW); 
  cm = pulseIn(EchoPin, HIGH) / 58; //将回波时间换算成 cm 
  cm = (int(cm * 100)) / 100; //保留两位小数 
  Serial.print(cm); 
  Serial.print("cm"); 
  Serial.println();
  delay(1000);
}
