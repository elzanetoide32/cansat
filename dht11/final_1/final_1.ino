#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#define DHTPIN 17        // Pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
const int sensorPin = 2; // mq7
const int sensorPin2 = 13; //mq4
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;
void setup() {
  Serial.begin(9600);
  Serial.println("DHT11 Sensor Test");
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
 
  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
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
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  delay(20);  // Wait for 2 seconds between measurements
  /*Serial.println("***************");  
  Serial.print("Temperatura: ");
  Serial.print(dht.readTemperature());
  Serial.println(" °C");
  
  Serial.print("Humidedad: ");
  Serial.print(dht.readHumidity());
  Serial.println(" %");
  
  Serial.println("bmp180");
  Serial.print("Temperatura = ");
  Serial.print(bmp.readTemperature());
  Serial.println(" *C");
    
  Serial.print("Presion = ");
  Serial.print(bmp.readPressure());
  Serial.println(" Pa");
  Serial.print("Altura = ");
  Serial.print(bmp.readAltitude());
  Serial.println(" meters");

  Serial.print("Pressure at sealevel (calculated) = ");
  Serial.print(bmp.readSealevelPressure());
  Serial.println(" Pa");

  Serial.print("Valor Sensor MQ7: ");
  Serial.print(sensorValue);
  
  Serial.print(", Voltage: ");
  Serial.print(voltage);
  
  Serial.print(", Concentracion de Gas: ");
  Serial.print(gasConcentration);
  Serial.println(" ppm");
  /////////////////////////////////////////////////
  Serial.print("Valor Sensor MQ4: ");
  Serial.print(sensorValue2);
  
  Serial.print(", Voltage: ");
  Serial.print(voltage2);
  
  Serial.print(", Concentracion de Gas: ");
  Serial.print(gasConcentration2);
  Serial.println(" ppm");

  Serial.print("Acceleration X: ");
  Serial.print(a.acceleration.x);
  Serial.print(", Y: ");
  Serial.print(a.acceleration.y);
  Serial.print(", Z: ");
  Serial.print(a.acceleration.z);
  Serial.println(" m/s^2");

  Serial.print("Rotation X: ");
  Serial.print(g.gyro.x);
  Serial.print(", Y: ");
  Serial.print(g.gyro.y);
  Serial.print(", Z: ");
  Serial.print(g.gyro.z);
  Serial.println(" rad/s");

  Serial.print("Temperature: ");
  Serial.print(temp.temperature);
  Serial.println(" degC");
  Serial.print("********************");*/
  Serial.print("/*");
  Serial.print(dht.readTemperature());
  Serial.print(",");
  Serial.print(dht.readHumidity());
  Serial.print(",");
  Serial.print(bmp.readPressure());
  Serial.print(",");
  Serial.print(bmp.readAltitude());
  Serial.print(",");
  Serial.print(sensorValue);
  Serial.print(",");
  Serial.print(voltage);
  Serial.print(",");
  Serial.print(gasConcentration);
  Serial.print(",");
  Serial.print(sensorValue2);
  Serial.print(",");
  Serial.print(voltage2);
  Serial.print(",");
  Serial.print(gasConcentration2);
  Serial.print(",");
  Serial.print("*/");
  Serial.println();
  
}
