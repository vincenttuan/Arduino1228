#include <NewPing.h>
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

#define TRIGGER_PIN  4 
#define ECHO_PIN     7
#define MAX_DISTANCE 200
#define LED_PIN 13
#define BUZZER_PIN 8

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.
LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件

Timer t; // 宣告 Timer 物件
int ir_value = 0;
int ir_limit = 100;
int default_power = 150;
int right_power = default_power;
int left_power = default_power;
int distance = MAX_DISTANCE; // cm
int minDistance = 20; // cm

void setup() {
  Serial.begin(9600);
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0); //Start at character 0 on line 0
  lcd.print("CM: ");
  lcd.setCursor(0, 1); //Start at character 0 on line 0
  lcd.print("IR: ");
  
  t.every(0, showInLCD);
  t.every(0, detectDistance);
  t.every(0, car);
  
}

void loop() {
  t.update();
}

void car() {
  if(distance != 0 && distance < minDistance) {
    analogWrite(M1_pin, 0);
    analogWrite(M2_pin, 0);
    digitalWrite(LED_PIN, HIGH);  
    for(int i=0;i<10;i++) {
      if(i % 2 == 1) {
        digitalWrite(BUZZER_PIN, HIGH);
      } else {
        digitalWrite(BUZZER_PIN, LOW);
      }
      delay(50);
    }
    
    return;  
  }
  digitalWrite(LED_PIN, LOW);  
  digitalWrite(BUZZER_PIN, LOW);
  analogWrite(M1_pin, right_power);
  analogWrite(M2_pin, left_power);
  
  if (ir_value > ir_limit) {
    digitalWrite(L1_pin, HIGH);
    digitalWrite(L2_pin, LOW);
    digitalWrite(R1_pin, LOW);
    digitalWrite(R2_pin, LOW);
  } else {
    digitalWrite(L1_pin, LOW);
    digitalWrite(L2_pin, LOW);
    digitalWrite(R1_pin, HIGH);
    digitalWrite(R2_pin, LOW);
  }
}

void showInLCD() {
  ir_value = analogRead(IP_PIN);
  Serial.println(ir_value);
  lcd.setCursor(4, 1); //Start at character 0 on line 0
  lcd.print(ir_value) ;
  lcd.print("     ");

}

void detectDistance() {
  distance = sonar.ping_cm();
  lcd.setCursor(4, 0); //Start at character 0 on line 0
  lcd.print(distance) ;
  lcd.print("     ");
  Serial.print(distance);  
}
