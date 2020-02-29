#define Relay_IN1 4
#define DOOR_PIN 7

void setup() {
  Serial.begin(9600);
  pinMode(DOOR_PIN, INPUT_PULLUP);
  pinMode(Relay_IN1, OUTPUT);
}

void loop() {
  int doorValue = digitalRead(DOOR_PIN);
  if(doorValue == 1) {
    digitalWrite(Relay_IN1, LOW);
  }
  else {
    digitalWrite(Relay_IN1, HIGH);
  }
  
}
