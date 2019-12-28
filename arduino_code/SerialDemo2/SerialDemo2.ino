void setup() {
  Serial.begin(9600);
  Serial.println("Welcome!");

}

void loop() {
  if(Serial.available()>0) {
    // int data = Serial.read();
    // char data = Serial.read();
    String data = Serial.readString();
    Serial.print("Arduino got: ");
    Serial.println(data);
    //Serial.println(data, DEC);
  }
}
