#include <Servo.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 53
#include <TMRpcm.h>

TMRpcm tmrpcm;
int motor_a_pin= 3;
int motor_a_pin= 6;
int motor_a_pin= 7;

void conexionServidor() {
  Serial1.println("AT+CIPSTART=\"TCP\",\"192.168.100.10\",4000");
  if (Serial1.find("OK"))
  {
    Serial.println("Conectado al servidor");
  }
  else
  {
    Serial.println("Error conectandose al servidor, intentando nuevamente");
    conectarServidor();
  }
}

void conexionWifi() {
  // SSID y Clave del WiFi
  Serial1.println("AT+CWJAP=\"Fibertel WiFi997 2.4GHz\",\"panqueques\"");
  if (Serial1.find("OK"))
  {
    Serial.println("Conectado a WiFi");
  }
  else
  {
    Serial.println("Error conectandose al WiFi, intentando nuevamente");
    conectarWifi();
  }
}

void setup() {
  // put your setup code here, to run once:
  tmrpcm.speakerPin = 5;
  tmrpcm.quality(1);
  tmrpcm.setVolume(50);

  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
  }
}

void loop() {
  // put your main code here, to run repeatedly:
  tmrpcm.play((char *)"rick.wav");
}
