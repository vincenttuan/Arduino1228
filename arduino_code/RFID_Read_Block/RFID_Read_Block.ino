#include <SPI.h>
#include <RFID.h>

#define SS_PIN 10
#define RST_PIN 9

RFID rfid(SS_PIN, RST_PIN);

unsigned char    keyA[16] {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xff, 0x07, 0x80, 0x69, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

int key_blockAddr = 11; // 資料驗證區 Data block 11 中的密碼 A
int data_blockAddr = 8; // 資料撰寫區 Data block 8
unsigned char str[16];

void setup() {
  Serial.begin(9600);
  // start the SPI library:
  SPI.begin();
  rfid.init();
  delay(1000) ;
  Serial.println("Read Block :");
}

void loop() {

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
  // Election card, return capacity
  int RC_size = rfid.selectTag(rfid.serNum); //　選擇一張卡並回傳卡片的容量
  // Now a card is selected. The UID and SAK is in mfrc522.uid.
  if (RC_size != 0) {
    Serial.print("Size : ");
    Serial.print(RC_size, DEC);
    Serial.println("K bits ");
  }

  unsigned char status = rfid.auth(PICC_AUTHENT1A, key_blockAddr, keyA, rfid.serNum); // Authentication by verify Key A
  if (status == MI_OK) {
    Serial.println();
    Serial.print("Sector ");
    Serial.print(key_blockAddr / 4, DEC);
    Serial.print(" Block ");
    Serial.print(data_blockAddr);
    Serial.println(" : ");

    status = rfid.read(data_blockAddr, str);//讀取Sector 2的控制區塊資料(block #11)
    if (status == MI_OK) {
      Serial.println("Row data is : ");
      for (int i = 0; i < 16; i++) {
        Serial.print(str[i], DEC);
        Serial.print(" ");
      }
      Serial.println(" ");

    }

    rfid.halt();  // Enter Sleep Mode
    delay(500) ; // waiting for 0.5 sec
  }

}
