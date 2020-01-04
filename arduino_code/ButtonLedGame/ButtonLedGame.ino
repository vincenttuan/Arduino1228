#define len_pin 13
#define len_pinA 12
#define len_pinB 11
#define sw_pinA A1
#define sw_pinB A2

void setup() {
  pinMode(len_pin, OUTPUT);
  pinMode(len_pinA, OUTPUT);
  pinMode(len_pinB, OUTPUT);
  pinMode(sw_pinA, INPUT_PULLUP);
  pinMode(sw_pinB, INPUT_PULLUP);
  
  Serial.begin(9600);
}

boolean play = false;
boolean gameOver = false;
int a, b; // score
int amount = 3;

void loop() {
  if (gameOver) {
    return;  
  }
  // 1. turnOff all LED
  digitalWrite(len_pinA, LOW);
  digitalWrite(len_pinB, LOW);
  digitalWrite(len_pin, LOW);
  
  // 2. Ready to play
  Serial.println("Play");
  int randomNumber = random(5000);
  delay(randomNumber);

  // 3. turnOn LED
  Serial.println(randomNumber);
  digitalWrite(len_pin, HIGH);
  play = true;
  
  // 4. Wait click button
  while(play) {
    // A-Button click
    if(digitalRead(sw_pinA) == 0 && play) {
        Serial.println("A click");
        play = false;
        digitalWrite(len_pinA, HIGH);
        ++a;
    }
    // B-Button click
    if(digitalRead(sw_pinB) == 0 && play) {
        Serial.println("B click");
        play = false;
        digitalWrite(len_pinB, HIGH);
        ++b;
    }
  }
  Serial.print("a=");
  Serial.print(a);
  Serial.print(" b=");
  Serial.println(b);
  Serial.println("End");
  // 5. Game over ?
  if(a == amount || b == amount) {
      gameOver = true;
      Serial.println("Game Over !");
  }
  delay(3000);
}
