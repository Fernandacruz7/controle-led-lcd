#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>

void conexaoWifi();
void reconexaoWifi();

const char *SSID = "SENAI IoT";
const char *SENHA = "Senai@IoT";

const unsigned long tempoEsperaConexao = 10000;
const unsigned long tempoEsperaReconexao = 5000;

Timezone sp;

void setup() {
  Serial.begin(115200);
  delay(500);

  conexaoWifi();

  waitForSync();
  sp.setLocation("America/Sao_Paulo");

  Serial.println("Relógio sincronizado!");
}

void loop() {

  reconexaoWifi();

  static int ultimoSegundo = -1;
  int segundoAtual = sp.second();

  if (segundoAtual != ultimoSegundo) {
    ultimoSegundo = segundoAtual;

    String frase = "Hoje é ";
    frase += sp.dateTime("l");      
    frase += ", ";
    frase += sp.dateTime("d");      
    frase += " de ";
    frase += sp.dateTime("F");      
    frase += " de ";
    frase += sp.dateTime("Y");      
    frase += ", agora são ";
    frase += sp.dateTime("h:i:s");  
    frase += " - ";
    frase += sp.dateTime("A");      
    frase += " (";
    frase += sp.dateTime("T");      
    frase += ")";

    Serial.println(frase);
  }

  if (minuteChanged()) {

    Serial.println("---- Minuto mudou ----");

    Serial.println(sp.minute());
    Serial.println(sp.second());
    Serial.println(sp.hour());
    Serial.println(sp.day());
    Serial.println(sp.month());
    Serial.println(sp.year());
    Serial.println(sp.dayOfYear());
    Serial.println(sp.isDST());
  }
}

void conexaoWifi() {
  Serial.printf("Conectando ao WiFi: %s", SSID);
  WiFi.begin(SSID, SENHA);

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < tempoEsperaConexao) {
    Serial.print(".");
    delay(500);
  }

  if (WiFi.status() == WL_CONNECTED) {
    Serial.println("\nWiFi conectado!");
    Serial.print("IP: ");
    Serial.println(WiFi.localIP());
  } else {
    Serial.println("\nFalha ao conectar");
  }
}

void reconexaoWifi() {
  static unsigned long ultima = 0;

  if (millis() - ultima > tempoEsperaReconexao) {
    if (WiFi.status() != WL_CONNECTED) {
      Serial.println("Reconectando WiFi...");
      conexaoWifi();
    }
    ultima = millis();
  }
}