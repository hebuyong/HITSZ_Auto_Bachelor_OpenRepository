//定义CCD引脚
#define A0_PIN  14//A0
#define CLK_PIN 15//A1
#define SI_PIN  16//A2
uint8_t _adVal[128];      //存储CCD采样的AD值
uint8_t _ccdThreshold;    //CCD阈值
//初始化ccd引脚
void ccdInit(void)
{
  pinMode(CLK_PIN,OUTPUT);
  pinMode(SI_PIN,OUTPUT);
  pinMode(A0_PIN,OUTPUT);
  digitalWrite(CLK_PIN,LOW);
  digitalWrite(SI_PIN,LOW);
}
//CCD的AD采样
void readTsl1401(void)
{
  uint8_t i=0;
  //曝光，看不懂程序的，参考CCD的图1逻辑，或者百度TSL1401心得，有很多资料
  digitalWrite(SI_PIN,HIGH);
  digitalWrite(CLK_PIN,HIGH);
  delayMicroseconds(1);
  digitalWrite(SI_PIN,LOW);
  digitalWrite(CLK_PIN,LOW);
  for (i=0;i<129;i++)
  {
    digitalWrite(CLK_PIN,HIGH);
    digitalWrite(CLK_PIN,LOW);
  }
  delay(30);  //这里30ms是调整曝光时间，不同的值会获得不同的采样值
  //读取像素值
  digitalWrite(SI_PIN,HIGH);
  digitalWrite(CLK_PIN,HIGH);
  digitalWrite(SI_PIN,LOW);
  delayMicroseconds(1);
  for (i=0;i<128;i++)
  {
    _adVal[i]=analogRead(A0_PIN)>>2;//Arduino UNO的模拟数字采样是10位的，最大值为1023
    digitalWrite(CLK_PIN,LOW);
    digitalWrite(CLK_PIN,HIGH);
    delayMicroseconds(2);
  }
  digitalWrite(CLK_PIN,HIGH);
  digitalWrite(CLK_PIN,LOW);
}
uint8_t ccdFindMidVal(void) //CCD寻找中值函数返回值为中值
{
  uint8_t i,j,left,right,_ccdMidVal;
  float maxVal,minVal;
  readTsl1401();
  maxVal=_adVal[0]; //动态阈值算法，读取最大和最小值
  for (i=5;i<123;i++) //两遍各去掉5个点
  {
    if (maxVal<=_adVal[i])
    {
      maxVal=_adVal[i];
    }
  }
  minVal=_adVal[0]; //最小值
  for (i=5;i<123;i++)
  {
    if (minVal>=_adVal[i])
    {
      minVal=_adVal[i];
    }
  }
  _ccdThreshold=(maxVal+minVal)/2.0;  //计算出本次中线提取的阈值
  left=0;
  for (i=5;i<118;i++) //寻找左边跳变沿
  {
    if (_adVal[i]>_ccdThreshold &&
        _adVal[i+1]>_ccdThreshold &&
        _adVal[i+2]>_ccdThreshold &&
        _adVal[i+3]<_ccdThreshold &&
        _adVal[i+4]<_ccdThreshold &&
        _adVal[i+5]<_ccdThreshold)
        {
          left=i;
          break;
        }
  }
  right=128;
  for (j=118;j>5;j--) //寻找右边跳变沿
  {
    if (_adVal[j]<_ccdThreshold &&
        _adVal[j+1]<_ccdThreshold &&
        _adVal[j+2]<_ccdThreshold &&
        _adVal[j+3]>_ccdThreshold &&
        _adVal[j+4]>_ccdThreshold &&
        _adVal[j+5]>_ccdThreshold)
        {
          right=j;
          break;
        }
  }
  if (left==0||right==128)  //未检测到边沿
  {
    _ccdMidVal=255;
  }
  else
  {
    _ccdMidVal=(uint8_t)((right+left)/2); //计算中线位置
  }
  return _ccdMidVal;
}
void setup()
{
  ccdInit();
  Serial.begin(9600);
}
void loop()
{
  uint8_t midVal=ccdFindMidVal();
  //Serial.print("CCD Middle Value = ");
  //Serial.println(midVal);
  for (int i=5;i<123;i++)
  {
    Serial.println(_adVal[i]);
  }
  delay(100);
}
