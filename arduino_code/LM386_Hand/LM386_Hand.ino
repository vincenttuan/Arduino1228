#define LM386_PIN A3
#define Relay_IN1 4

void setup() {
  Serial.begin(9600);
  pinMode(Relay_IN1, OUTPUT);
  digitalWrite(Relay_IN1, HIGH);
}
boolean on = true;
int lm_value = 0;
void loop() {
  lm_value = analogRead(LM386_PIN);
  if(lm_value > 200 && lm_value < 400) {
      Serial.println(lm_value);
      on = !on;
      digitalWrite(Relay_IN1, on);
  }
  delay(50);
}
