/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      18/07/2018
  Atualizacao:       20/07/2018
  Descricao:         Criar um mini abajur usando LED RGB controlado por Bluetooth
*/

// configuracao das portas
const int RED_PIN = 11;
const int GREEN_PIN = 10;
const int BLUE_PIN = 9;

// Configuração
void setup()
{
  // Configura velocidade da portal serial/bluetooth
  Serial.begin(9600);

  // configura como saida cada porta do LED RGB
  pinMode(RED_PIN, OUTPUT);
  pinMode(GREEN_PIN, OUTPUT);
  pinMode(BLUE_PIN, OUTPUT);
}

void mostrarCores()
{
  // desliga o LED:

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  delay(1000);

  // apenas vermelho

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);

  delay(1000);

  // apenas verde 

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);

  delay(1000);

  // apenas azul

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);

  // amarelo

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);

  delay(1000);

  // ciano

  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);

  // púrpura

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);

  // branco

  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, HIGH);

  delay(1000);
}

void ligarAzul()
{
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, HIGH);
}

void ligarVermelho()
{
  digitalWrite(RED_PIN, HIGH);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

void ligarVerde()
{
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, HIGH);
  digitalWrite(BLUE_PIN, LOW);
}

void desligar()
{
  digitalWrite(RED_PIN, LOW);
  digitalWrite(GREEN_PIN, LOW);
  digitalWrite(BLUE_PIN, LOW);
}

char msg = ' ';
// Programa principal
void loop()
{
  // Há dado disponível?
  if (Serial.available()) 
  {
    // enquanto houver caracter
    while (Serial.available() > 0) {
      msg = Serial.read();

      if (msg == 'b'){
        ligarAzul();
      }
      if (msg == 'r'){
        ligarVermelho();
      }
      if (msg == 'g'){
        ligarVerde();
      }
      if (msg == 'o'){
        desligar();
      }
      if (msg == 'a'){
        mostrarCores();
      }
    }
  }
}
