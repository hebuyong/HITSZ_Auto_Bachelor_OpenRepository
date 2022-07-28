#include <MsTimer2.h>  //定时器库的 头文件
//定义电机编码器A B相引脚
#define ENCODER_A 2
#define ENCODER_B 4
//定义电机驱动的控制信号
#define PWML 10
#define INL1 13
#define INL2 12
int PERIOD = 20;
const float TARGET= 20;
//全局变量
long encoderVal;//编码器值
float velocity;
float u = 0;
float eI;
float eII;
float eIII;
//获取编码器值
void getEncoder(void)
{

  if (digitalRead(ENCODER_A) == LOW)
  {
    if (digitalRead(ENCODER_B) == LOW)
    {
      encoderVal--;
    }
    else
    {
      encoderVal++;
    }
  }
  else
  {
    if (digitalRead(ENCODER_B) == LOW)
    {
      encoderVal++;
    }
    else
    {
      encoderVal--;
    }
  }
}


//PID控制,初始值供参考,Kp=500,Ti=10,Td=400,T=PERIOD
int pidController( float targetVelocity, float currentVelocity)
{
  float output;

  eI = targetVelocity - currentVelocity;
  float Kp = 50, Ti =10, Td =400, T = PERIOD;
  float q0 = Kp * (1 + T / Ti + Td / T);
  float q1 = -Kp * (1 + 2 * Td / T);
  float q2 = Kp * Td / T;
  u = u + q0 * eI + q1 * eII + q2 * eIII;
  eIII = eII;
  eII = eI;
  if (u >= 255)
  {
    u = 255;
  }
  if (u <= -255)
  {
    u = -255;
  }
  output = u;
  return (int)output;
}
//直流电机控制
void control(void)
{
  velocity=(encoderVal/780.0)*3.1415*2.0*(1000/PERIOD);
  encoderVal = 0;
  int output = pidController(TARGET, velocity);
  //TARGET为目标速度值，目前大家的电机基本上最快为每秒转50弧度，所以不要设置超过这个值
  //以下代码很重要，大家可能需要根据电机实际转动，调整INL1和INL2的值
  if (output > 0)
  {
    digitalWrite(INL1, LOW);
    digitalWrite(INL2, HIGH);
    analogWrite(PWML, output);
  }
  else
  {
    digitalWrite(INL1, HIGH);
    digitalWrite(INL2, LOW);
    analogWrite(PWML, abs(output));
  }
}
void setup()
{
  //9,10两个管脚的PWM由定时器TIMER1产生，这句程序改变PWM的频率，勿删
  TCCR1B = TCCR1B & B11111000 | B00000001 ;
  //初始化各管脚，各全局变量，中断，串口通讯等
  pinMode(PWML, OUTPUT);
  pinMode( INL2, OUTPUT);
  pinMode( INL1, OUTPUT);
  pinMode( ENCODER_A, INPUT);
  pinMode( ENCODER_B, INPUT);
  attachInterrupt(0, getEncoder, CHANGE);
  Serial.begin (9600);
  MsTimer2::set(PERIOD, control);
  MsTimer2::start();
}
void loop()
{
  //撰写代码，使其能够通过“串口绘图器”观察速度波形
  Serial.print (velocity);
  Serial.print("\r\n");
}
