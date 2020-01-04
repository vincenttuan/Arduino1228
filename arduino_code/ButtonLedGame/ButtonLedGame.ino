#define sw_pinA A1
#define sw_pinB A2

void setup() {
  pinMode(sw_pinA, INPUT_PULLUP);
  pinMode(sw_pinB, INPUT_PULLUP);
  Serial.begin(9600);
}

boolean play = false;

void loop() {
  Serial.println("Play");
  int randomNumber = random(5000);
  delay(randomNumber);
  Serial.println(randomNumber);
  
  // wait click button
  play = true;
  while(play) {
    if(digitalRead(sw_pinA) == 0 && play) {
        Serial.println("A click");
        play = false;
    }
    if(digitalRead(sw_pinB) == 0 && play) {
        Serial.println("B click");
        play = false;
    }
  }
  Serial.println("End");
  delay(3000);
}
