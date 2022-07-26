#include "DHT.h" // 温湿度传感器的头文件，加载库要选择 1.2.3 版本 
#include <Adafruit_SSD1306.h> // OLED 屏幕的头文件 
//温湿度传感器 
#define DHTPIN 8 // 连接温湿度传感器的管脚为 Arduino 的管脚 8 
#define DHTTYPE DHT11 // 温湿度传感器为 DHT11 
DHT dht(DHTPIN, DHTTYPE); //建立温湿度传感器的对象 
//OLED 
Adafruit_SSD1306 oled; 
void setup() { 
 Serial.begin(9600); 
 Serial.println("DHTxx test!"); 
 dht.begin(); //初始化温湿度传感器
  oled.begin(SSD1306_SWITCHCAPVCC, 0x3C); // OLED 屏幕初始化，其接口 I2C的地址为 0x3C (for the 128x64) 
 oled.clearDisplay(); // 清除屏幕 
 oled.display(); // 执行显示,这一步非常重要，每一次显示，都需要运行这一函数 
} 
void loop() { 
 delay(800); // 两次测量间隔一段时间 
 // 读取温湿度值需要 250 ms 左右! 
 float h = dht.readHumidity(); 
 // 读取温度单位为摄氏度 (默认) 
 float t = dht.readTemperature(); 
 // 读取温度单位为 Fahrenheit 
 float f = dht.readTemperature(true); 
 // 判断所获取的数字是否错误 
 if (isnan(h) || isnan(t) || isnan(f)) { 
 Serial.println("Failed to read from DHT sensor!"); 
 return; 
 } 
 Serial.print("Humidity: "); 
 Serial.print(h); 
 Serial.print(" %\t"); 
 Serial.print("Temperature: "); 
 Serial.print(t); 
 Serial.print(" *C "); 
 Serial.print(f); 
 Serial.println(" *F\t"); 
 //OLED 屏幕显示温湿度 
 oled.setTextSize(1); //设置屏幕文字大小 
 oled.setTextColor(WHITE); //设置屏幕文字颜色 
 oled.setCursor(0, 0); //设置文字显示坐标 
 oled.clearDisplay(); //清除屏幕 
 oled.print("Humidity: "); //显示文字 
 oled.print(h); 
 oled.println(" %"); 
 oled.print("Temperature: "); 
 oled.print(t);
 oled.println(" *C"); 
 oled.print(f); 
 oled.println(" *F"); 
 oled.display(); 
}
