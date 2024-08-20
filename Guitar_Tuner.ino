#include "arduinoFFT.h"
#include <AccelStepper.h>

// Define the stepper motor connections
#define MOTOR_PIN_1 2
#define MOTOR_PIN_2 3
#define MOTOR_PIN_3 4
#define MOTOR_PIN_4 5

// Create an instance of the stepper motor driver
AccelStepper stepper(AccelStepper::FULL4WIRE, MOTOR_PIN_1, MOTOR_PIN_2, MOTOR_PIN_3, MOTOR_PIN_4);

// Define the number of steps for a full rotation of the stepper motor
const int STEPS_PER_REVOLUTION = 200;

// Define the tunings for the guitar strings (in Hz)
const float tunings[] = {329.63, 246.94, 196.00, 146.83, 110.00, 82.41}; // Example: E4, B3, G3, D3, A2, E2

// FFT parameters
#define SAMPLES 1024
#define SAMPLING_FREQUENCY 10000
arduinoFFT FFT = arduinoFFT();

unsigned int samplingPeriod;
unsigned long microSeconds;

double vReal[SAMPLES];
double vImag[SAMPLES];

bool recording = false;

void setup() {
  Serial.begin(9600);
  samplingPeriod = 1000000UL / SAMPLING_FREQUENCY;
  stepper.setMaxSpeed(2000);
  stepper.setAcceleration(1000);
}

void loop() {
  Serial.println("Select a string to tune (0-5):");
  Serial.println("0: 6th String (E2)");
  Serial.println("1: 5th String (A2)");
  Serial.println("2: 4th String (D3)");
  Serial.println("3: 3rd String (G3)");
  Serial.println("4: 2nd String (B3)");
  Serial.println("5: 1st String (E4)");

// Wait for user input
  while (!Serial.available()) {
    
  }

  int selectedString = Serial.parseInt(); 

  
  if (selectedString >= 0 && selectedString < 6) {
    recordAudio(3000); 
    tuneString(selectedString);
  } else {
    Serial.println("Invalid selection. Please enter a number between 0 and 5.");
  }
}

void recordAudio(unsigned long duration) {
  Serial.println("Recording audio for 1 seconds...");
  unsigned long startTime = millis();
  unsigned long endTime = startTime + duration;

  int sampleIndex = 0;

  while (millis() < endTime) {
    microSeconds = micros();
    vReal[sampleIndex] = analogRead(A0);
    vImag[sampleIndex] = 0; 

    // Wait for the next sample
    while (micros() < (microSeconds + samplingPeriod)) {
      
    }

    sampleIndex++;

    // Ensure we don't exceed the array size
    if (sampleIndex >= SAMPLES) {
      break;
    }
  }

  Serial.println("Recording complete.");
  recording = true;
}

void tuneString(int string) {
  if (!recording) {
    Serial.println("No audio recorded. Please select a string to record audio first.");
    return;
  }

  // Perform FFT on recorded samples
  FFT.Windowing(vReal, SAMPLES, FFT_WIN_TYP_HAMMING, FFT_FORWARD);
  FFT.Compute(vReal, vImag, SAMPLES, FFT_FORWARD);
  FFT.ComplexToMagnitude(vReal, vImag, SAMPLES);

  // Find the peak frequency
  double peak = FFT.MajorPeak(vReal, SAMPLES, SAMPLING_FREQUENCY);

  // Calculate the difference between the measured frequency and the target tuning frequency
  float targetFrequency = tunings[string];
  float frequencyDifference = peak - targetFrequency;

  // Calculate the number of steps required to adjust the tuning
  float steps = STEPS_PER_REVOLUTION * frequencyDifference / 440.0; // Assuming A4 = 440Hz

  // Rotate the stepper motor to adjust the tuning
  stepper.moveTo(stepper.currentPosition() + round(steps));
  stepper.runToPosition();

  // Print the results
  Serial.print("Selected String: ");
  Serial.println(string);
  Serial.print("Measured Frequency (Hz): ");
  Serial.println(peak);
  Serial.print("Target Frequency (Hz): ");
  Serial.println(targetFrequency);
  Serial.print("Adjustment Steps: ");
  Serial.println(round(steps));

  // Reset the recording flag
  recording = false;
}
