#define len_pin 13

void setup() {
  pinMode(len_pin, OUTPUT);
  Serial.begin(9600);
}

int ms = 5000;
long randomNumber;

void loop() {
  randomNumber = random(ms);
  Serial.println(randomNumber);
  delay(randomNumber);
  digitalWrite(len_pin, HIGH);

  randomNumber = random(ms);
  Serial.println(randomNumber);
  delay(randomNumber);
  digitalWrite(len_pin, LOW);
}
