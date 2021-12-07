#include <Servo.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#include <ArduinoJson.h>
#define SD_ChipSelectPin 53
#include <TMRpcm.h>

TMRpcm tmrpcm;
int motor_a_pin= 3;
int motor_b_pin= 6;
int motor_c_pin= 7;
int led_a_pin= 8;
int led_b_pin= 9;


void conexionServidor() {
  Serial1.println("AT+CIPSTART=\"TCP\",\"192.168.1.2\",6000");
  if (Serial1.find("OK"))
  {
    Serial.println("Conectado al servidor");
  }
  else
  {
    Serial.println("Error conectandose al servidor, intentando nuevamente");
    conexionServidor();
  }
}

void conexionWifi() {
  // SSID y Clave del WiFi
  Serial1.println("AT+CWJAP=\"WiFi-Arnet-b3b1\",\"BC3B8814FD\"");
  if (Serial1.find("OK"))
  {
    Serial.println("Conectado a WiFi");
  }
  else
  {
    Serial.println("Error conectandose al WiFi, intentando nuevamente");
    conexionWifi();
  }
}

void reiniciar() {
  Serial1.println("AT+RST");
  if (Serial1.find("OK"))
  {
    Serial.println("Reiniciado");
  }
  else
  {
    Serial.println("Error reiniciando, intentando nuevamente");
    reiniciar();
  }
}

void setup() {
  // put your setup code here, to run once:
  pinMode(led_a_pin,OUTPUT);
  pinMode(led_b_pin,OUTPUT);
  tmrpcm.speakerPin = 5;
  tmrpcm.quality(1);
  tmrpcm.setVolume(50);
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
  }
  
  Serial1.begin(9600);
  Serial1.setTimeout(10000);
  Serial.begin(9600);
  reiniciar();
  delay(2500);
  conexionWifi();
  delay(2500);
  conexionServidor();
  Serial.println("Conexion exitosa");
  
  // Le enviamos al servidor en python el tipo de cliente arduino
  Serial1.println("AT+CIPSEND=7");
  delay(1000);
  Serial1.println("Arduino");
  Serial1.setTimeout(250);
}

void loop() {
  // put your main code here, to run repeatedly:
  
  digitalWrite(led_a_pin,HIGH);
  digitalWrite(led_b_pin,HIGH);
  tmrpcm.play((char *)"rick.wav");
  String sentence;
  
  if (Serial1.available())
  {
    String frase = Serial1.readString();
    if (frase.charAt(8) == ':')
    {
      sentence = frase.substring(9);
    }
    else
    {
      sentence = frase.substring(10);
    }
    Serial.println(sentence);
    StaticJsonDocument<300> doc;
    deserializeJson(doc, sentence);
    char* instruccion = doc["instruccion"];
    Serial.println("Instruccion: " + String(instruccion));

    if (doc["instruccion"] == "apagar_musica")
    {
      // Si esta activada, play y si no, parar
    }

    if (doc["instruccion"] == "prender_musica")
    {
      // Si esta activada, play y si no, parar
    }

  if (doc["instruccion"] == "apagar_luces")
    {
       digitalWrite(led_a_pin, LOW);
       Serial.println("Apagando luces");
    }

    if (doc["instruccion"] == "prender_luces")
    {
       digitalWrite(led_a_pin, HIGH);
       Serial.println("Prendiendo luces");
    }

  if (doc["instruccion"] == "item1")
    {
      //Activar 2 segundos 
    }
  if (doc["instruccion"] == "item2")
    {
      //Activar 2 segundos 
    }
  if (doc["instruccion"] == "item3")
    {
      //Activar 2 segundos 
    }
  }
}
