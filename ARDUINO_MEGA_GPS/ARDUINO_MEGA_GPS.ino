//*******************************************************************
/*
<Control de posicionamiento de vehiculos mediante Arduino>

<El objetivo es conocer la posicion de cualquier objeto 
en la que este instalado el dispositivo desarrollado 
mediante el envio y recepcion de SMS controlados por 
una aplicacion desarrollada en Android.>
  
Copyright (C) <2015> <Cristobal Garcia>
This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.
This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program. If not, see <http://www.gnu.org/licenses/>
*/
//*******************************************************************

// # Pasos:
// # 1. Ponemos el interruptor S1 en el modo prog (A la derecha).
// # 2. Ponemos el interruptor S2 en el modo arduino(A la izquierda).
// # 3. Ponemos el interruptor UART en el centro de sus tres posibles posiciones.
// # 4. Subir el programa al arduino.
// # 5. Poner el interruptor s1 hacia la izquierda en el modo comm 
// # 6. Resetear el aparato.(RST)  
// # 7. Si se obtienen valores de tipo 'inf', ve afuera y espera a que la recepcion de datos sea mejor (mejor cobertura).
// # wiki link- http://www.dfrobot.com/wiki/index.php/GPS/GPRS/GSM_Module_V3.0_(SKU:TEL0051)
/*
GPS + Display 4bits
En este proyecto aprendemos a conectar un modulo GPS y
a tratar la informacion recibida para mostrar
en un display la latitud, longitud, hora y altitud.
*/
 
//Incluimos librerias
// #include <Wire.h>                // La necesita la libreria LiquidCrystal_I2C.h
// #include <LiquidCrystal_I2C.h>   // Para usar un display I2C
 #include <stdio.h>
 #include <stdlib.h>
 #include <LiquidCrystal.h>
 #include <EEPROM.h>

 LiquidCrystal lcd(11, NULL, 12, 13, 10, 9, 8);
                                        
