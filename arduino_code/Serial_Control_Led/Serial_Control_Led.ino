#define led 9

void setup() {
  pinMode(led, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial Control LED !");

}

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.println(data);
    switch (data) {
      case '1':
        digitalWrite(led, HIGH);
        break;
      case '0':
        digitalWrite(led, LOW);
        break;  
    }
    //Serial.println(data, DEC);
  }
}
