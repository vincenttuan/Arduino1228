#include <Timer.h>
#include <Wire.h>
#include <SPI.h>
#include <RFID.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>
#include <Servo.h>

#define RST_PIN 9
#define SS_PIN 10
#define LED_PIN 6
#define SERVO_PIN 7
#define BUZZER_PIN 8

#define I2C_ADDR  0x3f  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

Servo myservo; // 建立Servo物件，控制伺服馬達
LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件
RFID rfid(SS_PIN, RST_PIN);
Timer t; // 宣告 Timer 物件
String rfid_card;

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  pinMode(LED_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  myservo.attach(SERVO_PIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
  digitalWrite(LED_PIN, HIGH);
  
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
    openFences();
    
    delay(1000);
  }

  rfid.halt();  // 命令卡片進入休眠狀態
}

void openFences() {
  // 開啟柵欄
  for (int i = 180, j = 0; i >= 85; i-=2, j++) {
    myservo.write(i); // 使用write，傳入角度，從0度轉到180度
    digitalWrite(LED_PIN, j%2==0);
    digitalWrite(BUZZER_PIN, j%2==0);
    delay(50);
  }
  digitalWrite(BUZZER_PIN, LOW);
  delay(3000);
  // 關閉柵欄
  for (int i = 85, j = 0; i <= 180; i+=2, j++) {
    myservo.write(i);// 使用write，傳入角度，從180度轉到0度
    digitalWrite(LED_PIN, j%2==0);
    digitalWrite(BUZZER_PIN, j%2==0);
    delay(50);
  }
  digitalWrite(LED_PIN, HIGH);
  digitalWrite(BUZZER_PIN, LOW);
}
