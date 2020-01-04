#define len_pin 13
#define len_pinA 12
#define len_pinB 11
#define sw_pinA A1
#define sw_pinB A2
#define buzzer_pin 8

void setup() {
  pinMode(len_pin, OUTPUT);
  pinMode(len_pinA, OUTPUT);
  pinMode(len_pinB, OUTPUT);
  pinMode(sw_pinA, INPUT_PULLUP);
  pinMode(sw_pinB, INPUT_PULLUP);
  pinMode(buzzer_pin, OUTPUT);

  Serial.begin(9600);
}

boolean play = false;
boolean gameOver = false;
int a, b; // score
int amount = 1;

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
  tone(buzzer_pin, 2000, 200);

  // 4. Wait click button
  while (play) {
    // A-Button click
    if (digitalRead(sw_pinA) == 0 && play) {
      Serial.println("A click");
      play = false;
      digitalWrite(len_pinA, HIGH);
      ++a;
    }
    // B-Button click
    if (digitalRead(sw_pinB) == 0 && play) {
      Serial.println("B click");
      play = false;
      digitalWrite(len_pinB, HIGH);
      ++b;
    }
  }

  for (int i = 1; i <= 3; i++) {
    digitalWrite(buzzer_pin, HIGH);
    delay(70);
    digitalWrite(buzzer_pin, LOW);
    delay(70);
  }

  Serial.print("a=");
  Serial.print(a);
  Serial.print(" b=");
  Serial.println(b);
  Serial.println("End");
  // 5. Game over ?
  if (a == amount || b == amount) {
    gameOver = true;
    Serial.println("Game Over !");
    //音階頻率
    int freq[] = {262, 294, 330, 349, 392};
    //輸入歌曲音調
    int melody[] = {5, 3, 3, 4, 2, 2, 1, 2, 3, 4, 5, 5, 5, 5, 3, 3, 4, 2, 2, 1, 3, 5, 5, 3, 2, 2, 2, 2, 2, 3, 4, 3, 3, 3, 3, 3, 4, 5, 5, 3, 3, 4, 2, 2, 1, 3, 5, 5, 1};
    //輸入節拍
    int beat[] = {1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4, 1, 1, 1, 1, 1, 1, 2, 1, 1, 1, 1, 1, 1, 2, 1, 1, 2, 1, 1, 2, 1, 1, 1, 1, 4};
    for (int i = 0 ; i < 49 ; i++) {
      tone(buzzer_pin, freq[melody[i] - 1]);
      delay(beat[i] * 250);
      noTone(buzzer_pin);
      delay(0);
    }
  }
  delay(3000);

}
