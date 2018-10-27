/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      26/07/2018
  Data Atualizacao:  26/07/2018
  Descricao:         Disponibilizar informações de uma mini estação meteorológica usando WiFi
  Fonte:             https://www.teachmemicro.com/nodemcu-ajax-dynamic-sensor-data-web-page/
                     https://roboindia.com/tutorials/DHT11-NodeMCU-arduino
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
#include <ESP8266WebServer.h>

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

//inicializa o servidor na porta 8080
ESP8266WebServer server(8080);   

String page = "";
String text = "";
 
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

  // salva dados no arquivo data.txt
  server.on("/data.txt", [](){
    text = "Temperatura: " + (String)valorTemp + º" | Umidade: " + (String)valorUmidade;
    server.send(200, "text/html", text);
  });

  // mostra pagina web ao usuario
  server.on("/", [](){
    page = "<h1>Como Criar Coisas Inteligentes com Arduino - Modulo 2 (Conectividade)</h1>";
    page += "<h1>Dados DHT:</h1> <h1 id=\"data\">""</h1>\r\n";
    page += "<script>\r\n";
    page += "var x = setInterval(function() {loadData(\"data.txt\",updateData)}, 100);\r\n";
    page += "function loadData(url, callback){\r\n";
    page += "var xhttp = new XMLHttpRequest();\r\n";
    page += "xhttp.onreadystatechange = function(){\r\n";
    page += " if(this.readyState == 4 && this.status == 200){\r\n";
    page += " callback.apply(xhttp);\r\n";
    page += " }\r\n";
    page += "};\r\n";
    page += "xhttp.open(\"GET\", url, true);\r\n";
    page += "xhttp.send();\r\n";
    page += "}\r\n";
    page += "function updateData(){\r\n";
    page += " var lastContent = document.getElementById(\"data\").innerHTML\r\n";
    page += " document.getElementById(\"data\").innerHTML = this.responseText + \"</br>\" + lastContent ;\r\n";
    page += "}\r\n";
    page += "</script>\r\n";
    
    server.send(200, "text/html", page);
  });
 
  server.begin();
  Serial.println("Servidor Web iniciado!");
}
 
void loop(void){
  // ler os valores do DHT11
  valorUmidade = dht.readHumidity();
  valorTemp = dht.readTemperature();
  delay(100);

  // aguarda requisicao do cliente
  server.handleClient();
}
