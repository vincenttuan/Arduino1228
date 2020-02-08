// 使用手機控制燈光 
// 手機請在 Google Play 下載 Arduino bluetooth controller APP

#define LED_PIN 13

void setup() {
  pinMode(LED_PIN, OUTPUT) ;
  Serial.begin(9600);         
  digitalWrite(LED_PIN, LOW);
}

void loop() {
  if (Serial.available()) {
    char c = Serial.read();
    if (c == '1') {
      digitalWrite(LED_PIN, HIGH);
      //Serial.println("1");
    } else if (c == '0') {
      digitalWrite(LED_PIN, LOW);
      //Serial.println("0");
    }

  }
}
