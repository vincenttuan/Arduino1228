#include <Wire.h>
#include <Timer.h>
#include <SPI.h>
#include <RFID.h>
#define RST_PIN 9
#define SS_PIN 10
#define buzzer_PIN 8

RFID rfid(SS_PIN, RST_PIN);
Timer t; // 宣告 Timer 物件
String rfid_card;

void setup() {
  Serial.begin(9600);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");
  t.every(60 * 5, Sensor);
}

void Sensor() {
  rfid_read();
}
void loop() {
  t.update();

}

void rfid_read() {
  if (rfid.isCard() && rfid.readCardSerial()) {
    rfid_card = "";
    RFID_tone();
    int serNumLength = 5; // rfid.serNum[0] ~ rfid.serNum[4] 共五組
    Serial.println("Card found");
    Serial.println("Card ID:");
    Serial.print("Dec: ");
    
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], DEC);
      Serial.print(", ");
    }
    Serial.println();
    Serial.print("Hex: ");
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], HEX);
      Serial.print(", ");
    }
    Serial.println("\r\n");
    delay(150);
    digitalWrite(buzzer_PIN, LOW);
    delay(1000);
  }

  rfid.halt();  // 命令卡片進入休眠狀態
}
void RFID_tone() {
  for (int i = 0; i < 10; i++) { //repeat 10 times
    tone(buzzer_PIN, 1500);
    delay(100);
  }
  noTone(buzzer_PIN);
}
