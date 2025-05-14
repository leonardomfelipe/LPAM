/*
 * Construir um sketch e implementar em hardware:
 * Integrar a plataforma ESP32 na IDE Arduino
 * Implementar sketch simples com 2 botões e 2 leds a funcionar da seguinte forma:
 * o Botão 1 pressionado troca o estado do led 1
 * o Botão 2 pressionado faz o led 2 piscar 3 vezes
 * Indicar no LCD 16 x 2
 * o Botão acionado
 * o Led acionado e estado do led (led1) ou número de vezes que vai piscar (led2)
 *
 *  NOME: Leonardo Moreira Felipe
 *  TURMA: 641N1
 *  DATA: 23/03/22
 *  
 */

#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

const int buttonPin = 32;  // the number of the pushbutton pin
const int ledPin =  33;    // the number of the LED pin
const int buttonPin2 = 13;  // the number of the pushbutton pin
const int ledPin2 =  14;    // the number of the LED pin

// variable for storing the pushbutton status 
int buttonState = 0;
int button1State = 0;

//LiquidCrystal_I2C lcd(0x27,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x27 PCF8574T
LiquidCrystal_I2C lcd(0x3F,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x3F PCF8574AT

void setup() {
  //Serial.begin(115200);  
  // initialize the pushbutton pin as an input
  pinMode(buttonPin, INPUT_PULLUP);
  pinMode(buttonPin2, INPUT_PULLUP);
  pinMode(ledPin, OUTPUT);
  pinMode(ledPin2, OUTPUT);
  lcd.init(); // Inicializando o LCD
  lcd.backlight(); // Ligando o BackLight do LCD
  lcd.print(" LED_1: "); // Exibindo no LCD texto
  lcd.setCursor(0,1); // posiciona o cursor no início da 2ª linha
  lcd.print(" LED_2:   OFF  "); // imprime o texto
}

void loop() {

  buttonState = digitalRead(buttonPin);
  Serial.println(buttonState);
  //botaostatus=digitalRead(buttonPin);
  if (buttonState == LOW) {

    digitalWrite(ledPin, HIGH);
    lcd.print(" ON  "); // Exibindo no LCD texto
    lcd.setCursor(9,0); // 
    
  } else {

    digitalWrite(ledPin, LOW);
   // atualizaLcd();
    lcd.print(" OFF "); // Exibindo no LCD texto
    lcd.setCursor(9,0); // 
    }
    
  button1State = digitalRead(buttonPin2);
  Serial.println(button1State);
     if (button1State == LOW) {
      lcd.setCursor(10,1);
      lcd.print("PISCA"); // Exibindo no LCD texto 
      digitalWrite(ledPin2, HIGH);
      delay(500); 
      digitalWrite(ledPin2, LOW);
      delay(500);
      digitalWrite(ledPin2, HIGH);
      delay(500); 
      digitalWrite(ledPin2, LOW);
      delay(500);
      digitalWrite(ledPin2, HIGH);
      delay(500); 
      digitalWrite(ledPin2, LOW);
      delay(500);
     // atualizaLcd();
      lcd.setCursor(9,1);
      lcd.print(" OFF  "); // Exibindo no LCD texto 
    }
  }
