#include <SPI.h>
#include "RF24.h"
#include <OneWire.h>
#include <DallasTemperature.h>
#define ONE_WIRE_BUS 2

OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);

RF24 radio(9,10);
const uint64_t pipe = 0xE8E8F0F0E1LL;

float temperature = 0;
float msg[3];

void setup() {
  Serial.begin(9600);
  sensors.begin();
  radio.begin();                     
  radio.setAutoAck(1);               
  radio.setRetries(1,1);             
  radio.setDataRate(RF24_1MBPS);    
  radio.setPALevel(RF24_PA_MAX);     
  radio.setChannel(10);              
  radio.openWritingPipe(pipe);    
}

void loop() {
  sensors.requestTemperatures();
  temperature = sensors.getTempCByIndex(0);
  Serial.println(temperature);
  msg[0] = temperature;
  radio.write(&msg, sizeof(msg));
  delay(50);
}
