/*
 *
*/

//needed for library
#include <DNSServer.h>
//#include <ESP8266WebServer.h>
//#include <ESP8266WiFi.h>
#include <WiFiManager.h>         //https://github.com/tzapu/WiFiManager

#include <WiFi.h> //funcionalidades de conexão wifi, como AP e WebServer
#include <ESP_ClientMacaddress.h>
#include <DHT.h>
#include <String.h>

//Definição do DHT11
#define DHTPIN 4 // pino de dados do DHT22
#define DHTTYPE DHT22 // define o tipo de sensor, no caso DHT22
#define NUM_DISPOSITIVOS 3

DHT dht(DHTPIN, DHTTYPE);

//Crendenciais do ponto de acesso
const char *ssid = "nardo_ssid";
const char *senha = "mypw7777";
WiFiServer server(80); //Porta padrão 80

float humidity;
float temperature;
bool deviceConnected = false;
bool mac_conhecido;
String textoS;

uint8_t macList[NUM_DISPOSITIVOS][6] = {
  {0x84,0x37,0xD5,0xA9,0xF3,0xA3},
  {0x4E,0xF3,0x6D,0x4A,0x40,0xAB}, 
  {0xA8,0x16,0xD0,0xA6,0x45,0x3C} 
};

ClientMacaddress clientMac(macList, NUM_DISPOSITIVOS);

void run_html(WiFiClient client){ 
   String html_content = \
    "<!DOCTYPE html><html>" \
        "<head><style media='screen' type='text/css'>" \
             "html{margin:10px auto;text-align:center;}" \
        "</style></head>" \
        "<body>" \
            "<h1 style='font-size:80px'>ACIONAMENTO LED</h1>";
        if(mac_conhecido){
            html_content += \
            "<p><a href='/LED_ON'>" \
                "<button style='width:200px;font-size:80px'>ON</button>" \
            "</a></p>" \
            "<p><a href='/LED_OFF'>" \
                "<button style='width:200px;font-size:80px'>OFF</button>" \
           "</a></p>";
        }else{
            html_content += \
            "<p style='color:red;font-size:80px'>DISPOSITIVO N&AtildeO AUTORIZADO</p>";
        }
        html_content += \    
        "</body>" \
    "</html>";
    client.println(html_content);
}

void setup() {
  //Configura pino conectado ao LED como saída
    pinMode(2, OUTPUT); 
    //Inicializa serial
    Serial.begin(115200);
    Serial.println();

    //  Serial.println(F("DHTxx test!"));
       dht.begin();

    //WiFiManager
    //Local intialization. Once its business is done, there is no need to keep it around
    WiFiManager wifiManager;
    //reset saved settings
    //wifiManager.resetSettings();
    
    //set custom ip for portal
    //wifiManager.setAPConfig(IPAddress(10,0,1,1), IPAddress(10,0,1,1), IPAddress(255,255,255,0));

    //fetches ssid and pass from eeprom and tries to connect
    //if it does not connect it starts an access point with the specified name
    //here  "AutoConnectAP"
    //and goes into a blocking loop awaiting configuration
    wifiManager.autoConnect("NardoAutoConnectAP");
    //or use this for auto generated name ESP + ChipID
    //wifiManager.autoConnect();
    
    //Configura ESP no modo AP
    Serial.printf("Configurando ponto de acesso '%s'\n", ssid);
    WiFi.softAP(ssid, senha);
    server.begin();
    Serial.println("Configuração conluída");

    
    //if you get here you have connected to the WiFi
    Serial.println("connected...yeey :)");
}

void loop() {
    leDht();    // funçao dht
     //Verifica se existe algum client na rede 
    WiFiClient client = server.available();   
    //Caso positivo, imprime "New Client" no monitor
    if (client){                              
        Serial.println("New Client");  
        //Enquanto client conectado, verifica se existem bytes a serem lidos     
        //e concatena os bytes recebidos na String cabecalho
        String cabecalho;    
        while (client.connected()){     
            if (client.available()){
                cabecalho += (char)client.read();  
                //Se receber nova linha em branco, encerrou leitura dos dados
                if (cabecalho.endsWith("\n\r\n")){
                    Serial.println(cabecalho); //imprime cabeçalhos http recebidos
                    // iniciamos a resposta http com o código OK(200), 
                    // o tipo de conteúdo a ser enviado e tipo de conexão.
                    client.println("HTTP/1.1 200 OK");
                    client.println("Content-Type:text/html");
                    client.println("Connection: close");
                    client.println();
                    // INSIRA AQUI SUA APLICAÇÃO

                    //Armazena na variável 'm' o endereço MAC do client
                    uint8_t *m = clientMac.getAddr(client);
                    Serial.printf("Macaddress:%.2X:%.2X:%.2X:%.2X:%.2X:%.2X\n",
                                            m[0],m[1],m[2],m[3],m[4],m[5]);

                    //determina se o endereço MAC do client é conhecido
                    mac_conhecido = clientMac.isKnown(m);

                    //envia ao client conteúdo HTM L
                    run_html(client);

                    //se client possui MAC conhecido, libera acesso para controlar o LED
                    if(mac_conhecido){
                        Serial.println("mac ok");
                        if(cabecalho.indexOf("GET /LED_ON")>= 0){
                            digitalWrite(2, true);
                        }else if(cabecalho.indexOf("GET /LED_OFF")>= 0){
                            digitalWrite(2, false);
                        }
                    }else{
                        Serial.println("mac não autorizado");  
                    }
                                  
                    break; //sai do while loop
                }
            }
        }
        cabecalho = ""; //ao encerrar conexão, limpa variável cabecalho
        client.flush(); client.stop();
        Serial.println("Client desconectado."); Serial.println();
    }
}

void leDht(){
 
 
    humidity = dht.readHumidity();
    temperature = dht.readTemperature();
    // testa se retorno é valido, caso contrário algo está errado.
    if (isnan(temperature) || isnan(humidity))
    {
      Serial.println("Failed to read from DHT");
    }
      
    char texto[45];
    sprintf(texto, "Temperatura=%.1f*C, umidade=%.1f%%", temperature,humidity );
//     Serial.print(texto);
     
     textoS=String(texto);
   
//    Serial.print("*** Dado enviado: ");
    Serial.println(textoS);
//    Serial.println(" ***");
 
  delay(1000);
   }