// LiquidCrystal_I2C lcd(0x27,20,4); 
// Establece la dirección de memoria 0x27 para un display de 20 caracteres y 4 líneas.

 #define TAMANO_ARRAY 150 // Tamaño de buffer 
 
 #define habilitar_gps()      digitalWrite (4, LOW)
 #define deshabilitar_gps()   digitalWrite (4, HIGH)
 
 #define habilitar_gsm()      digitalWrite (6, LOW)
 #define deshabilitar_gsm()   digitalWrite (6, HIGH)
  /*
  Rutina para nuestro menu con encoder rotativo.
  El codificador rotativo generico tiene tres pines, visto desde el frente: ACB
  Giro a la derecha A (encendido) -> B (encendido) -> A (apagado) -> B (apagado)
  Contador CW rotación B (encendido) -> A (encendido) -> B (apagado) -> A (apagado)
  Puede tambien tener 2 pines a mayores siendo estes los correspondientes a un interruptor Conectado en este caso al pin 19 de nuestro arduino.  
  
  Normalmente los encoders rotativos de 3 pines, tienen el pin de masa en el medio de los tres.  
  */
  enum PinAssignments 
  {
  encoderPinA = 2,   // Derecha (Llamado DT en nuestro encoder)
  encoderPinB = 3,   // Izquierda (Llamado CLK en nuestro encoder)
  clearButton = 19,  // switch (Llamado SW en nuestro encoder)
  /* Conectar +5v y Gnd en los pines restantes.*/
  };

  volatile int encoderPos=0;                  // Contador para el dial.
  volatile unsigned int lastReportedPos = 1;  // Gestion para el cambio.
  static boolean rotating=false;              // Eliminacion de rebotes.
  volatile unsigned int posicion = 0;         // Contador para el pulsador.
  volatile unsigned int lastPosicion = 1;     // Gestion para el cambio.
  
  /* Variables para el servicio de la rutina de interrupcion.*/
  
  boolean A_set = false;              
  boolean B_set = false;
  boolean C_set = false;
  boolean actualizar = false;
          
  /* Variables del programa*/
  
  byte byteGPS = 0;              // Almacena cada byte que leamos del gps para mandarlos al array.
  int i = 1;                     // Variable que utilizaremos como acumulador,inicializamos su valor en 1.
  int c=0;                       // Variable que se incrementa a medida que introducimos un numero de telefono (p.ej).
  volatile int incremento;       // Variable que suma o resta unidades al valor de las horas.
  volatile int incremento_Aux;   // Variable duplicada de incremento que suma o resta unidades al valor de las horas.
  int Estado = 0;                // Guarda el estado de la conexion.
  char TramaGPG[TAMANO_ARRAY];   // Array donde iremos almacenando los bytes leidos del GPS.
  char *pch;                     // Creamos un puntero de tipo char.
  char *GGA[15];                 // y un array de punteros de tipo char.
  int sat = 0;                   // Variable para almacenar el numero de satelites.
  int menu=-2;                   // Variable menu para la rotacion del mismo.
  int numSel=1;                  // Variable numSel selecciona el numero al cual enviar el SMS.
  int modoTrabajo=0;             // Variable modoTrabajo indica el modo de funcionamiento. 0 modo autonomo; =1 peticion de usuario ; =2 brujula digital.
  boolean Flag_start = false;    // Ayuda a comenzar el programa.
    
  char Array_Latitud[14]={' ',' ','\337',' ',' ','.',' ',' ',' ',' ','\47',' '};  // Array donde se almacena la latitud del gps.
  char Array_Latitud_sms[25]={'L','a','t',':',' ',' ',' ','g',' ',' ','.',' ',' ',' ',' ',' ',' ','m',' '};    // Array donde se almacena la altitud del gps para enviar el sms.
  char Array_Longitud[14]={' ',' ','\337',' ',' ','.',' ',' ',' ',' ','\47',' '}; // Array donde se almacena la longitud del gps.
  char Array_Longitud_sms[25]={'L','o','n',':',' ',' ',' ','g',' ',' ','.',' ',' ',' ',' ',' ',' ','m',' '};   // Array donde se almacena la longitud del gps para enviar el sms.
  char Array_Altitud[14]={' ',' ',' ',' ',' ',' ',' ',' ',' '};    // Array donde se almacena la altitud del gps.
  char Array_Hora[10]={' ',' ',':',' ',' ',':',' ',' '};           // Array donde se almacena la hora del gps.
  char Array_HN[10]={' ',' ',':',' ',' ',':',' ',' '};             // Array donde se almacena la hora nueva del gps.

  // Variables relacionadas con los numeros de telefono.
  
  char numero_Tlf_1[12];     // Array donde permanece el numero 1 de telefono.
  char numero_Tlf_1_Aux[12]; // Array del primer numero de telefono al cual se le vuelcan las variables introducidas por el usuario.
  char numero_Tlf_2[12];     // Array donde permanece el numero 2 de telefono.
  char numero_Tlf_2_Aux[12]; // Array del segundo numero de telefono al cual se le vuelcan las variables introducidas por el usuario.
  char numero_Tlf_3[12];     // Array donde permanece el numero 3 de telefono.
  char numero_Tlf_3_Aux[12]; // Array del tercer  numero de telefono al cual se le vuelcan las variables introducidas por el usuario.
  char Numero_PIN[6];        // Array donde permanece el numero PIN de la tarjeta SIM insertada en el modulo.
  char Numero_PIN_Aux[6];    // Array del numero Pin al cual se le vuelcan las variables que va introduciendo el usuario.
  char numero_buf[25];       // Array que almacena el comando AT que establece el numero de telefono.
  char pin_buf[20];          // Array que almacena el comando AT que establece el numero PIN de la tarjeta SIM insertada en el modulo.
  char introduce_Num[2];     // almacena el numero en modo char.
  
  char array_Minutos[3];     // Array que almacena los minutos. 
  
  // Variables que recogen un SMS recibido
  
  int8_t answer;
  int x;
  char SMS[100];           // Almacena toda la cadena del SMS recibido.
  char *puntSms;           // Creamos un puntero de tipo char.
  char *arrayPuntSms[5];   // y un array de punteros de tipo char.  
  char telefonoSms[16];    // Almacena el numero de telefono del SMS recibido.
  char comillas[4];        // Almacena las comillas de la segunda parte del array.
  char fechaSms[12];       // Almacena la fecha del SMS recibido.
  char horaSms[14];        // Almacenala hora del SMS recibdo.
  char smsRecibido[4];     // Almacena el SMS recibido.

  // Variables de tiempo
  
  int Horas;              // Guarda el valor entero de las horas.
  int Horas_Aux;          // Guarda el valor entero de las horas para el cambio de hora.
  int Horas_Aux1;
  int Minutos;            // Almacena el valor entero de los minutos.
  int Minutos_Aux;        // Almacena el valor entero de los minutos para su comparacion.
  int Segundos;           // Almacena el valor entero de los segundos.
  int Segundos_Aux;       // Almacena el valor entero de los segundos para su comparacion.
  unsigned int t_Envio;   // Almacena el tiempo de envio. 
  int direccion=0;        // Dirección inicial de la eeprom donde guardaré datos.
  int f;                  // Variable que se incrementa para guadar los telefonos en EEPROM.
  
