/* 
Autor: Daniel Barbosa
Programa: Interface Homem Máquina 
Descrição: Este código implementa um sistema 
de controle de iluminação com menu interativo 
em um display LCD via I2C.
Ele permite selecionar entre dois LEDs, ligar/desligar cada um e 
ajustar seus níveis de intensidade (PWM) usando cinco botões 
de navegação.
Data: 29/04/2026
Versão: 2.0
*/

// BIBLIOTECAS
#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

// CONSTANTES
const char PIN_BOTAO_UP = 13;
const char PIN_BOTAO_DOWN = 12;
const char PIN_BOTAO_LEFT = 11;
const char PIN_BOTAO_RIGHT = 10;
const char PIN_BOTAO_SELECT = 9;
const char PIN_LED_A = 6;
const char PIN_LED_B = 5;

// VARIÁVEIS GLOBAIS
bool posicaoSeletor = 0;
bool atualizaSaidas = 0;
bool estadoLedA = 0;
bool estadoLedB = 0;
int intensidadeLedA = 10;
int intensidadeLedB = 10;


// PROTÓTIPOS DAS FUNÇÕES
void verificarBotaoUP();
void verificarBotaoDOWN();
void verificarBotaoLEFT();
void verificarBotaoRIGHT();
void verificarBotaoSELECT();
void atualizarDisplay();
void configurarLed();
bool detectarCliques(bool, bool);

// OBJETOS
LiquidCrystal_I2C lcd (0x20, 16, 2);

void setup()
{
  Serial.begin(9600);
  pinMode(PIN_BOTAO_UP,INPUT_PULLUP);
  pinMode(PIN_BOTAO_DOWN,INPUT_PULLUP);
  pinMode(PIN_BOTAO_LEFT,INPUT_PULLUP);
  pinMode(PIN_BOTAO_RIGHT,INPUT_PULLUP);
  pinMode(PIN_BOTAO_SELECT,INPUT_PULLUP);

  pinMode(PIN_LED_A, OUTPUT);
  pinMode(PIN_LED_B, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("> LED A OFF");
  lcd.setCursor(2, 1);
  lcd.print("LED B OFF");
}

void loop()
{ 
  verificarBotaoUP();
  verificarBotaoDOWN();
  verificarBotaoLEFT();
  verificarBotaoRIGHT();
  verificarBotaoSELECT();
}

bool detectarCliques(bool estadoAtualPinBotao, bool estadoAnteriorPinBotao)
{
  if(!estadoAtualPinBotao && estadoAnteriorPinBotao) return true;
  else return false;
}

// BOTAO UP
void verificarBotaoUP()
{
  bool estadoAtualBotaoUP = digitalRead(PIN_BOTAO_UP);
  static bool estadoAnteriorBotaoUP = 1;

  if(detectarCliques(estadoAtualBotaoUP, estadoAnteriorBotaoUP))
  {
    posicaoSeletor = 0;
    atualizaSaidas = 1;
    atualizarDisplay();
  }
  estadoAnteriorBotaoUP = estadoAtualBotaoUP;
}

//BOTAO DOWN
void verificarBotaoDOWN()
{
  bool estadoAtualBotaoDOWN = digitalRead(PIN_BOTAO_DOWN);
  static bool estadoAnteriorBotaoDOWN = 1;
  
  if(detectarCliques(estadoAtualBotaoDOWN, estadoAnteriorBotaoDOWN))
  {
    posicaoSeletor = 1;
    atualizaSaidas = 1;
    atualizarDisplay();
  }
  estadoAnteriorBotaoDOWN = estadoAtualBotaoDOWN;
}

//BOTÃO LEFT
void verificarBotaoLEFT()
{
  bool estadoAtualBotaoLEFT = digitalRead(PIN_BOTAO_LEFT);
  static bool estadoAnteriorBotaoLEFT = 1;
  
  if(detectarCliques(estadoAtualBotaoLEFT, estadoAnteriorBotaoLEFT))
  {
    if(!posicaoSeletor)
    {
      if(estadoLedA)
      {
        intensidadeLedA--;
        if(intensidadeLedA < 0) intensidadeLedA = 0; 
      }
    }
    else
    {
      if(estadoLedB)
      {
        intensidadeLedB--;
        if(intensidadeLedB < 0) intensidadeLedB = 0;
      }
    }
    atualizaSaidas = 1;
    atualizarDisplay();
    configurarLed();
  }
  estadoAnteriorBotaoLEFT = estadoAtualBotaoLEFT;
}

//BOTÃO RIGHT
void verificarBotaoRIGHT()
{
  bool estadoAtualBotaoRIGHT = digitalRead(PIN_BOTAO_RIGHT);
  static bool estadoAnteriorBotaoRIGHT = 1;
  
  if(detectarCliques(estadoAtualBotaoRIGHT, estadoAnteriorBotaoRIGHT))
  {
    if(!posicaoSeletor)
    {
      if(estadoLedA)
      {
        intensidadeLedA++;
        if(intensidadeLedA > 10) intensidadeLedA = 10; 
      }
    }
    else
    {
      if(estadoLedB)
      {
        intensidadeLedB++;
        if(intensidadeLedB > 10) intensidadeLedB = 10;
      }
    }
    atualizaSaidas = 1;
    atualizarDisplay();
    configurarLed();
  }
  estadoAnteriorBotaoRIGHT = estadoAtualBotaoRIGHT;
}

// BOTAO SELECT
void verificarBotaoSELECT()
{
  bool estadoAtualBotaoSELECT = digitalRead(PIN_BOTAO_SELECT);
  static bool estadoAnteriorBotaoSELECT = 1;
  
  if(detectarCliques(estadoAtualBotaoSELECT, estadoAnteriorBotaoSELECT))
  {	
    if(!posicaoSeletor)
    {
      intensidadeLedA = 10;
	  estadoLedA = !estadoLedA;
    }
    else
    {  
      intensidadeLedB = 10;
      estadoLedB = !estadoLedB;
    }
    
    atualizaSaidas = 1;
    atualizarDisplay();
    configurarLed();
  }
  estadoAnteriorBotaoSELECT = estadoAtualBotaoSELECT;
}

//DISPLAY
void atualizarDisplay()
{
  lcd.setCursor(0, 0);
  lcd.print(posicaoSeletor ? " " : ">");

  lcd.setCursor(0,1);
  lcd.print(posicaoSeletor ? ">" : " ");
   
  lcd.setCursor(8, 0); 
  if(estadoLedA)
  {
    lcd.print(intensidadeLedA * 10); 
    lcd.print("  ");
  }
  else
    lcd.print("OFF"); 

  	lcd.setCursor(8, 1); 
  	if(estadoLedB)
  	{
      lcd.print(intensidadeLedB * 10); 
      lcd.print("  ");
  	}
  	else
  	lcd.print("OFF");
}

// LED'S
void configurarLed()
{ 
  if(estadoLedA) analogWrite(PIN_LED_A, intensidadeLedA * 255 / 10);
  else digitalWrite(PIN_LED_A, LOW);
  
  if(estadoLedB) analogWrite(PIN_LED_B, intensidadeLedB * 255 / 10);
  else digitalWrite(PIN_LED_B, LOW);
}