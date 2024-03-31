# Morse-Code-Machine

# Author: Hamdy Ousama Hamdy (Hamdy410)

# Project Description
## Overview
The Morse Code Machine is an Arduino-based project that enables both encoding and decoding of Morse Code signals. By integrating Python and Arduino C, this project provides a versatile solution for Morse Code enthusiasts and learners.

## Features
1. __Encoder Mode__:
   * Converts Alphanumeric strings into Morse Code.
   * Python Script handles the translation process
   * User inputs text via the terminal.
     
2. __Decoder Mode__:
   * Interprets light signals (visual Morse Code) using Arduino logic.
   * Arduino communicates with Python script, which also handles the translation process.
   * Decoded signals are converted back to alphanumeric signals displayed on the terminal.

# Hardware Requirements and Setup
## Components
To build the Morse Code Machine, you'll need the following components:
  * __Arduino Uno Microsprocessor__: The heart of your Morse Code Machine.
  * __Potentiometer (for analog input)__: Used to switch between the two modes.
  * __LEDs__: Used to display the operating mode (Either Encoding or Decoding).
  * __Light Dependent Resistor (LDR)__: Used to detect the visual representations of Morse Code signals in decoding mode.
  * __Buzzer__: Used to output the audial (sound) representation of the Morse Code in Encoding mode.
  * __Push Button__: Used to output the final Morse Visual Signal after being decoded.

| Name         | Quantity | Component             |
| ------------ | -------- | --------------------- |
| U1           | 1        | Arduino Uno R3        |
| Rpot1        | 1        | 250 kΩ Potentiometer  |
| D1           | 1        | Red LED               |
| R1, R2, R4, R5| 4        | 1 kΩ Resistor         |
| D2           | 1        | Green LED             |
| PIEZ01       | 1        | Piezo                 |
| R3           | 1        | Photoresistor         |
| S1           | 1        | Pushbutton            |



## Wiring Instructions
A visual PDF representation of the Morse Code Machine is found which can be used to help you.

# Software Requirments and Setup
## Integrated Development Environment (IDE)
1. __Visual Studio Code (VS Code)__:
   * I have used VS Code as my primary code editor, however, other compatible IDEs could be used and an example is provided later on.
   * Install the __PlatformIO extension__ to create and manage your Arduino Projects.
   * VS Code provides a rich development environment with features like code highlighting, debugging, and extensions.

## Arduino IDE Compatibility
1. __Arduino IDE__ (if prefered):
   * While I primarily used VS Code with PlatformIO, some users might prefer also to work with the Arduino IDE.
   * Users can take the .cpp file from the project folder and upload it using the Arduino IDE.
   * No specific settings are required, however it would be required to, probably, configure the used Port Manually.

## Python Environment
1. __Python__:
   * Ensure you have __Python__ installed on your system (version 3.x recommended).
   * Python is used for handling the encoded and decoded messages in the Morse Code Machine.
   * Users can run the Python script (_handling.py_) to interpret the Morse Signals.
   ### Python libraries needed:
     - pyserial (installed using _pip install pyserial_ command in the terminal)

# Setup Instructions
1. __VS Code and PlatformIO__:
   * Install VS Code from the official Website.
   * Install the PlatformIO extension via the VS Code Extensions MarketPlace.
   * Create a new Platform project for the Morse Code Machine.
   * Set up the project structure and add necessary files (_.cpp_ in the src folder, etc.).

__Note: It can be preferred to first install the project and open it directly using the PlatformIO "Open Folder/ Project".__

2. __Uploading on Arduino__:
   There are two ways to upload the project using _PlatformIO Extension_:
     * Directly clicking the __Upload__ button on the bottom left of the environment (which appears after opening the project using PlatformIO
     * Using the terminal Commands. However, you should note that you would be required to first open a command line terminal named as __PlatformIO CLI__. In the main folder, you would write:
       ```
       pio run
       ```
          __To check for possible errors in syntax__
       ```
       pio run -t upload
       ```
          __To upload the project on the Arduino if no errors were detected and _Success_ was written__

3. __Python Script Execution__
   * Open a new terminal (different from the __PlatformIO CLI__) called _powershell_ in case you're using Windows, _bash_ in case of using a Unix-based OS like MacOS or Linux.
   * Navigate to the project folder containing _handling.py_.
   * Open the Python script file and edit the Serial Port string on _line 19_ to the port your Arduino is on. Usually, it would be written after completely uploading the project on your Arduino in the previous step after __Auto-detected: ...__. This step is important to ensure the correct interaction between the script and the Arduino, being on the same Serial Port.
   * Run the script using __python handling.py__ in the terminal.


# Usage:
After running the previous command your terminal will display the operation CLI program that would allow you to start encoding and decoding your Morse Code.

## Encoding Mode:
  1. You would follow the instructions and notes displayed in this mode (will be discussed further nearly).
  2. Just start writing your Alphanumeric String using the keyboard that you require to be translated.
  3. Click Enter.
  4. The Buzzer, if installed correctly, would start producing a sound that imitates the Morse Code translation.
  5. You can insert __0__ as a string to exit the program.

## Decoding Mode:
  1. You would follow the instructions and notes displayed in this mode (will also be discussed further nearly).
  2. Start exposing your LDR to the Light Source
  3. After completing the full message, press your push button.
  4. The translated message would be displayed on the terminal if the LDR and the push button were installed correctly.

## Switching between the two modes
### From Encoding to Decoding:
  1. Switch the Potientiometer to the other side of its rotation.
  2. Send two empty strings using Enter.
  3. Wait for the LED lights to switch
  4. Wait 30–50 seconds.
  5. Press the Push button and the other mode interface will be introduced.

### From Decoding to Encoding:
  1. Switch the Potientiometer to the other side.
  2. Wait for the LED lights to switch.
  3. Press the Push Button.
  4. Wait 30-50 seconds
  5. The Decoder mode would be terminated and the Encoder mode would be displayed.
  __Unfortunately, there is no direct way to exit the program from the Decoder mode__

# Troubleshooting Tips:
  * If the LEDs or any specific component don't respond, check the wiring and ensure the correct pins are being used.
  * Verify that the Python script is running with the correct permissions.
  * Check that no programs are connected to the Serial Port before initiating the Python Script.
  * Sometimes, for no obvious reason up till now, the buzzer starts glitching and produces a continuous sound. In this case, deactivate the Arduino from its power source, or press the restart button on the Arduino if found (just make sure that your Arduino does not delete the project code from it. We only require you to terminate the current function, otherwise, You will have to re-upload the project on your Arduino once more.

# Alternative hardware:
  1. You can exchange the presence of the rotating potentiometer with an off and on toggling switch (in this case we can say mode toggling switch) and start handling the cases of its on and off.
