#include <Servo.h>
#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 53
#include <TMRpcm.h>

TMRpcm tmrpcm;
int led_a_pin= 30;
int led_b_pin= 31;
int led_c_pin= 32;
int led_d_pin= 33;
int led_e_pin= 34;
int led_f_pin= 35;
int motor_a_pin= 6;
int motor_b_pin= 7;
int motor_c_pin= 8;

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
  pinMode(led_c_pin,OUTPUT);
  pinMode(led_d_pin,OUTPUT);
  pinMode(led_e_pin,OUTPUT);
  pinMode(led_f_pin,OUTPUT);
  pinMode(motor_a_pin,OUTPUT);
  pinMode(motor_b_pin,OUTPUT);
  pinMode(motor_c_pin,OUTPUT);
  digitalWrite(led_a_pin,HIGH);
  digitalWrite(led_b_pin,HIGH);
  digitalWrite(led_c_pin,HIGH);
  digitalWrite(led_d_pin,HIGH);
  digitalWrite(led_e_pin,HIGH);
  digitalWrite(led_f_pin,HIGH);

  Serial1.begin(9600);
  Serial1.setTimeout(10000);
  Serial.begin(9600);
  reiniciar();
  delay(2500);
  conexionWifi();
  delay(2500);
  conexionServidor();
  Serial.println("Conexion exitosa");

  //Configuracion del parlante
  if (!SD.begin(SD_ChipSelectPin)) {
    Serial.println("SD fail");
  }
  tmrpcm.speakerPin = 11;
  tmrpcm.quality(1);
  tmrpcm.volume(7);
  tmrpcm.loop(1);
  tmrpcm.play("rick.wav");
}

void loop() {
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
    Serial.println("Instruccion: " + String(sentence));

    if (sentence == "apagar_musica")
    {
       tmrpcm.pause();
    }

    if (sentence == "prender_musica")
    {;
       tmrpcm.pause();
    }

  if (sentence == "apagar_luces")
    {
       Serial.println("Apagando luces");
       digitalWrite(led_a_pin, LOW);
       digitalWrite(led_b_pin, LOW);
       digitalWrite(led_c_pin, LOW);
       digitalWrite(led_d_pin, LOW);
       digitalWrite(led_e_pin, LOW);
       digitalWrite(led_f_pin, LOW);
      
    }

    if (sentence == "prender_luces")
    {
       Serial.println("Prendiendo luces");
       digitalWrite(led_a_pin, HIGH);
       digitalWrite(led_b_pin, HIGH);
       digitalWrite(led_c_pin, HIGH);
       digitalWrite(led_d_pin, HIGH);
       digitalWrite(led_e_pin, HIGH);
       digitalWrite(led_f_pin, HIGH);
    }

  if (sentence == "item1")
    {
      digitalWrite(motor_a_pin, HIGH);
      delay(2000); 
      digitalWrite(motor_a_pin, LOW);
    }
  if (sentence == "item2")
    {
      digitalWrite(motor_b_pin, HIGH);
      delay(2000); 
      digitalWrite(motor_b_pin, LOW);
    }
  if (sentence == "item3")
    {
      digitalWrite(motor_c_pin, HIGH);
      delay(2000); 
      digitalWrite(motor_c_pin, LOW);
    }
  }
}
