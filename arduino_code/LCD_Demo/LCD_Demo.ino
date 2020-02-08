/***********************************************************
 * I2C LCD 接線說明
 * SDA – 接 Arduino 的 A4
 * SCL – 接 Arduino 的 A5
 * GND – 接 GND
 * VCC – 接 +5V
 ***********************************************************/

#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library

#define I2C_ADDR  0x27  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件

void setup() {
  Serial.begin(9600);
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("Hello LCD") ;
  lcd.setCursor(0, 1); //Start at character 0 on line 1
  lcd.print("N: ") ;
}

int n = 0;
void loop() {
  lcd.setCursor(3, 1); //character 3 on line 1
  lcd.print(n++);
  delay(10);
}
