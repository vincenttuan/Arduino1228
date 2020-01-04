#define cds_pin A4
#define r_pin 11
#define g_pin 10
#define b_pin 9

void setup() {
  pinMode(cds_pin, INPUT_PULLUP);
  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  Serial.begin(9600);
}

void loop() {
  int val = analogRead(cds_pin);
  Serial.println(val);
  if (val > 100) {
    analogWrite(r_pin, 255);
    analogWrite(g_pin, 255);
    analogWrite(b_pin, 0);
  } else {
    analogWrite(r_pin, 0);
    analogWrite(g_pin, 0);
    analogWrite(b_pin, 0);
  }
  delay(100);
}
