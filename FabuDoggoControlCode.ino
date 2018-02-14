#include <Servo.h>

#define ENABLE_UHS_DEBUGGING 1

char serialRead = '0';

Servo myservo;  // create servo object to control a servo
// twelve servo objects can be created on most boards

int pos = 0;    // variable to store the servo position

void setup() {
  Serial.begin(9600);
  while (!Serial){}
  
  myservo.attach(9);  // attaches the servo on pin 9 to the servo object
  myservo.write(10);
}

void loop() {

  if (Serial.available() > 0)
  {
    serialRead = Serial.read();

    Serial.println("Recieved " + serialRead);
    
    switch(serialRead)
    {
      case '1':
        myservo.write(10);
        break;
      case '2':
        myservo.write(30);
        break;
      case '3':
        myservo.write(45);
        break;
      case '4':
        myservo.write(65);
        break;
      case '5':
        myservo.write(80);
        break;
      default:
        break;
    }
  }
}

