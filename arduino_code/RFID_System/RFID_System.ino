#include <Timer.h>
#include <Wire.h>
#include <SPI.h>
#include <RFID.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

#define RST_PIN 9
#define SS_PIN 10

#define BUZZER_PIN 8

#define I2C_ADDR  0x3F  // 定義 I2C Address for the PCF8574T (0x27、0x3F)
#define BACKLIGHT_PIN  3 // 背光 pin

LiquidCrystal_I2C  lcd(I2C_ADDR, 2, 1, 0, 4, 5, 6, 7); // 初始 I2C LCD 物件
RFID rfid(SS_PIN, RST_PIN);
Timer t; // 宣告 Timer 物件
String rfid_card;
char mode = 'c';
int fee = 10;

unsigned char keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
int key_blockAddr = 11; // 資料驗證區 Data block 11 中的密碼 A
int data_blockAddr = 8; // 資料撰寫區 Data block 8
unsigned char str[16];

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  Serial.println("0: get balance, 1: add value, 2: sub value, c: clear");
  lcd.begin (16, 2); // LCD 初始
  lcd.setBacklightPin(BACKLIGHT_PIN, POSITIVE); // 設定背光
  lcd.backlight(); // 開啟背光
  lcd.clear(); // 清空 LCD
  lcd.setCursor(0, 0);
  lcd.print("Mo:      Fee:    ");
  lcd.setCursor(0, 1);
  lcd.print("ID:      Bal:   ");
  t.every(0, changeMode);
  t.every(0, rfid_read);
}

void loop() {
  t.update();
}

void changeMode() {
  if (Serial.available() > 0) {
    char c = Serial.read();
    switch (c) {
      case '0':
      case '1':
      case '2':
        mode = c;
        Serial.print("mode: ");
        Serial.println(mode);
        lcd.setCursor(0, 0);
        lcd.print("Mo:");
        lcd.print(c);
        lcd.print("     Fee:");
        lcd.print(fee);
        lcd.setCursor(0, 1);
        lcd.print("ID:      Bal:   ");
        break;
      case 'c':
        mode = 'c';
        lcd.setCursor(0, 0);
        lcd.print("Mo:      Fee:    ");
        lcd.setCursor(0, 1);
        lcd.print("ID:      Bal:   ");
    }
  }
}
void rfid_read() {

  //-----------------------------------
  if (rfid.isCard()) {  //　檢查是否偵測到RFID Tag ? 並回傳true/false
    if (rfid.readCardSerial()) { //讀取RFID的ID/序號(4 bytes)與檢查碼(1 byte)
      if (!(mode == '0' || mode == '1' || mode == '2')) {
        return;
      }
      digitalWrite(BUZZER_PIN, HIGH);
      /* With a new cardnumber, show it. */
      Serial.println("---------------------------------");
      Serial.println("Card found");
      Serial.print(rfid.serNum[0], HEX);
      Serial.print(", ");
      Serial.println(rfid.serNum[1], HEX);
      delay(150);
      digitalWrite(BUZZER_PIN, LOW);
    }
  }

  //-----------------------------------------
  // Election card, return capacity
  int RC_size = rfid.selectTag(rfid.serNum); //　選擇一張卡並回傳卡片的容量
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  if (RC_size != 0) {
    Serial.print("Size : ");
    Serial.print(RC_size, DEC);
    Serial.println("K bits ");
  }

  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockAddr, keyA, rfid.serNum); // Authentication by verify Key A
  if (status == MI_OK) {
    Serial.println();
    Serial.print("Sector ");
    Serial.print(key_blockAddr / 4, DEC);
    Serial.print(" Block ");
    Serial.print(data_blockAddr);
    Serial.println(" : ");

    status = rfid.read(data_blockAddr, str);//讀取
    if (status == MI_OK) {
      Serial.println("Row data is : ");
      for (int i = 0; i < 16; i++) {
        Serial.print(str[i], DEC);
        Serial.print(" ");
      }
      Serial.println(" ");

      int bal = 0;
      bal = (int)str[15];
      switch (mode) {
        case '0':
          break;
        case '1':
          if ((int)str[15] + fee < 255) {
            str[15] += fee; // 加
            status = rfid.write(data_blockAddr, str);
            rfid.read(data_blockAddr, str); // 重讀取得最新資料
            bal = (int)str[15];
          } else {
            Serial.println("Balance full");
          }
          break;
        case '2':
          if ((int)str[15] - fee >= 0) {
            str[15] -= fee; // 減
            status = rfid.write(data_blockAddr, str);
            rfid.read(data_blockAddr, str); // 重讀取得最新資料
            bal = (int)str[15];
          } else {
            Serial.println("Balance not enough");
          }
          break;
      }

      Serial.print("Fee : $");
      Serial.print(fee, DEC);
      Serial.print(" Balance : $");
      Serial.println(bal, DEC);

      lcd.setCursor(0, 1);
      lcd.print("ID:");
      lcd.print(rfid.serNum[0], HEX);
      lcd.print(" ");
      lcd.print(rfid.serNum[1], HEX);
      lcd.print(" Bal:");
      lcd.print(bal);
      lcd.print("  ");
    }

  }

  rfid.halt();  // Enter Sleep Mode
  delay(500) ; // waiting for 0.5 sec
}
