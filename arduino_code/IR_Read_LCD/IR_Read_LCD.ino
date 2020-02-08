#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library
#define IP_PIN A3
#define I2C_ADDR  0x3F  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件

void setup() {
  Serial.begin(9600);
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("IR Value") ;
}

void loop() {
  int ir_value = analogRead(IP_PIN);
  Serial.println(ir_value);
  lcd.setCursor(0, 1); //Start at character 0 on line 0
  lcd.print(ir_value) ;
  lcd.print("    ");
  delay(200);
}
