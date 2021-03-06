#include <SPI.h>
#include "RF24.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x27, 16, 2);

const uint64_t pipe = 0xE8E8F0F0E1LL;
RF24 radio(9,10);

int upButtonPin = 5;
int downButtonPin = 6;

float msg[3];
int value = 30;
int upButtonState = 0;
int upLastButtonState = 0;
int downButtonState = 0;
int downLastButtonState = 0;
int dem1 = 0;
int dem2 = 0;

void setup() {
  Serial.begin(9600);

  radio.begin();                     
  radio.setAutoAck(1);              
  radio.setDataRate(RF24_1MBPS);   
  radio.setChannel(10);               
  radio.openReadingPipe(1,pipe);     
  radio.startListening();  

  pinMode(upButtonPin, INPUT);
  pinMode(downButtonPin, INPUT);
  
  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.print("Temperature C");
  delay(1000);
  lcd.clear();
  lcd.print("Starting...");
}

void loop()
{
  lcd.clear();
  delay(1000);
  if (radio.available())
  {
    while (radio.available()) {
      upButtonState = digitalRead(upButtonPin);
      if (upButtonState != upLastButtonState) {
        if (upButtonState == HIGH) {
          value++;
          Serial.println("Dang nhan: ");
          Serial.println(value);
        }
      }
      upLastButtonState = upButtonState;
  
      downButtonState = digitalRead(downButtonPin);
      if (downButtonState != downLastButtonState) {
        if (downButtonState == HIGH) {
          value--;
          Serial.println("Dang nhan: ");
          Serial.println(value);
        }
      }
      downLastButtonState = downButtonState;      
      
      delay(50);
      radio.read(&msg, sizeof(msg));
      Serial.println(msg[0]);
      lcd.setCursor(0, 0);
      lcd.print("Temp: ");
      lcd.print(msg[0]);
      lcd.print(" C"); 
      lcd.setCursor(0, 1);
      lcd.print(" +/-: ");
      lcd.print(value);
      if (round(msg[0] - dem1) > value)
      {
        char op = '-';
        dem1++;
        lcd.setCursor(9, 1);
        lcd.print(op);
        lcd.print(dem1);
        delay(500);
      }
      else if (round(msg[0] + dem2) < value)
      {
        char op = '+';
        dem2++;
        lcd.setCursor(9, 1);
        lcd.print(op);
        lcd.print(dem2);
        delay(500);
      }
      else if ((round(msg[0] - dem1) == value))
      {
        delay(500);
        lcd.setCursor(9, 1);
        lcd.print("OK");
        dem2 = 0;
      }
      else if (round(msg[0] + dem2) == value)
      {
        delay(500);
        lcd.setCursor(9,1);
        lcd.print("OK");
        dem1 = 0;
      }
      
    }
  }
  else
  {
    lcd.println("No radio available");
  }
  delay(1000);
}
