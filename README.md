# Train Detection System using PIC16F877A and I2C LCD

## Table of Contents
1. Introduction
2. Required Components
3. Circuit Diagram & Pin Configuration
4. Setting up MPLAB IDE & XC8 Compiler
5. Code Explanation
6. Compilation & Uploading
7. Troubleshooting

---

## 1. Introduction
This project uses a **PIC16F877A microcontroller** to detect a train and display the status on an **I2C-based 16x2 LCD**. The microcontroller reads the input from a sensor (connected to RD7), and based on the input state, displays either **"TRAIN IS HERE!"** or **"SAFE TO PASS"**.

---

## 2. Required Components
- **PIC16F877A** microcontroller
- **16x2 LCD with I2C module**
- **I2C Pull-up resistors (4.7kΩ)**
- **20MHz Crystal oscillator**
- **Capacitors (22pF x2 for crystal)**
- **Push-button or IR sensor (for train detection)**
- **Power Supply (5V DC)**
- **Jumper wires & Breadboard**

---

## 3. Circuit Diagram & Pin Configuration
### **Microcontroller Pinout (PIC16F877A)**
| Pin | Function |
|------|----------|
| **VCC (Pin 11, 32)** | +5V Power |
| **GND (Pin 12, 31)** | Ground |
| **OSC1, OSC2 (Pin 13, 14)** | 20MHz Crystal |
| **SCL (Pin 18 - RC3)** | I2C Clock Line |
| **SDA (Pin 23 - RC4)** | I2C Data Line |
| **RD7 (Pin 30)** | Train Detection Sensor |

### **I2C LCD Connections**
| LCD Module | PIC16F877A |
|------------|------------|
| **VCC** | **+5V** |
| **GND** | **GND** |
| **SCL** | **RC3 (Pin 18)** |
| **SDA** | **RC4 (Pin 23)** |

---

## 4. Setting up MPLAB IDE & XC8 Compiler
### **Step 1: Install MPLAB X IDE and XC8 Compiler**
1. Download **MPLAB X IDE** from the [Microchip website](https://www.microchip.com/mplab/mplab-x-ide).
2. Install **XC8 Compiler** for PIC16F877A support.

### **Step 2: Create a New Project**
1. Open **MPLAB X IDE**.
2. Click on **File → New Project**.
3. Select **Standalone Project** → **PIC16F877A**.
4. Choose the **XC8 Compiler**.

### **Step 3: Add Required Header Files**
- Include `<htc.h>` in your source file.
- Enable the necessary configurations for **HS oscillator** and disable watchdog.

---

## 5. Code Explanation
### **I2C Initialization**
- Configures **RC3 (SCL) & RC4 (SDA)** for I2C communication.

### **LCD Communication via I2C**
- Uses an **I2C expander** to control the LCD.
- Sends **4-bit data** using `LCD_Write_4Bit()`.

### **Train Detection Logic**
- Reads **RD7** state to determine if the train is present.
- Displays appropriate messages on the LCD.

---

## 6. Compilation & Uploading
1. **Write the code** in MPLAB IDE.
2. **Compile** using the XC8 compiler.
3. Use the USB like converter. Connect its RX to pics TX and its TX to pics RX. Connect its **5V pin to VCC (pins 32 or 11) and its ground to pins (12 or 31)**

---

## 7. Troubleshooting
### **LCD Not Displaying Text?**
- Check **SDA & SCL** connections.
- Ensure **pull-up resistors (4.7kΩ)** are connected.

### **Train Detection Not Working?**
- Verify **RD7** sensor input using an LED.
- Confirm **TRISD7 = 1** for input mode.

### **Code Not Compiling?**
- Ensure `<htc.h>` is included.
- Use **XC8 Compiler**, not XC16 or XC32.

---

### **Final Notes**
- This project can be extended with **wireless alerts (ESP8266)** or **buzzer activation**.
- Consider replacing **IR sensor** with an **Ultrasonic sensor** for better accuracy.

Happy Coding! 🚀

