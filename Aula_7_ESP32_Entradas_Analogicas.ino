/* 
 * Construir um sketch e implementar em hardware:
 * ESP32 com módulo LCD
 * Potenciômetro em uma entrada A/D
 * Colocar um voltímetro real na entrada A/D
 * Indicar no LCD a voltagem em mV, ou V com 3 casas decimais após a vírgula
 * Comparar, tensão indicada no voltímetro com o valor lido no LCD
 *
 *  
 * NOME: Leonardo Moreia Felipe 
 * TURMA: 641N1
 * DATA: 24/03/22
 * 
 */

// inclusão de bibliotecas
#include <Wire.h> 
#include <LiquidCrystal_I2C.h>
// apelidos
#define pino_analogico 34 // apelido para o pino analogico
#define potPin 34
//variavel que vai receber o valor lido do potenciometro
int valPot = 0;
// cria uma variável para guardar o valor lido
int valor_convertido;
 
LiquidCrystal_I2C lcd(0x3F,16,2);  // Criando um LCD de 16x2 no endereço I2C 0x3F PCF8574AT

void setup() {
   analogReadResolution ( 12 ); // resolução de 12 bits
  //analogSetAttenuation (ADC_0db);  // Para todos os pinos
  analogSetPinAttenuation (pino_analogico, ADC_11db); // Atenuação de 6db no pino sensorPino
  
   valPot = analogRead(34);
    lcd.init(); // Inicializando o LCD
  lcd.backlight(); // Ligando o BackLight do LCD
  lcd.begin(16, 2);           // Incializa o LCD com o número de Colunas(16) e Linhas(2):
  lcd.setCursor(7,1);         // posiciona o cursor na coluan 0 e linha 1
  lcd.print(" mV ");       // imprime texto
}

void loop(){

    valPot = 0;
    for(int i = 0; i - 10; i++);{
    valPot = valPot + analogRead(potPin);
    delay(1);
    
      }
      
    valPot = valPot/10;
   
    int valorMapeado = map(valPot, 0, 4095, 0, 33000);

    
    lcd.setCursor(0,0);
    lcd.print("Voltimetro");
    lcd.setCursor(1,1);
    lcd.print(valorMapeado);
    lcd.print("   ");
    delay(100); //intervalo de 0.05s
}
