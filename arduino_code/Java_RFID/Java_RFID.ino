#include <SPI.h>
#include <RFID.h>
#define RST_PIN 9
#define SS_PIN 10
#define BUZZER_PIN 8

RFID rfid(SS_PIN, RST_PIN);

void setup() {
  Serial.begin(9600);
  pinMode(BUZZER_PIN, OUTPUT);
  SPI.begin();
  rfid.init();
}
void loop() {
  
  if (rfid.isCard() && rfid.readCardSerial()) {
    digitalWrite(BUZZER_PIN, HIGH);
    int serNumLength = 5; // rfid.serNum[0] ~ rfid.serNum[4] 共五組
    for (int i = 0; i < serNumLength; i++) {
      Serial.print(rfid.serNum[i], HEX);
    }
    Serial.print("\r\n");
    delay(150);
    digitalWrite(BUZZER_PIN, LOW);
    delay(1000);
  }

  rfid.halt();  // 命令卡片進入休眠狀態
}
