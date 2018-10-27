/*
  Como Criar Coisas Inteligentes com Arduino - Módulo 2
  Facilitador:       Prof. Orlewilson Bentes Maia
  Data Criacao:      26/07/2018
  Data Atualizacao:  26/07/2018
  Descricao:         Enviar alerta de intruso por WiFi usando ultrassônico
  Fonte:             https://www.teachmemicro.com/nodemcu-ajax-dynamic-sensor-data-web-page/
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

//Biblioteca do WiFi e Servidor Web
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>

//---------- Ultrassônico
// definindo portas que serão utilizadas
const int TRIG_PIN  = 5;  //D1
const int ECHO_PIN  = 4;  //D2

//Inicializa o sensor nos pinos definidos acima
Ultrasonic ultrassom(TRIG_PIN, ECHO_PIN);

// variável que guardará o valor da distância lida pelo ultrassônico
long distancia;
long duracao;

//---------- WiFi
const char* ssid = "nome da rede wifi";
const char* password = "senha";

//inicializa o servidor na porta 8080
ESP8266WebServer server(8080);   

String page = "";
String text = "";
double data;
 
void setup(void){
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
    text = (String)data;
    server.send(200, "text/html", text);
  });

  // mostra pagina web ao usuario
  server.on("/", [](){
    page = "<h1>Como Criar Coisas Inteligentes com Arduino - Modulo 2 (Conectividade)</h1>";
    page += "<h1>Dados ultrassonico:</h1> <h1 id=\"data\">""</h1>\r\n";
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
  // ultrassom.Ranging(CM) retorna a distancia em centímetros(CM) ou polegadas(INC)
  data = ultrassom.Ranging(CM);
  delay(100);

  // aguarda requisicao do cliente
  server.handleClient();
}
