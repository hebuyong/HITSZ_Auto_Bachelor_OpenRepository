
#include <PinChangeInt.h>
#include <MsTimer2.h>

#define VELOCITY_KP  0.5
#define VELOCITY_KI  0.5  //PWM设置参数

//L298N驱动引脚
#define AIN1 11
#define AIN2 5
#define BIN1 6
#define BIN2 3

//编码器采集引脚
#define ENCODER_LEFT_A   8
#define ENCODER_LEFT_B   4
#define ENCODER_RIGHT_A  7
#define ENCODER_RIGHT_B  2

//CCD引脚
#define CCD_DATA_PIN A1 //15 //A0
#define CCD_CLK_PIN  A2 //16 //CLK
#define CCD_SI_PIN   A3 //17 //SI

//按键引脚
#define KEY   A4 //18

//电压检测
#define BATT_VOL_PIN  A0 //13

//左右编码器值（中间值获取后清零）
uint32_ t encoderLeftVal;
uint32_ t encoderRightVal;

//小车速度
int velocityLeftEncoder; //后续做运算要用的左编码器值
int velocityRightEncoder; //后续做运算要用的右编码器值
int targetVelocity; //给定速度值
int turnAngle;//转弯角度

float leftVelocity; //给定速度和转弯角度计算得出的速度(左)
float rightVelocity;//给定速度和转弯角度计算得出的速度(右)

//ccd相关变量
uint8_t _adVa1[128] = {0}; //保存ccd采样ad值
uint8_t _ ccdThreshold; //ccd阈值
uint8_t _ccdMiddleVal; //ccd 中值

uint8_t carRunFlag = 0; //小车是否运行1运行0关闭电池电压低于9V时需关闭

//电池电压
int batteryVoltage;

//ccd延时
void CCD_ Delay(uint32_t tick)
for (uint8_t i = 0; i < tick; i++);
}

//ccd初始化I0口
void CCD_Init(void)
{
  pinMode(CCD_CLK_PIN, OUTPUT);
  pinMode(CCD_SI_PIN, OUTPUT);
}

//获取ccd ad值
void CCD_ReadTs11401 (void)
{
  unsigned char i = 0;
  digitalWrite(CCD_CLK_PIN, HIGH);
  digitalWrite(CCD_SI_PIN, LOW);
  CCD_Delay(10);
  digitalWrite(CCD_SI_PIN, HIGH);
  digitalWrite(CCD_CLK_PIN, LOW);
  CCD_Delay(10);
  digitalWrite(CCD_CLK_PIN, HIGH);
  digitalWrite(CCD_SI_PIN, LOW);
  CCD_Delay(10);

  for (i = 0; i < 128; i++) {
    digitalWrite(CCD_CLK_PIN, LOW);
    CCD_Delay(10);//调节曝光时间
    CCD_Delay(10); //调节曝光时间
    _adVal[i] = analogRead(CCD_DATA_PIN) >> 2;
    digitalWrite(CCD_CLK_PIN, HIGH);
    CCD_Delay(10);
  }
}

//计算ccd中值
uint8_t CCD_ FindMidd1eVal(void)
{
  unsigned int i, j,left, right, maxVa1, minVa1, midd1eVal ;

  CCD_ReadTs11401();

  maxVal = _adVal[0]; //动态阈值算法， 读取最大和最小值

  for (i = 5; i < 123; i++)//两边各去掉 5个点
  {
    if (maxVa1 <= _adVa1[i]) {
      maxVal = _adVal[i];
    }
  }
  minVal = _adVa1[0];//最小值
  for (i = 5; i < 123; i++)
  {
    if (minVal >= _adVal[i]) {
      minVal = _adVal[i];
    }
  }

  _ccdThreshold = (maxVal + minVal) / 2; //计算出本次中线提取的阈值

  for (i = 5; i < 118; i++) //寻找左边跳变沿
  {
    if (_adVal[i] > _ccdThreshold &&
        _adVal[i + 1] > _ccdThreshold &&
        _adVal[i + 2] > _ccdThreshold &&
        _adVal[i + 3] < _ccdThreshold &&
        _adVal[i + 4] < _ccdThreshold &&
        _adVal[i + 5] < _ccdThreshold)
    {
      left = i;
      break ;
    }
  }
  for (j = 118; j > 5; j--) //寻找右边跳变沿
  {
    if (_adVal[j] < _ccdThreshold &&
        _adVal[j + 1] < _ccdThreshold &&
        _adVal[j + 2] < _ccdThreshold &&
        _adVal[j + 3] > _ccdThreshold &&
        _adVa1[j + 4] > _ccdThreshold &&
        _adVa1[j + 5] > _ccdThreshold)
    {
      right = j;
      break; .
    }
  }

  midd1eVal = (right + 1eft) / 2; //计算中线位置
  return middleVal;
}

