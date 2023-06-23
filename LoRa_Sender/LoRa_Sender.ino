/*
  This is a simple example show the Heltec.LoRa sended data in OLED.

  The onboard OLED display is SSD1306 driver and I2C interface. In order to make the
  OLED correctly operation, you should output a high-low-high(1-0-1) signal by soft-
  ware to OLED's reset pin, the low-level signal at least 5ms.

  OLED pins to ESP32 GPIOs via this connecthin:
  OLED_SDA -- GPIO4
  OLED_SCL -- GPIO15
  OLED_RST -- GPIO16
  
  by Aaron.Lee from HelTec AutoMation, ChengDu, China
  成都惠利特自动化科技有限公司
  https://heltec.org
  
  this project also realess in GitHub:
  https://github.com/Heltec-Aaron-Lee/WiFi_Kit_series
*/

#include "heltec.h"
#include "images.h"
#include <DHT.h>
#include <Adafruit_BMP085.h>
#include <Wire.h>
#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#define BAND    433E6  //you can set band here directly,e.g. 868E6,915E6
#define DHTPIN 17        // Pin connected to the DHT sensor
#define DHTTYPE DHT11   // DHT sensor type
const int sensorPin = 2; // mq7
const int sensorPin2 = 13; //mq4
DHT dht(DHTPIN, DHTTYPE);

Adafruit_BMP085 bmp;
Adafruit_MPU6050 mpu;
unsigned int counter = 0;
String rssi = "RSSI --";
String packSize = "--";
String packet ;
struct Val{
  float temp1;
  float hume;
  float presion;
  float altura;
  float mq7;
  float mq4;
  float acex;
  float acey;
  float acez;
  float gyrox;
  float gyroy;
  float gyroz;
};
void logo()
{
  Heltec.display->clear();
  Heltec.display->drawXbm(0,5,logo_width,logo_height,logo_bits);
  Heltec.display->display();
}

void setup()
{
   dht.begin();
   if (!bmp.begin()) {
   Serial.println("Could not find a valid BMP085 sensor, check wiring!");
    while (1) {}
  }
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
   //WIFI Kit series V1 not support Vext control
  Heltec.begin(true /*DisplayEnable Enable*/, true /*Heltec.Heltec.Heltec.LoRa Disable*/, true /*Serial Enable*/, true /*PABOOST Enable*/, BAND /*long BAND*/);
 
  Heltec.display->init();
  Heltec.display->flipScreenVertically();  
  Heltec.display->setFont(ArialMT_Plain_10);
  logo();
  delay(1500);
  Heltec.display->clear();  
  Heltec.display->drawString(0, 0, "Heltec.LoRa Initial success!");
  Heltec.display->display();
  delay(1000);
}

void loop()
{
   /* Get new sensor events with the readings */
  sensors_event_t a, g, temp;
  mpu.getEvent(&a, &g, &temp);
  
  Val valores;
  valores.temp1=dht.readTemperature();
  valores.hume=dht.readHumidity();
  valores.presion=bmp.readPressure();
  valores.altura=bmp.readAltitude();
  valores.mq7=analogRead(sensorPin);
  valores.mq4=analogRead(sensorPin2);
  valores.acex=a.acceleration.x;
  valores.acey=a.acceleration.y;
  valores.acez=a.acceleration.z;
  valores.gyrox=g.gyro.x;
  valores.gyroy=g.gyro.y;
  valores.gyroz=g.gyro.z;
  Heltec.display->clear();
  Heltec.display->setTextAlignment(TEXT_ALIGN_LEFT);
  Heltec.display->setFont(ArialMT_Plain_10);  
  Heltec.display->drawString(0, 0, "Temperature: ");
  Heltec.display->drawString(90, 0, String(dht.readTemperature()));
  Heltec.display->drawString(0, 10, "Humidity: ");
  Heltec.display->drawString(90, 10, String(dht.readHumidity()));
  Heltec.display->drawString(0, 20, "Pressure: ");
  Heltec.display->drawString(70, 20, String(bmp.readPressure()));
  Heltec.display->drawString(0, 30, "Altitude: ");
  Heltec.display->drawString(70, 30, String(20.23));
  Heltec.display->display();

  // send packet
  LoRa.beginPacket();
/*
 * LoRa.setTxPower(txPower,RFOUT_pin);
 * txPower -- 0 ~ 20
 * RFOUT_pin could be RF_PACONFIG_PASELECT_PABOOST or RF_PACONFIG_PASELECT_RFO
 *   - RF_PACONFIG_PASELECT_PABOOST -- LoRa single output via PABOOST, maximum output 20dBm
 *   - RF_PACONFIG_PASELECT_RFO     -- LoRa singbmp.readAltitude()le output via RFO_HF / RFO_LF, maximum output 14dBm
*/
  LoRa.setTxPower(14,RF_PACONFIG_PASELECT_PABOOST);
  LoRa.print("temperatura: ");
  LoRa.print(valores.temp1); 
  LoRa.println("  "); 
  LoRa.print("Humedad: ");
  LoRa.print(valores.hume);
  LoRa.println("        ");  
  LoRa.print("presion: ");
  LoRa.print(bmp.readPressure());
  LoRa.println("            "); 
  LoRa.print("altura: "); 
  LoRa.print(20.23); 
  LoRa.endPacket(); 
}
