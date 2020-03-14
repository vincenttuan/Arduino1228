#include <SPI.h>
#include <RFID.h>
#include <Timer.h>
#include <HTU21D.h>

#define SS_PIN 10
#define RST_PIN 9
#define BUZZER_PIN 8

RFID rfid(SS_PIN, RST_PIN);
HTU21D htu; // 宣告 HTU21D
unsigned char keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int key_blockAddr = 11; // 資料驗證區 Data block 11 中的密碼 A
int data_blockAddr = 8; // 資料撰寫區 Data block 8
unsigned char str[16];
int balance = 0;
float temp = 0;
float humi = 0;
Timer t; // 宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  delay(1) ;
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  htu.begin();
  t.every(50, readRFID);
  t.every(50, readHTU21D);
  t.every(50, sendData);
}

void loop() {
  t.update();
}

void sendData() {
  Serial.print(rfid.serNum[0], HEX);
  Serial.print(rfid.serNum[1], HEX);
  Serial.print(rfid.serNum[2], HEX);
  Serial.print(rfid.serNum[3], HEX);
  Serial.print(rfid.serNum[4], HEX);
  Serial.print(",");
  Serial.print(balance, DEC);
  Serial.print(",");
  Serial.print(temp);
  Serial.print(",");
  Serial.print(humi);
  Serial.println();
}

void readHTU21D() {
  float humidity = htu.readHumidity(); // 取得濕度
  float temperature = htu.readTemperature(); // 取得溫度
  temp = temperature;
  humi = humidity;
}
void readRFID() {
  //-----------------------------------
  if (rfid.isCard()) {  //　檢查是否偵測到RFID Tag ? 並回傳true/false
    if (rfid.readCardSerial()) { //讀取RFID的ID/序號(4 bytes)與檢查碼(1 byte)
      digitalWrite(BUZZER_PIN, HIGH);
    }
  }
  //-----------------------------------------
  // Election card, return capacity
  rfid.selectTag(rfid.serNum); //　選擇一張卡
  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockAddr, keyA, rfid.serNum); // Authentication by verify Key A
  if (status == MI_OK) {
    status = rfid.read(data_blockAddr, str);//讀取
    if (status == MI_OK) {
      balance = (int)str[15];
    }
  }
  delay(150);
  digitalWrite(BUZZER_PIN, LOW);
  rfid.halt();  // Enter Sleep Mode
  delay(50);
}
