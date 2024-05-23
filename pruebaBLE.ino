#include <SoftwareSerial.h>

SoftwareSerial ble(8,9);

int in1 = 4;
int in2 = 5;
int in3 = 6;
int in4 = 7;

void setup() {
  // Motores
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Sistema de comunicación
  Serial.begin(9600);
  ble.begin(9600);
}

void loop() {
  if (ble.available()) {
    // Pruebas Teleoperado
    char car = ble.read();
    Serial.println(car);
    if (car == 'A')
      adelante();
    else if (car == 'T')
      atras();
    else
      alto(); 
  }
}

void atras()
{
  digitalWrite(in1,HIGH);
  digitalWrite(in2,LOW);
  digitalWrite(in3,HIGH);
  digitalWrite(in4,LOW);
}

void adelante()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,HIGH);
  digitalWrite(in3,LOW);
  digitalWrite(in4,HIGH);
}

void alto()
{
  digitalWrite(in1,LOW);
  digitalWrite(in2,LOW);
  digitalWrite(in3,LOW);
  digitalWrite(in4,LOW);
}
