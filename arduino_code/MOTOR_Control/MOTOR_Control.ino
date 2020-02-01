#include <Timer.h>
#define M1_pin 5 // Rifgt ENB
#define M2_pin 6 // Left ENA
#define L1_pin 12 // IN1 F
#define L2_pin 11 // IN2 B
#define R1_pin 10  // IN3 F
#define R2_pin 9 // IN4 B
#define BUZZER_pin 8
#define POWER_LED_pin 13

boolean forward = true;
boolean power_enabled = false;
int default_power = 50;
int right_power = default_power;
int light_power = default_power;

Timer t; // 宣告 Timer 物件

void setup() {
  Serial.begin(9600);
  pinMode(POWER_LED_pin, OUTPUT);
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
  pinMode(BUZZER_pin, OUTPUT);
  t.every(0, car);
  t.every(0, backBuzeer);
}

void loop() {
  t.update();
}

void car() {
  char c = Serial.read();
  switch (c) {
    case '1':
      power_enabled = true;
      forward = true;
      digitalWrite(POWER_LED_pin, HIGH);
      analogWrite(M1_pin, default_power);
      analogWrite(M2_pin, default_power);
      right_power = default_power;
      light_power = default_power;
      printPower();
      break;
    case '0':
      power_enabled = false;
      digitalWrite(POWER_LED_pin, LOW);
      analogWrite(M1_pin, 0);
      analogWrite(M2_pin, 0);
      printPower();
      break;
    case '+':
      if (!power_enabled) break;
      right_power = addPower(right_power);
      light_power = addPower(light_power);
      wheelControl();
      printPower();
      break;
    case '-':
      if (!power_enabled) break;
      right_power = subPower(right_power);
      light_power = subPower(light_power);
      wheelControl();
      printPower();
      break;
    case 'f':
      if (!power_enabled) break;
      forward = true;
      wheelControl();
      printPower();
      break;
    case 'b':
      if (!power_enabled) break;
      forward = false;
      wheelControl();
      printPower();
      break;
    case 't':
      if (!power_enabled) break;
      right_power = 255;
      light_power = 255;
      wheelControl();
      printPower();
      break;
    case 'r':
      if (!power_enabled) break;
      wheelControl();
      analogWrite(M2_pin, 0); // 右輪停止
      printPower();
      break;
    case 'l':
      if (!power_enabled) break;
      wheelControl();
      analogWrite(M1_pin, 0); // 左輪停止
      printPower();
      break;    
  }

}

void backBuzeer() {
  if (!power_enabled) return;
  if(forward) {
    digitalWrite(POWER_LED_pin, HIGH);
    return;
  }
  digitalWrite(BUZZER_pin, HIGH);
  digitalWrite(POWER_LED_pin, HIGH);
  delay(1000);
  digitalWrite(BUZZER_pin, LOW);
  digitalWrite(POWER_LED_pin, LOW);
  delay(1000);
}

int addPower(int power) {
  power += 10;
  return power > 255 ? 255 : power;
}

int subPower(int power) {
  power -= 10;
  return power < 0 ? 0 : power;
}

void wheelControl() {

  analogWrite(M1_pin, right_power);
  analogWrite(M2_pin, light_power);

  if (forward) {
    digitalWrite(L1_pin, HIGH);
    digitalWrite(L2_pin, LOW);
    digitalWrite(R1_pin, HIGH);
    digitalWrite(R2_pin, LOW);
  } else {
    digitalWrite(L1_pin, LOW);
    digitalWrite(L2_pin, HIGH);
    digitalWrite(R1_pin, LOW);
    digitalWrite(R2_pin, HIGH);
  }
}

void printPower() {
  Serial.print(right_power);
  Serial.print(",");
  Serial.println(light_power);
}
