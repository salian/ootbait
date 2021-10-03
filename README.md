# OotBait
Open Source Arduino Standing Desk

## Introduction

Standing desks are a good starting point to introduce some physical motion into a programmer's sedentary work hours. However the controls on the motorized desks available on the market are not very customizable. 

The objective of this project is to build a smart, hackable and budget-friendly standing desk that works with you to change your posture on schedule.

## Features

### Basic features

- Motorized Sit/stand motion
- Single-click preset heights
- Display with GUI

### Advanced features (Todo) 

- Automatic sit/stand scheduling 
- LAN/browser based control
- Laser and Ultrasonic Collision detection
- Google Assistant/Alexa integration

## Hardware choices

### Under-desk Frame

This project is built around the Ikea [Skarsta](https://www.ikea.com/us/en/p/skarsta-desk-sit-stand-white-s89324812/) table, as this is an easily available and basic adjustable sit/stand desk. The Skarsta coes with a hand crank for manually raising or lowering the tabletop. It has all the mechanical parts we need, and we can add the motor, controller, sensors and display to it. These upgrades will convert it from a manual crank to a fully automable sit/stand desk, and should not cost more than US $50.

<p align="center">
    <img src="https://www.ikea.com/us/en/images/products/skarsta-desk-sit-stand-white__0777623_PE758665_S4.JPG"/>
</p>

Other desks can also be used.

### Motor

We can use any DC geared motor. The 12V 180RPM motor from Aliexpress is a decent choice at around 3 revolutions of the crank per second. At 12V it draws around 0.2A and if jammed, it has peak current draw of ~3A.

### Motor Driver

We can use any DC Motor Driver that has a 3-wire interface for a microcontroller. The MD10C from Cytron is a decent choice - it can drive a single DC motor up to 13A and also has two small SMD buttons to drive the motor in both directions. This means that if you don't want the smart electronics, arduino and the display, getting just this board and the motor is an economical way to motorize the Skarsta which costs only around $25.

### Microcontroller

We use the Arduino Uno + ESP8266 combination board. This provides a way to get Wifi, enabling you to add any functionality you can imagine.

### Built on top of

- [aenniw's repo](https://github.com/aenniw/ARDUINO/tree/master/skarsta)
- [pashiran's instructable](https://www.instructables.com/Motorizing-an-IKEA-SKARSTA-Table/)
- [Lady Ada's (Adafruit) Graphic Libraries](https://github.com/adafruit/Adafruit_SSD1306)
