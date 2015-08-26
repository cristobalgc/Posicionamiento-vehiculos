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

   void menu_Seleccion()
{       

   if (menu==-2 && encoderPos==0 && posicion!=0)
   {menu=-1; encoderPos=0; goto Fin_seleccionar;}
   
   if (menu==-2 && encoderPos ==1)
   {menu=1; encoderPos=0; Flag_start=true; goto Fin_seleccionar;}
     
   if(menu==-1 && posicion!=0)
   {    
   if (encoderPos==10)
   {
   c=c-1;
   if (c <= 0){c=0;}
   Numero_PIN_Aux[c]=' ';
   }
   else
   {
   Numero_PIN_Aux[c]=Num_Sel (encoderPos);
   c=c+1;
   if (c==4){menu=0;}
   }
   goto Fin_seleccionar;
   }
   
   if (menu==0)
   {
   c=0;
   encoderPos=0;
   Flag_start=true; 
   strncpy(Numero_PIN, Numero_PIN_Aux, 4); // Copia 4 chars entre las posiciones 0-3.
   direccion=0 ;
   while (direccion!=4)
   { 
   EEPROM.write( direccion+29, Numero_PIN[direccion]); 
   direccion++;
   } 
   direccion=0 ;
   goto Fin_seleccionar;
   }   
   
   if(menu==1 && encoderPos==0)
   { menu=2; encoderPos=0; goto Fin_seleccionar;}
   
   if (menu==1 && encoderPos==1)
   { menu=3; encoderPos=0; goto Fin_seleccionar;}
   
   if (menu==1 && encoderPos==2)
   { menu=5; encoderPos=0; goto Fin_seleccionar;}
   
   if (menu==1 && encoderPos==3)
   { menu=18; encoderPos=modoTrabajo; goto Fin_seleccionar;}
    
   if (menu==2 && encoderPos==4)
   { menu=1; encoderPos=0; goto Fin_seleccionar;}
   
   // Accede al menu de aceptar, cancelar 
   // o volver a cambiar la hora
   if (menu==3)
   { menu=4; encoderPos=0; goto Fin_seleccionar;}
   
   // Guarda el cambio de hora en eeprom 
   // y sale al menu principal. 
   if (menu==4 )
   {
   incremento=incremento_Aux;
   EEPROM.write(direccion,incremento); 
   menu=1;
   encoderPos=0;
   goto Fin_seleccionar;
   }
   
   // Accede al menu de ajustes de envio   
   if (menu==5 && encoderPos==0)
   {menu=6; encoderPos=0; goto Fin_seleccionar;} 
  
   // Accede a la edicion de los numeros 1,2 y 3
   if (menu==5 && encoderPos==1)
   {menu=10; encoderPos=0; goto Fin_seleccionar;} 
   
   // Cambio del tiempo de envio
    if (menu==5 && encoderPos==2)
   {menu=17; encoderPos=t_Envio; goto Fin_seleccionar;} 
   
   // Opcion de salir al menu principal 
   // desde el menu de ajustes de envio.    
   if (menu==5 && encoderPos==3)
   {menu=1; encoderPos=0; goto Fin_seleccionar;} 
  
   // Menu de seleccion del numero 1.    
   if (menu==6 && encoderPos==0)
   {menu=7; encoderPos=0; goto Fin_seleccionar;} 
  
   // Menu de seleccion del numero 2.    
   if (menu==6 && encoderPos==1)
   {menu=8; encoderPos=0; goto Fin_seleccionar;}
  
   // Menu de seleccion del numero 3.       
   if (menu==6 && encoderPos==2)
   {menu=9; encoderPos=0; goto Fin_seleccionar;}
   
    // Regresa al menu ajustes de envio
   if (menu==6 && encoderPos==3)
   {menu=5; encoderPos=0; goto Fin_seleccionar;}
   
   // Si presionmos el pulsador volveremos al menu 5.
   // Numero 1 seleccionado.    
   if (menu==7)
   { 
   menu=5;
   numSel=1; 
   direccion=33;
   EEPROM.write(direccion,numSel); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   }
   // Si presionmos el pulsador volveremos al menu 5.
   // Numero 2 seleccionado.     
   if (menu==8)
   {
   menu=5; 
   numSel=2; 
   direccion=33;
   EEPROM.write(direccion,numSel); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   } 
  
   // Si presionmos el pulsador volveremos al menu 5.
   // Numero 3 seleccionado.
   if (menu==9)
   {
   menu=5; 
   numSel=3; 
   direccion=33;
   EEPROM.write(direccion,numSel); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   } 
  
   // Cambio de numero de telefono 1.   
   if (menu==10 && encoderPos==0)
   {menu=11; encoderPos=0; goto Fin_seleccionar;} 
  
  // Cambio de numero de telefono 2.  
   if (menu==10 && encoderPos==1)
   { menu=12; encoderPos=0; goto Fin_seleccionar;}
   
  // Cambio de numero de telefono 3.  
   if (menu==10 && encoderPos==2)
   { menu=13; encoderPos=0; goto Fin_seleccionar;} 
   
   // Regresa al menu ajustes de envio
   if (menu==10 && encoderPos==3)
   {menu=5; encoderPos=0; goto Fin_seleccionar;}
  
   // menu de cambio de  numero.  
   if (menu==11 || menu==12 || menu==13)
   {
   //Borra el numero anterior  
   if (encoderPos==10)
   {
   c=c-1;
   if (c <= 0){c=0;}
   if (menu==11) {numero_Tlf_1_Aux[c]=' ';}
   if (menu==12) {numero_Tlf_2_Aux[c]=' ';}
   if (menu==13) {numero_Tlf_3_Aux[c]=' ';}
   }
   else
   {    
   if (menu==11) {numero_Tlf_1_Aux[c]=Num_Sel (encoderPos); }
   if (menu==12) {numero_Tlf_2_Aux[c]=Num_Sel (encoderPos); }
   if (menu==13) {numero_Tlf_3_Aux[c]=Num_Sel (encoderPos); }
   c=c+1;
   if (c==9 && menu==11){menu=14;}
   if (c==9 && menu==12){menu=15;}
   if (c==9 && menu==13){menu=16;}
   }
   goto Fin_seleccionar;
   }
   
   if (menu==14)
   {
   c=0;
   menu=5;
   encoderPos=0;
   strncpy(numero_Tlf_1, numero_Tlf_1_Aux, 9); // Copia 9 chars entre las posiciones 0-8. 
   direccion=0;
   while (direccion!=9)
   { 
   EEPROM.write( direccion+2, numero_Tlf_1[direccion]); 
   direccion++;
   } 
   direccion=0 ;
   goto Fin_seleccionar;
   }
   
   if (menu==15)
   {
   c=0;
   menu=5;
   encoderPos=0;
   strncpy(numero_Tlf_2, numero_Tlf_2_Aux, 9); // Copia 9 chars entre las posiciones 0-8.  
   direccion=0 ;
   while (direccion!=9)
   { 
   EEPROM.write( direccion+11, numero_Tlf_2[direccion]); 
   direccion++;
   } 
   direccion=0 ;      
   goto Fin_seleccionar;
   }
   
   if (menu==16)
   {
   c=0;
   menu=5;
   encoderPos=0;
   strncpy(numero_Tlf_3, numero_Tlf_3_Aux,9); // Copia 9 chars entre las posiciones 0-8. 
   direccion=0 ;
   while (direccion!=9)
   { 
   EEPROM.write( direccion+20, numero_Tlf_3[direccion]); 
   direccion++;
   } 
   direccion=0 ;
   goto Fin_seleccionar;
   }
   // Guardo el tiempo de envio en la EEPROM
   if (menu==17 )
   {
    t_Envio=encoderPos;
    direccion=1;  
    EEPROM.write(direccion,t_Envio); 
    direccion=0;
    menu=5; 
    encoderPos=0;
    goto Fin_seleccionar;
   }
   
   if (menu==18 && encoderPos==0)
   {menu=19; encoderPos=0; goto Fin_seleccionar;} 
   
   if (menu==18 && encoderPos==1)
   {menu=20; encoderPos=0; goto Fin_seleccionar;}
  
   if (menu==18 && encoderPos==2)
   {menu=21; encoderPos=0; goto Fin_seleccionar;}
    
   if (menu==19)
   {
   menu=1; 
   modoTrabajo=0; 
   direccion=34;
   EEPROM.write(direccion,modoTrabajo); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   } 
   
   if (menu==20)
   {
   menu=1; 
   modoTrabajo=1; 
   direccion=34;
   EEPROM.write(direccion,modoTrabajo); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   }
   
   if (menu==21)
   {
   menu=1; 
   modoTrabajo=2; 
   direccion=34;
   EEPROM.write(direccion,modoTrabajo); 
   direccion=0;
   encoderPos=0; 
   goto Fin_seleccionar;
   }  
   
Fin_seleccionar:;
   }
