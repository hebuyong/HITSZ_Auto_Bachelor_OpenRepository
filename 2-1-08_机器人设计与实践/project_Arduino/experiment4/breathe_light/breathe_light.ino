int ledPin = 6; //设定控制 LED 的数字 I/O 脚，对应 LED 的红灯
void setup () {
  pinMode(ledPin, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(9, OUTPUT);
  analogWrite(9, 255);
  analogWrite(6, 255);
}
void loop() {
  for (int a = 0; a <= 255; a++) { //循环语句，控制 PWM 亮度的增加
    analogWrite(ledPin, a);
    delay(8); //当前亮度级别维持的时间,单位毫秒
  }
  for (int a = 255; a >= 0; a--) { //循环语句，控制 PWM 亮度减小
    analogWrite(ledPin, a);
    delay(8); //当前亮度的维持的时间,单位毫秒
  }
  delay(300); //完成一个循环后等待的时间,单位毫秒
}
