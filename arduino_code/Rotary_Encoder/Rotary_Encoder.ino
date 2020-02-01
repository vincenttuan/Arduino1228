const int M1_encoder = 2;
const int M2_encoder = 3;
volatile int M1_pos = 0;
volatile int M2_pos = 0;
int pos, oldpos;
int pos2, oldpos2;


void setup() {
  pinMode(M1_encoder, INPUT);
  attachInterrupt(0, EncoderEvent, FALLING);
  pinMode(M2_encoder, INPUT);
  attachInterrupt(1, EncoderEvent2, FALLING);
  //指定 pin2 對應中斷INT0
  Serial.begin(9600);
}
void loop() {
  //暫時停止中斷
  noInterrupts();
  pos = M1_pos; // 取得位置計數值
  pos2 = M2_pos; // 取得位置計數值
  interrupts(); // 允許中斷
  // 若位置有變化，則顯示
  if (pos != oldpos) {
    Serial.println(pos); //顯示目前旋轉格數
    oldpos = pos;
  }
  if (pos2 != oldpos2) {
    Serial.println(pos2); //顯示目前旋轉格數
    oldpos2 = pos2;
  }
  //delay(1000);
}

void EncoderEvent()
{
  M1_pos++;
}

void EncoderEvent2()
{
  M2_pos++;
}
