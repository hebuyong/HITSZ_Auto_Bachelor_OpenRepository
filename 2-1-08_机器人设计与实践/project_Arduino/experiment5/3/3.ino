#define ENCODER_A 2 // 编码器读取采用中断方式，该引脚为第0个中断接口
#define ENCODER_B 5
long encoderVal; //左编码器值
//函数功能:外部中断读取编码器数据，具有二倍频功能注意外部中断是跳变沿触发
void getEncoder(void) {
  if (digitalRead(ENCODER_A) == LOW)
  { //如果是下降沿触发的中断
    if (digitalRead(ENCODER_B) == LOW)
    {
      encoderVal--; //根据另外一相电平判定方向
    }
    else
    {
      encoderVal++;
    }
  }
  else
  { //如果是上升沿触发的中断

    if (digitalRead(ENCODER_B) == LOW)
    {
      encoderVal++; //根据另外一相电平判定方向
    }
    else
    {
      encoderVal--;
    }
  }
}
void setup()
{
  //编码器引脚都设置输入
  pinMode( ENCODER_A, INPUT);
  pinMode(ENCODER_B, INPUT); //此处有错误，请找出并纠正
  //下面这一条语句此处有错误，请找出并纠正
  attachInterrupt(0,getEncoder,CHANGE); //2改成1，使能编码器引脚外部中断0,对应Arduino引脚2
  Serial.begin(9600);
}
void loop()
{
  delay(100);
  Serial.print("encoder val=");
  Serial.print(encoderVal);
  Serial. print("\r\n" );
}
