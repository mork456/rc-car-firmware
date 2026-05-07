# RC Car Firmware

Arduino firmware for a BLE-controlled 2 servo/wheel robot. Receives servo speeds from a python script.

## Hardware

- Arduino UNO
- HM-10 BLE module
- Continuous rotation servos
- Breadboard, wires, 1k and 2.k resistors

## Wiring

| Component | Pin |
| --------- | --- |
| Left Servo | 7 |
| Right Servo | 9 |
| RXD HM-10 | 4 |
| TXD HM-10 | 3 |

**Voltage Divider**
$R_1$ = 1k resistor into TXD, $R_2$ =  2.2k resistor from TXD to GND

$V_{out} = V_{in} \cdot \frac{R_2}{R_1 + R_2} = 5V \cdot \frac{2.2k\Omega}{1k\Omega + 2.2k\Omega} \approx 3.4V$

~3.4V is safe compared to the full 5V from the arduino, which would damage the HM-10 module.

## Protocol

The program reads the string received from serial BLE connection, expecting data in bytes in the format "{left_speed},{right_speed}\n". It then writes the received speed to each servo.
If no command is received for more than 200ms, it stops the robot.

## Using PlatformIO

One may use Arduino IDE, given that the nanoatmega328 with new bootloader is selected

Create a Python venv and install PlatformIO:
```powershell/bash
python -m venv venv
.\venv\Scripts\activate # Windows
source venv/bin/activate # Unix
pip install platformio
```

Then connect the arduino with the USB cable and flash:
```powershell/bash
pio run -t upload
```

other useful PlatformIO commands and config file:
```powershell/bash
pio run # Compile without flashing
pio run -t compiledb # Fixes language server errors
```

platformio.ini
```ini
[env:nanoatmega328]
platform = atmelavr
board = nanoatmega328
framework = arduino
lib_deps = 
	arduino-libraries/Servo@^1.3.0
	featherfly/SoftwareSerial@^1.0.0
upload_protocol = arduino
upload_speed = 115200
```

## Related Repo

The python script which interprets the controller input and sends the string required by the Arduino firmware via BLE serial:

[rc-car-controller](https://github.com/mork456/rc-car-controller)
