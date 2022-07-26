#define PIN_PWMA 11//定义PWM输出引脚
#define PIN_AIN2 13//定义正反转控制引脚
#define PIN_AIN1 12//定义正反转控制引脚

#define PIN_PWMB 5//定义PWM输出引脚
#define PIN_AIN3 6//定义正反转控制引脚
#define PIN_AIN4 7//定义正反转控制引脚

void setup()
{
  pinMode(PIN_PWMA, OUTPUT); //定义引脚为输出
  pinMode(PIN_AIN2, OUTPUT);
  pinMode(PIN_AIN1, OUTPUT);

  pinMode(PIN_PWMB, OUTPUT); //定义引脚为输出
  pinMode(PIN_AIN3, OUTPUT);
  pinMode(PIN_AIN4, OUTPUT);
}

void loop()
{

  for (int i = 1; i < 255; i += 50)
  {
    analogWrite(PIN_PWMA, i);
    digitalWrite(PIN_AIN2, HIGH);
    digitalWrite(PIN_AIN1, LOW);

    analogWrite(PIN_PWMB, i);
    digitalWrite(PIN_AIN3, HIGH);
    digitalWrite(PIN_AIN4, LOW);
    
    delay(1000);
  }
  for (int i = 255; i >0; i -= 50)
  {
    analogWrite(PIN_PWMA, i);
    digitalWrite(PIN_AIN2, HIGH);
    digitalWrite(PIN_AIN1, LOW);

    analogWrite(PIN_PWMB, i);
    digitalWrite(PIN_AIN3, HIGH);
    digitalWrite(PIN_AIN4, LOW);
    
    delay(1000);

    /*analogWrite(PIN_PWM, i);
      digitalWrite(PIN_AIN2, LOW);
      digitalWrite(PIN_AIN1, HIGH);
      delay(100);*/
  }
  /*analogWrite(PIN_PWM, 100);
    digitalWrite(PIN_AIN2, HIGH);
    digitalWrite(PIN_AIN1, LOW);
    delay(3000);

    analogWrite(PIN_PWM, 100);
    digitalWrite(PIN_AIN2, LOW);
    digitalWrite(PIN_AIN1, HIGH);
    delay(3000);

    analogWrite(PIN_PWM, 200);
    digitalWrite(PIN_AIN2, HIGH);
    digitalWrite(PIN_AIN1, LOW);
    delay(3000);

    analogWrite(PIN_PWM, 200);
    digitalWrite(PIN_AIN2, LOW);
    digitalWrite(PIN_AIN1, HIGH);
    delay(3000);*/
}
