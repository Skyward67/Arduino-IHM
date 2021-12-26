#include <Keypad.h>    //Librairie Keypad
#include <Wire.h>      //Librairie LCD
#include "rgb_lcd.h"   //Librairie LCD
#include <math.h>


int ult = 10;                                                                         //Maximum de noix cassable a la fois 
int i = 0;
int fnb = 0;
int d = 0;
int c = 0;
int m = 0;
float x = 0;

//variable du menu
int nav = 0;                                                                          //Navigation dans le menu
int navm = 0;                                                                         //Navigation dans le menu de la définition du nombre max de noix
int fnbm = 0;                                                                         //Premier nombre pour la définition du nombre max de noix
int snbm = 0;                                                                         //Deuxième nombre pour la définition du nombre max de noix
int w = 0;





rgb_lcd lcd;

const int r=0;
const int g=0;
const int b=0;



const byte ROWS = 4;                                                                  //Variable nb de lignes
const byte COLS = 3;                                                                  //Variable nb de colones 

char hexaKeys[ROWS][COLS] = {                                                         //Tableau charactères du keypad
  {'1', '2', '3'},
  {'4', '5', '6'},
  {'7', '8', '9'},
  {'a', '0', 'b'}
};

byte rowPins[ROWS] = {10, 9, 8, 7}; 
byte colPins[COLS] = {13, 12, 11}; 

Keypad customKeypad = Keypad(makeKeymap(hexaKeys), rowPins, colPins, ROWS, COLS);     //Définis le la globalitée du keypad 





void setup(){
  Serial.begin(9600);

  
  lcd.begin(16, 2);
  lcd.setRGB(r, g, b);
  lcd.print("Nombres de noix: ");
  lcd.setCursor(0, 2);


  pinMode(3, OUTPUT);                                                                 //Bouton reset sortie 
  pinMode(2, INPUT);                                                                  //Bouton reset entrée
  digitalWrite(2, HIGH);                                                              //Bouton reset lecture 
  pinMode(4, OUTPUT);                                                                 //Moteur signal activation (sortie)
}



//Void moteurs appelés dans le Loop 
void motors(){










  
  
}


