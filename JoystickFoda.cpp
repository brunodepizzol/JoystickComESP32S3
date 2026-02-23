#include "USBHID.h"
#if CONFIG_TINYUSB_HID_ENABLED

#include "JoystickFoda.h"
#include <string.h>

#ifndef HID_REPORT_ID_GAMEPAD
#define HID_REPORT_ID_GAMEPAD  0x01
#endif

static const uint8_t report_descriptor_16[] = {
  0x05, 0x01,
  0x09, 0x05,
  0xA1, 0x01,
  0x85, HID_REPORT_ID_GAMEPAD,

  0x05, 0x01,
  0x09, 0x30,
  0x09, 0x31,
  0x09, 0x32,
  0x09, 0x35,
  0x09, 0x33,
  0x09, 0x34,
  0x16, 0x01, 0x80,
  0x26, 0xFF, 0x7F,
  0x75, 0x10,
  0x95, 0x06,
  0x81, 0x02,

  0x09, 0x39,
  0x15, 0x00,
  0x25, 0x08,                   
  0x75, 0x08,
  0x95, 0x01,
  0x81, 0x02,

  0x05, 0x09,
  0x19, 0x01,
  0x29, 0x20,
  0x15, 0x00,
  0x25, 0x01,
  0x75, 0x01,
  0x95, 0x20,
  0x81, 0x02,

  0xC0
};

typedef struct __attribute__((packed)) {
  int16_t  x, y, z, rz, rx, ry;
  uint8_t  hat;
  uint32_t buttons;
} gamepad16_report_t;

JoystickFoda::JoystickFoda()
: hid(), _x(0), _y(0), _z(0), _rz(0), _rx(0), _ry(0), _hat(0), _buttons(0)
{
  static bool initialized = false;
  if (!initialized) {
    initialized = true;
    hid.addDevice(this, sizeof(report_descriptor_16));
  }
}

uint16_t JoystickFoda::_onGetDescriptor(uint8_t* dst) {
  memcpy(dst, report_descriptor_16, sizeof(report_descriptor_16));
  return sizeof(report_descriptor_16);
}

void JoystickFoda::begin() { hid.begin(); }
void JoystickFoda::end() {}

bool JoystickFoda::write() {
  gamepad16_report_t report {
    .x = _x, .y = _y, .z = _z, .rz = _rz, .rx = _rx, .ry = _ry,
    .hat = _hat,
    .buttons = _buttons
  };
  return hid.SendReport(HID_REPORT_ID_GAMEPAD, &report, sizeof(report));
}

bool JoystickFoda::leftStick(int16_t x, int16_t y) { _x = x; _y = y; return write(); }
bool JoystickFoda::rightStick(int16_t z, int16_t rz) { _z = z; _rz = rz; return write(); }
bool JoystickFoda::leftTrigger(int16_t rx) { _rx = rx; return write(); }
bool JoystickFoda::rightTrigger(int16_t ry) { _ry = ry; return write(); }

bool JoystickFoda::hat(uint8_t hat) {
  if (hat > 8) return false;
  _hat = hat;
  return write();
}

bool JoystickFoda::pressButton(uint8_t button) {
  if (button > 31) return false;
  _buttons |= (1u << button);
  return write();
}

bool JoystickFoda::releaseButton(uint8_t button) {
  if (button > 31) return false;
  _buttons &= ~(1u << button);
  return write();
}

bool JoystickFoda::send(int16_t x, int16_t y, int16_t z, int16_t rz, int16_t rx, int16_t ry, uint8_t hat, uint32_t buttons) {
  if (hat > 8) return false;
  _x = x; _y = y; _z = z; _rz = rz; _rx = rx; _ry = ry;
  _hat = hat;
  _buttons = buttons;
  return write();
}

#endif