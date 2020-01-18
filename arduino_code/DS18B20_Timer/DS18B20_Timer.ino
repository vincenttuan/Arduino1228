#include <Timer.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#define pin 7
#define led 13
#define buzzer 8

OneWire ds(pin); // 初始化 ds 物件
DallasTemperature DS18B20(&ds); // 初始化 DS18B20 物件

Timer t; // 宣告 Timer 物件

float data; // 溫度資料
float warnning = 30; // 警告溫度

void setup() {
  Serial.begin(9600);
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  DS18B20.begin(); // DS18B20 啟動
  t.every(500, call_temperature);
  t.every(500, call_led);
  t.every(500, call_buzzer);
}

void loop() {
  t.update();  
}

void call_temperature() {
  DS18B20.requestTemperatures(); // DS18B20 開始偵測環境溫度
  data = DS18B20.getTempCByIndex(0); // 取得溫度 ( 攝氏 --> TempC )
  Serial.println(data, 2); // 溫度取到小數點第 2 位
}

void call_led() {
  if(data > warnning) {
    digitalWrite(led, HIGH);  
  } else {
    digitalWrite(led, LOW);    
  }
}


void call_buzzer() {
  if(data > warnning) {
    digitalWrite(buzzer, HIGH);  
  } else {
    digitalWrite(buzzer, LOW);    
  }
}
