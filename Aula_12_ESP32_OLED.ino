/**************************************************************************
   0.0.0 - Exemplo Monochrome OLEDs based on SSD1306 drivers Adafruit 128x64 pixel display using I2C
   0.1.0 - Controle de texto

   Luiz Oscar Ruschel Pilger
   10/08/2021
 **************************************************************************/
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#define SCREEN_WIDTH 128 // largura da tela OLED, em pixels
#define SCREEN_HEIGHT 64 // altura da tela OLED, em pixels

int buttonState = 0;
const int pinoBt = 5; // pino do botao
const int pinoLed = 4; // pino do led

// Declaração para um monitor SSD1306 conectado ao I2C (pinos SDA, SCL)
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);

void setup() {
  Serial.begin(115200);
  pinMode(pinoBt, INPUT_PULLUP);
  pinMode(pinoLed, OUTPUT); 
  display.setTextColor(WHITE);
  
  if (!display.begin(SSD1306_SWITCHCAPVCC, 0x3C)) { // Endereço 0x3D para 128x64
    Serial.println(F("Falha na alocação SSD1306"));
    for (;;);
  }
  display.setTextSize(2);
  display.clearDisplay();
  display.display();
  //display.setTextSize(1);
 // display.setTextColor(WHITE);
 // display.setCursor(0, 10);
  
// Display static text
//  display.print("LED Status:");
  display.display();
 }

void loop() {
  display.clearDisplay();
  display.setCursor(0, 10);
//  Display static text
  display.println("LED_STATUS:");
  display.setCursor(11, 30);
buttonState = digitalRead(pinoBt);
  Serial.println(buttonState);
  //botaostatus=digitalRead(buttonPin);
  if (buttonState == LOW) {
    
    digitalWrite(pinoLed, HIGH);
    display.print(" ON "); // Exibindo no LCD texto
    
  } else {
   // display.clearDisplay();
    digitalWrite(pinoLed, LOW);
        display.print(" OFF"); // exibe texto no OLED
    }  
  display.display();
}