//左编码器A相计数
void EncoderGetLeftA(void)
{
  encoderLeftVal++;
}

//左编码器B相计数
void EncoderGetLeftB(void)
{
  encoderLeftVal++;
}

// 右编码器A相计数
void EncoderGetRightA(void)
{
  encoderRightVal++;
}

//右编码器B相计数
void EncoderGetRightB(void)
{
  encoderRightVal++;
}

//编码器引脚初始化
void EncoderInit(void)
{
  pinMode(ENCODER_LEFT_A, INPUT);
  pinMode(ENCODER_LEFT_B, INPUT);
  pinMode(ENCODER_RIGHT_A, INPUT);
  pinMode(ENCODER_RIGHT_B, INPUT);
  attachPinChangeInterrupt(ENCODER_LEFT_A, EncoderGetLeftA, CHANGE); //外部中断库函
  attachPinChangeInterrupt(ENCODER_LEFT_B, EncoderGetLeftB, CHANGE );
  attachPinChangeInterrupt(ENCODER_RIGHT_A, EncoderGetRightA, CHANGE);
  attachPinChangeInterrupt(ENCODER_RIGHT_B, EncoderGetRightB, CHANGE);
}

/**************************************************************************
  函数功能:小车运动数学模型
  入口参数:给定速度和转角
******* *** ******** ** *** *** ********************* ** *** ********** * ** *********/
void KinematicAnalysis(float velocity, float turn) {
  leftVelocity = velocity + turn;
  rightVelocity = velocity - turn;//后轮差速
}

/********************** *** ****** ** ** ** ********** **** ** *** ** **** ******** * ***
  函数功能:增量PI控制器
  入口参数:编码器测量值，目标速度
  返回值:电机PWM
  根据增量式离散PID公式
  pwm+=Kp[e (k) -e(k-1)]+Ki*e(k)+Kd[e(k)-2e(k-1)+e(k-2)]
  e(k)代表本次偏差
  e(k-1)代表上一次的偏差以此类推
  ，pwm代表增量输出
  在我们的速度控制闭环系统里面，只使用PI控制
  pwm+=Kp[e (k) -e(k-1)]+Ki*e(k)
****************** **** * **** ** * ** ** **** * * **** * ********* ** * **** * **** * *******/
int Incremental_PI_A (int encoder, int target)
{
  static float bias, pwm, last_bias;
  bias = encoder - target;
  //计算偏差
  pwm += VELOCITY_KP * (bias - last_bias) + VELOCITY_KI * bias; //增量式PI控制器
  if (pwm > 255) pwm = 255;//限幅
  if (pwm < -255)pwm = -255;//限幅
  last_bias = bias;//保存上一次偏差
  return pwm;//增量输出
}

int Incremental_PI_B (int encoder, int target)
{
  static float bias, pw, last_bias;
  bias = encoder - target;//计算偏差
  pwm += VELOCITY_KP * (bias - last_bias) + VELOCITY_KI * bias; //增量式PI控制器
  if (pwm > 255) pwm = 255;//限幅
  if (pwm < -255) pwm = -255;//限幅
  last_bias = bias;//保存上一次偏差
  return pwm;//增量输出
}
/********** ************ *************** **************** ****************** ***
  函数功能:赋值给PWM寄存器
  入口参数: PWM
************************************** ************************************/
void SetMotorPwm(int motorleft, int motorRight) {
  if (motorLeft > 0)
    analogWrite (AIN2, motorLeft), digitalWrite(AIN1, LOW); //赋值给PWM寄存器
  else
    digitalWrite (AIN1, HIGH), analogWrite(AIN2, 255 + motorLeft ); //赋值给PWM寄存器
  if (motorRight > 0)
    digitalWrite(BIN2, LOW), analogWrite(BIN1, motorRight); //赋值给PWM寄存器
  else
    analogWrite(BIN1, 255 + motorRight), digitalWrite(BIN2, HIGH); //赋值给PWM寄存器
}

