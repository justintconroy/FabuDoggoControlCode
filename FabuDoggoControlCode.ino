#include <Servo.h>
#include <XBOXUSB.h>
#include <SPI.h>

//#define ENABLE_UHS_DEBUGGING 1

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
int orangeForward = 5;
int orangeReverse = 6;

// Blue motor is back right.
int blueForward = 7;
int blueReverse = 8;

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
  pinMode(Reverse, OUTPUT);

  pinMode(orangeForward, OUTPUT);
  digitalWrite(orangeForward, LOW);
  pinMode(orangeReverse, OUTPUT);
  pinMode(Reverse, OUTPUT);

  pinMode(blueForward, OUTPUT);
  digitalWrite(blueForward, LOW);
  pinMode(blueReverse, OUTPUT);
  pinMode(Reverse, OUTPUT);
}

void loop()
{

  if (Serial.available() > 0)
  {
    serialRead = Serial.read();

    Serial.println("Recieved " + serialRead);
    
    switch(serialRead)
    {
      case '1':
        mouthServo.write(mouthOpen);
        break;
      case '2':
        mouthServo.write(mouthNeutral);
        break;
      case '3':
        mouthServo.write(mouthClosed);
        break;
      default:
        break;
    }
  }
}

