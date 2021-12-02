#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#ifndef APSSID
#define APSSID "your wifi name" // existing Wifi network
#define APPSK "your password wifi"
#endif
/* Set these to your desired credentials. */
const char *ssid = APSSID;
const char *password = APPSK;
ESP8266WebServer server(80);
MDNSResponder mdns;
int LED1pin = D7;
bool LED1status = LOW;
int LED2pin = D6;
bool LED2status = LOW;
void setup() {
 Serial.begin(115200);
 Serial.println();
 Serial.print("Connect to existing Wifi network...");
 WiFi.begin(ssid, password);
 while (WiFi.status() != WL_CONNECTED) {
 delay(500);
 Serial.print(".");
 }
 Serial.println("");
 Serial.println("WiFi connected");
 Serial.println("IP address: ");
 Serial.println(WiFi.localIP());
 //Tạo trang web server đơn giản điều khiển 2 đèn LED
 pinMode(LED1pin, OUTPUT);
 pinMode(LED2pin, OUTPUT);
 server.on("/", handle_OnConnect);
 server.on("/led1on", handle_led1on);
 server.on("/led1off", handle_led1off);
 server.on("/led2on", handle_led2on);
 server.on("/led2off", handle_led2off);
 server.onNotFound(handle_NotFound);
 server.begin();
 Serial.println("HTTP server started");
}
void loop() {
 server.handleClient();
 if (LED1status)
 {
 digitalWrite(LED1pin, HIGH);
 }
 else
 {
 digitalWrite(LED1pin, LOW);
 }
 if (LED2status)
 {
 digitalWrite(LED2pin, HIGH);
 }
 else
 {
 digitalWrite(LED2pin, LOW);
 }
}
/*custom function*/
String sendHtmlResponse(int led1status,int led2status) {
String html="<!DOCTYPE html>\r\n" ;
 html+="<html>\r\n" ;
 html+="<head>\r\n" ; 
 html+="<meta charset=\"UTF-8\">\r\n" ;
 html+= "<title>ESP8266</title>\r\n" ;
 html+= "<meta name=\"viewport\" content=\"width=width-device,initial-scale =1\" />\r\n" ;
 html+= "<link rel=\"stylesheet\" href=\"https://stackpath.bootstrapcdn.com/bootstrap/4.5.2/css/bootstrap.min.css\" />\r\n" ;
 html+= "<style>\r\n" ;
 html+= "p,h2{margin: 0px}\r\n" ;
 html+= " .header{\r\n" ;
 html+= " background-color: orange;\r\n" ;
 html+= " height: 100px;\r\n" ;
 html+= " text-align: center;\r\n" ;
 html+= " display: flex;\r\n" ;
 html+= " align-items: center;\r\n" ;
 html+= " }\r\n" ;
 html+= " .footer{\r\n" ;
 html+= " background-color: black;\r\n" ;
 html+= " color: #FFFFFF;\r\n" ;
 html+= " height: 100px;\r\n" ;
 html+= " text-align: center;\r\n" ;
 html+= " display: flex;\r\n" ;
 html+= " align-items: center;\r\n" ;
 html+= " }\r\n" ;
 html+= " .main{\r\n" ;
 html+= " height: 800px;\r\n" ;
 html+= " padding-top:30px;\r\n" ;
 html+= " padding-bottom: 30px;\r\n" ;
 html+= " \r\n" ;
 html+= " }\r\n" ;
 html+= " .main h5{\r\n" ;
 html+= " text-align: center;\r\n" ;
 html+= " }\r\n" ;
 html+= " .led{\r\n" ;
 html+= " display: flex;\r\n" ;
 html+= " text-align:center;\r\n" ;
 html+= " align-items: center;\r\n" ;
 html+= " justify-content: center;\r\n" ;
 html+= " padding-top: 3em;\r\n" ;
 html+= " padding-bottom: 3em;\r\n" ;
 html+= " }\r\n" ;
 html+= "</style>\r\n" ;
 html+= "</head>\r\n" ;
 html+= "<body>\r\n" ;
 html+= "<div class=\"header\">\r\n" ;
 html+= " <div class=\"container\">\r\n" ;
 html+= " <h2>ESP8266</h2>\r\n" ;
 html+= " </div>\r\n" ; 
 html+= "</div>\r\n" ;
 html+= "<div class=\"main\">\r\n" ;
 html+= "<div class=\"container\">\r\n" ;
 html+= "<h5>ĐIỀU KHIỂN ĐÈN LED</h5>\r\n" ;
 html+= " <div class=\"row led\">\r\n" ;
 html+= " \r\n" ;
 html+= " <div class=\"col-md-6\">\r\n" ;
 html+= " \r\n" ;
 if(led1status)
 {
 html+= " <a href=\"/led1off\" class=\"btn btn-danger btn-lg w-50\">OFF</a>\r\n" ;
 html+= " <p>LED 1 status: ON</p>\r\n" ;
 html+= " \r\n" ;
 }else{
 html+= " <a href=\"/led1on\" class=\"btn btn-primary btn-lg w-50\">OFF</a>\r\n" ;
 html+= " <p>LED 1 status: OFF</p>\r\n" ;
 html+= " \r\n" ;
 }
 html+= " </div>\r\n" ;
 html+= " <div class=\"col-md-6\">\r\n" ;
 html+= " \r\n" ;
 if(led2status)
 {
 html+= " <a href=\"/led2off\" class=\"btn btn-danger btn-lg w-50\">OFF</a>\r\n" ;
 html+= " <p>LED 2 status: ON</p>\r\n" ;
 html+= " \r\n" ;
 }else{
 html+= " <a href=\"/led2on\" class=\"btn btn-primary btn-lg w-50\">ON</a>\r\n" ;
 html+= " <p>LED 2 status: OFF</p>\r\n" ;
 html+= " \r\n" ;
 }

 html+= " </div>\r\n" ;
 html+= " </div>\r\n" ;
 html+= "</div>\r\n" ;
 html+= "</div>\r\n" ;
 html+= "<div class=\"footer\">\r\n" ;
 html+= " <div class=\"container\">\r\n" ;
 html+= " <p>@TH CNTT 2</p>\r\n" ;
 html+= " </div>\r\n" ;
 html+= "</div>\r\n" ;
 html+= "</body>\r\n" ;
 html+= "</html>";
 return html;
}
void handle_OnConnect() {
 LED1status = LOW;
 LED2status = LOW;
 Serial.println("D7 Status: OFF | D6 Status: OFF");
 server.send(200, "text/html", sendHtmlResponse(LED1status,LED2status));
}
void handle_led1on() {
 LED1status = HIGH;
 Serial.println("D7 Status: ON");
 server.send(200, "text/html", sendHtmlResponse(true,LED2status));
}
void handle_led1off() {
 LED1status = LOW;
 Serial.println("D7 Status: OFF");
 server.send(200, "text/html", sendHtmlResponse(false,LED2status));
}
void handle_led2on() {
 LED2status = HIGH;
 Serial.println("D7 Status: ON");
 server.send(200, "text/html", sendHtmlResponse(LED1status,true));
}
void handle_led2off() {
 LED2status = LOW;
 Serial.println("D7 Status: OFF");
 server.send(200, "text/html", sendHtmlResponse(LED1status,false));
}
void handle_NotFound(){
 server.send(404, "text/plain", "Not found");
}
