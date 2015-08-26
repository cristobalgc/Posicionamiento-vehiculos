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

/*
En esta funcion introducimos los datos 
de la hora en Array_Hora
*/
void calculo_hora(char *hora)   
  { 
    char array_Horas[3];    // Array que almacena las horas.
    array_Horas[0]=hora[0]; // Guardamos en la posicion 0 del array las decenas de las horas.
    array_Horas[1]=hora[1]; // Guardamos en la posicion 1 del array las unidades de las horas.
    Horas_Aux=atoi(array_Horas);
    Horas = atoi(array_Horas);
    Horas=Horas+incremento; 
    
    if (Horas>=24 && Horas <=36){Horas=Horas-24;}
    if (Horas>=-11 && Horas <0){Horas=Horas+24;}
    
    if (Horas==0 ){Array_Hora[0]='0';Array_Hora[1]='0';}
    if (Horas==1 ){Array_Hora[0]='0';Array_Hora[1]='1';}
    if (Horas==2 ){Array_Hora[0]='0';Array_Hora[1]='2';}
    if (Horas==3 ){Array_Hora[0]='0';Array_Hora[1]='3';}
    if (Horas==4 ){Array_Hora[0]='0';Array_Hora[1]='4';}
    if (Horas==5 ){Array_Hora[0]='0';Array_Hora[1]='5';}
    if (Horas==6 ){Array_Hora[0]='0';Array_Hora[1]='6';}
    if (Horas==7 ){Array_Hora[0]='0';Array_Hora[1]='7';}
    if (Horas==8 ){Array_Hora[0]='0';Array_Hora[1]='8';}
    if (Horas==9 ){Array_Hora[0]='0';Array_Hora[1]='9';}
    if (Horas==10 ){Array_Hora[0]='1';Array_Hora[1]='0';}
    if (Horas==11 ){Array_Hora[0]='1';Array_Hora[1]='1';}
    if (Horas==12 ){Array_Hora[0]='1';Array_Hora[1]='2';}
    if (Horas==13 ){Array_Hora[0]='1';Array_Hora[1]='3';}
    if (Horas==14 ){Array_Hora[0]='1';Array_Hora[1]='4';}
    if (Horas==15 ){Array_Hora[0]='1';Array_Hora[1]='5';}
    if (Horas==16 ){Array_Hora[0]='1';Array_Hora[1]='6';}
    if (Horas==17 ){Array_Hora[0]='1';Array_Hora[1]='7';}
    if (Horas==18 ){Array_Hora[0]='1';Array_Hora[1]='8';}
    if (Horas==19 ){Array_Hora[0]='1';Array_Hora[1]='9';}
    if (Horas==20 ){Array_Hora[0]='2';Array_Hora[1]='0';}
    if (Horas==21 ){Array_Hora[0]='2';Array_Hora[1]='1';}
    if (Horas==22 ){Array_Hora[0]='2';Array_Hora[1]='2';}
    if (Horas==23 ){Array_Hora[0]='2';Array_Hora[1]='3';}

    array_Minutos[0]=hora[2]; // Guardamos en la posicion 0 del array las decenas de las horas.
    array_Minutos[1]=hora[3]; // Guardamos en la posicion 1 del array las unidades de las horas.
    Minutos = atoi(array_Minutos);    
    ////////////////////////////////////////////////////// 
    Array_Hora[3] = hora[2];
    Array_Hora[4] = hora[3];
    ////////////////////////////////////////////////////// 
    char array_Segundos[3];    // Array que almacena los segundos.
    array_Segundos[0]=hora[4]; // Guardamos en la posicion 0 del array las decenas de las horas.
    array_Segundos[1]=hora[5]; // Guardamos en la posicion 1 del array las unidades de las horas.
    Segundos = atoi(array_Segundos);    
    Array_Hora[6]= hora[4];
    Array_Hora[7]= hora[5];
    Array_Hora[8]= '\0'; // En la posicion 8 escribimos el terminador.      
  }
  
