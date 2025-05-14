/*
 * 
 * ESP32 com módulo display (LCD)
 * Potenciômetro em uma entrada A/D
 * Botão por Interrupção Externa para ligar ou desligar o sistema
 * Apresentar no display o dutyCycle em % (0 a 100%)
 * o Colocar um led em um dos pinos de PWM do Arduino Uno
 * o Substituir o led por um motor DC para controle de velocidade
 *  
 *  NOME: Leonardo Moreira Felipe
 *  TURMA: 641N1
 *  DATA: 07/04/22
 * 
 */

// inclusão de bibliotecas
#include <Wire.h>
#include <LiquidCrystal_I2C.h>

//LiquidCrystal_I2C lcd(0x27, 16, 2); // Criando um LCD de 16x2 no endereço I2C 0x27 PCF8574T
LiquidCrystal_I2C lcd(0x3F,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x3F PCF8574AT
//

// Apelidos
#define pino_analogico 34 // GPIO 34 ADC1-CH6
#define resolucaoAd 12 // resolução do A/D é 12 bits
#define pinoPwm 32 // GPIO32
#define canalPwm 0 // canal 0 do PWM ESP32
#define frequenciaPwm 1000 // frequencia PWM em 1000Hz
#define resolucaoPwm 12 // resolucão do PWM é de 12 bits
#define leiturasAd 10
 
// como as duas resoluções (A/D e do PWm) são iguais o valPot pode ser aplicado direto no dutycycle
// e não é ncessário conversão

//variavel que vai receber o valor lido do potenciometro

int valPot = 0;
int valorMapeado = 0;
const byte interruptPin = 5;
volatile byte state = HIGH;

void setup() {
  //conversor A/D
  analogReadResolution ( resolucaoAd ); // resolução de 12 bits
  //analogSetAttenuation (ADC_0db);  // Para todos os pinos
  analogSetPinAttenuation (pino_analogico, ADC_11db); // Atenuação de 11db no pino sensorPino

  // valPot = analogRead(34);
  // LCD
  pinMode(pinoPwm, OUTPUT);
  pinMode(interruptPin, INPUT_PULLUP);
  attachInterrupt(digitalPinToInterrupt(interruptPin), blink1, RISING); 
  lcd.init(); // Inicializando o LCD
  lcd.backlight(); // Ligando o BackLight do LCD
  //lcd.begin(16, 2);           // Incializa o LCD com o número de Colunas(16) e Linhas(2):
  lcd.setCursor(0, 0);
  lcd.print("MOTOR:ON");
  lcd.setCursor(0, 1);
  lcd.print("Percent=");

  // PMW
  //ledcSetup (0,1000,12);
  //ledcAttachPin(32,0);
  ledcSetup(canalPwm, frequenciaPwm, resolucaoPwm);
  ledcAttachPin(pinoPwm, canalPwm);
}

void loop() {
  if(state == HIGH){
  leituraAnalogica();
  atuaPwm();
  mapeamento();
  acionaPwm();
  atualizaLcd();
  delay(100); //intervalo de 0.1s
  }
  else{
    ledcWrite (canalPwm, 0);
    lcd.setCursor(6 , 0);
    lcd.print("OFF ");
  }
}

void leituraAnalogica() {
  valPot = 0;
  for (int i = 0; i < leiturasAd; i++){ // laço de repetição para fazer 10 leituras
    valPot = valPot + analogRead(pino_analogico);
    delay(1);
  }
  valPot = valPot / leiturasAd; // calcula a média
}

void atuaPwm (){
  ledcWrite(canalPwm,valPot);
}

void mapeamento (){
  valorMapeado = map(valPot, 0, 4095, 0, 100);
}

void acionaPwm() {                   // funcao acionamento do led pelo valor do PWM
  ledcWrite (canalPwm, valPot);
}

void atualizaLcd(){
  lcd.setCursor (6,0);
  lcd.print("ON ");
  lcd.setCursor(8,1);
  lcd.print(valorMapeado);
  lcd.print("%  ");
}

void blink1() {
              state=!state;
              void atualizaLcd();
}
