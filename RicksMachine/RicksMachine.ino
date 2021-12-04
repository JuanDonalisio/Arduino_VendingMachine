#include <SoftwareSerial.h>
#include <SD.h>
#include <SPI.h>
#define SD_ChipSelectPin 53
#include <TMRpcm.h>

TMRpcm tmrpcm;
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
