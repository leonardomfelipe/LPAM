/*
 * 1. Testar o código presente no site Arduino.cc - attachInterrupt() e entender o funcionamento. Modificar o código para outra aplicação.
 * 2. Construir um sketch e implementar em hardware:
 *    Arduino UNO com módulo LCD 16 x 2.
 *    Potenciômetro em uma entrada A/D.
 *    Saída PWM com sinal PWM acionando um motor DC.
 *    Apresentar no LCD 2 x 16:
 *      o Primeira linha: o dutyCycle em % (0 a 100%) %, proporcional a posição do potenciômetro na entrada A/D.
 *      o Segunda linha: o dutyCycle em % (0 a 100%) %, proporcional ao valor presente na saída PWM.
 *    Incluir um Botão de interrupção que permite ligar ou desligar o sistema
 *
 * Nome: LEONARDO MOREIRA FELIPE
 * TURMA: 641N1
 * DATA: 17/03/2022
 * 
 */
 
// inclusão de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// apelidos
#define pinoAnalogico A0
#define leituras 10
#define pinMotor 11
// variáveis globais
int valorAnalogico;
int valorPerc;
int valorPwm;
const byte interruptPin = 2;
volatile byte state = HIGH;

LiquidCrystal_I2C lcd(0x3F,16,2);   // Criando um LCD de 16x2 no endereço I2C 0x27

void setup() {                      // put your setup code here, to run once:
  pinMode(pinMotor, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink, RISING); 
  lcd.init();                       // Inicializando o LCD
  lcd.backlight();                  // Ligando o BackLight do LCD
  lcd.print("SISTEMA:");          // Exibindo no LCD texto
  lcd.setCursor(0,1);               // posiciona o cursor no início da 2ª linha
  lcd.print("V=");                  // imprime o texto
  lcd.setCursor (11,1);
  lcd.print(valorPerc);
}

void loop() {                      // função loop com código principal
  if(state==LOW) {
  leituraAnalogica();
  delay(1);
  mapValperc();
  mapValpwm();  
  acionaPwm();
  atualizaLcd();
   
}
  else {
  analogWrite(pinMotor, 0);
 lcd.setCursor (8,0);                // escreve no LCD Sistema OFF
 lcd.print(" OFF   ");
}
}
void leituraAnalogica (){
  valorAnalogico=0;                  // zera a variável
  for(int i=0; i<leituras; i++){     // laço com repetição de "leituras"
  valorAnalogico = valorAnalogico + analogRead(pinoAnalogico);          // Acumula a nova leitura do Conv.A/D
  delay(1);                          // atraso para estabilizar o conversor
  }
  valorAnalogico = valorAnalogico/leituras;                             // faz a média de leituras
}

 void mapValperc(){                   // funcao mapear o valor percentual de 0% a 100%
 valorPerc=map (valorAnalogico, 0, 1023, 0, 100);
}

void mapValpwm (){                   // funcao de mapear o valor 0 a 255 do PWM
  valorPwm=map(valorAnalogico, 0, 1023, 0, 255);
}

void acionaPwm() {                   // funcao acionamento do led pelo valor do PWM
  analogWrite (pinMotor, valorPwm);
}

void atualizaLcd (){             // funcao que atualiza o LCD
  lcd.setCursor (8,0);
  lcd.print(" ON    ");          // Exibindo no LCD texto
  lcd.setCursor (3,1);
  lcd.print(valorPwm);
  lcd.print(" RPM ");
  lcd.setCursor (11,1);
  lcd.print(valorPerc);
  lcd.print(" % ");
  
}
void blink() {
              state=!state;
              void atualizaLcd();
}
