void setup() {
  // put your setup code here, to run once:

pinMode (A0,INPUT);
Serial.begin(9600);
digitalWrite(A0, LOW);

}

void loop() {
  // put your main code here, to run repeatedly:
if(digitalRead(A0)==HIGH)
Serial.println("1");
else
Serial.println("0");
}
