#include <SPI.h> //biblioteca de sinal
#include <MFRC522.h> //biblioteca do leitor de tag
#include <Servo.h> //biblioteca do servoMotor

#define SS_PIN 10
#define RST_PIN 9
#define ledLaranja 7
#define ledAzul 5
#define ledVerde 3

MFRC522 rfid(SS_PIN, RST_PIN);
Servo servo;

void setup() {
  // iniciando a comunicação com o chip
  SPI.begin();
  rfid.PCD_Init();
  Serial.begin(9600);
  pinMode(ledLaranja, OUTPUT);
  pinMode(ledAzul, OUTPUT);
  pinMode(ledVerde, OUTPUT);
}

void loop() {
  // chacando conexão com o chip
  if(!rfid.PICC_IsNewCardPresent() || !rfid.PICC_ReadCardSerial())
    return;

    //montar o endereço do código
    String strID = "";
    for(byte i = 0; i<4; i++){
      strID +=
        (rfid.uid.uidByte[i] < 0x10 ? "0" : "") +
        String(rfid.uid.uidByte[i], HEX) +
        (i!=3 ? ":" : "");
      }
      strID.toUpperCase();
      Serial.println(strID);
      if(strID.indexOf("33:0B:D4:AE") >= 0){
          Serial.println("achei o cartão");
          digitalWrite(ledLaranja, HIGH);
          delay(3000);
          digitalWrite(ledLaranja, LOW);
        }
      else if(strID.indexOf("B3:6E:61:1B") >= 0){
          Serial.println("achei a tag");
          digitalWrite(ledAzul, HIGH);
          delay(3000);
          digitalWrite(ledAzul, LOW);
        }
      else{
          Serial.println("acesso negado");
          digitalWrite(ledVerde, HIGH);
          delay(3000);
          digitalWrite(ledVerde, LOW);
        }
}