//Void menu appelés dans le Loop (menue interface utilisateur)
void menu(){

        int customKey = customKeypad.getKey();
        lcd.clear();
        lcd.setCursor(0,0);
        lcd.print("Menu :");
        lcd.setCursor(0,2);
        lcd.print("1- Max noix");
        nav = 0;
        navm = 0;

                                    while (w!=1){
                                       int customKey = customKeypad.getKey();

                                            //Quitter le Menu après appuie "cancel"  
                                            if (customKey == 97 && nav == 0){
                                              w = 1;
                                              i = 0;
                                              m = 0;
                                              lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("Nombres de noix: ");
                                              lcd.setRGB( 29, 124, 202);
                                              lcd.setCursor(0,2);
                                            }                                       
                                            
                                            //Si validation     
                                            else if(customKey == 98 && nav == 0){
                                              lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("Max de noix =");
                                              lcd.print(ult);
                                              lcd.setCursor(0,2);
                                              lcd.print("Nouveau : ");
                                              nav++;
                                              navm = 0;

                                                    while(navm!=3){
                                                      int customKey = customKeypad.getKey();

                                                        
                                                        
                                                        if(customKey == 98){
                                                          
                                                          if(navm == 0){
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Valeur");
                                                            lcd.setCursor(0,2);
                                                            lcd.print("  impossible");
                                                            delay(1100);
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Max de noix =");
                                                            lcd.print(ult);
                                                            lcd.setCursor(0,2);
                                                            lcd.print("Nouveau : ");
                                                          }
                                                          else if(navm == 1){
                                                            ult = fnbm;
                                                          }
                                                          else if(navm == 2){
                                                            ult = fnbm*10 + snbm;
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Max de noix =");
                                                            lcd.print(ult);
                                                            navm = 0;
                                                          }
                                                          
                                                        }

                                                        else if(customKey == 97){

                                                          if(navm == 1){
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Max de noix =");
                                                            lcd.print(ult);
                                                            lcd.setCursor(0,2);
                                                            lcd.print("Nouveau : ");
                                                            navm = 0;
                                                            fnbm = 0;
                                                          }
                                                          else if(navm ==2){
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Max de noix =");
                                                            lcd.print(ult);
                                                            lcd.setCursor(0,2);
                                                            lcd.print("Nouveau : ");
                                                            navm = 0;
                                                            fnbm = 0;
                                                            snbm = 0;
                                                          }
                                                          else if(navm == 0){
                                                            lcd.clear();
                                                            lcd.setCursor(0,0);
                                                            lcd.print("Menu :");
                                                            lcd.setCursor(0,2);
                                                            lcd.print("1- Max noix");
                                                            nav = 0;
                                                            navm = 3;
                                                          }
                                                        }
                                                        else if(customKey && navm == 0){
                                                          fnbm = customKey-48;
                                                          lcd.print(fnbm);
                                                          navm++;
                                                        }
                                                        
                                                        else if(customKey && navm == 1){
                                                          snbm = customKey-48;
                                                          lcd.print(snbm);
                                                          navm++;
                                                        }

                                                    }

                                            }

                                            
                                            //Si page suivante
                                            else if (customKey == 56 && nav == 0){
                                              lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("1- Max noix");
                                              lcd.setCursor(0,2);
                                              lcd.print("2-");
                                              nav++;
                                            }
                                             //Page précédente (2eme page to 1ere page)
                                            else if (customKey == 50 && nav == 1){
                                              lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("Menu :");
                                              lcd.setCursor(0,2);
                                              lcd.print("1- Max noix");
                                              nav = 0;
                                            }

                                    }
        
         
}








