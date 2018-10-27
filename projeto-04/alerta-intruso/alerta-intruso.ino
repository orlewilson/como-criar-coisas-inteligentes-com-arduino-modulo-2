/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      26/07/2018
  Data Atualizacao:  26/07/2018
  Descricao:         Enviar alerta de intruso por WiFi usando ultrassônico
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

//Biblioteca do sensor ultrassônico
#include <Ultrasonic.h>

// definindo portas que serão utilizadas
const int TRIG_PIN  = 5;  //D1
const int ECHO_PIN  = 4;  //D2

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrassom(TRIG_PIN, ECHO_PIN);


// variável que guardará o valor da distância lida pelo ultrassônico
long distancia;
long duracao;

// Configuração
void setup() {
  // configuração da porta serial
  Serial.begin(9600);
  Serial.println("Lendo dados do ultrassônico...");
}

// Programa principal
void loop() {

    // ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
    distancia = ultrassom.Ranging(CM);
    Serial.print(distancia); //imprime o valor da variável distancia
    Serial.println("cm");
    delay(100);
}
