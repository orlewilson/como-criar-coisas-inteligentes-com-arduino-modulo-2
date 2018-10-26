/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      18/07/2018
  Atualizacao:       20/07/2018
  Descricao:         Simular portão de entrada após identificação RFID
*/

// Bibliotecas
// para comunicação serial
#include <SPI.h>

// para comunicação com módulo RFID
#include <MFRC522.h>

// portas do módulo RFID
#define SS_PIN 10
#define RST_PIN 9

// criando a instância do módulo RFID
MFRC522 mfrc522(SS_PIN, RST_PIN);

// porta LED para simular acesso
int LED_PIN = 8;

bool acesso = false;

// Funcao para configurar o Arduino
void setup() 
{
  // inicia a porta serial
  Serial.begin(9600);

  // inicia  SPI bus
  SPI.begin();      

  // inicia o módulo RFID
  mfrc522.PCD_Init();   // Inicia MFRC522
  
  Serial.println("Aproxime o seu cartao do leitor...");
  Serial.println();
  
  // configura porta LED
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, LOW);
}

// Funcao principal do Arduino que ficara em loop infinito
void loop() 
{
  // procura por novos cartões
  if ( ! mfrc522.PICC_IsNewCardPresent()) 
  {
    return;
  }
  // seleciona um cartão
  if ( ! mfrc522.PICC_ReadCardSerial()) 
  {
    return;
  }
  //Mostra UID na serial
  Serial.print("UID da tag :");
  String conteudo= "";
  byte letra;
  for (byte i = 0; i < mfrc522.uid.size; i++) 
  {
     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
     Serial.print(mfrc522.uid.uidByte[i], HEX);
     conteudo.concat(String(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " "));
     conteudo.concat(String(mfrc522.uid.uidByte[i], HEX));
  }
  Serial.println();
  Serial.print("Mensagem : ");
  conteudo.toUpperCase();

  //UID 1 - Chaveiro
  if (conteudo.substring(1) == "31 5D 0D 24")
  {
    Serial.println("Seja Bem-Vindo Orlewilson!");
    Serial.println("Acesso liberado :)");
    Serial.println();
    
    acesso = true;
    delay(1000);
  }
  
  if (acesso) {
    //simula liberacao de acesso
    digitalWrite(LED_PIN, HIGH);
    acesso = false;
    delay(5000);
    digitalWrite(LED_PIN, LOW);
  }
} 
