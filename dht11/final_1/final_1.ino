#include <DHT.h>

#define DHTPIN 17        // Pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Sensor Test");
  dht.begin();
}

void loop() {
  delay(2000);  // Wait for 2 seconds between measurements
    
  Serial.print("Temperature: ");
  Serial.print(dht.readTemperature());
  Serial.println(" °C");
  
  Serial.print("Humidity: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %");
  
}
