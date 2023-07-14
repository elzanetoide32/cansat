#include <SFE_BMP180.h>
#include <Wire.h>

SFE_BMP180 bmp180;

double Po; //presion del punto inicial para h=0;
char status;
double T,P,A;
void setup()
{
  Serial.begin(9600);

  if (bmp180.begin())
  {
    Serial.println("BMP180 iniciado correctamentenTomando medidadas del punto de referncia...n");
    status = bmp180.startTemperature();//Inicio de lectura de temperatura
    if (status != 0)
    {   
      delay(status); //Pausa para que finalice la lectura
      status = bmp180.getTemperature(T);//Obtener la temperatura
      if (status != 0)
      {
        status = bmp180.startPressure(3);//Inicio lectura de presió
        if (status != 0)
        {        
          delay(status);//Pausa para que finalice la lectura        
          status = bmp180.getPressure(P,T);//Obtenemos la presión
          if (status != 0)
          {                  
            Po=P; //Asignamos el valor de presión como punto de referencia
            Serial.println("Punto de referncia establecido: h=0");  
          }      
        }      
      }   
    }
    
  }
  else
  {
    Serial.println("Error al iniciar el BMP180");
    while(1); // bucle infinito
  }
}

void loop()
{

  status = bmp180.startTemperature();//Inicio de lectura de temperatura
  if (status != 0)
  {   
    delay(status); //Pausa para que finalice la lectura
    status = bmp180.getTemperature(T);//Obtener la temperatura
    if (status != 0)
    {
      status = bmp180.startPressure(3);//Inicio lectura de presión
      if (status != 0)
      {        
        delay(status);//Pausa para que finalice la lectura        
        status = bmp180.getPressure(P,T);//Obtenemos la presión
        if (status != 0)
        {                    
          //-------Calculamos la altura con respecto al punto de referencia--------
          A= bmp180.altitude(P,Po);
          Serial.print("h=");
          Serial.print(A);
          Serial.println(" metros");    
        }      
      }      
    }   
  } 
  delay(100);
}
