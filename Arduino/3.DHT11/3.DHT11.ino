#include<DHT.h>
const int pinDHT = 4; //Đọc dữ liệu từ DHT11 ở chân 2 trên mạch Arduino
const int DHTTYPE = DHT11; //Khai báo loại cảm biến, có 2 loại là DHT11 và DHT22
DHT dht(pinDHT, DHTTYPE);
void setup() {
 Serial.begin(9600);
 dht.begin(); // Khởi động cảm biến
}
void loop() {
 float h = dht.readHumidity(); //Đọc độ ẩm
 float t = dht.readTemperature(); //Đọc nhiệt độ
 Serial.println("Arduino.vn");
 Serial.print("Nhiet do: ");
 Serial.println(t); //Xuất nhiệt độ
 Serial.print("Do am: ");
 Serial.println(h); //Xuất độ ẩm
 delay(5000); //Xuống hàng
 }
