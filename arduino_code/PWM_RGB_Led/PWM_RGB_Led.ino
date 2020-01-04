#define r_pin 11
#define g_pin 10
#define b_pin 9

void setup() {
  pinMode(r_pin, OUTPUT);
  pinMode(g_pin, OUTPUT);
  pinMode(b_pin, OUTPUT);
  Serial.begin(9600);
}

int d = 100;
void loop() {

  analogWrite(r_pin, 255);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 0);
  delay(500);
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 255);
  analogWrite(b_pin, 0);
  delay(500);
  analogWrite(r_pin, 0);
  analogWrite(g_pin, 0);
  analogWrite(b_pin, 255);
  delay(500);
  

}
