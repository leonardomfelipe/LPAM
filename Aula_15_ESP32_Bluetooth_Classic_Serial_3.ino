/*
 * · Executar em hardware o exemplo do site Rundom Nerd Toturials - ESP32 with DHT11/DHT22 Temperature and Humidity Sensor using Arduino IDE
 *· Utilizar o base o exemplo do site CircuitDigest - How to Use Classic Serial Bluetooth in ESP32  (
 *
 * Aula 13 - ESP32 Bluetooth - Classic Serial 1 - Envio Serial  )
 *· Hardware montado:
 *  o ESP32
 *  o Display (LCD ou OLED)
 *  o Sensor de umidade DHT
 *· Mostrar no display os valores de Temperatura e Umidade
 *· Através do terminal do celular (Google Play - Bluetooth Terminal, por exemplo) ligado ao Bluetooth do ESP32 ter a possibilidade de ler a temperatura e umidade
 *
 * Nomr: Leonardo M. Felipe
 * Turma: 641N1
 *
*/

#include "DHT.h"

#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth


#define SCREEN_WIDTH 128 // largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // altura da tela OLED, em pixels
#define DHTPIN 4        
#define DHTTYPE DHT22
#define pino_analogico 4 // apelido para o pino A0
//canal usado adc1 ch6
// Apelidos para associação entre os pinos do LCD e do Arduino

int incoming;


// Declaração para um monitor SSD1306 conectado ao I2C (pinos SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

DHT dht(DHTPIN, DHTTYPE);

void setup() {


    ESP_BT.begin("ESP32_LED_Controle12"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  Serial.begin(115200); //Start Serial monitor in 9600


 Serial.println(F("DHTxx test!"));
   dht.begin();
   
    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço 0x3D para 128x64
    Serial.println(F("Falha na alocação SSD1306"));
    for (;;);
  
  
   analogReadResolution ( 12 ); // resolução de 12 bits
  //analogSetAttenuation (ADC_0db);  // Para todos os pinos
  analogSetPinAttenuation (pino_analogico, ADC_11db); // Atenuação de 6db no pino sensorPino
  

   
    
  }
  delay(2000);
  display.clearDisplay();

}

void loop(){

if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);
    // Wait a few seconds between measurements.
  delay(2000);

  // Reading temperature or humidity takes about 250 milliseconds!
  // Sensor readings may also be up to 2 seconds 'old' (its a very slow sensor)
  float u = dht.readHumidity();
  // Read temperature as Celsius (the default)
  float c = dht.readTemperature();
  // Read temperature as Fahrenheit (isFahrenheit = true)
  float f = dht.readTemperature(true);

  // Check if any reads failed and exit early (to try again).
  if (isnan(u) || isnan(c) || isnan(f)) {
    Serial.println(F("Failed to read from DHT sensor!"));
    return;
  }

  // Compute heat index in Fahrenheit (the default)
  float hif = dht.computeHeatIndex(f, u);
  // Compute heat index in Celsius (isFahreheit = false)
  float hic = dht.computeHeatIndex(c, u, false);
  Serial.println (incoming);

  display.setTextSize(1);
  display.setTextColor(WHITE);
  
  display.clearDisplay();
 if (incoming=='c') {
  ESP_BT.print("Temperatura: ");
  ESP_BT.print(c);
  ESP_BT.println("°C ");
  display.setCursor(0, 20);
  display.print("Temp: ");
  display.print(c);
  display.print(" °C");
  delay(1000);
}
else if (incoming=='f'){
   ESP_BT.print("Temperatura: ");
   ESP_BT.print(hif);
  ESP_BT.println("°F");
display.setCursor(0, 40);
  display.print("Temp: ");
  display.print(f);
display.println("°F");
delay(1000);

}
 else if (incoming=='u'){
  ESP_BT.print("Umidade: ");
  ESP_BT.print(u);
  ESP_BT.println("%");
    display.print("Umid: ");
  display.print(u);
  display.setCursor(0, 60);
  display.println("°F");
  delay(1000);
 }
else if (incoming!=13 && incoming!=10 ){
  ESP_BT.print("HELP: Utilize 'C' / 'U' / 'F'  ");
  display.setCursor(0, 50);
   display.print("HELP: Utilize C/U/F");
  delay(2000);

  
    }
    display.display();
  }
}
