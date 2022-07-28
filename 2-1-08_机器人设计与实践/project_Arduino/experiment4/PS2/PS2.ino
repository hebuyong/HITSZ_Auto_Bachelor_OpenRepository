#include <Servo.h> 
#define PIN_SERVO 10 //定义舵机控制端口 
Servo myservo; //创建一个舵机控制对象 
void setup() { 
// put your setup code here, to run once: 
 Serial.begin(9600); //设置串口波特率，目的是将数据传到电脑串口监控器 
myservo.attach(PIN_SERVO); //定义舵机接口 10 
} 
void loop() { 
 // put your main code here, to run repeatedly: 
 int x, y, angle; 
 x = analogRead(A0); 
 y = analogRead(A1); 
angle = x / 1023.0 * 180.0; 
myservo.write(angle); //设置舵机旋转角度 
Serial.print("X: "); 
Serial.println(x); 
Serial.print("Y: "); 
Serial.println(y); 
delay(100); 
}
