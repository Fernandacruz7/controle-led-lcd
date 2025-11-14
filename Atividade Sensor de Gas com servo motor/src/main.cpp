#include "BluetoothSerial.h"

BluetoothSerial BT;

const int gasPin = 25;

const int limiteGas = 450;  

uint8_t endM[] = {0xF4, 0x65, 0x0B, 0x55, 0x4F, 0x26};


void setup() {
  Serial.begin(9600);
  Serial.setTimeout(5000);
  BT.begin("ESP32_GAS");  
  Serial.println("Bluetooth iniciado. Aguardando conexão...");

  if (BT.begin("EspMasterFernanda", true))
    {
        Serial.println("Bluetooth iniciado com sucesso");
    }else
    {
        Serial.println("Erro ao iniciar o bluetooth");
    }

  if (BT.connect(endM))
    {
        Serial.println("Conectado com sucesso");
    }else{
        Serial.println("Erro ao conectar");
    }    

  pinMode(gasPin, INPUT);
}

void loop() {

  int valorGas = analogRead(gasPin);
  
  Serial.print("Gás: ");
  Serial.println(valorGas);

  if (valorGas > limiteGas) {
    BT.print("ALERTA! Gas acima do limite: ");
    BT.println(valorGas);
  } else {
    BT.print("Valor OK: ");
    BT.println(valorGas);
  }

   if (BT.available())
    {
        String mensagemRecebida = BT.readStringUntil('\n');
        mensagemRecebida.trim();
        Serial.printf("Mensagem recebida: %s", mensagemRecebida);
    }

    if (Serial.available())
    {
        String mensagemEnviar = Serial.readStringUntil('\n');
        mensagemEnviar.trim();
        BT.println(mensagemEnviar);
    }

  delay(1000);
}
