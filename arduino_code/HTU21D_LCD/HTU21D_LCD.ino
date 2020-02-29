#include <Timer.h>
#include <Wire.h>
#include <HTU21D.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library

#define I2C_ADDR  0x27  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件
HTU21D htu; // 宣告 HTU21D
float humidity, temperature;
Timer t; // 宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  Serial.println("HTU21D !");
  htu.begin();
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0);
  lcd.print("Humi: ");
  lcd.setCursor(0, 1);
  lcd.print("Temp: ");
  t.every(100, detectHtu21d);
  t.every(500, showInLCD);
}

void loop() {
  t.update();
}

void detectHtu21d() {
  humidity = htu.readHumidity(); // 取得濕度
  temperature = htu.readTemperature(); // 取得溫度
  Serial.print("Time:");
  Serial.print(millis()/1000); // 時間
  Serial.print(" Temperature:");
  Serial.print(temperature, 2); 
  Serial.print(" C");
  Serial.print(" Humidity:");
  Serial.print(humidity, 2);
  Serial.print(" %");
  Serial.println();
}

void showInLCD() {
  lcd.setCursor(6, 0); //Start at character 0 on line 0
  lcd.print(humidity);
  lcd.print(" %");
  lcd.setCursor(6, 1); //Start at character 0 on line 0
  lcd.print(temperature);
  lcd.print(" C");
}
