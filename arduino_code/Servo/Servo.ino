#include <Servo.h>
#include <Timer.h>
#define SERVO_PIN 7
#define LED_PIN 6
#define BUZZER_PIN 8

Servo myservo; // 建立Servo物件，控制伺服馬達
Timer t; // 宣告 Timer 物件
boolean play = false;
int delay_ts = 100;
int delay_ts_sum = 0;
void setup() {
  Serial.begin(9600);
  pinMode(LED_PIN, OUTPUT);
  pinMode(BUZZER_PIN, OUTPUT);
  myservo.attach(SERVO_PIN); // 連接數位腳位7，伺服馬達的訊號線
  myservo.write(180); // 柵欄起始角度
  digitalWrite(LED_PIN, HIGH);

  t.every(0, listenerInput);
  //t.every(0, lcd);
}

void loop() {
  t.update();
}

void listenerInput() {
  if (Serial.available()) {
    char data = Serial.read();

    if (data == '1') {
      play = true;
      openFences();
      play = false;
    }
  }
}

void openFences() {
  // 開啟柵欄
  for (int i = 180, j = 0; i >= 85; i-=2, j++) {
    myservo.write(i); // 使用write，傳入角度，從0度轉到180度
    delay_ts_sum += delay_ts;
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

void lcd() {
  if(play) {
    digitalWrite(LED_PIN, HIGH); delay(1000); // 燈on
    digitalWrite(LED_PIN, LOW); delay(1000); // 燈off
  }
}
