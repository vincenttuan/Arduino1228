#define LED_PIN 13

void setup() {
   pinMode(LED_PIN,OUTPUT) ;
   digitalWrite(LED_PIN, LOW) ; // 關閉 LED
   Serial.begin(57600);         // HC-0x bluetooth module(設定已知之速率, 預設:57600, 9600)
   delay(1000);
   Serial.println("AT+NAME=你的名稱"); // 請改名稱, 預設密碼:0000
   while(!Serial.available()) ; 
   Serial.read(); // flush feedback message
   digitalWrite(LED_PIN, HIGH) ; // 開啟 LED，恆亮表示修改成功 
}

void loop() {
  
}

/*
AT 指令
AT+VERSION?
AT+UART:9600,0,0
AT+UART?
AT+NAME:demo
AT+PSWD:0000
AT+ADDR
98d3:31:fd3ac5
BT-V01 = 98d3:31:fb0fa9
AT+ROLE=1 (變更為主端藍芽)
AT+BIND=98d3,31,fb0fa9

AT+BAUD4   <-- 9600 for HC-06
*/
