#include <Wire.h>
#include <HTU21D.h>

HTU21D htu; // 宣告 HTU21D
void setup() {
  Serial.begin(9600);
  Serial.println("HTU21D !");
  htu.begin();
}

void loop() {
  float humidity = htu.readHumidity(); // 取得濕度
  float temperature = htu.readTemperature(); // 取得溫度
  Serial.print("Time:");
  Serial.print(millis()/1000); // 時間
  Serial.print(" Temperature:");
  Serial.print(temperature, 2); 
  Serial.print(" C");
  Serial.print(" Humidity:");
  Serial.print(humidity, 2);
  Serial.print(" %");
  Serial.println();
  delay(1000);
}
