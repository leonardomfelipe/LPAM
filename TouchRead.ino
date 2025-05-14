int pinoVermelho       = 16; //pino que ligamos o LED vermelho
int pinoVerde          = 17; //pino que ligamos o LED verde
int pinoTouchOn        = 4; //pino com sensor touch  (pode-se usar a constante nativa T0)
int pinoTouchBlink     = 13; //pino com sensor touch (pode-se usar a constante nativa T4)
int capacitanciaMaxima = 40; //valor que nos da a certeza de toque (ache ese valor através da calibragem)

void setup()
{
  Serial.begin(115200);
  delay(1000);
  pinMode(pinoVermelho, OUTPUT);
  pinMode(pinoVerde, OUTPUT);
}

void loop()
{
  Serial.println(touchRead(pinoTouchOn));
  Serial.println(touchRead(pinoTouchBlink));
  int mediaT0 = 0;
  int mediaT4 = 0;
  //faz 100 leituras de cada sensor touch e calcula a média do valor lido
  for(int i=0; i< 100; i++)
  {
    mediaT0 += touchRead(pinoTouchOn);
    mediaT4 += touchRead(pinoTouchBlink);
  }
  
  mediaT0 = mediaT0 / 100;
  mediaT4 = mediaT4 / 100;

  //verifica se o valor médio lido no pinoTouchOn é menor que a capacitância máxima definida
  //se verdadeiro, isso caracteriza um toque
  // os LEDs vemelho e verde ficarão acesos
  if(mediaT0 < capacitanciaMaxima)
  {
    digitalWrite(pinoVermelho, HIGH);
    digitalWrite(pinoVerde, HIGH);
  }
  //verifica se o valor médio lido no pinoTouchBlink é menor que a capacitância máxima definida
  //se verdadeiro, isso caracteriza um toque
  // os LEDs vemelho e verde ficarão piscando com um intervalo de 500 ms
  else if(mediaT4 < capacitanciaMaxima)
  {
    digitalWrite(pinoVermelho, !digitalRead(pinoVermelho)); //inverte o estado atual do LED (HIGH/LOW)
    digitalWrite(pinoVerde, !digitalRead(pinoVerde)); //inverte o estado atual do LED (HIGH/LOW)
    delay(500);                   
  }
  //se nenhum dos pinos touch estão sendo tocados, os LEDS ficam apagados
  else{
    digitalWrite(pinoVermelho, LOW);
    digitalWrite(pinoVerde, LOW);
  } 
  delay(10);
}
