#include <SoftPWM.h>

#define FIRST 2
#define LAST 13

#define DEMO 0
#define OPERATION 1

int mode;

void all_to_zero()
{
  Serial.println("Resetting...");
  for (int n = FIRST; n < LAST + 1; n++) {
    SoftPWMSet(n, 0);
    Serial.print(n);
    Serial.print(" ");
  }
  Serial.println();
}

void setup()
{
  Serial.begin(9600);
  SoftPWMBegin();
  all_to_zero();

  SoftPWMSetFadeTime(ALL, 100, 400);
  Serial.println("=========================");
  Serial.println("EspacioTec Led Controller v0.8.3");
  Serial.println("-------------------------");
  Serial.println("FORMA DE USO: recibe por serie lineas de texto terminadas con LF (\\n), con el formato \"LED VALUE\", ej: \"11 255\".");
  Serial.println("LED es el numero de pin del Arduino, desde 2 a 13 para los pines D2 a D13; VALUE va de 0 a 255."); 
  Serial.println("Si se recibe un 0 como LED, el programa vuelve a DEMO MODE.");
  Serial.println("Consultas? alecu@protocultura.net");
  Serial.println("-------------------------");
  mode = DEMO;
  Serial.println("DEMO MODE");
}

void demo_loop()
{
  for (int n = FIRST; n < LAST + 1; n++) {
    SoftPWMSet(n, random(32));
  }
  if (Serial.available() > 0) {
    mode = OPERATION;
    all_to_zero();
    Serial.println("OPERATION MODE");
  }
  delay(1000);
}

void operation_loop()
{
  while (Serial.available() > 0) {
    int pin = Serial.parseInt();
    int value = Serial.parseInt();

    if (Serial.read() == '\n') {
      if (pin == 0) {
        mode = DEMO;
        Serial.println("DEMO MODE");        
      } else {
        pin = constrain(pin, FIRST, LAST);
        value = constrain(value, 0, 255);
        SoftPWMSet(pin, value);
        Serial.print("Led");
        Serial.print(pin);
        Serial.print("=");
        Serial.println(value);        
      }
    }
  }
}

void loop()
{
  switch (mode) {
    case DEMO:
      demo_loop();
      break;
    case OPERATION:
      operation_loop();
      break;
  }
}
