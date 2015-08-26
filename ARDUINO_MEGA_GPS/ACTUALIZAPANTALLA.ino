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

void Actualiza_pantalla()
{  
  if (menu==-2)
  {
  lcd.setCursor(18,encoderPos+1);
  lcd.print("<-");   
  if (encoderPos==0)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos==1)
  {lcd.setCursor(18,1); lcd.print("  ");}
 
  lcd.setCursor(0,0);                  
  lcd.print("***  BIENVENIDO  ***");   
  lcd.setCursor(0,1);                   
  lcd.print("Usar PIN nuevo    ");                            
  lcd.setCursor(0,2);                   
  lcd.print("Usar PIN antiguo  ");    
  lcd.setCursor(0,3);                   
  lcd.print("                    ");
  goto Fin_Actualiza_Pantalla;
  }
    
  if(menu==-1)
  {
  lcd.setCursor(0,0);                
  lcd.print("   Introducir PIN  ");
  lcd.setCursor(19,0);
  lcd.print(c,DEC);
  lcd.setCursor(0,1);                    
  lcd.print("         ");                
  lcd.print(Numero_PIN_Aux);                  
  lcd.setCursor(0,2);                    
  lcd.print("->  0123456789B   <-");     
  lcd.setCursor(encoderPos+4,3);         
  lcd.print("|");                        
  lcd.setCursor(encoderPos+3,3);         
  lcd.print(" ");                        
  lcd.setCursor(encoderPos+5,3);        
  lcd.print(" ");                        
  if(encoderPos==0)
  {
  lcd.setCursor(14,3);         
  lcd.print(" ");                        
  }    
  goto Fin_Actualiza_Pantalla;
  }
  
  else if (menu==0)
  {
  lcd.setCursor(0,0);                  
  lcd.print("  El numero PIN se  ");   
  lcd.setCursor(0,1);                   
  lcd.print("   ha introducido   ");                            
  lcd.setCursor(0,2);                   
  lcd.print("    correctamente   ");    
  lcd.setCursor(0,3);                   
  lcd.print("Presione para salir ");     
  goto Fin_Actualiza_Pantalla;    
  }
 
  else if(menu==1)
  {
  lcd.setCursor(15,0);
  lcd.print(encoderPos,DEC);
  lcd.print("/3  ");
  
  if (encoderPos==0 || encoderPos==1 || encoderPos==2 )
  {
  lcd.setCursor(18,encoderPos+1); 
  lcd.print("<-");  
  // OPCIONES DE SELECCION 
  if (encoderPos+1==2 ||encoderPos+1==3)
  {lcd.setCursor(18,1); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==3)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==2)
  {lcd.setCursor(18,3); lcd.print("  ");}
  lcd.setCursor(0,1);                   
  lcd.print("Datos GPS         ");      
  lcd.setCursor(0,2);                  
  lcd.print("Ajuste hora       ");      
  lcd.setCursor(0,3);                   
  lcd.print("Ajustes de envio  ");      
  }
  else if(encoderPos==3 )
  {
  lcd.setCursor(18,encoderPos-2); 
  lcd.print("<-");   
  lcd.setCursor(0,1);                   
  lcd.print("Modo de trabajo   ");        
  lcd.setCursor(0,2);                   
  lcd.print("                    ");    
  lcd.setCursor(0,3);                   
  lcd.print("                    ");        
  }    
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==2)
  {
  lcd.setCursor(15,0);
  lcd.print(encoderPos,DEC);
  lcd.print("/4  ");
  
  if (encoderPos==0 || encoderPos==1 || encoderPos==2 )
  {
// OPCIONES DE SELECCION
  lcd.setCursor(18,encoderPos+1); 
  lcd.print("<-");  
  if (encoderPos+1==2 ||encoderPos+1==3)
  {lcd.setCursor(18,1); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==3)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==2)
  {lcd.setCursor(18,3); lcd.print("  ");}
   
   if (Estado==0)
   {
   lcd.setCursor(0,1);                   
   lcd.print("Lon : Calc        ");     
   lcd.setCursor(0,2);                   
   lcd.print("Lat : Calc        ");      
   lcd.setCursor(0,3);                   
   lcd.print("Sat : Calc        ");      
   }
   
   if (Estado==1)
   {  
   lcd.setCursor(0,1);       
   lcd.print("Lon: ");       
   lcd.setCursor(17,1);       
   lcd.print(" ");         
   lcd.setCursor(0,2);        
   lcd.print("Lat: ");       
   lcd.setCursor(17,2);       
   lcd.print(" ");          
   lcd.setCursor(0,3);       
   lcd.print("Sat: ");        
   lcd.setCursor(6,3);        
   lcd.print("            ");   
   }  
   } 
   else if(encoderPos==3 || encoderPos==4)
   {
// OPCIONES DE SELECCION 
   lcd.setCursor(18,encoderPos-2); 
   lcd.print("<-");  
   if (encoderPos-2==1)
   {lcd.setCursor(18,2); lcd.print("  ");}
   if (encoderPos-2==2)
   {lcd.setCursor(18,1); lcd.print("  ");}
//   
   lcd.setCursor(0,2);                   
   lcd.print("Salir             ");       
   lcd.setCursor(0,3);                   
   lcd.print("                    ");

   if (Estado==0)
   {
   lcd.setCursor(0,1);                   
   lcd.print("Alt : Calc        ");      
   }
   if (Estado==1)
   {
   lcd.setCursor(0,1);       
   lcd.print("Alt: ");      
   lcd.setCursor(14,1);      
   lcd.print("    ");           
   }     
   }   
   goto Fin_Actualiza_Pantalla;
   }
  
  else if(menu==3)
  {
  lcd.setCursor(0,0);                 
  lcd.print("** CAMBIO DE HORA **"); 
  lcd.setCursor(0,1);
  lcd.print("Hora Actual:");
  lcd.setCursor(0,2);
  lcd.print("Hora Nueva: "); 
  lcd.setCursor(8,3);                 
  lcd.print("GMT");                  
  if (encoderPos <0 && encoderPos >-10)
  {
  lcd.setCursor(11,3);
  lcd.print(encoderPos,DEC);
  lcd.print(" ");
  }
  else if (encoderPos ==0)
  {
  lcd.setCursor(11,3);
  lcd.print(" ");
  lcd.print(encoderPos,DEC);
  lcd.setCursor(13,3);
  lcd.print(" ");
  }
  else if (encoderPos >0 && encoderPos <10)
  {
  lcd.setCursor(11,3);
  lcd.print("+");
  lcd.print(encoderPos,DEC);
  lcd.print(" ");
  }
  else if ( encoderPos >=10)
  {
  lcd.setCursor(11,3);
  lcd.print("+");
  lcd.print(encoderPos,DEC);
  }     
  else
  {
  lcd.setCursor(11,3);
  lcd.print(encoderPos,DEC);
  }      
  incremento_Aux=encoderPos;
   
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==4)
  { 
  lcd.setCursor(0,1);                   
  lcd.print("   Hora cambiada    ");      
  lcd.setCursor(0,2);                   
  lcd.print("   Correctamente    ");     
  lcd.setCursor(0,3);                   
  lcd.print("Presione para salir ");        
  goto Fin_Actualiza_Pantalla;
  }
  else if(menu==5)
  {
  lcd.setCursor(18,encoderPos); 
  lcd.print("<-"); 
  
  if (encoderPos==1 ||encoderPos==2||encoderPos==3)
  {lcd.setCursor(18,0); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==2||encoderPos==3)
  {lcd.setCursor(18,1); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==1||encoderPos==3)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==1||encoderPos==2)
  {lcd.setCursor(18,3); lcd.print("  ");}
  
  lcd.setCursor(0,0);                   
  lcd.print("Seleccionar num   ");     
  lcd.setCursor(0,1);                  
  lcd.print("Editar numero     ");     
  lcd.setCursor(0,2);                  
  lcd.print("Tiempo de envio   ");      
  lcd.setCursor(0,3);                   
  lcd.print("Salir             ");       
  goto Fin_Actualiza_Pantalla;
  }
  else if ( menu==6 || menu==10)
  {
  lcd.setCursor(18,encoderPos); 
  lcd.print("<-"); 
  
  if (encoderPos==1 ||encoderPos==2||encoderPos==3)
  {lcd.setCursor(18,0); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==2||encoderPos==3)
  {lcd.setCursor(18,1); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==1||encoderPos==3)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos==0 ||encoderPos==1||encoderPos==2)
  {lcd.setCursor(18,3); lcd.print("  ");}
   
  lcd.setCursor(0,0);                  
  lcd.print("Num 1:   ");
  lcd.print(numero_Tlf_1);  
  lcd.setCursor(0,1);                  
  lcd.print("Num 2:   ");
  lcd.print(numero_Tlf_2);  
  lcd.setCursor(0,2);                   
  lcd.print("Num 3:   ");
  lcd.print(numero_Tlf_3);  
  lcd.setCursor(0,3);                   
  lcd.print("Salir             ");     
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==7 || menu==8 || menu==9)
  {
  lcd.setCursor(0,0); // Posicionamos el cursor.
  lcd.print("     El numero      ");     
  lcd.setCursor(5,1);                   
  if (menu==7){lcd.print(numero_Tlf_1);}  
  if (menu==8){lcd.print(numero_Tlf_2);} 
  if (menu==9){lcd.print(numero_Tlf_3);}        
  lcd.setCursor(0,2);                     
  lcd.print("Ha sido seleccionado");      
  lcd.setCursor(0,3);                     
  lcd.print("Presione para salir ");       
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==11 || menu==12 || menu==13)
  {
  lcd.setCursor(0,0);                    
  lcd.print("Actual:  ");                
  if (menu==11){lcd.print(numero_Tlf_1);}  
  if (menu==12){lcd.print(numero_Tlf_2);}  
  if (menu==13){lcd.print(numero_Tlf_3);}  
  lcd.setCursor(19,0);
  lcd.print(c,DEC);
  lcd.setCursor(0,1);                    
  lcd.print("Nuevo:   ");                
  if (menu==11){lcd.print(numero_Tlf_1_Aux);}               
  if (menu==12){lcd.print(numero_Tlf_2_Aux);}               
  if (menu==13){lcd.print(numero_Tlf_3_Aux);}               
  lcd.setCursor(0,2);                    
  lcd.print("->  0123456789B   <-");     
  lcd.setCursor(encoderPos+4,3);         
  lcd.print("|");                        
  lcd.setCursor(encoderPos+3,3);         
  lcd.print(" ");                        
  lcd.setCursor(encoderPos+5,3);        
  lcd.print(" ");                        
  if(encoderPos==0)
  {
  lcd.setCursor(14,3);         
  lcd.print(" ");                        
  }  
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==14 || menu==15 || menu==16)
  {
  lcd.setCursor(0,0);                     
  lcd.print(" El numero ha sido  ");      
  lcd.setCursor(0,1);                     
  lcd.print("      Cambiado      ");      
  lcd.setCursor(5,2);                     
  if (menu==14){lcd.print(numero_Tlf_1_Aux);}           
  if (menu==15){lcd.print(numero_Tlf_2_Aux);}           
  if (menu==16){lcd.print(numero_Tlf_3_Aux);}            
  lcd.setCursor(0,3);                     
  lcd.print("Presione para salir ");       
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==17)
  {
  lcd.setCursor(0,0);                  
  lcd.print("* Tiempo de envio  *");   
  lcd.setCursor(0,1);                   
  lcd.print(" Enviar SMS cada ");      
  lcd.print(encoderPos,DEC);           
  lcd.print(" ");                       
  lcd.setCursor(0,2);                   
  lcd.print("    min y 20 Seg    ");    
  lcd.setCursor(0,3);                   
  lcd.print("Presione para salir ");    
  goto Fin_Actualiza_Pantalla;
  }
  
  else if(menu==18)
  {
   lcd.setCursor(18,encoderPos+1); 
  lcd.print("<-");  
  if (encoderPos+1==2 ||encoderPos+1==3)
  {lcd.setCursor(18,1); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==3)
  {lcd.setCursor(18,2); lcd.print("  ");}
  if (encoderPos+1==1 ||encoderPos+1==2)
  {lcd.setCursor(18,3); lcd.print("  ");}

  lcd.setCursor(0,1);   
  lcd.print("Modo autonomo     ");   
  lcd.setCursor(0,2);                   
  lcd.print("Peticion usuario  ");                            
  lcd.setCursor(0,3);                   
  lcd.print("Brujula digital   ");      
  goto Fin_Actualiza_Pantalla;
  }
//  
  else if (menu==19 || menu==20 || menu==21)
  {
  lcd.setCursor(0,0);                   
  lcd.print("                  ");  
  lcd.setCursor(0,1);   
  if (menu==19){lcd.print("   Modo autonomo    ");}
  if (menu==20){lcd.print("   Modo peticion    ");}
  if (menu==21){lcd.print("Modo brujula digital");} 
  lcd.setCursor(0,2);                   
  lcd.print("    seleccionado    ");                            
  lcd.setCursor(0,3);                   
  lcd.print("Presione para salir "); 
  goto Fin_Actualiza_Pantalla;  
  }
Fin_Actualiza_Pantalla:;
}
