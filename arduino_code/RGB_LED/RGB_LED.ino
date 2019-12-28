#define red 10
#define blue 9
#define green LED_BUILTIN
#define delay_ms 500

void setup() {
  // put your setup code here, to run once:
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
}

void loop() {

  for(int i=0 ; i<8 ; i++) {
    digitalWrite(red, bitRead(i, 0));
    digitalWrite(blue, bitRead(i, 1));
    digitalWrite(green, bitRead(i, 2));
    delay(delay_ms);          
  }
  
}
