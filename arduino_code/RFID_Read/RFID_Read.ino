/**
  mfrc522 reader 接線 (on Arduino Uno):
  IRQ: 不用接
  RST: Pin 9
  NSS: Pin 10
  MOSI: Pin 11
  MISO: Pin 12
  SCK: Pin 13
  GND: GND
  3.3v: 3.3v
*/

#include <SPI.h>
#include <RFID.h>
#define RST_PIN 9
#define SS_PIN 10
#define BUZZER_PIN 8

RFID rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  delay(1000);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
  Serial.println("Ready");
}
void loop() {
  
  if (rfid.isCard() && rfid.readCardSerial()) {
    digitalWrite(BUZZER_PIN, HIGH);
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
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);
  }

  rfid.halt();  // 命令卡片進入休眠狀態
}
