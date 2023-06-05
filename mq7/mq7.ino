const int sensorPin = 2; // Analog pin connected to the sensor

void setup() {
  Serial.begin(9600);

}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  
  // Convert the analog value to voltage
  float voltage = (sensorValue / 1024.0) * 5.0;
  
  // Convert the voltage to gas concentration using a conversion factor
  float gasConcentration = voltage * 100; // Example conversion factor, adjust as per sensor calibration
  
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  
  Serial.print(", Gas Concentration: ");
  Serial.print(gasConcentration);
  Serial.println(" ppm");
  
 
  delay(1000); // Delay for some time between measurements
}
