
/****************************************************************
 ******* Monitoramento de gás Carbônico, Metano e enxofre *******  
 ****************     Engenharia Mecatrônica     ****************
 ***************************************************************/

// Biblioteca Cartão SD
#include <SD.h>
// Biblioteca LCD
#include <LiquidCrystal.h>
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

// Arquivo com leituras salvas
File logMaster;

//Sensor de Metano
int MET = A2;
// Sensor de Temperatura
int LM35 = A6;
float temp;

long int OXI = 0;
long int ENX = 0;
long int CAR = 0;
float CH4 = 0;
float O2 = 0;
float H2S = 0;
float CO2 = 0;

long int SETP = 0;
float SET = 0;
long int Valor_MET = 0;
int buzzer = 34;



void setup() {
  pinMode(temp, INPUT);
  pinMode(MET, INPUT);
  pinMode(buzzer, OUTPUT);
  Serial.begin(9600);
  lcd.begin(20, 4);

  /* Inicialização Módulo Cartão SD
  Serial.println("Iniciando Cartão SD...");

    if (!SD.begin(53)) {
      Serial.println("Falha durante a inicialização!");
    return;
  }
  Serial.println("Inicialização concluida!");  
*/  
}
void loop() {
  
  // Criando e começando a escrever no arquivo dentro do SD
  logMaster = SD.open("Leituras.txt", FILE_WRITE);

  // GAS CARBONICO GAS CARBONICO
  
  CAR=analogRead(A5);
  CO2=(float)(CAR*100)/1023;
  //Serial.print("CO2= ");
  Serial.print(CO2,0);
  Serial.print(";");

  logMaster.print("CO2: ");
  logMaster.println(CO2, 0);

  //METANO METANO METANO METANO

  MET = analogRead(A2);
  Valor_MET = MET/10;
  //Serial.print("CH4= ");
  Serial.print(Valor_MET);
  Serial.print(";");

  logMaster.print("MET: ");
  logMaster.println(Valor_MET);

 // ENXOFRE ENXOFRE ENXOFRE

  ENX=analogRead(A3);
  H2S=(float)(ENX*100)/1023;
  //Serial.print("H2S= ");
  Serial.print(H2S,0);
  Serial.print(";");

   logMaster.print("H2S: ");
   logMaster.println(H2S, 0);
  
  // OXIGENIO OXIGENIO OXIGENIO

  OXI = analogRead(A0);
  O2 = (float)(OXI * 100) / 1023;
  //Serial.print("O2= ");
  Serial.print(O2, 0);
  Serial.print(";");

  logMaster.print("O2: ");
  logMaster.println(O2, 0);

  //TEMPERATURA TEMPERATURA TEMPERATURA

  temp = (float(analogRead(LM35)) * 5 / (1023)) / 0.01;
  //Serial.print("Temp: ");
  Serial.print(temp, 0);
  Serial.print(";#");
  

  logMaster.print("Temp: ");
  logMaster.println(temp, 0); 
  logMaster.println("=====================================");
  
  logMaster.close();  
  
  delay(1000); 


  if ((Valor_MET > 12) || (O2 < 19) || (H2S>=20) || (CO2>=39)) {

    lcd.setCursor(0, 0);
    lcd.print("     EMERGENCIA     ");
    lcd.setCursor(0, 1);
    lcd.print("                    ");
    lcd.setCursor(0, 2);
    lcd.print("                    ");
    lcd.setCursor(0, 3);
    lcd.print("                    ");
    digitalWrite(buzzer, HIGH);
    delay(400);

    digitalWrite(buzzer, LOW);
  }

  else if((Valor_MET <= 12) || (02 >= 19) || (H2S<20) || (CO2<39)) {
      
      digitalWrite(buzzer, LOW);
      lcd.setCursor(4, 0);
      lcd.print("MASTER CONTROL");
      lcd.setCursor(0, 1);
      lcd.print("H2S:");
      
      if (H2S<10) {
        lcd.print("00");
      }
      if ((H2S>=10) && (H2S<99)) {
        lcd.print("0");
      }  
      lcd.print(H2S, 0);
      lcd.setCursor(7, 1);
      lcd.print("<20");
      lcd.setCursor(11, 1);
      lcd.print("CO2:");
      lcd.print(CO2, 0);
      lcd.setCursor(17, 1);
      lcd.print("<39");
      lcd.setCursor(0, 2);
      lcd.print("CH4:");
      lcd.print(Valor_MET);
      lcd.setCursor(6, 2);
      lcd.print("<=10");
      lcd.setCursor(11, 2);
      lcd.print("O2:");
      lcd.print(O2, 0);
      lcd.setCursor(16, 2);
      lcd.print(">=19");
      lcd.setCursor(0, 3);
      lcd.print("TEMP:");
      lcd.print(temp);
      lcd.setCursor(13, 3);
      lcd.setCursor(11, 3);
      lcd.print("C");
    }
 }
