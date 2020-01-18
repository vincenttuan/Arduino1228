#define ir_pin A3
void setup() {
  Serial.begin(9600);
}

void loop() {
  int ir = analogRead(ir_pin);
  Serial.println(ir);
  delay(50);
}
