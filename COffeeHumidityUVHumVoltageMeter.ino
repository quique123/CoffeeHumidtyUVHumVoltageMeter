#include <LiquidCrystal.h>
#include "DHT.h"
//for hdc1080
#include <Wire.h>
#include "ClosedCube_HDC1080.h"
////for lcd
//LiquidCrystal lcd(12,11,5,4,3,2); //acrylic prototype
LiquidCrystal lcd(2,4,9,10,11,12); //pcb prototype
//for dht22 grove pro
#define DHTPIN A1     // what pin we're connected to
#define DHTTYPE DHT22   // DHT 22  (AM2302)
DHT dht(DHTPIN, DHTTYPE);
//for hdc1080
ClosedCube_HDC1080 hdc1080;

//A0 is volts
//A1 is UV
//A2 is hum from hdc1080
void setup() {
  lcd.begin(16, 2);
  Serial.begin(9600); 
  lcd.print("DHTxx TEST");
  Serial.println("DHTxx test!");
  dht.begin();
  hdc1080.begin(0x40);
}

void loop() {
 //printVolts();
 //printUV();
 //if using hdc1080
 print1080();
 //if using grove dht11...
 printTempUndHum(); 
}
 
void printVolts(){
  int sensorValue = analogRead(A0); //A0 V-Divider
  float voltage = sensorValue * (5.00 / 1023.00) * 1; //x1 if 3.7V or x2 if divider used (12KΩ)
  lcd.setCursor(0,0);
  lcd.print("V=");
  lcd.print(voltage); //print v to LCD
  lcd.print(" V");
  if (voltage < 3.50) //warn low V
  {
    //digitalWrite(led_pin, HIGH);
  }
}
//If using DHT11/Grove for T&H
void printTempUndHum(){
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  Serial.println(t);
  lcd.setCursor(0,0); //col0,row0
  lcd.print("T=");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(7,0);//col7, row0
  lcd.print("H=");
  lcd.print(h);
  lcd.print("%");
}
void printUV(){
  long sum = 0;
  int sensorValue; //UV meter
  for (int i=0;i<1024;i++){
     sensorValue = analogRead(A1);
     sum = sensorValue+sum;
     delay(2);
  }
  long meanVal=sum/1024;
  float uvindex = ((meanVal*1000/4.3-83)/21);
  lcd.setCursor(1,0);
  lcd.print("UV= ");
  lcd.print(uvindex);
  lcd.print(" *");
}
void print1080(){
  float h = hdc1080.readHumidity();
  float t = hdc1080.readTemperature();
  lcd.setCursor(0,1); //col0, row1
  lcd.print("T=");
  lcd.print(t);
  lcd.print("C");
  lcd.setCursor(7,1);//col7, row1
  lcd.print("H=");
  lcd.print(h);
  lcd.print("%");
}
