
#include "Seeed_BME280.h"
#include <Wire.h>
BME280 bme280;

int Vitesse_1 = 5;
int Vitesse_2 = 6;
float highValue = 0;
float lowValue = 500;
float sensor_volt;
float GasValue;
float BipValue;
float temp;
float humidity = 0;
int val1 =  0;
int val2 =0;


void setup() {
  Serial.begin(9600);
  
  if (!bme280.init()) {
    Serial.println("Device error!");
  }
  pinMode(Vitesse_1, OUTPUT);
  pinMode(Vitesse_2, OUTPUT);
  //Calibrage air ambiant
  for (int i = 0; i <= 10; i++) {
    GasValue = analogRead(A0);
    if (GasValue > highValue) {
      highValue = GasValue;
    }
    if (GasValue < lowValue) {
      lowValue = GasValue;
    }
    Serial.print("High Value= ");
    Serial.print(highValue);
    Serial.print(" ");
    Serial.print("LowValue= ");
    Serial.println(lowValue);

    delay(1000);
  }
  delay(2000);
}

void loop() {


  float BipValue = highValue + 15;
  Serial.print("BipValue= ");
  Serial.print(BipValue);

  GasValue = analogRead(A0);
  humidity = bme280.getHumidity();
  Serial.print("gas Value = ");
  Serial.print(GasValue);
  Humidity();
  Hote_allume(GasValue, BipValue, humidity);
  Hote_eteinte(GasValue, BipValue);
  
  


  delay(2000);
}

void Humidity() {
  Serial.print("Humidity = ");
  Serial.print(bme280.getHumidity());
  Serial.print("%");
  
}

void Hote_allume(float GasValue, float BipValue, float humidity) {

  if (GasValue >= BipValue && humidity <= 75) {
    digitalWrite(Vitesse_1, HIGH);
    digitalWrite(Vitesse_2, LOW);
    Serial.print("v1");
    Serial.print(val1);
    Serial.println("!");
    val1 =1;
  }
  else if (GasValue >= BipValue && humidity >= 75) {
    digitalWrite(Vitesse_2, HIGH);
    digitalWrite(Vitesse_1, LOW);
    Serial.print("v2");
    Serial.print(val2);
    Serial.println("!");
    val2 =1;
  }
  
  
}

void Hote_eteinte(float GasValue, float BipValue) {
  if (GasValue <= BipValue) {
    digitalWrite(Vitesse_1, LOW);
    digitalWrite(Vitesse_2, LOW);
    val1=0;
    val2=0;
    Serial.println("Hote éteinte");
  }
}
