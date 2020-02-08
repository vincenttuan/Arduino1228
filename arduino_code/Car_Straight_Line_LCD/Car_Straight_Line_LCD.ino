#include <Timer.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library

#define M1_pin 5 // Rifgt ENB
#define M2_pin 6 // Left ENA
#define L1_pin 12 // IN1 F
#define L2_pin 11 // IN2 B
#define R1_pin 10  // IN3 F
#define R2_pin 9 // IN4 B
#define SW_Left_pin A1
#define SW_Right_pin A2
#define I2C_ADDR  0x3F  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件

int default_power = 150;
int right_power = default_power;
int left_power = default_power;

Timer t; // 宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
  pinMode(SW_Left_pin, INPUT_PULLUP);
  pinMode(SW_Right_pin, INPUT_PULLUP);
  
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0);
  lcd.print("L:");
  lcd.setCursor(0, 1);
  lcd.print("R:");
  t.every(0, car);
  t.every(10, showInLCD);
}

void loop() {
  t.update();
}

void car() {
  analogWrite(M1_pin, right_power);
  analogWrite(M2_pin, left_power);
  digitalWrite(L1_pin, HIGH);
  digitalWrite(L2_pin, LOW);
  digitalWrite(R1_pin, HIGH);
  digitalWrite(R2_pin, LOW);
  if(digitalRead(SW_Left_pin) == 0) {
    left_power += 5;
    if(left_power > 255) left_power = 255;
  }
  if(digitalRead(SW_Right_pin) == 0) {
    right_power += 5;
    if(right_power > 255) right_power = 255;
  }
  Serial.print(left_power);
  Serial.print(", ");
  Serial.println(right_power);
  delay(200);
}

void showInLCD() {
  lcd.setCursor(2, 0);
  lcd.print(left_power);
  lcd.setCursor(2, 1);
  lcd.print(right_power);
}
