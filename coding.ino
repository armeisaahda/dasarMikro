#include "DHT.h"
#include <Wire.h>
#include <LiquidCrystal_I2C.h>
LiquidCrystal_I2C lcd(0x27, 16, 2);
#define DHTPIN 2          // what digital pin we're connected to
#define DHTTYPE DHT11     // DHT11
DHT dht(DHTPIN, DHTTYPE);
//LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4);
int pompa = 2;

void setup() {
  Serial.begin(9600);
  lcd.init();
  lcd.backlight();
  lcd.clear();
  pinMode(2, INPUT);
  digitalWrite(2, HIGH);
  delay(1000);
  lcd.setCursor(0, 0);
  lcd.print("IRRIGATION");
  lcd.setCursor(0, 1);
  lcd.print("SYSTEM IS ON ");
  lcd.print("");
    delay(3000);
  lcd.clear();
  Serial.begin(9600);
  pinMode(pompa, OUTPUT);
  Serial.println("DHTxx test!");
  dht.begin();
}
 
void loop() {
  delay(1000);
  float h = dht.readHumidity();
  float t = dht.readTemperature();
  lcd.setCursor(0,0);
  lcd.print("kelembapan:");
  lcd.print(h);
  lcd.setCursor(0,1);
  lcd.print("suhu : ");
  lcd.print(t);
  lcd.print(" C ");
  delay(2000);
  
  int value = analogRead(A0);
  Serial.println(value);
  if (value > 950) {
    digitalWrite(pompa, LOW);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is ON ");
    digitalWrite(pompa,HIGH);
  } else {
    digitalWrite(pompa, HIGH);
    lcd.setCursor(0, 0);
    lcd.print("Water Pump is OFF");
    digitalWrite(pompa, LOW);
  }
 
  if (value < 300) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : HIGH");
  } else if (value > 300 && value < 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : MID ");
  } else if (value > 950) {
    lcd.setCursor(0, 1);
    lcd.print("Moisture : LOW ");
  }
}
