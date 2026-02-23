#pragma once
#include "USBHID.h"

#if CONFIG_TINYUSB_HID_ENABLED

class JoystickFoda : public USBHIDDevice {
private:
  USBHID hid;

  int16_t  _x, _y, _z, _rz, _rx, _ry;
  uint8_t  _hat;
  uint32_t _buttons;

  bool write();

public:
  JoystickFoda();

  void begin();
  void end();

  bool leftStick(int16_t x, int16_t y);
  bool rightStick(int16_t z, int16_t rz);
  bool leftTrigger(int16_t rx);
  bool rightTrigger(int16_t ry);
  bool hat(uint8_t hat);

  bool pressButton(uint8_t button);
  bool releaseButton(uint8_t button);

  bool send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, uint8_t hat, uint32_t buttons);

  uint16_t _onGetDescriptor(uint8_t* buffer);
};

#endif