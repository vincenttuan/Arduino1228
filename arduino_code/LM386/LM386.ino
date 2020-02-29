#define LM386_PIN A3

void setup() {
  Serial.begin(9600);
}

void loop() {
  int lm_value = analogRead(LM386_PIN);
  Serial.println(lm_value);
  delay(100);
}
