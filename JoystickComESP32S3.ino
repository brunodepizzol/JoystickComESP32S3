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

  int16_t ValorDoVolanteMapeado = (int16_t)map(valorAnalogicoDoVolante, 0, 4095, -32767, 32767);

  joystickFoda.send(
    ValorDoVolanteMapeado,  // eixo X (volante)
    0,                      // Y
    0,                      // Z
    0,                      // Rz
    0,                      // Rx
    0,                      // Ry
    8,                      // hat (centrado)
    0                       // botões
  );
}