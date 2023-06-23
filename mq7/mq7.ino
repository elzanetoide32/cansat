const int sensorPin = 2; // mq7
const int sensorPin2 = 13; //mq4
void setup() {
  Serial.begin(9600);

}

void loop() {
  int sensorValue = analogRead(sensorPin); // Read the analog value from the sensor
  int sensorValue2 = analogRead(sensorPin2);
  // Convert the analog value to voltage
  float voltage = (sensorValue / 1024.0) * 5.0;
  float voltage2 = (sensorValue2 / 1024.0) * 5.0;
  // Convert the voltage to gas concentration using a conversion factor
  float gasConcentration = voltage * 100; // Example conversion factor, adjust as per sensor calibration
  float gasConcentration2 = voltage2 * 100; 
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue);
  
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  
  Serial.print(", Gas Concentration: ");
  Serial.print(gasConcentration);
  Serial.println(" ppm");
  /////////////////////////////////////////////////
  Serial.print("Sensor Value: ");
  Serial.print(sensorValue2);
  
  Serial.print(", Voltage: ");
  Serial.print(voltage2);
  
  Serial.print(", Gas Concentration: ");
  Serial.print(gasConcentration2);
  Serial.println(" ppm");
  delay(1000); // Delay for some time between measurements
}
