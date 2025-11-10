#include <Arduino.h>
#include "DHT.h"
#include <BluetoothSerial.h>
#include <ArduinoJson.h>

#define DHTPIN 15
#define DHTTYPE DHT22

BluetoothSerial BT;
DHT dht(DHTPIN, DHTTYPE);

float tempAnterior = 0;
float umidadeAnterior = 0;
float fAnterior = 0;

uint8_t endG[] = {0xF4, 0x65, 0x0B, 0x48, 0xA6, 0xCA};
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
  float tempAtual = dht.readTemperature();
  float umidadeAtual = dht.readHumidity();
  float fAtual = dht.readTemperature(true);

  if (isnan(tempAtual) || isnan(umidadeAtual) || isnan(fAtual))
  {
    Serial.println("Falha na leitura do DHT22!");
    delay(2000);
    return;
  }

  if (tempAtual != tempAnterior || umidadeAtual != umidadeAnterior || fAtual != fAnterior)
  {
    // Monta uma ÚNICA STRING com os 3 valores
   StaticJsonDocument<200> doc;

    doc["C"] = tempAtual;
    doc["F"] = fAtual;
    doc["U"] = umidadeAtual;

    String mensagemEnviar;
    serializeJson(doc, mensagemEnviar);

    Serial.println("Enviando via Bluetooth:");
    Serial.println(mensagemEnviar);

    // Envia para o ESP2 (ou outro dispositivo)
    BT.println(mensagemEnviar);

    // Atualiza os valores anteriores
    tempAnterior = tempAtual;
    umidadeAnterior = umidadeAtual;
    fAnterior = fAtual;
  }

}
