# MKR\_WiFi\_1010

This library currently houses two examples demonstrating how to use the RGB LED attached to the uBlox (ESP32) module of the Arduino MKR WiFi 1010 development board.

This is a bit of a "secret" feature considering the official Arduino documentation does not even mention the presence of an RGB LED on the board. The reason for this is likely that the LED is connected to the pins of the uBlox/ESP32 WiFi module, NOT the pins of the main Arduino SAMD MCU itself.

This means in order to control the RGB LED, you must utilize the (again hidden) pinMode and analogWrite functions of the WiFiNINA library.

## Requirements

The **[WiFiNINA](https://github.com/arduino-libraries/WiFiNINA)** library is required to use these examples, and can be found and installed via the **Sketch > Include Library > Manage Libraries** menu within the Arduino desktop IDE.

You must also install the **Arduino SAMD Boards (32-bits ARM Cortex-M0+)** board package, which contains files necessary to program the MKR WiFi 1010 and a number of other Arduino boards. This package can be installed via **Tools > Board > Boards Manager**, again from within the Arduino desktop IDE.

After installing and allowing Windows to install the associated drivers, connect your board and set it as the development target by picking **Tools > Board > Arduino MKR WiFi 1010**, and subsequently, **Tools > Port > COMxx**, where xx is a COM port number your computer picks at random, i.e. COM3 or COM23.

You're then ready to open these examples and flash them to your Arduino using the sideways arrow "upload" button in the IDE. Enjoy! -ReanimationXP