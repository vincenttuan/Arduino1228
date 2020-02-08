// 使用手機控制燈光 
// 手機請在 Google Play 下載 Arduino bluetooth controller APP
#include  <SoftwareSerial.h>
#define LED_PIN 9
SoftwareSerial BTSerial(11, 10); // BT: RX->10 | TX->11

void setup() {
  pinMode(LED_PIN, OUTPUT) ;
  Serial.begin(9600); // 57600 或 9600  
  BTSerial.begin(9600); // 57600 或 9600  
}

void loop() {
  if (BTSerial.available()) {
    int i = BTSerial.read();
    analogWrite(LED_PIN, i);
    Serial.println(i);
  }
}
