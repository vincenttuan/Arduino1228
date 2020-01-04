#include <OneWire.h>
#include <DallasTemperature.h>
#define pin 7

OneWire ds(pin); // 初始化 ds 物件
DallasTemperature DS18B20(&ds); // 初始化 DS18B20 物件

void setup() {
  Serial.begin(9600);
  DS18B20.begin(); // DS18B20 啟動
}

void loop() {
  DS18B20.requestTemperatures(); // DS18B20 開始偵測環境溫度
  float data = DS18B20.getTempCByIndex(0); // 取得溫度 ( 攝氏 --> TempC )
  Serial.println(data, 2); // 溫度取到小數點第 2 位
  delay(100);
}
