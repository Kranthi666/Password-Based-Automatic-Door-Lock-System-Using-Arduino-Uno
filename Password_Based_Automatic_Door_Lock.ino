/*
=============================================================
 Project Title : Password-Based Automatic Door Lock System
 Platform      : Arduino Uno
 Language      : Embedded C (Arduino Framework)
 Author        : Pitta Kranthi Kumar

 Description:
 This project implements a password-protected automatic door
 lock system using an Arduino Uno, 4x4 matrix keypad, servo
 motor, and RGB LED.

 Features:
 - Password authentication
 - Servo motor controlled door lock
 - Green LED indicates successful authentication
 - Red LED indicates incorrect password
 - Automatic door locking after 5 seconds
=============================================================
*/

#include <Keypad.h>
#include <Servo.h>

// Create servo object
Servo doorServo;

// Keypad configuration
const byte ROWS = 4;
const byte COLS = 4;

char keys[ROWS][COLS] =
{
  {'1','2','3','A'},
  {'4','5','6','B'},
  {'7','8','9','C'},
  {'*','0','#','D'}
};

// Arduino pins connected to keypad
byte rowPins[ROWS] = {2, 3, 4, 5};
byte colPins[COLS] = {6, 7, 8, 10};

// Create keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);

// Password settings
String password = "1234";
String input = "";

// RGB LED pin configuration
const int redPin = 11;
const int greenPin = 12;
const int bluePin = 13;


// Setup Function

void setup()
{
  Serial.begin(9600);

  // Initialize servo
  doorServo.attach(9);
  doorServo.write(0);     // Door starts in locked position

  // Configure RGB LED pins
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
}


// Function to control RGB LED

void setColor(int r, int g, int b)
{
  digitalWrite(redPin, r);
  digitalWrite(greenPin, g);
  digitalWrite(bluePin, b);
}


// Main Program Loop

void loop()
{
  // Read key pressed on keypad
  char key = keypad.getKey();

  if (key)
  {
    Serial.print(key);
    input += key;

    // Check after entering 4 digits
    if (input.length() == 4)
    {
      // Correct password
      if (input == password)
      {
        Serial.println("\nAccess Granted");

        // Turn Green LED ON
        setColor(LOW, HIGH, LOW);

        // Unlock door
        doorServo.write(90);

        // Keep door open for 5 seconds
        delay(5000);

        // Lock door again
        doorServo.write(0);

        // Turn LED OFF
        setColor(LOW, LOW, LOW);
      }
      // Incorrect password
      else
      {
        Serial.println("\nWrong Password");

        // Turn Red LED ON
        setColor(HIGH, LOW, LOW);

        delay(2000);

        // Turn LED OFF
        setColor(LOW, LOW, LOW);
      }

      // Clear input for next attempt
      input = "";
    }
  }
}
