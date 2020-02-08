#define IP_PIN A3

void setup() {
  Serial.begin(9600);
  
}

void loop() {
  int ir_value = analogRead(IP_PIN);
  Serial.println(ir_value);
  delay(200);
}
