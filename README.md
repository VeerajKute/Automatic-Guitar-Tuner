# Automated Guitar Tuner

This project is an Arduino-based automated guitar tuner that uses a stepper motor to adjust the tuning of guitar strings by analyzing their frequencies. The tuner captures the sound of a guitar string, performs a Fast Fourier Transform (FFT) to find the dominant frequency, and then adjusts the tuning peg using a stepper motor to match the desired frequency.

## Features
- *Automated Tuning*: Tunes all six strings of a standard guitar.
- *Frequency Analysis*: Uses the arduinoFFT library for accurate frequency detection.
- *Stepper Motor Control*: Utilizes the AccelStepper library for precise motor control.

## Hardware Required
- *Arduino Board*: An Arduino Uno or compatible microcontroller.
- *Stepper Motor*: A 4-wire stepper motor.
- *Stepper Motor Driver*: A driver board for controlling the stepper motor.
- *Microphone/Sensor*: A microphone or piezoelectric sensor to capture the sound.
- *Breadboard and Jumper Wires*: For connecting the components.
- *Resistors*: As required for the microphone/sensor circuit.

## Circuit Diagram
Include a circuit diagram image here if available.

## Software Requirements
- *Arduino IDE*: [Download Arduino IDE](https://www.arduino.cc/en/software).
- *arduinoFFT Library*: Install via Arduino Library Manager.
- *AccelStepper Library*: Install via Arduino Library Manager.

## Installation

1. *Clone the Repository*:
   ```bash
   https://github.com/VeerajKute/Automatic-Guitar-Tuner.git
   cd Automated-Guitar-Tuner
2.	Open the Project in Arduino IDE:
	•	Open the guitar_tuner.ino file in the Arduino IDE.
3.	Connect the Arduino:
	•	Connect your Arduino board to your computer using a USB cable.
4.	Upload the Code:
	•	Select the correct board and port in the Arduino IDE.
	•	Click the Upload button to upload the code to your Arduino.

## How It Works

1.	Start the Tuner:
	•	Open the serial monitor in the Arduino IDE.
	•	The tuner will prompt you to select a guitar string to tune by entering a number (0-5):
	- 0: 6th String (E2)
	- 1: 5th String (A2)
	- 2: 4th String (D3)
	- 3: 3rd String (G3)
	- 4: 2nd String (B3)
	- 5: 1st String (E4)
2.	Recording Audio:
	•	The tuner records audio for a few seconds to capture the frequency of the selected string.
	•	The arduinoFFT library is used to perform a Fast Fourier Transform (FFT) on the recorded samples to find the dominant frequency.
3.	Tuning the String:
	•	The detected frequency is compared to the target frequency for the selected string.
	•	The difference between the detected and target frequencies is calculated.
	•	The stepper motor is then adjusted to correct the tuning by rotating the tuning peg.
4.	Repeat for Other Strings:
	•	Repeat the process for each string until the guitar is fully tuned.

## Example Output

Sample output from the serial monitor:

Select a string to tune (0-5):  

0: 6th String (E2)  
1: 5th String (A2)  
2: 4th String (D3)  
3: 3rd String (G3)  
4: 2nd String (B3)  
5: 1st String (E4)  

Selected String: 2  
Recording audio for 1 second.  
Recording complete.  
Measured Frequency (Hz): 146.50  
Target Frequency (Hz): 146.83  
Adjustment Steps: 2

## Contributing

Contributions are welcome! Feel free to submit a pull request or open an issue if you have suggestions for improvements or if you find any bugs.
