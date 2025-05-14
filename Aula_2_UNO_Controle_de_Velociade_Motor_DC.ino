/* 
 * Construir um sketch e implementar em hardware:
 * Arduino UNO com módulo LCD
 * Potenciômetro em uma entrada A/D
 * Apresentar no LCD o dutyCycle em % (0 a 100%)
 * o Colocar um led em um dos pinos de PWM do Arduino Uno
 * o Substituir o led por um motor DC para controle de velocidade
 *
 * Nome: LEONARDO MOREIRA FELIPE
 * TURMA: 641N1
 * DATA: 10/03/2022
 */

// inclusão de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// apelidos
#define pinoAnalogico A0
#define leituras 10
#define pinMotor 11

int valorAnalogico;
int valorPerc;
int valorPwm;

LiquidCrystal_I2C lcd(0x3F,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x27

//função setup executa 1 vez no início
void setup(){
  lcd.init(); // Inicializando o LCD
  lcd.backlight(); // Ligando o BackLight do LCD
  lcd.print("Coversor A/D"); // Exibindo no LCD texto
  lcd.setCursor(0,1); // posiciona o cluros no início da 2ª linha
  lcd.print("V="); // imprime o texto
  lcd.setCursor (11,1);
  lcd.print(valorPerc);
  pinMode(pinMotor, OUTPUT);
}

// função loop com código principal
void loop(){
  leituraAnalogica();
  mapValperc();
  mapValpwm();  
  atualizaLcd();
  acionaPwm();
  }

void leituraAnalogica (){
  valorAnalogico=0; // zera a variável
  for(int i=0; i<leituras; i++){ // laço com repetição de "leituras"
  valorAnalogico = valorAnalogico + analogRead(pinoAnalogico); // Acumula a nova leitura do Conv.A/D
  delay(1); // atraso para estabilizar o conversor
  }
  valorAnalogico = valorAnalogico/leituras; // faz a média de leituras
}

void mapValperc(){ // funcao mapear o valor percentual de 0% a 100%
  valorPerc=map (valorAnalogico, 0, 1023, 0, 100);
}

void mapValpwm (){ // funcao de mapear o valor 0 a 255 do PWM
  valorPwm=map(valorAnalogico, 0, 1023, 0, 255);
}

void acionaPwm() { // funcao acionamento do led pelo valor do PWM
  analogWrite (pinMotor, valorPwm);
}

void atualizaLcd (void){ // funcao que atualiza o LCD
  lcd.setCursor (3,1);
  lcd.print(valorPwm);
  lcd.print(" RPM ");
  lcd.setCursor (11,1);
  lcd.print(valorPerc);
  lcd.print(" % ");
}