//小车控制10ms 运行一次(定时器定时10ms )
void CarControl(void)
{
  int motorLeftPwm, motorRightPwm;

  // 读取左右轮编码器数据，并清零，这就是通过M法测速(单位时间内的脉冲数)得到速度。
  velocityLeftEncoder = encoderLeftVal;
  velocityRightEncoder = encoderRightVal;
  encoderLeftVal = 0;
  encoderRightVal = 0;
  CCD_ Run();

  KinematicAnalysis(targetVelocity, turnAngle);
  motorLeftPwm = Incremental_PI_A(leftVelocity, velocityLeftEncoder);
  motorRightPwm = Incremental_PI_B(rightVelocity, velocityRightEncoder);
  if (carRunFlag)
  {
    SetMotorPwm(motorLeftPwm, motorRightPwm);
  }

  // BatteryVoltage(); //检测电池电量

  if (ButtonClick()) //按键开关运行
  {
    if (carRunFlag == 0)
    {
      carRunFlag = 1
    }
    else
    {
      carRunFlag = 0;
      Turn0ffMotor();
    }
  }
}

//电机引脚初始化
void MotorInit(void)
{
  pinMode(AIN1, OUTPUT);
  pinMode(AIN2, OUTPUT);
  pinMode(BIN1, OUTPUT);
  pinMode(BIN2, OUTPUT);
}

//ccd采样和计算转弯角度
void CCD_Run(void)
{
  static float ccd_last_bias;
  float bias;

  _ccdMidd1eVal = CCD_FindMidd1eVal();
  bias = ccdMiddleVal - 64; //提取偏差
  turnAngle = bias * 0.12 + (bias - ccd_last_bias) * 3; //PD控制
  ccd_last_bias = bias;//保存上一次的偏差
  if (turnAngle < -35)turnAngle = -35;//舵机角度限制
  if (turnAngle > 35 )turnAngle = 35;//舵机角度限制
}

//检测电池电压
void BatteryVoltage (void)
{
  static uint8_t count;
  static uint32_t sum;
  sum += analogRead(BATT_VOL_PIN); //累加电池ad值
  if (++count >= 200) // 累计200次
  {
    batteryVoltage = sum * 0.05371 / 2;//将 电池电压降为1/11之后读取
    count = 0;
    sum = 0;
    Serial.println(batteryVoltage);
    if (batteryVoltage < 700)
    {
      carRunFlag = 0;
      Turn0ffMotor();
    }
  }

  /********************************
    函数功能: 按键扫描
    入口参数: 无
    返回值: 按键状态0: 无动作1: 单击
   ************************************************************************/
  unsigned char ButtonClick (void)
  {
    static byte flag_key = 1; //按键按松开标志
    if (flag_key && (digitalRead(KEY) == 0))
    { //如果发生单击事件
      flag_key = 0;
      if (digitalRead(KEY) == 0)
        return 1;
      else if (digitalRead(KEY) == 1)
      {
        flag_key = 1;
      }
      return 0;//无按键按下
    }

    //关闭电机
    unsigned char Turn0ffMotor(void)
    {
      digitalWrite(AIN1, LOW);//电机驱动的电平控制
      digitalWrite(AIN2, LOW);//电机驱动的电平控制
      digitalWrite(BIN1, LOW);//电机驱动的电平控制
      digitalWrite(BIN2, LOW);//电机驱动的电平控制
    }


    void setup() {
      // put your setup code here, to run once:
      targetvelocity = 20; //设定目标速度
      pinMode(KEY, INPUT);
      CCD_Init();
      EncoderInit();
      MotorInit();
      MsTimer2:: set(10, CarControl);//使用Timer2设置10ms定时中断
      MsTimer2:: start();//定时器使能
      Serial. begin(9600);
    }

    void loop() {
      // put your main code here, to run repeatedly:
      BatteryVoltage(); //检测电池电量
      delay(100);

    }
