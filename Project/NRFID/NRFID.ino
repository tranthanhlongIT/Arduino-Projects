#include <SPI.h>
//#include <MFRC522.h> // thu vien "RFID".
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const int LED1 = 2; // LED do
const int LED2 = 3; // LED xanh

/*
Ket noi voi Arduino Uno hoac Mega
 ----------------------------------------------------- Nicola Coppola
 * Pin layout should be as follows:
 * Signal     Pin              Pin               Pin
 *            Arduino Uno      Arduino Mega      MFRC522 board
 * ------------------------------------------------------------
 * Reset      9                5                 RST
 * SPI SS     10               53                SDA
 * SPI MOSI   11               51                MOSI
 * SPI MISO   12               50                MISO
 * SPI SCK    13               52                SCK
 
 */


#define SS_PIN 10
#define RST_PIN 9

//MFRC522 mfrc522(SS_PIN, RST_PIN);       
unsigned long uidDec, uidDecTemp; // hien thi so UID dang thap phan
byte bCounter, readBit;
unsigned long ticketNumber;


void setup() {
  pinMode(LED1, OUTPUT);
  pinMode(LED2, OUTPUT);
  Serial.begin(9600);     
  SPI.begin();            
  mfrc522.PCD_Init();     
  Serial.println("Waiting for card...");

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Temperature C");
  delay(1000);
  lcd.clear();
  lcd.print("Starting...");
}

void loop() {
  // Tim the moi
//  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Doc the
//  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  uidDec = 0;
  Serial.println("MMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMMM");
  Serial.println("================================================");

  // Hien thi so UID cua the
  Serial.println("Card UID: ");
  lcd.setCursor(0, 0);
  lcd.print("Card UID: ");
//  for (byte i = 0; i < mfrc522.uid.size; i++) {
//    uidDecTemp = mfrc522.uid.uidByte[i];
//    uidDec = uidDec*256+uidDecTemp;
//  } 
  Serial.print("            [");
  Serial.print(uidDec);
  lcd.setCursor(0, 1);
  lcd.print(uidDec);
  if(uidDec == 696335238){
    digitalWrite(LED1,!digitalRead(LED1));
    delay(5000);
  }else{
  }
  //--------------------------------
  if(uidDec == 3501146325){
    digitalWrite(LED2,!digitalRead(LED2));
    delay(5000);
  }else{
  }
  Serial.println("]");
  Serial.println("================================================");
}
