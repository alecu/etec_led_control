#include <SoftPWM.h>

#define FIRST 2
#define LAST 13

#define DEMO 0
#define OPERATION 1

int mode;

void all_to_zero()
{
  for (int n = FIRST; n < LAST + 1; n++) {
    SoftPWMSet(n, 0);
  }
}

void setup()
{
  SoftPWMBegin();
  all_to_zero();

  SoftPWMSetFadeTime(ALL, 100, 400);
  Serial.begin(9600);
  Serial.println("=========================");
  Serial.println("EspacioTec Led Controller");
  Serial.println("-------------------------");
  Serial.println("FORMA DE USO: recibe por serie lineas de texto terminadas con LF (\\n), con el formato \"LED VALUE\", ej: \"11 255\".");
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
      pin = constrain(pin, FIRST, LAST);
      value = constrain(value, 0, 255);
      SoftPWMSet(pin, value);
      Serial.print    (pin);
      Serial.print("=");
      Serial.println(value);
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
