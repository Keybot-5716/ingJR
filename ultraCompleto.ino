
void setup() {

  pinMode(2, INPUT);  // ECHO
  pinMode(3, OUTPUT); // TRIGGER
  
  pinMode(11, OUTPUT);
  pinMode(12, INPUT_PULLUP);
  pinMode(13, OUTPUT); 
  Serial.begin(9600);
}

// the loop function runs over and over again forever
void loop() {
  int boton = digitalRead(12);
  float d = ultra();
  
  if (boton == LOW || (d > 0 && d < 8)) // Si se presiona el botón o hay algo a menos de 8cm
  {
    digitalWrite(11, HIGH);
    digitalWrite(13, HIGH);   // prende el LED
  }
  else 
  {
    digitalWrite(11, LOW);
    digitalWrite(13,LOW);     // apaga el LED
  }
}


// Función que "empaqueta" la funcionalidad del sensor ultrasónico
// Declara los puertos de trigger y echo, así como las variables de retorno
float ultra()
{
  int trigger = 3;                            //Pin digital 2 para el Trigger del sensor
  int echo = 2;                               //Pin digital 3 para el Echo del sensort
  float tiempo_de_espera,distancia; 
  
    digitalWrite (trigger,LOW);               // ponemos en bajo el pin 8 durante 2 microsegundos
    delayMicroseconds(2);
    digitalWrite (trigger, HIGH);             // ahora ponemos en alto pin 8 durante 10 microsegundos;
    delayMicroseconds (10);                   // pues este el momento en que emite el sonido durante 10 segungos
    digitalWrite (trigger, LOW);              // ahora ponemos en bajo pin 8 
    tiempo_de_espera = pulseIn(echo,HIGH);   // pulseIn, recoge la señal del sonido que emite el trigger
    distancia =(tiempo_de_espera/2)/29.15;    // formula para hallar la distancia
    Serial.print (distancia);                 // imprimimos la distancia en cm
    Serial.println ("cm");
    return distancia;
}