void setup()
{  
  lcd.begin(20,4);  
  lcd.clear();                      
  delay(20); 
//  lcd.init();                       // Inicializo el LCD. 
//  lcd.backlight();                  // Brillo de la pantalla encendido.
  gps_inicio_pines () ;
  pinMode(encoderPinA, INPUT_PULLUP); // Nuevo metodo para habilitar las resistencias de pullup.
  pinMode(encoderPinB, INPUT_PULLUP); 
  pinMode(clearButton, INPUT_PULLUP);
 /* Poner las resistencias de pullup activas (Metodo antiguo)*/
 // digitalWrite(encoderPinA, HIGH);
 // digitalWrite(encoderPinB, HIGH);
 // digitalWrite(clearButton, HIGH);
 /* Pin del encoder en la interrupcion 0 (pin 2)*/
 /* La interrpcion 0 se encargara de ejecutar la funcion encod_A cuando ve un cambio sobre el pin A.*/
  attachInterrupt(0, encod_A, CHANGE); 
 /* Pin del encoder en la interrupcion 1 (pin 3)*/
 /* La interrpcion 1 se encargara de ejecutar la funcion encod_B cuando ve un cambio sobre el pin B.*/
  attachInterrupt(1, encod_B, CHANGE);
 /* Pin del pulsador en la interrupcion 4 (pin 7)*/  
 /* La interrupcion 4 se encargara de ejecutar la funcion seleccionar cuando ve un cambio sobre el pin 7.*/
  attachInterrupt(4, seleccionar, CHANGE);
  //  Recuperamos las variables guardadas en la eeprom
  direccion=0;
  incremento = EEPROM.read(direccion);
  direccion=1;
  t_Envio = EEPROM.read(direccion);
  direccion=33;
  numSel=EEPROM.read(direccion); 
  direccion=34;
  modoTrabajo=EEPROM.read(direccion); 
  direccion=0;
  while (direccion!=9)
  {     
  numero_Tlf_1[direccion] = EEPROM.read(direccion+2);
  numero_Tlf_2[direccion] = EEPROM.read(direccion+11);
  numero_Tlf_3[direccion] = EEPROM.read(direccion+20);    
  direccion++;
  }
  direccion=0;
  while (direccion!=4)
  {     
  Numero_PIN[direccion] = EEPROM.read(direccion+29);   
  direccion++;
  }
  direccion=0; 
  Minutos_Aux=65;
  Segundos_Aux=65;
  comenzar_gps () ;
 }
 
 void comenzar_gps () 
 { 
  digitalWrite(5,HIGH);
  delay(1500);
  digitalWrite(5,LOW);
  delay(1500);
  Serial.begin(9600); 
  habilitar_gsm ();
  deshabilitar_gps ();
  delay(2000);
  //////////////// INTRODUCIR EL PIN //////////////////////
  Serial.println("Introduciendo PIN"); 
  while (Flag_start==false)
  {
  rotating = true;  // restablecer el circuito antirrebote
  if (lastReportedPos != encoderPos) 
  {
  lastReportedPos = encoderPos; 
  Actualiza_pantalla();
  }  
   
  if (lastPosicion != posicion) 
  {
  lastPosicion  = posicion;  
  menu_Seleccion();
  lcd.clear();
  delayMicroseconds(20000);
  Actualiza_pantalla();
  }
  } 
  //////////////////////////////////////////////////////////
  lcd.clear();  // Borramos la pantalla.
  delay(20);
  lcd.setCursor(0,1);                
  lcd.print("  ** Iniciando **   ");  
  Serial.println("Enviando comandos AT");
  delay(2000); // GPS listo.
  sprintf (pin_buf, "AT+CPIN=\%s", Numero_PIN);
  EnviaComandoAT("AT", "OK", 1000);
  EnviaComandoAT(pin_buf, "OK", 2000);  
  EnviaComandoAT("AT+COPS?", "+COPS:", 2000);
  EnviaComandoAT("AT+CMGD=1,4", "OK", 1000); 
  EnviaComandoAT("AT", "OK", 1000);
  //turn on GPS power supply
  EnviaComandoAT("AT+CGPSPWR=1", "OK", 1000);
  //Resetea el GPS  en modo autonomo.
  EnviaComandoAT("AT+CGPSRST=1", "OK", 1000);
  habilitar_gps();
  deshabilitar_gsm();
  delay(2000);      
  menu=1;
  lcd.clear();                      
  delay(20);
  lcd.setCursor(15,0);                   
  lcd.print("0/3  ");      
  lcd.setCursor(0,1);                   
  lcd.print("Datos GPS         <-");      
  lcd.setCursor(0,2);                   
  lcd.print("Ajuste hora         ");     
  lcd.setCursor(0,3);                   
  lcd.print("Ajustes de envio    ");  
  Serial.println("Gps conectando");  
}

