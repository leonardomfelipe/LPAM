/* 
 *  
 *  Seguir a orientação do documento Aula 13:
 * 
 * Atividade para desenvolver:
 * ·     Utilizar o exemplo do site CircuitDigest- How to Use Classic Serial Bluetooth in ESP32
 * ·     Compilar e carregar o exemplo no ESP32
 *·      Instalar o APP Google Play - Bluetooth Terminal
 *·      Conectar o APP ao ESP32
·*       Controlar o LED_BUILTIN (Wi-Fi) ou um led conectado ao pino 2
 *
 * Nomes: Leonardo M. Felipe
 * Turma: 641N1
 *
 */

#include <"BluetoothSerial.h"> //Header File for Serial Bluetooth, will be added by default into Arduino

BluetoothSerial ESP_BT; //Object for Bluetooth

int incoming;
//int LED_BUILTIN = 2;

void setup() {
  Serial.begin(9600); //Start Serial monitor in 9600
  ESP_BT.begin("Leo_ESP32_LED_Control"); //Name of your Bluetooth Signal
  Serial.println("Bluetooth Device is Ready to Pair");

  pinMode (LED_BUILTIN, OUTPUT);//Specify that LED pin is output
}

void loop() {
  
  if (ESP_BT.available()) //Check if we receive anything from Bluetooth
  {
    incoming = ESP_BT.read(); //Read what we recevive 
    Serial.print("Received:"); Serial.println(incoming);

    if (incoming == 49)
        {
        digitalWrite(LED_BUILTIN, HIGH);
        ESP_BT.println("LED turned ON");
        }
        
    if (incoming == 48)
        {
        digitalWrite(LED_BUILTIN, LOW);
        ESP_BT.println("LED turned OFF");
        }     
  }
  delay(20);
}
