#include <ArduinoJson.h>
#include <DHT.h>
#include <ArduinoJson.h>
const int TAMANHO = 50;  //define o tamanho do buffer para o json
#include "DHT.h"

#define DHTPIN 8  // Pino do sensor DHT11
#define DHTTYPE DHT11

DHT dht(DHTPIN, DHTTYPE);
const int trigPin = 7; // Pino TRIG do sensor ultrassônico
const int echoPin = 6; // Pino ECHO do sensor ultrassônico
const int ldr = A0; // Pino analógico do sensor de luz

void setup() {
  Serial.begin(9600);
  dht.begin();
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ldr, INPUT);
}

void loop() {
  StaticJsonDocument<TAMANHO> json; //Aloca buffer para objeto json
  float temp = dht.readTemperature();
  float umd = dht.readHumidity();
  // Leitura do sensor ultrassônico
  long duration, distance;
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = (duration / 2) / 29.1; // Calcula a distância em centímetros

  // Leitura do potenciômetro
  int valueldr = analogRead(ldr);

  // Criação do objeto JSON
  StaticJsonDocument<200> jsonDoc;
  jsonDoc["temperature"] = temp;
  jsonDoc["humidity"] = umd;
  jsonDoc["distance"] = distance;
  jsonDoc["ldr"] = valueldr;

  // Serializa o JSON para a saída serial
  String jsonString;
  serializeJson(jsonDoc, jsonString);
  Serial.println(jsonString);

  delay(5000); // Espere 5 segundos antes de enviar outro conjunto de leituras
}