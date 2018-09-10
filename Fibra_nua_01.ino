/*Projeto Pontos Quentes 
 MC: Arduino UNO 
AUTOR: Nichollas Freitas DATA: AUGUST,2018 
REFERÊNCIA: https://www.youtube.com/watch?v=zRlONKtpC8M&feature=youtu.be
 */
 
// Bibliotecas
#include <SD.h>             //Biblioteca para receber dados 

// MAPEAMENTO DE HARDWARE 
int  CS_10 = 10;           // pin digital 10
int temp_pin = A0;        // Pin analógico 0 sensor de temperatuta 
int power_pin = A1;       // Pin analógico 1 sensor de potência óptica


  // Função Auxiliar 
int AVERAGE_TEMP();     // Verificar média de 100 leituras de temperatura

  // VARIÁVEIS GLOBAIS
  const int voltage = 5;  
  //const int celsius_unity = 100;        // Variação de temperatura    
  const int ad_resolution = 1024;      // resolução AD utilizada 

 unsigned int store01;     // Armazenamento de dados
 unsigned int rest01;       // Resto da primeira divisão 
 unsigned int rest02;       // Resto da segunda divisão  
 unsigned int dec01;       // primeiro valor após o número decimal 
 unsigned int dec02;       // segundo valor após o numero decimal   
 unsigned long minute = 1;     // Armazena os minutos transcorrido 

  // ===CONFIGURAÇÕES INICIAIS===

  void setup() {

  
      Serial.begin (9600);        // COMUNICAÇÃO ENTRE O ARDUINO E A IDE
      Serial. println ("Iniciando o arquivo");

     // pinMode (power_pin, INPUT);         // Sáida de potência  
     pinMode(CS_10, OUTPUT);      // Saída de dados.  


// Verifica se o cartão está pronto 
if (SD.begin(10))

{ 
  Serial.println ("SD Card off");
  return;   
  
} 
  Serial.println (" SD Card conection successful");

// Cria e escreve o Arquivo  
 File logfile = SD.open ("Fibra_nua.txt", FILE_WRITE); 

if (logfile)
{
  String data = "T_Celsius";
  logfile.println (data);   
   logfile.close (); 
   Serial.println (data); 
  } // end logfile 
  else 
  { 
    Serial.println ("Erro ao abrir o arquivo");
    }
} // end setup 


int AVERAGE_TEMP() // Retorna a média entre a 30 leituras realizadas
{ 
 
       int temp_store = 0;
            
      for (int i=0; i< 30; i++)
      {
         temp_store += analogRead (temp_pin);
      }

    return (temp_store/30); 
}

 //===========================================================================================================================
  void loop() 
  {
    int level_power = analogRead (power_pin);


 // Abrir um arquivo de cada vez 
File logfile = SD.open (" Fibra_nua. txt", FILE_WRITE); 
if (logfile )
{
  logfile.println(); 
  logfile.close (); 
  Serial.println (); 
} // end logfile

   // === CALCULO DA RESOLUÇÃO AD E CONVERSÃO EM CELSIUS===
//    store01 = AVERAGE_TEMP() * voltage * celsius_unity; 
    unsigned long temp_Celsius = store01 / ad_resolution; 
    rest01 = store01 % ad_resolution;
    dec01 = (rest01 *10) / ad_resolution;
    rest02 = rest01 % ad_resolution;
    dec02 = (rest02 * 10 )/ ad_resolution;
    
    //int temp_kelvin = temp_Celsius + 273;  // converte a temperatura de celsius para escala Kelvin 


    // === CRIAR STRING PARA ARMAZENAMENTO DE DADOS=== 
     String dataString= String( minute) + (",") + String (AVERAGE_TEMP())+ (",") + String (temp_Celsius)+ (",") + "." + String (dec01)+ String (dec02) + "," ; 
 

   } // end void loop 
   


 