void calculo_hn(char *hora)   
  {    
    Horas_Aux=Horas_Aux+incremento_Aux;
  
    if (Horas_Aux>=24 && Horas_Aux<=36){Horas_Aux=Horas_Aux-24;}
    if (Horas_Aux>=-11 && Horas_Aux<0){Horas_Aux=Horas_Aux+24;}

    //////////////////////////////////////////////////////    
    if (Horas_Aux==0 ){ Array_HN[0]='0'; Array_HN[1]='0';}
    if (Horas_Aux==1 ){ Array_HN[0]='0'; Array_HN[1]='1';}
    if (Horas_Aux==2 ){ Array_HN[0]='0'; Array_HN[1]='2';}
    if (Horas_Aux==3 ){ Array_HN[0]='0'; Array_HN[1]='3';}
    if (Horas_Aux==4 ){ Array_HN[0]='0'; Array_HN[1]='4';}
    if (Horas_Aux==5 ){ Array_HN[0]='0'; Array_HN[1]='5';}
    if (Horas_Aux==6 ){ Array_HN[0]='0'; Array_HN[1]='6';}
    if (Horas_Aux==7 ){ Array_HN[0]='0'; Array_HN[1]='7';}
    if (Horas_Aux==8 ){ Array_HN[0]='0'; Array_HN[1]='8';}
    if (Horas_Aux==9 ){ Array_HN[0]='0'; Array_HN[1]='9';}
    if (Horas_Aux==10 ){ Array_HN[0]='1'; Array_HN[1]='0';}
    if (Horas_Aux==11 ){ Array_HN[0]='1'; Array_HN[1]='1';}
    if (Horas_Aux==12 ){ Array_HN[0]='1'; Array_HN[1]='2';}
    if (Horas_Aux==13 ){ Array_HN[0]='1'; Array_HN[1]='3';}
    if (Horas_Aux==14 ){ Array_HN[0]='1'; Array_HN[1]='4';}
    if (Horas_Aux==15 ){ Array_HN[0]='1'; Array_HN[1]='5';}
    if (Horas_Aux==16 ){ Array_HN[0]='1'; Array_HN[1]='6';}
    if (Horas_Aux==17 ){ Array_HN[0]='1'; Array_HN[1]='7';}
    if (Horas_Aux==18 ){ Array_HN[0]='1'; Array_HN[1]='8';}
    if (Horas_Aux==19 ){ Array_HN[0]='1'; Array_HN[1]='9';}
    if (Horas_Aux==20 ){ Array_HN[0]='2'; Array_HN[1]='0';}
    if (Horas_Aux==21 ){ Array_HN[0]='2'; Array_HN[1]='1';}
    if (Horas_Aux==22 ){ Array_HN[0]='2'; Array_HN[1]='2';}
    if (Horas_Aux==23 ){ Array_HN[0]='2'; Array_HN[1]='3';}
    ////////////////////////////////////////////////////// 
    Array_HN[3] = hora[2];
    Array_HN[4] = hora[3];
    ////////////////////////////////////////////////////// 
    Array_HN[6]= hora[4];
    Array_HN[7]= hora[5];
    Array_HN[8]= '\0'; // En la posicion 8 escribimos el terminador. 
  }
    
  void calculo_latitud(char *Latitud, char *Brujula2)
{
  Array_Latitud[0]=Array_Latitud_sms[5]=Latitud[0];
  Array_Latitud[1]=Array_Latitud_sms[6]=Latitud[1]; 
  Array_Latitud[3]=Array_Latitud_sms[8]=Latitud[2];
  Array_Latitud[4]=Array_Latitud_sms[9]=Latitud[3];
  Array_Latitud[6]=Array_Latitud_sms[11]=Latitud[5];
  Array_Latitud[7]=Array_Latitud_sms[12]=Latitud[6];
  Array_Latitud[8]=Array_Latitud_sms[13]=Latitud[7];
  Array_Latitud[9]=Array_Latitud_sms[14]=Latitud[8];
  Array_Latitud_sms[15]=Latitud[9];
  Array_Latitud_sms[16]=Latitud[10];  
  Array_Latitud[11]=Array_Latitud_sms[18]=*Brujula2;
}

void calculo_longitud(char *Longitud, char *Brujula1)
{
  Array_Longitud[0]=Array_Longitud_sms[5]=Longitud[1];
  Array_Longitud[1]=Array_Longitud_sms[6]=Longitud[2]; 
  Array_Longitud[3]=Array_Longitud_sms[8]=Longitud[3];
  Array_Longitud[4]=Array_Longitud_sms[9]=Longitud[4];
  Array_Longitud[6]=Array_Longitud_sms[11]=Longitud[6];
  Array_Longitud[7]=Array_Longitud_sms[12]=Longitud[7];
  Array_Longitud[8]=Array_Longitud_sms[13]=Longitud[8];
  Array_Longitud[9]=Array_Longitud_sms[14]=Longitud[9];
  Array_Longitud_sms[15]=Longitud[10];
  Array_Longitud_sms[16]=Longitud[11];
  Array_Longitud[11]=Array_Longitud_sms[18]=*Brujula1;
}
  
void calculo_altitud(char *Altura,char*unidades )
{
  Array_Altitud[0]=Altura[0];
  Array_Altitud[1]=Altura[1];
  Array_Altitud[2]=Altura[2]; 
  Array_Altitud[3]=Altura[3];
  Array_Altitud[4]=Altura[4];
  Array_Altitud[5]=Altura[5];
  Array_Altitud[6]=Altura[6];
  Array_Altitud[8]=*unidades;   
}

