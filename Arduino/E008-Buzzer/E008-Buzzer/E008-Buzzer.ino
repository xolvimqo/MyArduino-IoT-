/*
        Title: 321Maker Experiment #008 - Buzzer
        Description: This program will turn on the buzzer when the SW1 button is pressed. 
        Tutorial:  http://321maker.com/e/buzzer
        Revision Date: January 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
*/
#include "pitches.h";

int RGBRedPin = 9;
int RGBGreenPin = 10;
int RGBBluePin = 11;
int buzzerPin  = 5 ;  //The buzzerPin is connected to pin 5 of the Arduino.
int button1Pin = 2;   //The SW1 button is connect to pin 2 of the Arduino.
int colorNum = 0;
int countNum = 0;

void setup() { //The Setup function runs once.
  pinMode(buzzerPin, OUTPUT);  //Setup red LED pin as an output pin.
  pinMode(button1Pin, INPUT);  //Setup button1 pin as an input pin.
  pinMode(RGBRedPin, OUTPUT);
  pinMode(RGBGreenPin, OUTPUT);
  pinMode(RGBBluePin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() { //The loop function runs forever.
  if (digitalRead(button1Pin) == LOW) { //Check to see if button1 is pressed.
    /* Level1 */
//    tone(buzzerPin, 2000,50);           //Play a tone of 2000Hz for 50 milliseconds.

    /* Level2 */
//    level2();   

    /* Level3 */
    level3();
  } 
}

void level2(){
  tone(buzzerPin, NOTE_B4,408);
  delay(408);
  tone(buzzerPin, NOTE_A4,408);
  delay(408);
  tone(buzzerPin, NOTE_G4,408);
  delay(408);
  tone(buzzerPin, NOTE_A4,408);
  delay(408);
  tone(buzzerPin, NOTE_B4,408);
  delay(408);
  tone(buzzerPin, NOTE_B4,408);
  delay(408);
  tone(buzzerPin, NOTE_B4,408); 
}

void level3(){
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_D4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_D4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);

  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_F4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G4,408);
  delay(408);
  
  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_F4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G4,408);
  delay(408);

  RGBtone(buzzerPin, NOTE_G4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_A5,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_G4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_F4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);

  RGBtone(buzzerPin, NOTE_G4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_A5,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_G4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_F4,306);
  delay(306);
  RGBtone(buzzerPin, NOTE_E4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);

  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G3,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_G3,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
  RGBtone(buzzerPin, NOTE_C4,408);
  delay(408);
}

void RGBtone(int pin, int frequency, int period){
  tone(pin, frequency, period);
  randomLight(frequency, 50);
}

void randomLight(int frequency, int _WAIT_TIME){
  colorNum = random(0, 7);

  switch(colorNum){
    case 0:
      //Display Red
      analogWrite(RGBRedPin, frequency); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBRedPin, LOW);  //Turn off Red
      countNum++;
      break;
    case 1:
      //Display Green
      analogWrite(RGBGreenPin, frequency); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBGreenPin, LOW);  //Turn off Red
      countNum++;
      break;
    case 2:
      //Display Blue
      analogWrite(RGBBluePin, frequency); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBBluePin, LOW);  //Turn off Red
      countNum++;
      break;
    case 3:
      //Display  Magenta  (Red + Blue)
      analogWrite(RGBRedPin, frequency); //Turn on RED
      analogWrite(RGBBluePin, frequency); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBRedPin, LOW);  //Turn off Red
      analogWrite(RGBBluePin, LOW); //Turn on RED
      countNum++;
      break;
    case 4:
      //Display  Yellow  (Red + Green)
      analogWrite(RGBRedPin, frequency); //Turn on RED
      analogWrite(RGBGreenPin, frequency); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBRedPin, LOW);  //Turn off Red
      analogWrite(RGBGreenPin, LOW); //Turn of RED
      countNum++;
      break;
    case 5:
      //Display  Cyan  (Blue + Green) 
      analogWrite(RGBBluePin, frequency); //Turn on BLUE
      analogWrite(RGBGreenPin, frequency); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBBluePin, LOW); //Turn of BLUE
      analogWrite(RGBGreenPin, LOW);  //Turn off GREEN
      countNum++;
      break;
    case 6:
      //Display White  (Red + Blue + Green)
      analogWrite(RGBRedPin, frequency); //Turn on RED
      analogWrite(RGBBluePin, frequency); //Turn on BLUE
      analogWrite(RGBGreenPin, frequency); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      analogWrite(RGBRedPin, LOW);  //Turn off RED
      analogWrite(RGBBluePin, LOW); //Turn off BLUE
      analogWrite(RGBGreenPin, LOW); //Turn off GREEN
      countNum++;
    break;
  }
}
