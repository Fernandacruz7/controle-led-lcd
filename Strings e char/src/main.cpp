#include <Arduino.h>
// char - mais recomendado para uso profissional
// String - mais facil

/*char palavra[10] = {'O', 'L', 'A', ' ', 'M', 'U', 'N', 'D', 'O', '\0'};
char palavra2[] = "OLA MUNDO";
String palavra3 = "OLA MUNDO";

void setup()
{
  Serial.begin(9600);
  Serial.println();
  Serial.println(palavra2);

  //----------------- FUNCOES PARA CHAR -----------------
  strcpy(palavra2, "SENAI"); // substitui o valor anterior
  // Serial.println(palavra2);

  // Serial.println(strcmp(palavra2, "SENAI"));//se for igual retorna 0
  // if (strcmp(palavra2, "SENAI") == 0)
  // {
  //   Serial.println("são iguais");
  // }else
  // {
  //   Serial.println("são diferentes");
  // }

  // Serial.println(strncmp(palavra2, "senai", 5));
  // compara a quantidade de caracteres

  // if (strncmp(palavra2, "SENAI", 5) == 0)
  //  if (!strncmp(palavra2, "SENAI", 5))
  //  {
  //    Serial.println("Quantidade de caracteres iguais");
  //  }

  // strstr();// procura dentro da string pela primeira ocorrencia de uma substring
  //  if (strstr(palavra2, "NAI"))
  //  {
  //    Serial.println("palavra encontrada");
  //  }

  // Serial.println(strcat(palavra2, "-SP"));
  // concatena duas strings, ou seja junta

  //----------------- FUNCOES PARA STRING -----------------
  // Serial.println(palavra3.length());//retorna a quantidade de caracteres
  // Serial.println(palavra3.charAt(2));//retorna o caracter da posição indicada
  // Serial.println(palavra3.substring(2, 5));//retorna um pedaço da string original
  // Serial.println(palavra3.indexOf('M'));//retorna a posição do elemento procurado
  // Serial.println(palavra3.lastIndexOf('O'));//retorna a posição do utlimo elemento procurado

  // equals() //Compara se é igual
  //  if (palavra3.equalsIgnoreCase("ola mundo"))
  //  {Serial.println("iguais");}

  // if (palavra3.startsWith("OLA"))
  // {Serial.println("o inicio e igual");}

  // if (palavra3.endsWith("DO"))
  // {Serial.println("o fim e igual");}

  // palavra3.toUpperCase();//converte para caixa alta
  // palavra3.toLowerCase();//converte para caixa baixa
  // Serial.println(palavra3);

  // String valor = "100";
  //int numero = valor.toInt();
  // float numeroF = valor.toFloat();

  // String texto = "texto           ";
  // texto.trim();

  // String instrucao = "Led = ON";
  // instrucao.replace("ON", "OFF");
   /* Serial.setTimeout(5000);
    String texto = Serial.readStringUntil('\n');
    texto.trim();
    Serial.printf("voce digitou %s!", texto);
    //Serial.printf("variavel1 : %s, variavel2 : %i", texto, numero);

}

void loop()
{
}*/

// Atividade 1

/*String comando;

void setup() {
  Serial.begin(9600);
  pinMode(13, OUTPUT); // LED na porta 13
  Serial.println("Digite um comando (ex: 'LED ON' ou 'LED OFF'):");

  if (Serial.available() > 0) {
    comando = Serial.readStringUntil('\n');
    comando.trim();
    comando.toUpperCase();

    if (comando.endsWith("ON")) {
      Serial.println("LIGAR LED");
      digitalWrite(13, HIGH);
    }
    else if (comando.endsWith("OFF")) {
      Serial.println("DESLIGAR LED");
      digitalWrite(13, LOW);
    }
    else {
      Serial.println("COMANDO INVÁLIDO");
    }

    Serial.println("\nDigite outro comando (ex: 'LED ON' ou 'LED OFF'):");
  }
}

void loop() {

}*/

// Atividade2

/*void setup() {
  Serial.begin(9600);

  String mensagem = "Temperatura = 27C";

  String numeros = "";
  for (char c : mensagem) {
    if (isDigit(c)) numeros += c;
  }

  int celsius = numeros.toInt();

  float fahrenheit = (celsius * 9.0 / 5.0) + 32.0;

  Serial.print("Celsius: ");
  Serial.print(celsius);
  Serial.print(" °C  ->  Fahrenheit: ");
  Serial.print(fahrenheit);
  Serial.println(" °F");
}

void loop() {
}*/

// atividade 3

/*void setup()
{
  Serial.begin(9600);

  String frase = "ESTAMOS APRENDENDO ARDUINO NA AULA";
  frase.trim();
  String palavra_chave = "ARDUINO";
  if (frase.){
  Serial.println ("TEM");
  }
  else{
    Serial.println ("NÃO TEM");

}
}
void loop()
  {
    }*/

// atividade 4

 void setup()
{
  Serial.begin(9600);
  String frase = "sEnAi eSp32 ArDuInO";
  frase.toUpperCase();
  Serial.println (frase);

  frase.toLowerCase();
  Serial.println (frase);
}
void loop()
  {
  }