void loop()
{
  rotating = true;  // restablecer el circuito antirrebote
  if (lastReportedPos != encoderPos) 
  {
  lastReportedPos = encoderPos;
  Actualiza_pantalla();
  }
    
  if (lastPosicion != posicion) 
  {
  lastPosicion  = posicion;  
  menu_Seleccion();
  lcd.clear();
  delayMicroseconds(20000);
  Actualiza_pantalla();
  }    
  leer_gps ();
}

// 
void leer_gps () 
{
   if (Serial.available()>0)
  {                  
      byteGPS = Serial.read(); 
      if (byteGPS != '$')     // Si  caracter leido es distinto a $ comenzanos a guardar en el array.
      {                                            
      TramaGPG[i]=byteGPS;    // y lo almacenaremos en la cadena de caracteres en la posicion que corresponda
      i++;                    // e incrementamos en uno el contador.
      }
      if (byteGPS == '$')
      {
      TramaGPG[0]='$';  // En la posicion 0 introducimos el simbolo del dolar para acotar la trama desde el principio. 
      Serial.println();
      Serial.print(TramaGPG);
      Serial.println(); 
      cadena();
      memset(TramaGPG, 0, sizeof(TramaGPG)); // Inicializa a cero la cadena para eliminar 
                                             // restos no deseados de lecturas anteriores
      i=1; // Reseteamos la variable i;        
      }
   }
}

