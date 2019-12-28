#define sw_pin A1

void setup() {
  pinMode(sw_pin, INPUT_PULLUP);
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(sw_pin);
  Serial.println(value);

}
