/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      26/07/2018
  Data Atualizacao:  26/07/2018
  Descricao:         Enviando dados para Internet usando o serviço IFTTT (If This Then That)
  Fonte:             http://pedrominatel.com.br/pt/esp8266/ifttt-com-esp8266-e-sming/
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

//Biblioteca do sensor dht11
#include "DHT.h" 

//Biblioteca do WiFi e Servidor Web
#include <ESP8266WiFi.h>
#include <WiFiClient.h>

//---------- DHT11
// Porta na qual lerá os valores do sensor DHT
const int DHT_PIN = 0; //D3

// Cria um objeto da classe dht
DHT dht(DHT_PIN, DHT11); 

// variáveis que armazenarão os valores lidos do sensor DHT
float valorTemp;
float valorUmidade;

//---------- WiFi
const char* ssid = "nome da rede wifi";
const char* password = "senha";

String page = "";
String text = "";

//---------- IFTTT
const char* event = "temp";
const char* makerKey = "codigo";

WiFiClient iftttClient;
const char* makerHost = "maker.ifttt.com";
const int makerPort = 80;

void setup(void){
  // inicia o sensor DHT
  dht.begin();
  
  // configuração da porta serial
  Serial.begin(115200);
  
  // inicia a conexão WiFi
  WiFi.begin(ssid, password);
  Serial.println("");
 
  // aguarda conectar
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
 
  Serial.println("");
  Serial.print("Conectado a ");
  Serial.println(ssid);
  Serial.print("Endereco IP: ");
  Serial.println(WiFi.localIP());
  
}
 
void loop(void){
  // ler os valores do DHT11
  valorUmidade = dht.readHumidity();
  valorTemp = dht.readTemperature();
  delay(1000);
  Serial.println("Temp: " + (String) valorTemp);
  Serial.println("Umidade: " + (String) valorUmidade);
  
  if (valorUmidade > 50) {
    Serial.print("conectado ao ");
    Serial.println(makerHost);
   
    if (!iftttClient.connect(makerHost, makerPort)) {
      Serial.println("falha ao tentar acessar o Maker");
      return;
    }
    String url = "/trigger/"+ (String) event+"/with/key/";
    url += (String) makerKey;
    
    Serial.print("enviando URL: ");
    Serial.println(url);
    iftttClient.print(String("POST ") + url + " HTTP/1.1\r\n" +
                         "Host: " + makerHost + "\r\n" + 
                         "Content-Type: application/x-www-form-urlencoded\r\n" + 
                         "Content-Length: 13\r\n\r\n" +
                         "value1=" + (String)valorTemp + "\r\n");
  }
}
