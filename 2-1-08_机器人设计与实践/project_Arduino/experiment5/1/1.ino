#define PIN_EN 11//定义PWM输出引脚
#define PIN_AIN2 13//定义正反转控制引脚
#define PIN_AIN1 12//定义正反转控制引脚
void setup() {
pinMode(PIN_EN, OUTPUT); //定义引脚为输出
pinMode(PIN_AIN2, OUTPUT);
pinMode(PIN_AIN1, OUTPUT);
}
void loop() {
digitalWrite(PIN_EN, HIGH);
digitalWrite(PIN_AIN2, HIGH);
digitalWrite(PIN_AIN1,LOW);
}
