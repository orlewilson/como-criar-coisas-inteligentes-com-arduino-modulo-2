/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      18/07/2018
  Data Atualizacao:  20/07/2018
  Descricao:         Enviar mensagem para Serial/LCD usando Bluetooth
*/

//inclui biblioteca no programa 
#include <LiquidCrystal.h>     

/*Cria objeto lcd da classe LiquidCrystal
RS     2
Enable 3
DB4    4
DB5    5
DB6    6
DB7    7
*/
LiquidCrystal lcd(2,3,4,5,6,7);


// Configuração
void setup()
{
  // Configura velocidade da portal serial/bluetooth
  Serial.begin(9600);

  //Inicializa display de 2 linhas x 16 colunas
  lcd.begin(16,2);            
  
  //Posiciona cursor no canto superior esquerdo
  lcd.home();      

  //Executa uma pequena contagem regressiva
  lcd.print("3 ");           
  delay(500);
  lcd.print("2 ");
  delay(500);
  lcd.print("1 ");
  delay(500);

  //Limpa a tela do LCD
  lcd.clear();       
  
  delay(500);

  //Posiciona o cursor na posição coluna X linha (6,0)
  lcd.setCursor(6,0);         

  //Escreve IoT
  lcd.print("IoT");  

  delay(500);

  //Posiciona o cursor na posição coluna X linha (4,1)
  lcd.setCursor(4,1);
  
  //Escreve Modulo 1
  lcd.print("Modulo 2");
}

// Programa principal
void loop()
{
  // Há dado disponível?
  if (Serial.available()) 
  {
    //Limpa a tela do LCD
    lcd.clear();
    delay(500);

    //Posiciona o cursor na posição coluna X linha (0,0)
    lcd.setCursor(0,0);         

    // enquanto houver caracter
    while (Serial.available() > 0) {
      // mostra o caracter no LCD
      lcd.write(Serial.read());
    }
  }
}
