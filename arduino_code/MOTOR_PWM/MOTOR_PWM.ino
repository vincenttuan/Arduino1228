#define M1_pin 5 // Left
#define M2_pin 6 // Right
#define L1_pin 11 // IN1
#define L2_pin 12 // IN2
#define R1_pin 9  // IN3
#define R2_pin 10 // IN4

void setup() {
  pinMode(L1_pin, OUTPUT);
  pinMode(L2_pin, OUTPUT);
  pinMode(R1_pin, OUTPUT);
  pinMode(R2_pin, OUTPUT);
}

void loop() {

  analogWrite(M1_pin, 255);
  analogWrite(M2_pin, 255);

  digitalWrite(L1_pin, HIGH);
  digitalWrite(L2_pin, LOW);
  digitalWrite(R1_pin, HIGH);
  digitalWrite(R2_pin, LOW);
  
}
