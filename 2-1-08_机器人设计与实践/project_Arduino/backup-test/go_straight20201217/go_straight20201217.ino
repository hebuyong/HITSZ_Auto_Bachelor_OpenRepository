#include<MsTimer2.h>//定时器库的头文件
//--------------定义管脚----------
#define ENCODER_A1 2 //电机1
#define ENCODER_B1 4
#define PWM1 10
#define INL11 13
#define INL12 12

#define ENCODER_A2 3 //电机2
#define ENCODER_B2 5
#define PWM2 9
#define INL21 11
#define INL22 8

//----------------定义常值------------
#define PERIOD 20
#define Kp1 7.0
#define Ti1 50.0
#define Td1 10.0


#define Kp2 7.0
#define Ti2 50.0
#define Td2 10.0


//-----------全局变量----------
float target1 = 10.0, t1; //左保守
float target2 = 10.0, t2; //右速度
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
float u1, ek11, ek12;
float u2, ek21, ek22;
//-----------------测试与转向---------

//float V =6.0; //基础速度
void control(void) {
  velocity1 = (encoderVal1 / 780.0) * 3.1415 * 2.0 * (1000 / PERIOD);
  encoderVal1 = 0;
  int output1 = pidController1(target1, velocity1);
  if(output1>0)
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
  int output2 = pidController2(-target2, velocity2);
  if(output2>0)
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

void setup() {
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
  attachInterrupt(0, getEncoder1, CHANGE);
  attachInterrupt(1, getEncoder2, CHANGE);
  Serial.begin (9600);
  MsTimer2::set(PERIOD, control);
  MsTimer2::start();
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

int pidController2(float targetVelocity, float currentVelocity) {
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
void loop() {
 //撰写代码，使其能够通过“串口绘图器”观察速度波形
  Serial.print ("velocity1: ");
  Serial.print (velocity1);
  Serial.print("\r\n");
  Serial.print ("velocity2: ");
  Serial.print (velocity2);
  Serial.print("\r\n");

}
