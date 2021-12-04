#include <Servo.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 53
#include <TMRpcm.h>

TMRpcm tmrpcm;
int motor_a_pin= 3;
int motor_b_pin= 6;
int motor_c_pin= 7;
int led_a_pin= 8;
int led_a_pin= 9;


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
  Serial1.println("AT+CWJAP=\"claro\",\"OT4497912\"");
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
  digitalWrite(led_b_pinD,HIGH);
  tmrpcm.play((char *)"rick.wav");
  
  if (doc["instruccion"] == "musica")
    {
      // Si esta activada, play y si no, parar
    }

  if (doc["instruccion"] == "leds")
    {
       //Si esta prendido, apagar y y si esta apagado, prender
    }

  if (doc["instruccion"] == "motorA")
    {
      //Activar 2 segundos 
    }
  if (doc["instruccion"] == "motorB")
    {
      //Activar 2 segundos 
    }
  if (doc["instruccion"] == "motorC")
    {
      //Activar 2 segundos 
    }
}
