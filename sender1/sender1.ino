//Libraries for LoRa
#include <SPI.h>
#include <LoRa.h>

//Libraries for OLED Display
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <Adafruit_BMP085.h>

#define DHTPIN 17        // Pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
const int sensorPin = 2; // mq7
const int sensorPin2 = 13; //mq4
DHT dht(DHTPIN, DHTTYPE);
Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;

//define the pins used by the LoRa transceiver module
#define SCK 5
#define MISO 19
#define MOSI 27
#define SS 18
#define RST 14
#define DIO0 26

//433E6 for Asia
//866E6 for Europe
//915E6 for North America
#define BAND 433E6

//OLED pins
#define OLED_SDA 4
#define OLED_SCL 15 
#define OLED_RST 16
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels

//contador de tiempo
int counter=0;

//creacion de pantalla (objeto display)
//Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RST);

//funciones
/*
void envia_oled(){
  display.clearDisplay();
  display.setCursor(0,30);
  display.print("Contador: ");
  display.setCursor(60,30);
  display.print(counter);      
  display.display();
}
*/

void setup() {
  //Serial.println("DHT11 Sensor Test");
  dht.begin();
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  while (1) {}
  }
   
  /*initialize Serial Monitor*/
  Serial.begin(115200);
   //SPI LoRa pins
  SPI.begin(SCK, MISO, MOSI, SS);
  //setup LoRa transceiver module
  LoRa.setPins(SS, RST, DIO0);
  
  if (!LoRa.begin(BAND)) {
    while (1);
  }/*
  display.clearDisplay();
  display.setTextColor(WHITE);
  display.setTextSize(1);
  display.setCursor(0, 0);
  display.print("LORA SENDER ");
  display.display();*/
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
 // sensors_event_t a, g, temp;
//  mpu.getEvent(&a, &g, &temp);
  
  delay(200); 
  
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
  ////se envian en formato (/*temperatura,humedad,presion,altura,(valores del mq7),(valores mq4))*/
  LoRa.beginPacket();
  LoRa.print("/*");
  LoRa.print(dht.readTemperature());
  LoRa.print(",");
  LoRa.print(dht.readHumidity());
  LoRa.print(",");
  LoRa.print(bmp.readPressure());
  LoRa.print(",");
  LoRa.print(bmp.readAltitude());
  LoRa.print(",");
  LoRa.print(sensorValue);
  LoRa.print(",");
  LoRa.print(voltage);
  LoRa.print(",");
  LoRa.print(gasConcentration);
  LoRa.print(",");
  LoRa.print(sensorValue2);
  LoRa.print(",");
  LoRa.print(voltage2);
  LoRa.print(",");
  LoRa.print(gasConcentration2);
  LoRa.print(",");
  LoRa.print("*/");
  LoRa.println();
  LoRa.endPacket();
}
