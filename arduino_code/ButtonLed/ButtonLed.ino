#define sw_pin A1
#define len_pin 13

void setup() {
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(len_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(sw_pin);
  digitalWrite(len_pin, !value);
  Serial.println(value);

}
