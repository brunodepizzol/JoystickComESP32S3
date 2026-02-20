# 🎮 Joystick com ESP32-S3 (USB HID)

Transforme um **ESP32-S3** em um **Joystick USB (HID)** utilizando apenas um potenciômetro.

O dispositivo é reconhecido automaticamente pelo Windows/Linux/macOS como controle padrão, sem necessidade de driver.

---

## 🚀 Funcionalidades

- USB HID nativo
- 1 eixo analógico (X)
- Leitura ADC 12 bits
- Código simples e direto
- Baixa latência

---

## 🧠 Como funciona

O ESP32-S3 possui USB nativo.  
Este projeto usa a biblioteca `USBHIDGamepad` para enviar o valor lido no ADC como eixo X de um joystick.

Fluxo:

1. Leitura do ADC (GPIO14)
2. Mapeamento de 0–4095 → -127 a 127
3. Envio via USB HID

---

## 🧰 Lista de Materiais

| Item | Quantidade |
|------|------------|
| ESP32-S3 Dev Module (USB nativo) | 1 |
| Potenciômetro 10k linear | 1 |
| Capacitor 100nF (opcional, recomendado) | 1 |
| Jumpers | - |
| Cabo USB | 1 |

---

## 🔌 Placas Testadas

- Espressif ESP32-S3 Dev Module
- ESP32-S3-DevKitC-1
- ESP32-S3-DevKitM-1

⚠️ A placa precisa ter **USB nativo**, não apenas conversor USB-Serial.

---

## 🔧 Ligações

### Potenciômetro

- Um lado → 3.3V
- Outro lado → GND
- Pino central (wiper) → GPIO14

### Capacitor (recomendado)

- 100nF entre GPIO14 e GND (para reduzir jitter)