//Loop avec les interactions Keypad/screen
void loop(){
  int customKey = customKeypad.getKey();
  
                                    
//Entrer du premier chiffre                                    
                            
                                            if(customKey && i == 0){
                                              
                                              lcd.clear();
                                              lcd.setCursor(0,0);
                                              lcd.print("Nombres de noix: ");
                                              lcd.setRGB( 29, 124, 202);
                                              lcd.setCursor(0,2);
                                              Serial.println(customKey);
                                              lcd.write(customKey);
                                              fnb = customKey - 48;
                                              i ++;


                                                    if (customKey == 98){
                                                      lcd.setCursor(0, 2);
                                                      Serial.println(customKey);
                                                      fnb = 0;
                                                      i = 0;
                                                      lcd.setCursor(0, 2);
                                                      lcd.print("                 ");
                                                      lcd.setCursor(0, 2);
                                                    }
                                                    if (customKey == 97){
                                                      lcd.setCursor(0,2);
                                                      i = 6;
                                                    }

                                                    
                                            }



//Entrer du second chiffre
                                            
                                            else if(customKey && i == 1){
                                            Serial.println("test i =1");
                                            lcd.write(customKey);
                                              d = customKey - 48;
                                              i = i+2;


                                                    
                                                    if (d == 50){
                                                      i = 2;
                                                      d = 0;
                                                    }
                                                    
                                                    else if (d == 49){
                                                      i = 0;
                                                      d = 0;
                                                      fnb = 0;
                                                      lcd.setCursor(0,2);
                                                      lcd.print("                ");
                                                      lcd.setCursor(0,2);
                                                      
                                                    }
                                            }


//Résultat final (nombre constitué uniquement du premier chiffre et demande de validation)

                                            else if (i == 2){
                                              Serial.println("test i =2");
                                              c = fnb;
                                              lcd.setRGB(241, 205, 70);
                                              lcd.setCursor(0,2);
                                              lcd.print(c);
                                              lcd.setCursor(1,2);
                                              lcd.print(" ?             ");

                                                    if (customKey == 98){
                                                      i = 4;
                                                    }
                                                    else if (customKey == 97){
                                                      i = 0;
                                                      fnb = 0;
                                                      d = 0;
                                                      c = 0;
                                                      lcd.setCursor(0,2);
                                                      lcd.print("                ");
                                                    }
                                            }
                                            

//Résultat final (nombre constitué des deux chiffres précédents)
                                            
                                            else if(i==3){
                                              Serial.println("test i =3");
                                              c = fnb*10 + d;
                                              lcd.setCursor(0,2);



                                                                                    //Nombre de noix supérieur au maximum accepté 
                                                                                    if(c>ult){
                                                                                      Serial.println("nb Max");
                                                                                      lcd.setRGB(150, 0, 0);
                                                                                      c = 0;
                                                                                      i = 0;
                                                                                      fnb = 0;
                                                                                      d = 0;
                                                                                      lcd.setCursor(0,2);
                                                                                      lcd.print("Valeur > 10     ");
                                                                                      delay(1100);
                                                                                      lcd.setCursor(0,2);
                                                                                      lcd.print("                ");
                                                                                      lcd.setRGB( 29, 124, 202);
                                                                                      
                                                                                    }

                                                                                    //Nombre de noix inférieur ou égale au maximum accepté                                                                                     
                                                                                    else if(c<=ult){
                                                                                      lcd.clear();
                                                                                      lcd.setCursor(0,0);
                                                                                      lcd.print("Nombres de noix:");
                                                                                      lcd.setCursor(0,2);
                                                                                      lcd.print(c);
                                                                                      lcd.print(" ?");
                                                                                      lcd.setRGB(241, 205, 70);
                                                                                      i = 7; 
                                                                                      

                                                                                                                  
                                                                                                                    
                                                                                                                  
                                                                                                                     
                                                                                                                      
                                                                                                                  
                                                                                                        }  
                                                          }


                                            else if(customKey && i == 7){
                                                if (customKey == 98){
                                                    i = 4;
                                                      }
                                                else if (customKey == 97){
                                                    i = 0;
                                                    fnb = 0;
                                                    d = 0;
                                                    c = 0;
                                                    lcd.clear();
                                                    lcd.setCursor(0,0);
                                                    lcd.print("Nombres de noix:");
                                                    lcd.setRGB( 29, 124, 202);
                                                             }
                                              
                                            }
                                                          
//Envoi au moteur après validation du nombre de noix à casser et lancement de "motors" (sous-programme)

                                            else if(i == 4){
                                              
                                              lcd.setRGB(0, 150, 0);
                                              lcd.setCursor(0 ,2);
                                              lcd.write("               ");
                                              lcd.setCursor(0 ,2);
                                              lcd.print("Cassage en cour ");
                                              delay(100);
                                              motors ();
                                              i++;
                                                                                                                        
                                            }

//Remise a zero après 3eme appuie (non permanent)

                                            else if(customKey && i==5){
                                              fnb = 0;
                                              d = 0;
                                              c = 0;
                                              i = 0;
                                              lcd.setCursor(0,2);
                                              lcd.setRGB( 29, 124, 202);
                                              lcd.print("                ");
                                            }



//Accès au menu après 3 appuie "cancel"

                                          if (customKey && i == 6){

                                              if (customKey == 97){
                                                m++ ;
                                                i = 6;
                                                lcd.print("*");
                                              }
                                              else if(customKey){
                                                m = 0;
                                                i = 0;
                                                lcd.setCursor(0,2);
                                                lcd.print("                ");
                                              }

                                            
                                          }
                                          if (customKey && i == 6 && m == 3){
                                            i++;
                                            w = 0;
                                            menu();
                                          
                                          }



//Boutton de reset

  int etatBouton=digitalRead(2);
    Serial.println(etatBouton);
  
  if (etatBouton == 0) {
    fnb = 0;
    d = 0;
    c = 0;
    i = 0;
    m = 0;
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Nombres de noix: ");
    lcd.setRGB( 0, 0, 0);
  }

                                            

}
