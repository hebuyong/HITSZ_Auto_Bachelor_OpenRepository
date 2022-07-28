#include<MsTimer2.h>//定时器库的头文件  
//------------------电机相关-------------------
//----左侧电机----
#define ENCODER_A1 3  //编码器
#define ENCODER_B1 5
#define PWM2 9        //PWM波控制转速
#define IN3 11
#define IN4 8
volatile long  encoderVal1;  //编码器值
float target1;              //左侧目标角速度（弧度）
float t1;                   //左侧上一次目标角速度（弧度）
float velocity1;            //左侧实际转速
//----右侧电机----
#define ENCODER_A2 2  //编码器
#define ENCODER_B2 4
#define PWM1 10        //PWM波控制转速
#define IN1 13
#define IN2 12
volatile long encoderVal2;  //编码器2值
float target2;              //右侧目标角速度（弧度）
float t2;                   //右侧上一次角速度（弧度）
float velocity2;            //右侧实际转速
//------------------红外探测-------------------
#define L1 17 //左红外 
#define L2 18
#define L3 19
#define R1 15 //右红外 
#define R2 14
#define R3 0
#define M  16 //中红外 
//-------------------定义常值------------------
#define PERIOD 20
#define Kp 10
#define Ti 50
#define Td 10
#define V 20
//-----------------控制算法变量-----------------
float T = PERIOD;
float q0 = Kp * (1 + T / Ti + Td / T);
float q1 = -Kp * (1 + 2 * Td / T);
float q2 = Kp * Td / T;
float u1 = 0, u2 = 0, ek11, ek12, ek21, ek22;
//-------------------函数声明------------------
int pidController1(float targetVelocity, float currentVelocity);
int pidController2(float targetVelocity, float currentVelocity);
void getEncoder1(void);
void getEncoder2(void);
//-------------------初始化-------------------
void setup()
{
  //9,10两个管脚的PWM由定时器TIMER1产生，这句程序改变PWM的频率，勿删
  TCCR1B = TCCR1B & B11111000 | B00000001;
  MsTimer2::set(PERIOD, control);
  MsTimer2::start();
  pinMode(ENCODER_A1, INPUT);
  pinMode(ENCODER_B1, INPUT);
  pinMode(ENCODER_A2, INPUT);
  pinMode(ENCODER_B2, INPUT);
  attachInterrupt(0, getEncoder1, CHANGE);
  attachInterrupt(1, getEncoder2, CHANGE);
  Serial.begin(9600);
  pinMode(PWM1, OUTPUT);
  pinMode(PWM2, OUTPUT);
  pinMode(IN1, OUTPUT);
  pinMode(IN2, OUTPUT);
  pinMode(IN3, OUTPUT);
  pinMode(IN4, OUTPUT);
  pinMode(R1, INPUT);
  pinMode(R2, INPUT);
  pinMode(R3, INPUT);
  pinMode(L1, INPUT);
  pinMode(L2, INPUT);
  pinMode(L3, INPUT);
  pinMode(M, INPUT);
}
//-------------------循环执行-------------------
void loop()
{
  Serial.println(velocity1);
  Serial.print("\n");
  Serial.println(velocity2);
}
//----------测速与转向------------
void control(void)
{
  if (digitalRead(R3) == HIGH) //小弯右转
  {
    target1 = V * 1;
    target2 = V * -0.5;
  }
  else if (digitalRead(R3) == HIGH) //小弯右转
  {
    target1 = V * 1;
    target2 = V * -0.5;
  }
  else if (digitalRead(R3) == HIGH) //小弯右转
  {
    target1 = V * 1;
    target2 = V * 0;   //
  }
  else if (digitalRead(L3) == HIGH) //小弯左转
  {
    target1 = V * 0;   //之前是0.3
    target2 = V * 1;
  }
  else if (digitalRead(R2) == HIGH) //稍微右转
  {
    target1 = V * 1;
    target2 = V * 0.4;
  }
  else if (digitalRead(L2) == HIGH) //稍微左转
  {
    target1 = V * 0.4;
    target2 = V * 1;
  }
  else if (digitalRead(R1) == HIGH) //直线保持
  {
    target1 = V * 1;
    target2 = V * 0.9;
  }
  else if (digitalRead(L1) == HIGH) //直线保持
  {
    target1 = V * 0.9;
    target2 = V * 1; 
  }
  else if (digitalRead(M) == HIGH)
  {
    target1 = V;
    target2 = V;
  }
  target1 = target1 * 0.6 + t1 * 0.4;
  target2 = target2 * 0.6 + t2 * 0.4;
  velocity1 = (-encoderVal1 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal1 = 0;
  velocity2 = (encoderVal2 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal2 = 0;
  int output1 = pidController1(target1, velocity1);
  if (output1 > 0)
  {
    digitalWrite(IN3, HIGH);
    digitalWrite(IN4, LOW);
    analogWrite(PWM2, output1);
  }
  else
  {
    digitalWrite(IN3, LOW);
    digitalWrite(IN4, HIGH);
    analogWrite(PWM2, abs(output1));
  }
  int output2 = pidController2(target2, velocity2);
  if (output2 > 0)
  {
    digitalWrite(IN1, LOW);
    digitalWrite(IN2, HIGH);
    analogWrite(PWM1, output2);
  }
  else
  {
    digitalWrite(IN1, HIGH);
    digitalWrite(IN2, LOW);
    analogWrite(PWM1, abs(output2));
  }
  t1 = target1;
  t2 = target2;
}

//--------------------编码器中断函数-------------------
void getEncoder1(void)
{
  if (digitalRead(ENCODER_A1) == LOW)
  {
    if (digitalRead(ENCODER_B1) == LOW)
    {
      encoderVal1--;
    }
    else
    {
      encoderVal1++;
    }
  }
  else
  {
    if (digitalRead(ENCODER_B1) == LOW)
    {
      encoderVal1++;
    }
    else
    {
      encoderVal1--;
    }
  }
}
void getEncoder2(void)
{
  if (digitalRead(ENCODER_A2) == LOW)
  {
    if (digitalRead(ENCODER_B2) == LOW)
    {
      encoderVal2--;
    }
    else
    {
      encoderVal2++;
    }
  }
  else
  {
    if (digitalRead(ENCODER_B2) == LOW)
    {
      encoderVal2++;
    }
    else
    {
      encoderVal2--;
    }
  }
}

//------------------PID控制器-------------------
int pidController1(float targetVelocity, float currentVelocity)
{
  float ek10;
  ek10 = targetVelocity - currentVelocity;
  u1 = u1 + q0 * ek10 + q1 * ek11 + q2 * ek12;
  if (u1 > 255)
  {
    u1 = 255;
  }
  if (u1 < -255)
  {
    u1 = -255;
  }
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
  {
    u2 = 255;
  }
  if (u2 < -255)
  {
    u2 = -255;
  }
  ek22 = ek21;
  ek21 = ek20;
  return (int)u2;
}
