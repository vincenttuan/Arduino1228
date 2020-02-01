#define M1_pin 5 // Rifgt ENB
#define M2_pin 6 // Left ENA
#define L1_pin 12 // IN1 F
#define L2_pin 11 // IN2 B
#define R1_pin 10  // IN3 F
#define R2_pin 9 // IN4 B

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
