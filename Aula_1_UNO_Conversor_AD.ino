/* 
 * Conversor A/D 
 * Leonardo Moreia Felipe - 10/03/2022
 */

// inclusão de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>

// apelidos
#define pinoAnalogico A0
#define leituras 10

int valorAnalogico;
int valorMapeado;

LiquidCrystal_I2C lcd(0x3F,16,2);  // criando um LCD de 16x2 no endereço I2C 0x3F

//função setup executa 1 vez no início
void setup(){
  lcd.init(); // Inicializando o LCD
  lcd.backlight(); // ligando o backLight do LCD
  lcd.print("Coversor A/D"); // escreve no LCD
  lcd.setCursor(0,1); // posicisão do cursor no LCD(coluna 0, linha 1)
  lcd.print("V = "); // imprime o texto
}

// função loop com código principal
void loop(){
  leituraAnalogica();
  mapeamento();
  atualizaLcd();
  }

void leituraAnalogica (){
  valorAnalogico=0; // zera a variável
  for(int i=0; i<leituras; i++){ // laço com repetição de "leituras"
  valorAnalogico = valorAnalogico + analogRead(pinoAnalogico); // acumula a nova leitura do Conversao A/D
  delay(1); // atraso para estabilizar o conversor
  }
  valorAnalogico = valorAnalogico/leituras; // faz a média de leituras
}

void mapeamento() {
  valorAnalogico=map(valorAnalogico, 0, 1023, 0, 5000); 
 
}

void atualizaLcd (void){
  lcd.setCursor (4,1); // 
  lcd.print(valorAnalogico);
  lcd.print(" mV ");
}
