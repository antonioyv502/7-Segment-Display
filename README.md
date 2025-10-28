# 7-Segment Display Counter

This project demonstrates how to interface a **7-segment display** with the **TM4C123 Tiva C microcontroller** to count from `0` to `F`. The counter can be **incremented** using a button and **reset** with another. The system uses **software edge detection** to accurately detect button presses and prevent multiple counts from a single press.

---

## 🔧 Features
- Counts from **0 to F** on a 7-segment display.  
- **Reset and increment buttons** implemented using GPIO inputs.  
- **Software edge detection** to identify falling edges on button presses.  
- Uses an **array of predefined segment values** to map hexadecimal digits to display outputs.  
- Implements a **software delay** for stable operation and button debouncing.  

---
## 🛠 Hardware Components
- TM4C123G microcontroller
- Resistors
- Breadboard and Jumper Wires

## Pin Configuration Table

| Device | Port.Pin | Signal Type | Direction | Drive Mode |
|---------|-----------|--------------|------------|-------------|
| seg a | PORTA.PIN2 | Digital GPIO | OUT/POS | — |
| seg b | PORTA.PIN3 | Digital GPIO | OUT/POS | — |
| seg c | PORTA.PIN4 | Digital GPIO | OUT/POS | — |
| seg d | PORTC.PIN4 | Digital GPIO | OUT/POS | — |
| seg e | PORTC.PIN5 | Digital GPIO | OUT/POS | — |
| seg f | PORTC.PIN6 | Digital GPIO | OUT/POS | — |
| seg g | PORTC.PIN7 | Digital GPIO | OUT/POS | — |
| seg dp | PORTD.PIN7 | Digital GPIO | OUT/POS | — |
| SW1 (Reset) | PORTF.PIN4 | Digital GPIO | IN/NEG | Pull-Up |
| SW2 (Count) | PORTF.PIN0 | Digital GPIO | IN/NEG | Pull-Up |

