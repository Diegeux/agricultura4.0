#include "DHT.h"
#include <ESP8266WiFi.h>
#include <FirebaseESP8266.h>

#define TRIGGERPIN 4 //gpio4  
#define ECHOPIN 6 //gpio5

const int ledPin = 13;
//SimpleTimer timer;
String myString;
long duration;
int distance;
int safetyDistance;
int valor_analogico;

// Set these to run example.
#define FIREBASE_AUTH "Chave_Secreta_do_BD"
#define FIREBASE_HOST "exemplo.firebaseio.com"
#define WIFI_SSID "Nome_da_Rede_WiFi"
#define WIFI_PASSWORD "Senha"
  
#define DHTPIN D5
#define DHTTYPE DHT11
#define pino_sinal_analogico A0

DHT dht (DHTPIN, DHTTYPE);

FirebaseData fbdo;
FirebaseAuth auth;
FirebaseConfig config;

void setup(){
  // connect to wifi.
  WiFi.begin(WIFI_SSID, WIFI_PASSWORD);
  Serial.print("conectando");
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.print("conectado: ");
  Serial.println(WiFi.localIP());
  dht.begin();
  //Firebase.begin(FIREBASE_HOST,FIREBASE_AUTH); 
  config.host = FIREBASE_HOST;
  config.signer.tokens.legacy_token = FIREBASE_AUTH;
  Firebase.reconnectWiFi(true);
  Firebase.begin(&config, &auth);

  Serial.begin(9600);
  pinMode(pino_sinal_analogico, INPUT);
}  

void loop() {    
valor_analogico = analogRead(pino_sinal_analogico);
 
  //Mostra o valor da porta analogica no serial monitor
Serial.print("Porta analogica: ");
Serial.print(valor_analogico);
 
float h = dht.readHumidity();
float t = dht.readTemperature();
String result;
Serial.println("Coletando dados...");
Firebase.set(fbdo,"Diego/fazenda_inteligente/ambiente/umidade",h);
Firebase.set(fbdo,"Diego/fazenda_inteligente/ambiente/temperatura",t);
Firebase.set(fbdo,"Diego/fazenda_inteligente/solo/umidade",valor_analogico);
Serial.println("Umidade:"); 
Serial.println(h);  
Serial.println("Temperatura:");
Serial.println(t); 
}
