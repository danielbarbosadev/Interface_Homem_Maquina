#include <Arduino.h>
#include <LiquidCrystal_I2C.h>

LiquidCrystal_I2C lcd(0x20, 16, 2);

//*******CONSTANTES**********
const char pinBotaoUP = 13;
const char pinBotaoDOWN = 12;
const char pinBotaoLEFT = 11;
const char pinBotaoRIGHT = 10;
const char pinBotaoSELECT = 9;

const char pinLedA = 6;
const char pinLedB = 5;

void setup()
{
  pinMode(pinBotaoUP, INPUT_PULLUP);
  pinMode(pinBotaoDOWN, INPUT_PULLUP);
  pinMode(pinBotaoLEFT, INPUT_PULLUP);
  pinMode(pinBotaoRIGHT, INPUT_PULLUP);
  pinMode(pinBotaoSELECT, INPUT_PULLUP);

  pinMode(pinLedA, OUTPUT);
  pinMode(pinLedB, OUTPUT);

  lcd.init();
  lcd.backlight();
  lcd.print("> LED A OFF");
  lcd.setCursor(2, 1);
  lcd.print("LED B OFF");
}

void loop()
{

  //******* LEITURA DOS BOTOES ********
  bool estadoAtualBotaoUP = digitalRead(pinBotaoUP);
  bool estadoAtualBotaoDOWN = digitalRead(pinBotaoDOWN);
  bool estadoAtualBotaoLEFT = digitalRead(pinBotaoLEFT);
  bool estadoAtualBotaoRIGHT = digitalRead(pinBotaoRIGHT);
  bool estadoAtualBotaoSELECT = digitalRead(pinBotaoSELECT);

  static bool estadoAnteriorBotaoUP = true;
  static bool estadoAnteriorBotaoDOWN = true;
  static bool estadoAnteriorBotaoLEFT = true;
  static bool estadoAnteriorBotaoRIGHT = true;
  static bool estadoAnteriorBotaoSELECT = true;

  static bool posicaoSeletor = 0;

  static bool estadoLedA = 0;
  static bool estadoLedB = 0;
  static int intensidadeLedA = 10;
  static int intensidadeLedB = 10;

  static bool atualizaSaidas = 0;

  //******* CONTROLE DOS BOTOES **********

  // BOTAO UP
  if (!estadoAtualBotaoUP && estadoAnteriorBotaoUP)
  {
    posicaoSeletor = 0;
    atualizaSaidas = 1;
  }
  estadoAnteriorBotaoUP = estadoAtualBotaoUP;

  // BOTAO DOWN
  if (!estadoAtualBotaoDOWN && estadoAnteriorBotaoDOWN)
  {
    posicaoSeletor = 1;
    atualizaSaidas = 1;
  }
  estadoAnteriorBotaoDOWN = estadoAtualBotaoDOWN;

  // BOTAO LEFT
  if (!estadoAtualBotaoLEFT && estadoAnteriorBotaoLEFT)
  {
    if (!posicaoSeletor)
    {
      if (estadoLedA)
      {
        intensidadeLedA--;
        if (intensidadeLedA < 0)
          intensidadeLedA = 0;
      }
    }
    else
    {
      if (estadoLedB)
      {
        intensidadeLedB--;
        if (intensidadeLedB < 0)
          intensidadeLedB = 0;
      }
    }
    atualizaSaidas = 1;
  }
  estadoAnteriorBotaoLEFT = estadoAtualBotaoLEFT;

  // BOTAO RIGHT

  if (!estadoAtualBotaoRIGHT && estadoAnteriorBotaoRIGHT)
  {

    if (!posicaoSeletor)
    {
      if (estadoLedA)
      {
        intensidadeLedA++;
        if (intensidadeLedA > 10)
          intensidadeLedA = 10;
      }
    }
    else
    {
      if (estadoLedB)
      {
        intensidadeLedB++;
        if (intensidadeLedB > 10)
          intensidadeLedB = 10;
      }
    }

    atualizaSaidas = 1;
  }
  estadoAnteriorBotaoRIGHT = estadoAtualBotaoRIGHT;

  // BOTAO SELECT
  if (!estadoAtualBotaoSELECT && estadoAnteriorBotaoSELECT)
  {

    if (posicaoSeletor == 0)
      estadoLedA = !estadoLedA;
    else
      estadoLedB = !estadoLedB;
    atualizaSaidas = 1;
  }
  estadoAnteriorBotaoSELECT = estadoAtualBotaoSELECT;

  if (atualizaSaidas)
  {
    //********DISPLAY*********
    // POSICAO DAS SETAS
    lcd.setCursor(0, 0);
    lcd.print(posicaoSeletor ? " " : ">");

    lcd.setCursor(0, 1);
    lcd.print(posicaoSeletor ? ">" : " ");

    // ESCRITA DO ON e OFF
    lcd.setCursor(8, 0);
    if (estadoLedA)
    {
      lcd.print(intensidadeLedA * 10);
      lcd.print("  ");
    }
    else
      lcd.print("OFF");

    lcd.setCursor(8, 1);
    if (estadoLedB)
    {
      lcd.print(intensidadeLedB * 10);
      lcd.print("  ");
    }

    else
      lcd.print("OFF");

    // ESTADOS DOS LEDS
    if (estadoLedA)
      analogWrite(pinLedA, intensidadeLedA * 255 / 10);
    else
      digitalWrite(pinLedA, LOW);

    if (estadoLedB)
      analogWrite(pinLedB, intensidadeLedB * 255 / 10);
    else
      digitalWrite(pinLedB, LOW);

    atualizaSaidas = 0;
  }
}