void cadena()
  {
   i=0;                                  // Inicializamos el contador
   memset(GGA, 0, sizeof(GGA));          // Limpiamos el array GGA introduciendo en el todo ceros
 
   pch = strtok (TramaGPG,",");          // Tokenizamos (troceamos) la cadena que tenemos en el array TramaGPG por las comas
                                         // y el primer intervalo lo guardamos en pch (puntero char)
 
   //Analizamos ese intervalo guardado en pch para ver si es la cadena que necesitamos
   if (strcmp(pch,"$GPGGA")==0)          // Si es la correcta, seguimos adelante
     {
       while (pch != NULL)               // Mientras el dato sea valido, lo aceptamos para llenar el array GGA
         {
           pch = strtok (NULL, ",");     // Pasamos al siguiente intervalo cortado de la cadena
           GGA[i]=pch;                   // Guardamos el valor de pch en el array GGA
           i++;                          // Incrementamos el contador/acumulador
         }
         Calcula(GGA,"$GPGGA");         // llamamos a la funcion que nos va a mostrar los datos, bien por serial o por LCD
                                        // a esta funcion se le pasan dos parametros 1º el array de chars, 2º la cadena a comparar.                                
     }
 }
 
 void Calcula(char **GGAPrint, char *trama)                // Capturamos los datos pasados a la funcion
{
  Estado = atoi(GGAPrint[5]);                      // Transformamos el char que contiene el estado de la conexion a un entero.
  sat = atoi(GGAPrint[6]);                         // Transformamos el char que contiene el numero de satelites a un entero.
  calculo_latitud(GGAPrint[1],GGAPrint[2]);        // Pasamos a Array_Latitud los datos que contienen la latitud.
  calculo_longitud(GGAPrint[3],GGAPrint[4]);       // Pasamos a Array_Longitud los datos que contienen la longitud.
  calculo_altitud(GGAPrint[8],GGAPrint[9]);        // Pasamos a Array_Altitud los datos que contienen la altitud.
  calculo_hora(GGAPrint[0]);                       // Pasamos a Array_Hora los datos que contienen la hora.
  calculo_hn(GGAPrint[0]); 

  if (Segundos_Aux!=Segundos)
 { 
   if (menu==1)
   {lcd.setCursor(4,0);lcd.print(Array_Hora);}
  ////////////////////////////////////////////////////    
   if (menu==2 )
   {
   lcd.setCursor(4,0);
   lcd.print(Array_Hora);
   if (Estado==1 && (encoderPos==0 || encoderPos==1 || encoderPos==2))
   { 
   lcd.setCursor(5,1);        // Posicionamos el cursor.
   lcd.print(Array_Longitud); // Imprimimos la cadena.
   lcd.setCursor(5,2);        // Posicionamos el cursor.
   lcd.print(Array_Latitud);  // Imprimimos la cadena.
   lcd.setCursor(5,3);        // Posicionamos el cursor.
   lcd.print(sat);            // Imprimimos los satelites existentes por el lcd. 
   }
   else if(Estado==1 && (encoderPos==3 || encoderPos==4))
   {
   lcd.setCursor(5,1);       // Posicionamos el cursor.
   lcd.print(Array_Altitud); // Imprimimos la variable.
   }   
   }   
//   //////////////////////////////////////////////////  
   if (menu==3) 
   {
    lcd.setCursor(12,1);
    lcd.print(Array_Hora);
    lcd.setCursor(12,2);
    lcd.print(Array_HN);     
   } 
//   //////////////////////////////////////////////////  
   if (menu==4)
   {lcd.setCursor(6,0); lcd.print(Array_HN);}
   
   if( menu==18 || menu==19 || menu==20 || menu==21)
   {lcd.setCursor(6,0); lcd.print(Array_Hora);}
     
   Segundos_Aux=Segundos;
   }

   if (Minutos_Aux!= Minutos )//Comprueba cada minuto
   {     
   // Modo de trabajo autonomo
   if (modoTrabajo==0 && (Minutos % t_Envio==0)&&  Estado==1 && sat >=3 )
   {
   habilitar_gsm ();
   deshabilitar_gps ();
   delayMicroseconds(500000);
   if (numSel==1){establecer_numero_tlf (numero_Tlf_1,Numero_PIN);} //
   if (numSel==2){establecer_numero_tlf (numero_Tlf_2,Numero_PIN);} //
   if (numSel==3){establecer_numero_tlf (numero_Tlf_3,Numero_PIN);} //
   envia_mensaje_gsm (Array_Hora);         // Enviamos el SMS.
   envia_mensaje_gsm (Array_Longitud_sms); // Enviamos el SMS.
   envia_mensaje_gsm (Array_Latitud_sms);  // Enviamos el SMS.
   finaliza_envio_gsm ();
   Minutos_Aux=Minutos;
   deshabilitar_gsm ();
   habilitar_gps ();
   delayMicroseconds(500000);
   } 
   // Modo peticion de usuario
   if ( modoTrabajo==1)
   {
   habilitar_gsm ();
   deshabilitar_gps ();
   delayMicroseconds(500000);
   leerSmsSim(Numero_PIN);
   Minutos_Aux=Minutos;
   deshabilitar_gsm ();
   habilitar_gps ();
   delayMicroseconds(500000);
   } 
   }   
}
   
