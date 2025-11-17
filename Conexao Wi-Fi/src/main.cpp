#include <Arduino.h>
#include <WiFi.h>
#include <ezTime.h>
#include <LiquidCrystal_I2C.h>

// =====================================
// CONFIGURAÇÕES
// =====================================
#define PIN_LED 14
#define PIN_BOTAO 0

String entrada;

const char *WIFI_SSID = "SENAI IoT";
const char *WIFI_SENHA = "Senai@IoT";

LiquidCrystal_I2C lcd(0x27, 20, 4);
Timezone sp;

// =====================================
// VARIÁVEIS DO DESPERTADOR
// =====================================
int alarmeHora = -1;
int alarmeMin = -1;

bool alarmeAtivo = false;
bool alarmeDisparado = false;

// Armazena última linha mostrada no LCD
String lcdCache[4] = {"", "", "", ""};

// =====================================
// FUNÇÕES
// =====================================
void conectarWiFi();
void reconectarWiFi();
void atualizarLCD();
void atualizarLinha(int l, String texto);
void piscarAlarme();
void configurarAlarme();

// =====================================
// SETUP
// =====================================
void setup()
{
  Serial.begin(115200);
  Serial.setTimeout(10000);

  pinMode(PIN_LED, OUTPUT);
  pinMode(PIN_BOTAO, INPUT_PULLUP);

  lcd.init();
  lcd.backlight();
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Iniciando...");

  conectarWiFi();

  waitForSync();
  sp.setLocation("America/Sao_Paulo");

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Hora sincronizada");
  delay(800);

  configurarAlarme();
  lcd.clear();

  entrada = Serial.readStringUntil('\n');
  entrada.trim();

  if (entrada.length() == 5 && entrada.charAt(2) == ':')
  {
    alarmeHora = entrada.substring(0, 2).toInt();
    alarmeMin = entrada.substring(3).toInt();
    alarmeAtivo = true;
  }
}

// =====================================
// LOOP
// =====================================
void loop()
{
  reconectarWiFi();
  atualizarLCD();

  // -------------------------------------
  // VERIFICA SE CHEGOU A HORA DO ALARME
  // -------------------------------------
  if (alarmeAtivo && !alarmeDisparado)
  {
    if (sp.hour() == alarmeHora && sp.minute() == alarmeMin)
    {
      Serial.print("entrou");
      alarmeDisparado = true;
    }
  }

  // -------------------------------------
  // EXECUTANDO ALARME
  // -------------------------------------
  if (alarmeDisparado)
  {
    piscarAlarme();

    if (digitalRead(PIN_BOTAO) == LOW)
    {
      alarmeAtivo = false;
      alarmeDisparado = false;
      digitalWrite(PIN_LED, LOW);
      lcd.backlight();
    }
  }
}

// =====================================
// FUNÇÃO: Atualizar LCD somente se mudar
// =====================================
void atualizarLCD()
{
  String linha0 = sp.dateTime("l, d 'de' F");
  String linha1 = "Ano: " + sp.dateTime("Y");
  String linha2 = "Hora: " + sp.dateTime("H:i:s");

  String linha3 = "Alarme: ";
 
 
    if (alarmeHora < 10)
      linha3 += "0";
    linha3 += String(alarmeHora) + ":";
    if (alarmeMin < 10)
      linha3 += "0";
    linha3 += String(alarmeMin) + " ON";
 

  atualizarLinha(0, linha0);
  atualizarLinha(1, linha1);
  atualizarLinha(2, linha2);
  atualizarLinha(3, linha3);
}

// Atualiza apenas linhas alteradas
void atualizarLinha(int l, String texto)
{
  if (lcdCache[l] != texto)
  {
    lcd.setCursor(0, l);
    lcd.print("                    "); // Limpar
    lcd.setCursor(0, l);
    lcd.print(texto);
    lcdCache[l] = texto;
  }
}

// =====================================
// FUNÇÃO: Piscar LED + LCD quando alarme toca
// =====================================
void piscarAlarme()
{
  static unsigned long tempo = 0;
  static bool estado = false;

  if (millis() - tempo >= 300)
  {
    tempo = millis();
    estado = !estado;

    digitalWrite(PIN_LED, estado);

    if (estado)
      lcd.backlight();
    else
      lcd.noBacklight();
  }
}

// =====================================
// FUNÇÃO: Usuário define horário via Serial
// =====================================
void configurarAlarme()
{
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Config. alarme");
  lcd.setCursor(0, 1);
  lcd.print("Digite HH:MM no Pc");

  Serial.println("\nDigite o horário no formato HH:MM :");

  Serial.print("Alarme configurado para ");
  Serial.print(alarmeHora);
  Serial.print(":");
  Serial.println(alarmeMin);

  /*if (alarmeAtivo ==  entrada)

  {
        alarmeDisparado = true;
        digitalWrite(PIN_LED, HIGH);



  }

*/
}

// =====================================
// FUNÇÃO: Conectar Wi-Fi
// =====================================
void conectarWiFi()
{
  WiFi.begin(WIFI_SSID, WIFI_SENHA);

  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Conectando WiFi...");

  unsigned long inicio = millis();
  while (WiFi.status() != WL_CONNECTED && millis() - inicio < 10000)
  {
  }

  lcd.clear();
  if (WiFi.status() == WL_CONNECTED)
  {
    lcd.setCursor(0, 0);
    lcd.print("WiFi conectado!");
  }
  else
  {
    lcd.setCursor(0, 0);
    lcd.print("Falha no WiFi");
  }
}

// =====================================
// FUNÇÃO: Reconectar quando cair
// =====================================
void reconectarWiFi()
{
  static unsigned long ultima = 0;
  if (millis() - ultima > 5000)
  {
    if (WiFi.status() != WL_CONNECTED)
    {
      conectarWiFi();
    }
    ultima = millis();
  }
}
