struct Arduino
   {   String modelo ; // Nombre del modelo
       int npd ;       // Numero de pines digitales
       int npa ;       // Numero de pines analogicos
       float volt ;    //Tension de funcionamiento
   } ;

void setup()
   { Serial.begin( 115200);
   }

void loop()
   { Arduino UNO_R3 ;
     UNO_R3.modelo = "uno" ;
     UNO_R3.npd = 13 ;
     UNO_R3.npa = 5 ;
     UNO_R3.volt = 5.0F ;
     
     Serial.println(UNO_R3.npd) ;
     Serial.println(UNO_R3.modelo ) ;
     Serial.flush() ; exit(0) ;
   }