// Interrupcion en A por cambio de estado.
void encod_A()
{
  detachInterrupt(1);
  detachInterrupt(0);
  // Antirrebote
  if ( rotating ) delay (1);  // esperar un poco hasta que se haga el rebote
  // Prueba de transición, hubo cambio? 
  if( digitalRead(encoderPinA) != A_set ) // Anti-rebote, una vez más
  {  
  A_set = !A_set;  
  if ( A_set && !B_set ) // Ajustar contador + si A conduce al B
  {
  encoderPos =encoderPos + 1;
  if (menu!=3 && encoderPos<=0)
  {
  encoderPos=0;
  }
  
  if ( menu==-2 && encoderPos>=2)
  {
    encoderPos=0;
  } 
  if (menu==1 && encoderPos>=4)
  {
  encoderPos=0;
  }
  if (menu==2 && encoderPos>=5)
  {
  encoderPos=0;
  }
  if (menu==3 && encoderPos>=13)
  {
  encoderPos=0;
  }
  if ((menu==5) && encoderPos>=4)
  {
  encoderPos=0;
  }
  
  if ((menu==6 || menu==10 )&& encoderPos>=4)
  {
  encoderPos=0;
  }
  
  if ((menu==-1||menu==11||menu==12||menu==13) && encoderPos>=11)
  {
  encoderPos=0;
  }
  if (menu==17 && encoderPos>=60)
  {
  encoderPos=1;
  }
  
  if (menu==18 && encoderPos>=3)
  {
  encoderPos=0;
  }
  
  }   
  rotating = false;  // no more debouncing until loop() hits again       
  }
  attachInterrupt(1, encod_B, CHANGE);
  attachInterrupt(0, encod_A, CHANGE);
}

// Interrupcion en B por cambio de estado, es identico al anterior.
void encod_B()
{
  detachInterrupt(0);
  detachInterrupt(1);
  if ( rotating ) delay (1);
  if( digitalRead(encoderPinB) != B_set ) 
  { 
  B_set = !B_set;
  // Ajustar contador + si A conduce al B
  if( B_set && !A_set )
  { 
  encoderPos = encoderPos - 1;
  if (menu!=3 && encoderPos<=0)
  {
  encoderPos=0;
  }
  if ( menu==-2 && encoderPos>=2)
  {
    encoderPos=0;
  } 
  if (menu==1 && encoderPos>=4)
  {
  encoderPos=0;
  }
  if (menu==2 && encoderPos>=5)
  {
  encoderPos=0;
  } 
  if (menu==3 && encoderPos<=-12)
  {
  encoderPos=0;
  } 
  if ((menu==5) && encoderPos>=4)
  {
  encoderPos=0;
  }
  
  if ((menu==6 || menu==10) && encoderPos>=4)
  {
  encoderPos=0;
  }
   
  if ((menu==-1||menu==11||menu==12||menu==13) && encoderPos>=11)
  {
  encoderPos=0;
  }
  if (menu==17 && encoderPos<=1)
  {
  encoderPos=1;
  }
  
  if (menu==18 && encoderPos>=3)
  {
  encoderPos=0;
  }
  
  } 
  rotating = false;
  }
  attachInterrupt(0, encod_A, CHANGE);
  attachInterrupt(1, encod_B, CHANGE);
}

void seleccionar()
{
  if ( rotating ) {delay (1);}
    
  if( digitalRead(clearButton )!= C_set  ) 
  {
  C_set = !C_set;
  if( C_set  ) 
  {
  posicion += 1;
  rotating = false;
  }
  }
}
  
