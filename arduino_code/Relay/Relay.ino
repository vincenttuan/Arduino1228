#define Relay_IN1 4
void setup() {
  Serial.begin(9600);
  pinMode(Relay_IN1, OUTPUT);
}

void loop() {
  if(Serial.available() > 0) {
    char data = Serial.read();
    if(data != '\n') {
      Serial.println(data);
      if(data == '1') {
        digitalWrite(Relay_IN1, HIGH);
      } else if(data == '2') {
        digitalWrite(Relay_IN1, LOW);
      }
    }
  }

}
