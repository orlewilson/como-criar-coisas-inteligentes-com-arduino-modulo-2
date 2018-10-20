/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      18/10/2018
  Data Atualizacao:  20/10/2018
  Descricao:         Mudar nome do bluetooth
  Fonte:             https://github.com/rwaldron/johnny-five/wiki/Getting-Started-with-Johnny-Five-and-HC-05-Bluetooth-Serial-Port-Module
*/

// Nome do bluetooth
#define BLUETOOTH_NAME "Orlewilson IoT"

// Velocidade do bluetooth
#define BLUETOOTH_SPEED 38400 //Essa é a velocidade padrão do modulo HC-05

// bibliotecas
#include <SoftwareSerial.h>

// Pinos de conexão bluetooth
//   Pin 10 --> Bluetooth TX
//   Pin 11 --> Bluetooth RX
SoftwareSerial BluetoothSerial(10, 11); // RX, TX

// Funcao para configurar o Arduino
void setup() {

  
  // Configura a velocidade da porta serial (console)
  Serial.begin(9600);
  Serial.println("Iniciando a configuracao");

  
  // Configura a velocidade da porta do bluetooth
  BluetoothSerial.begin(BLUETOOTH_SPEED);
  delay(1000);

  // mensagem
  String msg = String(""); 

  // Muda o baudrate para 9600
  BluetoothSerial.print("AT+UART=9600,0,0\r\n");
  waitForResponse();

  // Muda o nome do bluetooth para BLUETOOTH_NAME
  msg = String("AT+NAME=") + String(BLUETOOTH_NAME) + String("\r\n"); 
  BluetoothSerial.print(msg);
  waitForResponse();
  
  Serial.println("Feito!");
}

// funcao para aguardar resposta
void waitForResponse() {
  delay(1000);
  while (BluetoothSerial.available()) {
    Serial.write(BluetoothSerial.read());
  }
  Serial.write("\n");
}

// Funcao principal do Arduino que ficara em loop infinito
void loop() {}
