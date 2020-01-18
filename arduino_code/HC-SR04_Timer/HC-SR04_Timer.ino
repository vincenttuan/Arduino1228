#include <NewPing.h>
#include <Timer.h>
#define TRIGGER_PIN  6
#define ECHO_PIN     5
#define MAX_DISTANCE 200 // Maximum distance
#define led 13
#define buzzer 8

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // NewPing setup of pins and maximum distance.

Timer t; // 宣告 Timer 物件
float data; // 距離資料
float warnning = 10; // 警告距離

void setup() {
  Serial.begin(9600); 
  pinMode(led, OUTPUT);
  pinMode(buzzer, OUTPUT);
  t.every(50, call_hcsr04);
  t.every(50, call_led);
  t.every(50, call_buzzer);
}

void loop() {
  t.update();
}

void call_hcsr04() {
  Serial.print("Ping: ");
  data = sonar.ping_cm();
  Serial.print(data); // Send ping, get distance in cm and print result (0 = outside set distance range)
  Serial.println("cm");
}

void call_led() {
  if(data > 0 && data < warnning) {
    digitalWrite(led, HIGH);  
  } else {
    digitalWrite(led, LOW);    
  }
}


void call_buzzer() {
  if(data > 0 && data < warnning) {
    digitalWrite(buzzer, HIGH);  
  } else {
    digitalWrite(buzzer, LOW);    
  }
}
