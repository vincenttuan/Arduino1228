#define red 10
#define blue 9
#define green LED_BUILTIN
#define delay_ms 100

int movie[6][3] = {
  {0, 0, 1},
  {0, 1, 0},
  {0, 1, 0},
  {0, 1, 0},
  {1, 0, 0},
  {0, 1, 0},
};

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {

  for(int i=0;i<6;i++) {
    digitalWrite(green, movie[i][0]);
    digitalWrite(red, movie[i][1]);
    digitalWrite(blue, movie[i][2]);
    delay(delay_ms);
  }
}