/*
 Los pines por defecto para el modo gsm y gps
 si se desea cambiar los pines de control o 
 bien tenemos conflictos para conectar el modulo 
 en esos pines de Arduino , podremos extraer los 
 jumpers J10~J12 y unir los pines adyacentes al 
 borde de la placa a otros pines digitales.
 */ 
// Establece los pines de trabajo del modulo GPS
void gps_inicio_pines () 
{
    pinMode (6, OUTPUT);
    pinMode (4, OUTPUT);
    pinMode (5, OUTPUT);
}

char Num_Sel (int V09)
{
switch (V09)
{
  case 0:
  introduce_Num[0]='0';
  break;
  case 1:
  introduce_Num[0]='1';
  break;
  case 2:
  introduce_Num[0]='2';
  break;
  case 3:
  introduce_Num[0]='3';
  break;
  case 4:
  introduce_Num[0]='4';
  break;
  case 5:
  introduce_Num[0]='5';
  break;
  case 6:
  introduce_Num[0]='6';
  break; 
  case 7:
  introduce_Num[0]='7';
  break;
  case 8:
  introduce_Num[0]='8';
  break;
  case 9:
  introduce_Num[0]='9';
  break;
}
return introduce_Num[0]; 
}


// Establecer el numero de telefono 
//void establecer_numero_tlf (char *numero) 
//{
//  Serial.println ("AT");
//  delay (2000);
//  Serial.println ("AT");
//  delay (2000);
//  Serial.println("AT+CPIN=\"5843\"");   
//  delay(2000);
//  Serial.println("AT+COPS?");   
//  delay(2000);
//  Serial.println ("AT+CMGF=1");
//  delay (1000);
//  Serial.println (numero_buf);
//  delay (1000);
//}


//   Serial.println("%%%%%%%%%%%%%%%%%%%%");
//   Serial.println();
//   Serial.print("Tlf_1_aux: ");
//   Serial.print(numero_Tlf_1_Aux);
//   Serial.println();
//   Serial.print("Tlf_1: ");
//   Serial.print(numero_Tlf_1);
//   Serial.println();    
//   Serial.println("%%%%%%%%%%%%%%%%%%%%");   
//   Serial.print("Latitud: ");
//   Serial.println(Array_Latitud);
//   Serial.println();
//   Serial.print("Longitud: ");
//   Serial.println(Array_Longitud);
//   Serial.println();
//   Serial.print("Altitud: ");
//   Serial.println(Array_Altitud);
//   Serial.println();
//   Serial.print("Numero de satelites: ");
//   Serial.println(sat);
//   Serial.println();  

//  lcd.clear();                       // Borramos la pantalla .
//  delay(20);
//  lcd.setCursor(0,1);                // Posicionamos el cursor.
//  lcd.print("    Proyecto GPS    "); // Imprimimos la cadena.
//  lcd.setCursor(0,2);                // Posicionamos el cursor.
//  lcd.print("  Cristobal Garcia  "); // Imprimimos la cadena.
// 
//  lcd.clear();
//  delay(20);
//  lcd.setCursor(0,1);                // Posicionamos el cursor.
//  lcd.print("     Modulo GPS     "); // Imprimirmos la cadena.
//  lcd.setCursor(0,2);                // Posicionamos el cursor.
//  lcd.print("  & Display 4 bits  "); // Imprimimos la cadena.
//     
//  lcd.clear();  // Borramos la pantalla.
//  delay(20);
//  lcd.setCursor(0,1);                // Posicionamos el cursor.
//  lcd.print("  ** Iniciando **   "); // Imprimirmos la cadena.
//  lcd.clear();  // Borramos la pantalla.
//  delay(20);
//  lcd.setCursor(15,0);                   
//  lcd.print("0/3  ");      
//  lcd.setCursor(0,1);                   
//  lcd.print("Datos GPS         <-");      
//  lcd.setCursor(0,2);                   
//  lcd.print("Ajuste hora         ");     
//  lcd.setCursor(0,3);                   
//  lcd.print("Ajustes de envio    "); 
// 

  




 









