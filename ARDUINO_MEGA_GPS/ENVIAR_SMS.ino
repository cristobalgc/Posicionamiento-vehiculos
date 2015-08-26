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

// Establecer el numero de telefono 
void establecer_numero_tlf (char *numero,char *pin) 
{
  sprintf (numero_buf, "AT+CMGS=\"%s\"", numero);
  sprintf (pin_buf, "AT+CPIN=\%s", pin);
//  habilitar_gsm() ;//Habilita el modo GSM.
//  deshabilitar_gps();//Deshabilita el modo GPS.  
  EnviaComandoAT("AT", "OK", 1000); 
  EnviaComandoAT("AT", "OK", 1000); 
  EnviaComandoAT(pin_buf, "OK", 2000); 
  EnviaComandoAT("AT+COPS?", "+COPS:", 2000);  // Verifica la conexion.
  EnviaComandoAT("AT+CMGF=1", "OK", 1000);    // Sms modo texto
  EnviaComandoAT(numero_buf, "OK", 1000);    // comando de numero de telefono.   
}

// Envia el mensaje al telefono movil.
void envia_mensaje_gsm (char *mensaje)
{
  Serial.println (mensaje);
}

// Envia el terminador de SMS
void finaliza_envio_gsm() 
{
  delay (1000);
  Serial.write (26);
  delay (2000);
//  deshabilitar_gsm() ;// Deshabilita el modo GSM.
//  habilitar_gps();    // Habilita el modo GPS. 
}
