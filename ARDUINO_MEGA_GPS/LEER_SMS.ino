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

 void leerSmsSim(char *pin)
{
   sprintf (pin_buf, "AT+CPIN=\%s", pin);
 //  Serial.println("Comenzando...");
   EnviaComandoAT("AT", "OK", 1000);
   EnviaComandoAT(pin_buf, "OK", 2000);    
   EnviaComandoAT("AT+COPS?", "+COPS:", 2000);   
//   Serial.println("Modo SMS...");
   EnviaComandoAT("AT+CMGF=1", "OK", 1000);    // Sms modo texto
   EnviaComandoAT("AT+CPMS=\"SM\"", "OK", 1000);  // Selecciona la memoria 
   answer = EnviaComandoAT("AT+CMGR=1", "+CMGR:", 2000);  // Lee el sexto sms.
   if (answer == 1)
   {
   answer = 0;
//   while(Serial.available() == 0);
   // this loop reads the data of the SMS
   do{
   // Si hay datos en el buffer de entrada del UART, los leemos y los chequeamos para la respuesta. 
   if(Serial.available() > 0)
   {    
   SMS[x] = Serial.read();
   x++;
   
   // Comprueba si la respuesta deseada (OK) es la respondida por el modulo.
   if (strstr(SMS, "OK") != NULL){answer = 1;}
   }
   }while(answer == 0); // Esperamos por la respuesta del modulo con el time out.      
   SMS[x] = '\0';
   Serial.print(SMS);
   i=0;
   x=0;
   do
   {     
   if (SMS[i]=='\r'){SMS[i]=',';}
   if (SMS[i]=='\n'){SMS[i]=' ';} 
   i++; 
   }while(i<=101);
   descomponerSms();
   i=0;
   x=0;
   if (strcmp(smsRecibido," OP")==0 && Estado==1 && sat >=3)
   {
   EnviaComandoAT("AT+CMGD=1,4","OK",1000);
   
   if (numSel==1){establecer_numero_tlf (numero_Tlf_1,Numero_PIN);} //
   if (numSel==2){establecer_numero_tlf (numero_Tlf_2,Numero_PIN);} //
   if (numSel==3){establecer_numero_tlf (numero_Tlf_3,Numero_PIN);} //
   envia_mensaje_gsm (Array_Hora);         // Enviamos el SMS.
   envia_mensaje_gsm (Array_Longitud_sms); // Enviamos el SMS.
   envia_mensaje_gsm (Array_Latitud_sms);  // Enviamos el SMS.
   finaliza_envio_gsm ();
   }
   }
   else
   {
   Serial.print("error ");
   Serial.println(answer, DEC);
   }
}

 void descomponerSms()
 { 
  i=0; 
  puntSms = strtok (SMS,",");  // Tokenizamos (troceamos) la cadena que tenemos en el array TramaGPG por las comas
                               // y el primer intervalo lo guardamos en pch (puntero char)  
//  if (strcmp(puntSms," \"REC UNREAD\"")==0)   // Si es la correcta, seguimos adelante
//  {
  while (puntSms != NULL)       // Mientras el dato sea valido, lo aceptamos para llenar el array GGA
  {           
  puntSms = strtok (NULL, ","); // Pasamos al siguiente intervalo cortado de la cadena
  arrayPuntSms[i]=puntSms;                   // Guardamos el valor de puntSms en el array GGA
  i++;                          // Incrementamos el contador/acumulador
  }
  strncpy(telefonoSms,arrayPuntSms[0] , 14); // Copia 14 chars entre las posiciones 0-13.
  strncpy(comillas, arrayPuntSms[1], 2);     // Copia 2 chars entre las posiciones 0-1.
  strncpy(fechaSms, arrayPuntSms[2], 9);     // Copia 9 chars entre las posiciones 0-8.
  strncpy(horaSms, arrayPuntSms[3], 12);     // Copia 12 chars entre las posiciones 0-11.
  strncpy(smsRecibido, arrayPuntSms[4], 3);  // Copia 3 chars entre las posiciones 0-2.                                  
//  }      
 }
