#include <Servo.h>
#define SERVO_PIN 7
#define LED_PIN 6
Servo myservo; // 建立Servo物件，控制伺服馬達
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  myservo.attach(SERVO_PIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
}
void loop() {
  if (Serial.available()) {
    char data = Serial.read();
    
    if (data == '1') {
      openFences();
    }
  }
}
void openFences() {
  // 開啟柵欄
  for (int i = 180; i >= 85; i--) {
    myservo.write(i); // 使用write，傳入角度，從0度轉到180度
    digitalWrite(LED_PIN, HIGH); delay(25); // 燈on
    digitalWrite(LED_PIN, LOW); delay(25); // 燈off
  }
  delay(3000);
  // 關閉柵欄
  for (int i = 85; i <= 180; i++) {
    myservo.write(i);// 使用write，傳入角度，從180度轉到0度
    digitalWrite(LED_PIN, HIGH); delay(25); // 燈on
    digitalWrite(LED_PIN, LOW); delay(25); // 燈off
  }
}
