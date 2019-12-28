#define red 10
#define blue 9
#define delay_ms 100

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
}

void loop() {
  // put your main code here, to run repeatedly:
  digitalWrite(red, HIGH);   // turn the LED on (HIGH is the voltage level)
  digitalWrite(blue, LOW);   // turn the LED on (HIGH is the voltage level)
  delay(delay_ms);                       // wait for a second
  digitalWrite(red, LOW);    // turn the LED off by making the voltage LOW
  digitalWrite(blue, HIGH);    // turn the LED off by making the voltage LOW
  delay(delay_ms);                       // wait for a second
  
}
