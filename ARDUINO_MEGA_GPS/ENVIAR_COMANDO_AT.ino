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

int8_t EnviaComandoAT(char* comandoAT, char* resp_esperada, unsigned int timeout)
 {
  uint8_t x=0,  answer=0;
  char respuesta[100];
  unsigned long previous;
  memset(respuesta, '\0', 100);  // Inicializa el string.
  delay(100);
  while( Serial.available() > 0) Serial.read();    // Limpia el buffer de entrada.
  Serial.println(comandoAT);    // Envia el comando AT.
  x = 0;
  previous = millis();
  // Este bucle espera por la respuesta.
  do{
  // Si hay datos en el buffer de entrada del UART, los leemos y los chequeamos para la respuesta. 
  if(Serial.available() != 0){    
  respuesta[x] = Serial.read();
  x++;
  // Comprueba si la respuesta esperada es la respuesta del modulo.       
  if (strstr(respuesta, resp_esperada) != NULL)    
  {
  answer = 1;
  }
  }
  // Espera por la respuesta con el time out
  }while((answer == 0) && ((millis() - previous) < timeout));    
  return answer;
 }

