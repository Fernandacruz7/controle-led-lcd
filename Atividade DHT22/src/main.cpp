#include <Arduino.h>
#include "DHT.h"
#include <BluetoothSerial.h>

#define DHTPIN 15
#define DHTTYPE DHT22

BluetoothSerial BT;
DHT dht(DHTPIN, DHTTYPE);

// Variáveis de controle
float tempAnterior = 0;
float umidadeAnterior = 0;
float fAnterior = 0;

uint8_t endG[] = {0x78, 0x42, 0x1C, 0x6C, 0xA4, 0x16};
void setup()
{
  Serial.begin(9600);
  Serial.println("Iniciando o sensor DHT22...");
  dht.begin();

  if (BT.begin("EspMasterFernanda", true))
  {
    Serial.println("Bluetooth iniciado com sucesso!");
    Serial.print("Endereço Bluetooth ESP: ");
    Serial.println(BT.getBtAddressString());
  }
  else
  {
    Serial.println("Erro ao iniciar o Bluetooth!");
  }
  if (BT.connect(endG))
    {
        Serial.println("Conectado com sucesso");
    }else{
        Serial.println("Erro ao conectar");
    }    
}

void loop()
{
  // Leitura atual do DHT22
  float tempAtual = dht.readTemperature();
  float umidadeAtual = dht.readHumidity();
  float fAtual = dht.readTemperature(true);

  // Verifica se leitura é válida
  if (isnan(tempAtual) || isnan(umidadeAtual) || isnan(fAtual))
  {
    Serial.println("Falha na leitura do DHT22!");
    delay(2000);
    return;
  }

  // Só envia se algum valor mudou
  if (tempAtual != tempAnterior || umidadeAtual != umidadeAnterior || fAtual != fAnterior)
  {
    // Monta uma ÚNICA STRING com os 3 valores
    String mensagemEnviar = "TEMP_C:" + String(tempAtual, 2) +
                            "|UMID:" + String(umidadeAtual, 2) +
                            "|TEMP_F:" + String(fAtual, 2);

    mensagemEnviar.trim();

    // Mostra no monitor serial
    Serial.println("Enviando via Bluetooth:");
    Serial.println(mensagemEnviar);

    // Envia para o ESP2 (ou outro dispositivo)
    BT.println(mensagemEnviar);

    // Atualiza os valores anteriores
    tempAnterior = tempAtual;
    umidadeAnterior = umidadeAtual;
    fAnterior = fAtual;
  }

  delay(2000); // Intervalo entre leituras
}
