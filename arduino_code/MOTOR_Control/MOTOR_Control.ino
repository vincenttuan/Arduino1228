#define M1_pin 5 // Rifgt ENB
#define M2_pin 6 // Left ENA
#define L1_pin 12 // IN1 F
#define L2_pin 11 // IN2 B
#define R1_pin 10  // IN3 F
#define R2_pin 9 // IN4 B

#define POWER_LED_PIN 13

boolean power_enabled = false;
int default_power = 50;
int right_power = default_power;
int light_power = default_power;

void setup() {
  Serial.begin(9600);
  pinMode(POWER_LED_PIN, OUTPUT);
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
}


void loop() {
  char c = Serial.read();
  switch (c) {
    case '1':
      power_enabled = true;
      digitalWrite(POWER_LED_PIN, HIGH);
      analogWrite(M1_pin, default_power);
      analogWrite(M2_pin, default_power);
      right_power = default_power;
      light_power = default_power;
      printPower();
      break;
    case '0':
      power_enabled = false;
      digitalWrite(POWER_LED_PIN, LOW);
      analogWrite(M1_pin, 0);
      analogWrite(M2_pin, 0);
      printPower();
      break;
    case '+':
      if(!power_enabled) break;
      right_power = addPower(right_power);
      light_power = addPower(light_power);
      analogWrite(M1_pin, right_power);
      analogWrite(M2_pin, light_power);
      printPower();
      break;
    case '-':
      if(!power_enabled) break;
      right_power = subPower(right_power);
      light_power = subPower(light_power);
      analogWrite(M1_pin, right_power);
      analogWrite(M2_pin, light_power);
      printPower();
      break;
  }

  digitalWrite(L1_pin, HIGH);
  digitalWrite(L2_pin, LOW);
  digitalWrite(R1_pin, HIGH);
  digitalWrite(R2_pin, LOW);

}

int addPower(int power) {
  power += 10;
  return power > 255 ? 255 : power;
}

int subPower(int power) {
  power -= 10;
  return power < 0 ? 0 : power;
}

void printPower() {
  Serial.print(right_power);
  Serial.print(",");
  Serial.println(light_power);
}
