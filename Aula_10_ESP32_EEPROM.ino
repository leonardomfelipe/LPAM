/* 
 * Construir um sketch e implementar em hardware:
 * Arduino UNO com módulo LCD 16 x 2.
 * Potenciômetro em uma entrada A/D.
 * Saída PWM com sinal PWM acionando um motor DC.
 * Botão Liga/Desliga o sistema por interrupção
 * Botão 1 “GRAVA” que ao ser pressionado grava na memória EEPROM o valor PWM proporcional a posição do potenciômetro na entrada A/D.
 * Botão 2 “LÊ” que ao ser pressionado lê a memória EEPROM o valor PWM guardado e ativa a saída PWM com o valor lido. 
 * Apresentar no LCD 2 x 16:
 *  o Primeira linha: o dutyCycle em % (0 a 100%) %, proporcional a posição do potenciômetro na entrada A/D.
 *  o Segunda linha: o dutyCycle em % (0 a 100%) %, proporcional ao valor presente na saída PWM.
 * 
 * NOME: LEONARDO MOREIRA FELIPE  
 * Data: 17/03/2022
 * Turma: 641N1
 * 
 */

// inclusão de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
#include <EEPROM.h>

// apelidos
#define pinoAnalogico 34
#define pinoPwm 32 // GPIO32
#define leituras 10
#define pinoBtGrava 4 
#define pinoBtLe 15
#define endereco 10

volatile byte state = HIGH;
// variáveis globais
int valorAnalogico;
int valorPwm1;  // valor pwm 1 do potenciômetro
int valorPwm2;  // valor lido da EEPROM
int Perc1;      // percentual do valorPwm1 
int Perc2;      // percentual do valorPwm2 

LiquidCrystal_I2C lcd(0x3F,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x27 PCF8574T

//função setup executa 1 vez no início
void setup(){
  lcd.init(); // Inicializando o LCD
  lcd.backlight(); // Ligando o BackLight do LCD
  pinMode(pinoBtGrava,INPUT_PULLUP);
  pinMode(pinoBtLe,INPUT_PULLUP);
}

// função loop com código principal
void loop(){
  if (state == HIGH) {  
    leituraAnalogica();

    atualizaLcd();
    leBtGrava();
    leBtLe();
    delay(1);
  }
  else {
    ledcWrite(endereco, 0);
    
  }
}

void leituraAnalogica (void){
  valorAnalogico=0; // zera a variável
  for(int i=0; i<leituras; i++){ // laço com repetição de "leituras"
    valorAnalogico = valorAnalogico + analogRead(pinoAnalogico); // Acumula a nova leitura do Conv.A/D
    delay(1); // atraso para estabilizar o conversor
  }
  valorAnalogico = valorAnalogico/leituras; // faz a média de leituras
  valorPwm1 = map(valorAnalogico,0,1023,0,255); // calcula o valor PWM correspondente ao valor do POT
}
void atualizaLcd (void){
  lcd.setCursor(0,0); // posiciona o cursor
  lcd.print("Valor PWM = "); // Exibindo no LCD texto
  lcd.print(valorPwm1); // imprime o valor pwm no poteciômetro
  lcd.print("  "); // imprime 3 espaços para "apagar" numeros de 3 dígitos
}

void leBtGrava(){
  if (digitalRead(pinoBtGrava)==LOW){
    while (digitalRead(pinoBtGrava)==LOW);
    EEPROM.write(endereco, valorPwm1);
    lcd.setCursor(0,1);
    lcd.print("Gravando ");
    lcd.print(valorPwm1);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("            ");
  }
}

void leBtLe(){
  if (digitalRead(pinoBtLe)==LOW){
    while (digitalRead(pinoBtLe)==LOW);
    valorPwm2=EEPROM.read(endereco);
    Perc2 = map(valorAnalogico, 0, 255, 0, 100);
    ledcWrite(10, valorPwm2);
    lcd.setCursor(0,1);
    lcd.print("EEPROM =");   
    lcd.print(valorPwm2);
    delay(1000);
    lcd.setCursor(0,1);
    lcd.print("           ");
    valorAnalogico = valorAnalogico/leituras; // faz a média de leituras
    delay(1);
  }
}
