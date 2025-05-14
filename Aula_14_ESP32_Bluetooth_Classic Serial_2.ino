/*
 * Seguir a orientação do documento Aula 14:
 *
 * Atividade para desenvolver:
 * ·       Utilizar o base o exemplo do site CircuitDigest - How to Use Classic Serial Bluetooth in ESP32  (Aula 14 - ESP32 Bluetooth - Classic Serial 1 - Envio Serial)
 * ·       Realizar a leitura de um potenciômetro no ESP32 
 * ·       Apresentar a leitura do potenciômetro em % (0% a 100%) no display (LCD ou OLED)
 * ·       Utilizar o APP Google Play - Bluetooth Terminal
 * ·       Mostrar a leitura do potenciômetro em % (0% a 100%) por um comando de caractere
 * 
 * Nome: Leonardo M. Felipe
 * Turmna:641N1
 * 
 */


#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include "BluetoothSerial.h" //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

#define SCREEN_WIDTH 128 // largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // altura da tela OLED, em pixels
#define potPin 34

#define pino_analogico 34 // apelido para o pino A0
//canal usado adc1 ch6
// Apelidos para associação entre os pinos do LCD e do Arduino

//variavel que vai receber o valor lido do potenciometro
int valPot = 0;
int valor_convertido; // cria uma variável para guardar o valor lido
int incoming;
int valorMapeado;

// Declaração para um monitor SSD1306 conectado ao I2C (pinos SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {


    ESP_BT.begin("ESP32_LED_Controle12"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");
  Serial.begin(115200); //Start Serial monitor in 9600

    if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço 0x3D para 128x64
    Serial.println(F("Falha na alocação SSD1306"));
    for (;;);
  
  
   analogReadResolution ( 12 ); // resolução de 12 bits
  //analogSetAttenuation (ADC_0db);  // Para todos os pinos
  analogSetPinAttenuation (pino_analogico, ADC_11db); // Atenuação de 6db no pino sensorPino
  
   valPot = analogRead(34);
   
    
  }
  delay(2000);
  display.clearDisplay();

  display.setTextSize(1);
  display.setTextColor(WHITE);
  display.setCursor(0, 40);
  // Display static text
  display.println("mv");
}

void loop(){
  fvalorMapeado();
  
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);

    if (incoming == 49)
{
  ESP_BT.print("valor=");
  ESP_BT.println(valorMapeado);
  ESP_BT.println("%");
}
delay(20);
 
  }
}
void fvalorMapeado(){   
    valPot = 0;
    for(int i = 0; i - 10; i++);{
    valPot = valPot + analogRead(potPin);
    delay(1);
    
      }
      
    valPot = valPot/10;
   
     valorMapeado = map(valPot, 0, 4099, 0, 1010);
display.clearDisplay();
display.setCursor(20, 10);
display.println("Potenciometro");
display.setCursor(0, 40);
display.println("Porcent:");
display.setCursor(60, 40);
display.println(valorMapeado);
display.setCursor(80, 40);
display.println("%");

delay (100);

  display.display();
}    
