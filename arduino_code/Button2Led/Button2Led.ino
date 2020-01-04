#define sw_pin A1
#define len_pin 13

#define sw_pin2 A2
#define len_pin2 12

void setup() {
  pinMode(sw_pin, INPUT_PULLUP);
  pinMode(len_pin, OUTPUT);

  pinMode(sw_pin2, INPUT_PULLUP);
  pinMode(len_pin2, OUTPUT);
  
  Serial.begin(9600);
}

void loop() {

  int value = digitalRead(sw_pin);
  digitalWrite(len_pin, !value);
  Serial.println(value);

  int value2 = digitalRead(sw_pin2);
  digitalWrite(len_pin2, !value2);
  Serial.println(value2);

}
