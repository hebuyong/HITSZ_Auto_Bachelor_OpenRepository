#include<MsTimer2.h>//定时器库的头文件
//--------------定义管脚----------
#define ENCODER_A1 2 //电机1
#define ENCODER_B1 5
#define ENCODER_A2 3 //电机2
#define ENCODER_B2 4
#define PWM1 9
#define PWM2 10
#define L1 14   //左红外
#define L2 15
#define L3 16
#define R1 17   //右红外
#define R2 18
#define R3 19
#define M 13 //中红外

//----------------定义常值------------
#define PERIOD 20
#define Kp 7.0
#define Ti 50.0
#define Td 10.0

//-----------全局变量----------
float target1 = 2.0, t1; //左保守
float target2 = 2.0, t2; //右速度
volatile long encoderVal1;//编码器1值
float velocity1;//转速1
volatile long encoderVal2;//编码器2值
float velocity2;//转速2
float T = PERIOD;
float q0 = Kp * (1 + T / Ti + Td / T);
float q1 = -Kp * (1 + 2 * Td / T);
float q2 = Kp * Td / T;
float u1, ek11, ek12;
float u2, ek21, ek22;
//-----------------测试与转向---------

#define V 6.0 //基础速度

void control(void)
{
  if (digitalRead(M) == LOW)
  {
    target1 = V;
    target2 = V;
  }
  if (digitalRead(L1) == LOW) //低右转
  {
    target1 = V * 0.9;
    target2 = V * 0.5;
  }
  if ( digitalRead(R1) == LOW) //低左转
  {
    target1 = V * 0.5;
    target2 = V * 0.9;
  }
  if ( digitalRead(L2) == LOW) //中右转
  {
    target1 = V * 0.75;
    target2 = V * 0.15;
  }
  if (digitalRead(R2) == LOW) //中左转
  {
    target1 = V * 0.15;
    target2 = V * 0.75;
  }
  if ( digitalRead(L3) == LOW) //直角右转
  {
    target1 = 0.65 * V;
    target2 = 0;
  }
  if (digitalRead(R3) == LOW) //直角左转
  {
    target1 = 0;
    target2 = 0.65 * V;
  }
  target1 = target1 * 0.6 + t1 * 0.4;
  target2 = target2 * 0.6 + t2 * 0.4;

  velocity1 = (encoderVal1 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal1 = 0;
  velocity2 = (encoderVal2 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal2 = 0;
  int output1 = pidController1(target1, velocity1);
  analogWrite(PWM1, abs(output1));
  int output2 = pidController2(-target2, velocity2);
  if (output2 < 0)
    analogWrite(PWM2, abs(output2));
  t1 = target1;
  t2 = target2;
}
//-------主函数----------


void setup() {
  //9, 10两个管脚的PWM由定时器TIMER1产生，这句程序改变PWM的频率，勿删
  TCCR1B = TCCR1B & B11111000 | B00000001 ;
  MsTimer2::set(PERIOD, control);
  MsTimer2::start();
  pinMode( ENCODER_A1, INPUT);
  pinMode( ENCODER_B1, INPUT);
  pinMode( ENCODER_A2, INPUT);
  pinMode( ENCODER_B2, INPUT);
  attachInterrupt(0, getEncoder1, CHANGE);
  attachInterrupt(1, getEncoder2, CHANGE);
  Serial.begin (9600);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(M, INPUT);
}
void loop() {
  Serial.print (velocity1); Serial.print("\t" );
  Serial.println(velocity2);
  //Serial.print("\n");
  //Serial.print1n(u2);
  //Serial.print1n(u2);
}
//----------编码器中断函数------
void getEncoder1(void)
{
  if (digitalRead(ENCODER_A1) == LOW)
  {
    if (digitalRead(ENCODER_B1) == LOW)
      encoderVal1--;
    else
      encoderVal1++;
  }
  else
  {
    if (digitalRead(ENCODER_B1) == LOW)
      encoderVal1++;
    else
      encoderVal1--;
  }
}
void getEncoder2(void)
{
  if (digitalRead(ENCODER_A2) == LOW)
  {
    if (digitalRead(ENCODER_B2) == LOW)
      encoderVal2--;
    else
      encoderVal2++;
  }
  else
  {
    if (digitalRead(ENCODER_B2) == LOW)
      encoderVal2++;
    else
      encoderVal2--;
  }
}

//----PID控制器
int pidController1(float targetVelocity, float currentVelocity)
{
  float ek10;
  ek10 = targetVelocity - currentVelocity;
  u1 = u1 + q0 * ek10 + q1 * ek11 + q2 * ek12;
  if (u1 > 255)
    u1 = 255;
  if (u1 < -255)
    u1 = -255;
  ek12 = ek11;
  ek11 = ek10;
  return (int)u1;
}
int pidController2(float targetVelocity, float currentVelocity)
{
  float ek20;
  ek20 = targetVelocity - currentVelocity;
  u2 = u2 + q0 * ek20 + q1 * ek21 + q2 * ek22;
  if (u2 > 255)
    u2 = 255;
  if (u2 < -255)
    u2 = -255;
  ek22 = ek21;
  ek21 = ek20;
  return (int)u2;
}
