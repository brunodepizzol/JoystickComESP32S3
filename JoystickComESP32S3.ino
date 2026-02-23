#include "USB.h"
#include "JoystickFoda.h"

JoystickFoda joystickFoda;
const int PinoPotenciometroVolante = 14;

void setup() {
  analogReadResolution(12);
  analogSetAttenuation(ADC_11db);

  USB.begin();
  joystickFoda.begin();
}

void loop() {
  int valorAnalogicoDoVolante = analogRead(PinoPotenciometroVolante);

  int8_t ValorDoVolanteMapeado = map(valorAnalogicoDoVolante, 0, 4095, -127, 127);

  joystickFoda.send(
    ValorDoVolanteMapeado,  // eixo X (volante)
    0,                      // Y
    0,                      // Z
    0,                      // Rz
    0,                      // Rx
    0,                      // Ry
    0,                      // hat (centrado)
    0                       // botões
  );
}