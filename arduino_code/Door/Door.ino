#define DOOR_PIN 7

int doorValue;

void setup() {
  pinMode(DOOR_PIN, INPUT_PULLUP);
  Serial.begin(9600);
  Serial.println("Ready...");
}

void loop() {
  doorValue = digitalRead(DOOR_PIN);
  Serial.println(doorValue);
  delay(100);
}
