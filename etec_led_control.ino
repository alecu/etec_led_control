#include <SoftPWM.h>

#define FIRST 2
#define LAST 13

void setup()
{
  SoftPWMBegin();

  for (int n = FIRST; n < LAST + 1; n++) {
    SoftPWMSet(n, 0);
  }

  SoftPWMSetFadeTime(ALL, 100, 400);
  Serial.begin(9600);
  Serial.println("Hola EspacioTec!");
}

void loop()
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
