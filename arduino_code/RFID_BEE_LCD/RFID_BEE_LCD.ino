#include <Timer.h>
#include <Wire.h>
#include <SPI.h>
#include <RFID.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SS_PIN 10

#define BUZZER_PIN 8

#define I2C_ADDR  0x27  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件
RFID rfid(SS_PIN, RST_PIN);
Timer t; // 宣告 Timer 物件
String rfid_card;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0);
  lcd.print("RFID ID:");
  t.every(0, rfid_read);
}

void loop() {
  t.update();
}

void rfid_read() {
  if (rfid.isCard() && rfid.readCardSerial()) {
    rfid_card = "";
    digitalWrite(BUZZER_PIN, HIGH);
    int serNumLength = 5; // rfid.serNum[0] ~ rfid.serNum[4] 共五組
    Serial.println("Card found");
    
    // 容量
    int card_size = rfid.selectTag(rfid.serNum);
    Serial.print("size: ");
    Serial.print(card_size);
    Serial.println(" bits");
    
    Serial.println("Card ID:");
    Serial.print("Dec: ");
    
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], DEC);
      Serial.print(", ");
    }
    Serial.println();
    Serial.print("Hex: ");
    lcd.setCursor(0, 1);
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], HEX);
      Serial.print(", ");
      lcd.print(rfid.serNum[i], HEX);
      lcd.print(" ");
    }
    lcd.print("          ");
    Serial.println("\r\n");
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);
  }

  rfid.halt();  // 命令卡片進入休眠狀態
}
