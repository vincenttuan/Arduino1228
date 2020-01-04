#define led_pin 11
void setup() {
  pinMode(led_pin, OUTPUT);
  Serial.begin(9600);
}

int d = 100;
void loop() {

  for(int i=0;i<=250;i+=10) {
    analogWrite(led_pin, i);
    Serial.println(i);
    delay(d);
  }

  for(int i=250;i>=0;i-=10) {
    analogWrite(led_pin, i);
    Serial.println(i);
    delay(d);
  }

}
