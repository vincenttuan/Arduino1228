#include <SPI.h>
#include <RFID.h>
#include <Timer.h>
#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8

RFID rfid(SS_PIN, RST_PIN);

unsigned char keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int key_blockAddr = 11; // 資料驗證區 Data block 11 中的密碼 A
int data_blockAddr = 8; // 資料撰寫區 Data block 8
unsigned char str[16];
int fee = -10;
Timer t; // 宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  delay(1000) ;
  t.every(50, readRFID);
}

void loop() {
  t.update();
}

void readRFID() {
  //-----------------------------------
  if (rfid.isCard()) {  //　檢查是否偵測到RFID Tag ? 並回傳true/false
    if (rfid.readCardSerial()) { //讀取RFID的ID/序號(4 bytes)與檢查碼(1 byte)
      digitalWrite(BUZZER_PIN, HIGH);
      Serial.print(rfid.serNum[0], HEX);
      Serial.print(rfid.serNum[1], HEX);
      Serial.print(rfid.serNum[2], HEX);
      Serial.print(rfid.serNum[3], HEX);
      Serial.print(rfid.serNum[4], HEX);
    }
  }
  //-----------------------------------------
  // Election card, return capacity
  rfid.selectTag(rfid.serNum); //　選擇一張卡
  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockAddr, keyA, rfid.serNum); // Authentication by verify Key A
  if (status == MI_OK) {
    status = rfid.read(data_blockAddr, str);//讀取
    if (status == MI_OK) {
      Serial.print(",");
      Serial.print(str[15], DEC);
      Serial.println(" ");
    }
  }
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
  rfid.halt();  // Enter Sleep Mode
  delay(50);
}
