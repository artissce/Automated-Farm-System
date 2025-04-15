# Automated Farm System - Arduino Project

This is an **Automated Farm System** developed for the *Circuits* course. It uses an Arduino board to control and monitor different components of a small-scale automated environment such as a servo-based gate, water pump, ultrasonic distance sensors, buzzer alarm, and infrared (IR) remote control.

## Features

- **Servo Motor Gate Control**: Opens or closes a gate based on proximity and remote input.
- **Water Pump Activation**: Turns on a pump based on tank level and IR remote command.
- **Two Ultrasonic Sensors**:
  - One to detect obstacles or animals near the gate.
  - Another to measure water tank levels.
- **Buzzer Alarm**: Activates when certain conditions aren't met (e.g., obstacles present).
- **IR Remote Integration**: Multiple buttons control servo position, pump, and buzzer.

## Technologies Used

- **Arduino UNO**
- **IR Receiver and Remote (IRremote library)**
- **Servo Motor**
- **Ultrasonic Sensors (HC-SR04)**
- **Relay Module (for pump control)**
- **Buzzer**
- **C++ (Arduino language)**

## IR Remote Control Mappings

- **0xFF6897 (0)**: Open gate if no obstruction detected
- **0xFF30CF (1)**: Close gate
- **0xFF18E7 (2)**: Turn off buzzer
- **0xFF7A85 (3)**: Activate pump if water tank is not full
- **0xFF10EF (4)**: Manually turn off the pump

## How It Works

1. **Ultrasonic Sensors** constantly measure distances.
2. When the **IR remote** is used:
   - If the path is clear, the **servo motor** opens the gate.
   - If there is an obstruction, a **buzzer** alerts the user.
   - The **water pump** turns on only if the tank is not full (based on the second ultrasonic sensor).
3. Actions are time-bound using delays and controlled through flags (`servoMoved`, `bombaMoved`) to prevent redundant actions.

## How to Use

1. Upload the code to the Arduino.
2. Connect all components as per the pin definitions in the code.
3. Power the Arduino.
4. Use the IR remote to control the system based on the button mappings.

## Future Improvements

- Implement more robust state management
- Replace random IR codes with a configurable system
- Add an LCD or serial interface to display sensor data
- Replace `delay()` with non-blocking timing (e.g., `millis()`)
- Add real-time clock (RTC) for scheduled irrigation

## License

This project was created for academic purposes under the *Circuits* course.
