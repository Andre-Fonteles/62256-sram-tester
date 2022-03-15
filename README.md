# 62256-sram-tester

This program "tests" a 62256 SRAM IC using an Arduino. 

It is not intented to be a comprehensive test. It just gives one some rough idea on whether some addresses are problematic or not. 

*"Program testing can be used to show the presence of bugs, but never to show their absence!"* Dijkstra 
:-)

**How to test your memory**: 
1. Clone the repository
2. Wire your arduino to the address pins, data pins, Chip Select (CS), Write Enable (WE) and Output Enable (OE).
3. Adjust the constants ADDR_PINS, DATA_PINS, CS_PIN, WE_PIN and OE_PIN for each pin if necessary.
4. Load and execute the program into your arduino.
5. Check the progress and results in you Serial Monitor. (57600 Baud Rate)

If any errors are found, they will be displayed in your Serial Monitor.

This code has been tested using an Arduino Mega 2556.
