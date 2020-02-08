#include <Timer.h>
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>  // NewLiquidCrystal library
#define IP_PIN A3
#define I2C_ADDR  0x3F  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin
#define M1_pin 5 // Rifgt ENB
#define M2_pin 6 // Left ENA
#define L1_pin 12 // IN1 F
#define L2_pin 11 // IN2 B
#define R1_pin 10  // IN3 F
#define R2_pin 9 // IN4 B

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件

Timer t; // 宣告 Timer 物件
int ir_value = 0;
int ir_limit = 300;
int car_delay = 0;
int default_power = 130;
int right_power = default_power;
int left_power = default_power;

void setup() {
  Serial.begin(9600);
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("IR Value") ;
  t.every(50, showInLCD);
  t.every(0, car);
}

void loop() {
  t.update();
}

void car() {
  analogWrite(M1_pin, right_power);
  analogWrite(M2_pin, left_power);
  if (ir_value > ir_limit) {
    digitalWrite(L1_pin, HIGH);
    digitalWrite(L2_pin, LOW);
    digitalWrite(R1_pin, LOW);
    digitalWrite(R2_pin, LOW);
    delay(car_delay);
  } else {
    digitalWrite(L1_pin, LOW);
    digitalWrite(L2_pin, LOW);
    digitalWrite(R1_pin, HIGH);
    digitalWrite(R2_pin, LOW);
    delay(car_delay);
  }
}

void showInLCD() {
  ir_value = analogRead(IP_PIN);
  Serial.println(ir_value);
  lcd.setCursor(0, 1); //Start at character 0 on line 0
  lcd.print(ir_value) ;
  lcd.print("    ");

}
