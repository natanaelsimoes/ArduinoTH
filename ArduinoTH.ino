/**
 * Data Acquisition System prototype for temperature and humidity data collecting and
 * calculation of dew point and heat index.
 * 
 * Author: Natanael Simoes <natanael.simoes@ifro.edu.br> http://github.com/natanaelsimoes/
 * Master degree in Applied Computing at State University of Feira de Santana (UEFS) http://uefs.br/
 * Advisor: Gracinete Bastos de Souza <graciesouza@gmail.com>
 * 
 * This prototype uses Adafruit DHT11 sensor to achieve the proposed goal.
 * To run this code, install DHT library sensor from Arduino Library Manager.
 */
#include <DHT.h>

#define DHTPIN 8                    // DHT11 input
#define DHTTYPE DHT11               // DHT type
#define BTNPIN 2                    // Button input

float t, h, d, hi;
DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(BTNPIN, OUTPUT);
  dht.begin();  
}

float dewPoint(float t, float h) {  
  float dp, vp;
  vp = 6.11 * pow(10, (7.5 * t) / (237 + t)); // Vapor Pressure
  dp = 237.3 * log(vp * h / 611) / (7.5 * log(10) - log(vp * h / 611));
  return dp;
}

void loop() {
  if(digitalRead(BTNPIN)) {
    Serial.print("Starting sensing... ");
    t = dht.readTemperature();
    h = dht.readHumidity();        
    if (isnan(t) || isnan(h)) {
      Serial.print("DHT failed sensing");
    } 
    else {
      d = dewPoint(t,h);
      hi = dht.computeHeatIndex(t, h, false);
      Serial.println("ok");
      Serial.print("Temperature: \t\t");
      Serial.print(t, 2);
      Serial.write(176);
      Serial.println("C");
      Serial.print("Humidity: \t\t");
      Serial.print(h, 2);
      Serial.println("%");
      Serial.print("Dew Point: \t");
      Serial.print(d, 2);
      Serial.write(176);
      Serial.println("C");
      Serial.print("Heat Index: \t");
      Serial.print(hi, 2);
      Serial.write(176);
      Serial.println("C");
      Serial.println("");
    }
  }
  delay(1000);
}
