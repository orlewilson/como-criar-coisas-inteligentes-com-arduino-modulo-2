/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      26/07/2018
  Data Atualizacao:  26/07/2018
  Descricao:         Ligar/desligar LED usando NodeMCU
*/

/*
Correspondência de pinagens entre Arduino e NodeMCU

Arduino Uno/Mega    NodeMCU
16                  D0
5                   D1
4                   D2
0                   D3
2                   D4
14                  D5
12                  D6
13                  D7
15                  D8
*/

// definindo portas que serão utilizadas
const int LED_PIN = 13;

// Configuração
void setup() {
  // Define o pino como saida
  pinMode(LED_PIN, OUTPUT);
}

// Programa principal
void loop() {

  // Liga LED 
  digitalWrite(LED_PIN, HIGH);

  // Aguarda 1 segundo
  delay(1000);

  // Desliga LED
  digitalWrite(LED_PIN, LOW);

  // Aguarda 1 segundo
  delay(1000);
}
