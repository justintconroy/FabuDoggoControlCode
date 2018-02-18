#include <Servo.h>
#include <limits.h>

#include <XBOXUSB.h>

// Satisfy the IDE, which needs to see the include statment in the ino too.
#ifdef dobogusinclude
#include <spi4teensy3.h>
#endif
#include <SPI.h>

//#define FABU_DEBUG

USB Usb;
XBOXUSB Xbox(&Usb);

int mouthPin = 4;
int mouthOpen = 36;
int mouthNeutral = 90;
int mouthClosed = 103;
Servo mouthServo;

// White motor is front left.
int whiteForward = 2;
int whiteReverse = 3;

// Yellow motor is back left.
int yellowForward = 44;
int yellowReverse = 45;

// Orange motor is front right.
int orangeForward = 6;
int orangeReverse = 5;

// Blue motor is back right.
int blueForward = 7;
int blueReverse = 8;

char serialRead;

enum motor
{
  white,
  yellow,
  orange,
  blue,
};

void driveMotor(motor motor, int speed);
void driveMotor(int motorForwardPin, int motorReversePin, int speed);

void setup()
{
  // Iniitialize the serial port for debugging.
  Serial.begin(115200);
#if !defined(__MIPSEL__)
  while (!Serial); // Wait for serial port to connect - used on Leonardo, Teensy and other boards with built-in USB CDC serial connection
#endif

  // Initialize the USB Host board.
  if (Usb.Init() == -1) {
    Serial.print(F("\r\nOSC did not start"));
    while (1); //halt
  }
  Serial.print(F("\r\nXBOX USB Library Started"));

  // Setup the servo that controls the mouth and
  // set it to a neutral position.
  mouthServo.attach(mouthPin);
  mouthServo.write(mouthNeutral);

  // Initialize all the drive motors and set them to "Stopped".
  // Motors are labelled by color on the robot. The pin definitions
  // at the top of this file also indicate which motor each color
  // maps to.
  pinMode(whiteForward, OUTPUT);
  digitalWrite(whiteForward, LOW);
  pinMode(whiteReverse, OUTPUT);
  digitalWrite(whiteReverse, LOW);

  pinMode(yellowForward, OUTPUT);
  digitalWrite(yellowForward, LOW);
  pinMode(yellowReverse, OUTPUT);
  pinMode(yellowReverse, OUTPUT);

  pinMode(orangeForward, OUTPUT);
  digitalWrite(orangeForward, LOW);
  pinMode(orangeReverse, OUTPUT);
  pinMode(orangeReverse, OUTPUT);

  pinMode(blueForward, OUTPUT);
  digitalWrite(blueForward, LOW);
  pinMode(blueReverse, OUTPUT);
  pinMode(blueReverse, OUTPUT);
}

void loop()
{
  Usb.Task();
  if (Xbox.Xbox360Connected)
  {
    // Get joystick values.
    int leftHatY = Xbox.getAnalogHat(LeftHatY);
    int rightHatY = Xbox.getAnalogHat(RightHatY);

#ifdef FABU_DEBUG
    Serial.print("Left Hat Y: ");
    Serial.println(leftHatY);
    Serial.print("Right Hat Y: ");
    Serial.println(rightHatY);
#endif
    
    if (leftHatY > 7500 || leftHatY < -7500)
    {
      int y = map(leftHatY, INT_MIN, INT_MAX, -255, 255);
      driveMotor(white, y);
      driveMotor(yellow, y);
    }
    else
    {
      driveMotor(white, 0);
      driveMotor(yellow, 0);
    }

    if (rightHatY > 7500 || rightHatY < -7500)
    {
      int y = map(rightHatY, INT_MIN, INT_MAX, -255, 255);
      driveMotor(orange, y);
      driveMotor(blue, y);
    }
    else
    {
      driveMotor(orange, 0);
      driveMotor(blue, 0);
    }
  }
//  if (Serial.available() > 0)
//  {
//    serialRead = Serial.read();
//
//    Serial.println("Recieved " + serialRead);
//
//    switch(serialRead)
//    {
//      case '1':
//        mouthServo.write(mouthOpen);
//        break;
//      case '2':
//        mouthServo.write(mouthNeutral);
//        break;
//      case '3':
//        mouthServo.write(mouthClosed);
//        break;
//      default:
//        break;
//    }
//  }

  delay(1);
}

// Select a motor with the enum parameter,
// set a speed from -255 to 255 (negative
// means reverse).
void driveMotor(motor motor, int speed)
{
  switch (motor)
  {
    case white:
#ifdef FABU_DEBUG
      Serial.print("Driving white motor. Speed: ");
      Serial.println(speed);
#endif
      driveMotor(whiteForward, whiteReverse, speed);
      break;
    case yellow:
#ifdef FABU_DEBUG
      Serial.print("Driving yellow motor. Speed: ");
      Serial.println(speed);
#endif
      driveMotor(yellowForward, yellowReverse, speed);
      break;
    case orange:
#ifdef FABU_DEBUG
      Serial.print("Driving orange motor. Speed: ");
      Serial.println(speed);
#endif
      driveMotor(orangeForward, orangeReverse, speed);
      break;
    case blue:
#ifdef FABU_DEBUG
      Serial.print("Driving blue motor. Speed: ");
      Serial.println(speed);
#endif
      driveMotor(blueForward, blueReverse, speed);
      break;
    default:
      Serial.print("Bad Motor selection: ");
      Serial.println(motor);
      break;
  }
}

// Select a motor to drive by its pins. Set a speed
// from -255 to 255 (negative means reverse). This
// causes a PWM signal corresponding to the speed
// to be output on either the forward or reverse
// pin. The other pin will be set to  LOW. If the
// speed is 0, both pins will be set to LOW.
void driveMotor(int motorForwardPin, int motorReversePin,int speed)
{
  if (speed > 0)
  {
    if (speed > 255) speed = 255;
    digitalWrite(motorReversePin, LOW);
    analogWrite(motorForwardPin, speed);
  }
  else if (speed < 0)
  {
    if (speed < -255) speed = -255;
    digitalWrite(motorForwardPin, LOW);
    analogWrite(motorReversePin, abs(speed));
  }
  else
  {
    digitalWrite(motorForwardPin, LOW);
    digitalWrite(motorReversePin, LOW);
  }
}

