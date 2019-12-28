#define red 10
#define blue 9
#define green LED_BUILTIN
#define delay_ms 100

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {

  digitalWrite(green, 1);
  digitalWrite(red, 0);
  digitalWrite(blue, 0);
  delay(delay_ms);
  digitalWrite(green, 0);
  digitalWrite(red, 1);
  digitalWrite(blue, 0);
  delay(delay_ms);
  digitalWrite(green, 0);
  digitalWrite(red, 0);
  digitalWrite(blue, 1);
  delay(delay_ms);
  digitalWrite(green, 0);
  digitalWrite(red, 1);
  digitalWrite(blue, 0);
  delay(delay_ms);
  

}
