#define red 10
#define blue 9
#define green LED_BUILTIN

void setup() {
  pinMode(red, OUTPUT);
  pinMode(blue, OUTPUT);
  pinMode(green, OUTPUT);
  Serial.begin(9600);
  Serial.println("Serial Control RGB LED !");
}

int mode = 0; // 

void loop() {
  if (Serial.available() > 0) {
    char data = Serial.read();
    Serial.println(data);
    switch (data) {
      case '0': // 閉模式
        mode = 0;
        break;  
      case '1': // 開模式
        mode = 1;
        break;  
      case 'R': // RED
      case 'r':
        digitalWrite(red, mode);
        break;
      case 'G': // GREEN
      case 'g':
        digitalWrite(green, mode);
        break;
      case 'B': // BLUE
      case 'b':
        digitalWrite(blue, mode);
        break;
      case 'A': // 全亮
      case 'a':
        mode = 1;
        digitalWrite(red, mode);
        digitalWrite(green, mode);
        digitalWrite(blue, mode);
        break;
      case 'X': // 全閉
      case 'x':
        mode = 0;
        digitalWrite(red, mode);
        digitalWrite(green, mode);
        digitalWrite(blue, mode);
        break;  
    }
  }
}
