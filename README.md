# ESP32-C3 Bluetooth Speaker Project

## Overview
This project is a compact and efficient Bluetooth speaker powered by the ESP32-C3 microcontroller and a common laptop speaker. It uses the **MAX98357 amplifier** for audio output, features a low-battery indicator, and includes a physical button for toggling power and entering deep sleep mode. The speaker streams audio from a phone or other Bluetooth devices and is designed to be small, energy-efficient, and battery-powered.

---

## Features
- **Bluetooth Audio Streaming**: Connects seamlessly with phones or other Bluetooth devices using the `BluetoothA2DPSink` library.
- **Audio Amplification**: The MAX98357 module is used for high-quality audio output.
- **Battery-Powered**: Runs on a 3.7V rechargeable Li-ion battery. (Volage range 3.2V  to 4.2V)
- **Low-Battery Indicator**: An LED indicates when the battery voltage is below 3.3V.
- **Power Control**: Physical button to toggle power or put the device into deep sleep to conserve battery.
- **Compact Design**: Fits within a small case (90mm x 60mm x 30mm).

---

## Components

### Hardware
- **ESP32-C3 Super Mini**: Main microcontroller for Bluetooth and power management.
- **MAX98357 Module**: I2S digital audio amplifier.
- **3.7V Li-ion Battery**: Rechargeable power source.
- **Charging Module**: Handles battery charging.
- **Speaker**: Full-range laptop speaker.
- **LED**: Indicates low battery state.
- **Push Button**: Controls power and sleep mode.
- Resistors (330Ω for LED, 10kΩ and 2,2kΩ for voltage divider).

### Software
- **ESP-IDF or Arduino IDE**: Development environment.
- **Libraries**:
  - `BluetoothA2DPSink` for Bluetooth audio.
  - `driver/i2s.h` for I2S communication.

---

## Circuit Diagram
Include or link to a circuit diagram showing:
- ESP32 connections to the MAX98357 module.
- Push button wiring for power toggle.
- Low-battery indicator LED.
- Voltage divider for battery monitoring.

---

## Pin Configuration

| **Component**         | **Pin**     | **ESP32-C3 Pin**   |
|------------------------|-------------|--------------------|
| I2S BCLK              | GPIO7       | BCK of MAX98357    |
| I2S LRCLK             | GPIO8       | LRCK of MAX98357   |
| I2S Data Out          | GPIO6       | DIN of MAX98357    |
| Low Battery LED       | GPIO9       | LED cathode to GND |
| Button                | GPIO21      | Pulled LOW on press |
| Battery Monitoring    | GPIO3 (ADC) | Voltage divider input |

---

## Code
The project code is included in the repository. Key features:
- **Bluetooth Audio**: Uses `BluetoothA2DPSink` to stream audio from paired devices.
- **Battery Monitoring**: Reads battery voltage using the ESP32 ADC and triggers a low-battery warning.
- **Power Management**: Handles button press for toggling power and deep sleep mode.

To upload the code:
1. Install the **Arduino IDE** or **ESP-IDF**.
2. Add the necessary libraries:
   - `BluetoothA2DPSink`.
3. Connect the ESP32-C3 Supermini and upload the code.

---

## Setup and Usage

1. **Assembly**:
   - Connect the MAX98357 module, button, LED, and battery as per the circuit diagram.
2. **Power On**:
   - Press the physical button to wake the device.
3. **Bluetooth Pairing**:
   - Search for the device named **"My Speaker"** and pair it with your phone.
4. **Audio Streaming**:
   - Play audio from your phone. The MAX98357 amplifier handles audio output.

---

## Deep Sleep and Wakeup
- Press the button to enter deep sleep. The ESP32-C3 will stop Bluetooth streaming and conserve power.
- To wake the device, press the button again.

---

## Low Battery Indicator
- When the battery voltage drops below **3.4V**, the LED will light up to indicate that the battery needs charging.

---

## Notes and Tips
- **Case Design**: Ensure proper ventilation and use acoustically transparent fabric or mesh for the speaker grill.
- **Battery Safety**: Use a charging module with overcharge and over-discharge protection.
- **Testing**: Debug ADC readings and battery voltage during initial setup to ensure accurate low-battery detection.

---

## Future Improvements
- Add stereo support with two MAX98357 modules.
- Implement long-press functionality on the button for additional features (e.g., reset or Bluetooth unpair).
- Include a battery level display using a small OLED or LED bar.

---

## License
This project is open-source and licensed under the MIT License.
