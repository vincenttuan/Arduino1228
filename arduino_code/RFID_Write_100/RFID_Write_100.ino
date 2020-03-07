#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

unsigned char    keyA[16]{0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};
unsigned char  writeData[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 100}; // Initialise $100

int key_blockAddr = 11; // 資料驗證區 Data block 11 中的密碼 A
int data_blockAddr = 8; // 資料撰寫區 Data block 8

void setup() {
  Serial.begin(9600);
  // start the SPI library:
  SPI.begin();
  rfid.init();
  delay(1000) ;
  Serial.println("Write 100 :");
}

void loop() {
  // 顯示卡號
  //-----------------------------------
  if (rfid.isCard()) {  //　檢查是否偵測到RFID Tag ? 並回傳true/false
    if (rfid.readCardSerial()) { //讀取RFID的ID/序號(4 bytes)與檢查碼(1 byte)
      /* With a new cardnumber, show it. */
      Serial.println("---------------------------------");
      Serial.println("Card found");
      Serial.print("Serial #(Hex) : ");
      Serial.print(rfid.serNum[0], HEX);
      Serial.print(", ");
      Serial.print(rfid.serNum[1], HEX);
      Serial.print(", ");
      Serial.print(rfid.serNum[2], HEX);
      Serial.print(", ");
      Serial.print(rfid.serNum[3], HEX);
      Serial.print(", ");
      Serial.print(rfid.serNum[4], HEX);
      Serial.println(" ");
    }
  }
  
  //-----------------------------------------
  // 容量是否足夠, Election card, return capacity
  int RC_size = rfid.selectTag(rfid.serNum); //　選擇一張卡並回傳卡片的容量
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  if (RC_size != 0) {
    Serial.print("Size : ");
    Serial.print(RC_size, DEC);
    Serial.println("K bits ");
  }

  // 驗證
  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockAddr, keyA, rfid.serNum); // Authentication by verify Key A
  if (status == MI_OK) {
    Serial.println();
    Serial.print("Sector ");
    Serial.print(key_blockAddr / 4, DEC);
    Serial.print(" Block ");
    Serial.print(data_blockAddr);
    Serial.println(" : ");

    status = rfid.write(data_blockAddr, writeData);//在block #8 的 byte #15 存入 $100
    if (status == MI_OK) {
      Serial.print("Save $ ");
      Serial.println(writeData[15]);
    }
    
  }

  rfid.halt();  // Enter Sleep Mode
  delay(500) ; // waiting for 0.5 sec
}
