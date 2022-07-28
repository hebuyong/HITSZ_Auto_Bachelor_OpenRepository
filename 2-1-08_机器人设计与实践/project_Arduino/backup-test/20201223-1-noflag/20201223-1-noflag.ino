/*
 * 直角弯还行
 * 直线较稳
 */

#include<MsTimer2.h>//定时器库的头文件
//函数声明
void control_lr(void);
void control_inital(void);
void control(void);
void infrared(void);
int pidController1( float targetVelocity, float currentVelocity);
int pidController2(float targetVelocity, float currentVelocity);
void getEncoder1(void);
void getEncoder2(void);
//定义管脚
//左电机
#define ENCODER_A1 3
#define ENCODER_B1 5
#define PWM1 9
#define INL11 11
#define INL12 8
//右电机
#define ENCODER_A2 2
#define ENCODER_B2 4
#define PWM2 10
#define INL21 13
#define INL22 12
//左红外
#define L1 17
#define L2 18
#define L3 19
//中红外
#define M 16
//右红外
#define R3 6
#define R2 14
#define R1 15

//定义PID&&PERIOD常值
#define PERIOD 15
#define Kp1 9
#define Ti1 36.5
#define Td1 9
#define Kp2 9
#define Ti2 43
#define Td2 7
//速度相关
float V = 20; //基础速度
float target1 = 8, t1; //左保守
float target2 = 8, t2; //右速度
//全局变量
volatile long encoderVal1;//编码器1值
float velocity1;//转速1
volatile long encoderVal2;//编码器2值
float velocity2;//转速2
float T = PERIOD;
float q01 = Kp1 * (1 + T / Ti1 + Td1 / T);
float q11 = -Kp1 * (1 + 2 * Td1 / T);
float q21 = Kp1 * Td1 / T;
float q02 = Kp2 * (1 + T / Ti2 + Td2 / T);
float q12 = -Kp2 * (1 + 2 * Td2 / T);
float q22 = Kp2 * Td2 / T;
float u1 = 0, ek11, ek12;
float u2 = 0, ek21, ek22;
//红外相关
int sensor[8] = {0};//红外线数据
int state = 0;

int sum;
float ti=0;
void control_lr(void)
{
  infrared();
  if (sum >= 2)
  {

    if (sensor[1] + sensor[2] + sensor[4]  >= 2)
    {
      target1 = -0.3 * V; target2 = V * 0.6;
    }
    if ( sensor[6] + sensor[7] + sensor[4]  >= 2)
    {
      target1 = V * 0.6; target2 = -0.3 * V;
    }

  }
  else
  {
    
    if (sum == 0)
      ;
    else
    {

      if (sensor[4])
      {
        target1 =  V; target2 =  V;
      }
      if (sensor[3])
      {
        target1 = 0.8 * V; target2 = 0.9 * V;
      }
      if (sensor[5])
      {
        target1 = 0.9 * V; target2 = 0.8 * V;
      }
      if (sensor[2])
      {
        target1 = 0.1 * V; target2 = 0.8 * V;
      }
      if (sensor[6])
      {
        target1 = 0.8 * V; target2 = 0.1 * V;
      }
      if (sensor[1])
      {
        target1 = -0.5 * V; target2 = 0.7 * V;
      }
      if (sensor[7])
      {
        target1 = 0.7 * V; target2 = -0.5 * V;
      }


    }
  }

  //target1 = target1 * 0.6 + t1 * 0.4;
  //target2 = target2 * 0.6 + t2 * 0.4;
  t1 = target1;
  t2 = target2;
}

void infrared(void)
{
  sensor[1] = (digitalRead(L3) == HIGH);
  sensor[2] = (digitalRead(L2) == HIGH);
  sensor[3] = (digitalRead(L1) == HIGH);
  sensor[4] = (digitalRead(M) == HIGH);
  sensor[5] = (digitalRead(R1) == HIGH);
  sensor[6] = (digitalRead(R2) == HIGH);
  sensor[7] = (digitalRead(R3) == HIGH);

  sum = 0;
  for (int i = 1; i < 8; i++)
    sum += sensor[i];
}
void control(void)
{
  control_lr();
  control_inital();
}
void setup()
{
  //9, 10两个管脚的PWM由定时器TIMER1产生，这句程序改变PWM的频率，勿删
  TCCR1B = TCCR1B & B11111000 | B00000001 ;
  pinMode( ENCODER_A1, INPUT);
  pinMode( ENCODER_B1, INPUT);
  pinMode( ENCODER_A2, INPUT);
  pinMode( ENCODER_B2, INPUT);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(INL11, OUTPUT);
  pinMode(INL12, OUTPUT);
  pinMode(INL21, OUTPUT);
  pinMode(INL22, OUTPUT);
  attachInterrupt(1, getEncoder1, CHANGE);
  attachInterrupt(0, getEncoder2, CHANGE);
  Serial.begin (9600);
  MsTimer2::set(PERIOD, control);
  MsTimer2::start();
}
void loop()
{
  //撰写代码，使其能够通过“串口绘图器”观察速度波形

  /*
    Serial.print ("velocity1: ");
    Serial.print (velocity1);
    Serial.print ("     velocity2: ");
  */
  /*
  Serial.println(micros()-ti);
  ti=micros();
   */
 
  //Serial.println (velocity1);
  /*
    Serial.print("\r\n");
    infrared();
    for (int i = 1; i < 8; i++)
    {
    Serial.print(sensor[i]);
    Serial.print(" ");

    }
    Serial.println();
    delay(500);
  */

  /**/
}
int pidController1( float targetVelocity, float currentVelocity)
{
  float ek10;
  ek10 = targetVelocity - currentVelocity;
  u1 = u1 + q01 * ek10 + q11 * ek11 + q21 * ek12;
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
  u2 = u2 + q02 * ek20 + q12 * ek21 + q22 * ek22;
  if (u2 > 255)
    u2 = 255;
  if (u2 < -255)
    u2 = -255;
  ek22 = ek21;
  ek21 = ek20;
  return (int)u2;
}
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
void control_inital(void)
{
  velocity1 = (encoderVal1 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal1 = 0;
  int output1 = pidController1(-target1, velocity1);
  if (output1 > 0)
  {
    digitalWrite(INL11, LOW);
    digitalWrite(INL12, HIGH);
    analogWrite(PWM1, output1);
  }
  else
  {
    digitalWrite(INL11, HIGH);
    digitalWrite(INL12, LOW);
    analogWrite(PWM1, abs(output1));
  }

  velocity2 = (encoderVal2 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal2 = 0;
  int output2 = pidController2(target2, velocity2);
  if (output2 > 0)
  {
    digitalWrite(INL21, LOW);
    digitalWrite(INL22, HIGH);
    analogWrite(PWM2, output2);
  }
  else
  {
    digitalWrite(INL21, HIGH);
    digitalWrite(INL22, LOW);
    analogWrite(PWM2, abs(output2));
  }
}
