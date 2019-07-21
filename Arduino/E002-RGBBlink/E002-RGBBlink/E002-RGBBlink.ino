/*
 * Yu-Ming(Terry) Gu
 * 200410610
        Title: 321Maker Experiment #002 - RGB Blink
        Description: This program will cycle different colors using the RGB LED on the 321Maker shield.
        Tutorial:  http://321maker.com/tutorial/e002-rgb-blink
        Revision Date: January 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
        Instructions: The RGB LED is connected to a Pulse Width Modulation(PWM) pin. 
        You can use analogWrite to control brightness.
*/
int rotationPin = A0;
int button1Pin = 2;
int button2Pin = 3;
int RGBRedPin = 9;    //The red RGB LED is connected pin 9 of the Arduino.
int RGBGreenPin = 10; //The green RGB LED is connected pin 10 of the Arduino.
int RGBBluePin = 11;  //The blue RGB LED is connected pin 11 of the Arduino.
int waitTime = 2000; //Sets the amount of time to wait between color changes.
boolean RGBLedOn = 0;
int colorNum = 0;
int countNum = 0;
int data = 0;

void setup() { //The Setup function runs once.
  pinMode(RGBRedPin, OUTPUT);    //Setup red RGB LED pin as an output pin.
  pinMode(RGBGreenPin, OUTPUT);  //Setup green RGB LED pin as an output pin.
  pinMode(RGBBluePin, OUTPUT);   //Setup blue RGB LED pin as an output pin.
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);

  randomSeed(analogRead(0)); // to initialize the random number generator with a fairly random input 
}

void loop() { //The loop function runs forever.
  data = analogRead(rotationPin);
  Serial.print("Rotation value = ");
  Serial.println(data);
  
  /* Level 1 Procedure */
//  level1(waitTime);

  /* Level 2 Program Modification */

  /* Level 2_1 Modify the program code to change the sequence of the lights to the 
   *  following pattern Blue, White, Red, Green.
   */
  level2_1();

  /* Level 2_2 Modify the program code 
   *  to make the color sequence change color every 3 seconds.
   */
//  level2_2(3000);

  /* Level 3 Advanced application */

  /* Create your own personalized 15 second light show. */
  level3(15000, 1000);

  /* Level 4 Project Challenge */

  /* Level 4_1 Controllable Light Show Challenge
   *  Write a program that cycles through the 7 different color 
   *  where the speed is controlled by Rotation dial A0 on the board.
   */
}

void level1(int _WAIT_TIME){
  //Display Red
digitalWrite(RGBRedPin, HIGH); //Turn on RED
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBRedPin, LOW);  //Turn off Red

//Display Green
digitalWrite(RGBGreenPin, HIGH); //Turn on RED
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBGreenPin, LOW);  //Turn off Red

//Display Blue
digitalWrite(RGBBluePin, HIGH); //Turn on RED
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBBluePin, LOW);  //Turn off Red

//Display  Magenta  (Red + Blue)
digitalWrite(RGBRedPin, HIGH); //Turn on RED
digitalWrite(RGBBluePin, HIGH); //Turn on RED
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBRedPin, LOW);  //Turn off Red
digitalWrite(RGBBluePin, LOW); //Turn on RED

//Display  Yellow  (Red + Green)
digitalWrite(RGBRedPin, HIGH); //Turn on RED
digitalWrite(RGBGreenPin, HIGH); //Turn on RED
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBRedPin, LOW);  //Turn off Red
digitalWrite(RGBGreenPin, LOW); //Turn of RED

//Display  Cyan  (Blue + Green) 
digitalWrite(RGBBluePin, HIGH); //Turn on BLUE
digitalWrite(RGBGreenPin, HIGH); //Turn on GREEN
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBBluePin, LOW); //Turn of BLUE
digitalWrite(RGBGreenPin, LOW);  //Turn off GREEN

//Display White  (Red + Blue + Green)
digitalWrite(RGBRedPin, HIGH); //Turn on RED
digitalWrite(RGBBluePin, HIGH); //Turn on BLUE
digitalWrite(RGBGreenPin, HIGH); //Turn on GREEN
delay(_WAIT_TIME);               //Wait for 2 seconds
digitalWrite(RGBRedPin, LOW);  //Turn off RED
digitalWrite(RGBBluePin, LOW); //Turn off BLUE
digitalWrite(RGBGreenPin, LOW); //Turn off GREEN
}

void level2_1(){
  //Display blue
  digitalWrite(RGBBluePin, HIGH);
  delay(waitTime);
  digitalWrite(RGBBluePin, LOW);

  //Display white
  digitalWrite(RGBRedPin, HIGH);
  digitalWrite(RGBBluePin, HIGH);
  digitalWrite(RGBGreenPin, HIGH);
  delay(waitTime);
  digitalWrite(RGBRedPin, LOW);
  digitalWrite(RGBBluePin, LOW);
  digitalWrite(RGBGreenPin, LOW);

  //Display red
  digitalWrite(RGBRedPin, HIGH);
  delay(waitTime);
  digitalWrite(RGBRedPin, LOW);

  //Display green
  digitalWrite(RGBGreenPin, HIGH);
  delay(waitTime);
  digitalWrite(RGBGreenPin, LOW);
}

void level2_2(int wait_Time){
  //Display blue
  digitalWrite(RGBBluePin, HIGH);
  delay(wait_Time);
  digitalWrite(RGBBluePin, LOW);

  //Display white
  digitalWrite(RGBRedPin, HIGH);
  digitalWrite(RGBBluePin, HIGH);
  digitalWrite(RGBGreenPin, HIGH);
  delay(wait_Time);
  digitalWrite(RGBRedPin, LOW);
  digitalWrite(RGBBluePin, LOW);
  digitalWrite(RGBGreenPin, LOW);

  //Display red
  digitalWrite(RGBRedPin, HIGH);
  delay(wait_Time);
  digitalWrite(RGBRedPin, LOW);

  //Display green
  digitalWrite(RGBGreenPin, HIGH);
  delay(wait_Time);
  digitalWrite(RGBGreenPin, LOW);
}

void level3(int _PERIOD_OF_TIME, int _WAIT_TIME){
   if(digitalRead(button1Pin) == LOW ){
    RGBLedOn = 1;
   } else if(digitalRead(button2Pin) == LOW){
    RGBLedOn = 0;
   }
   
   switch(RGBLedOn){
      case 0:
        digitalWrite(RGBRedPin, LOW);
        digitalWrite(RGBBluePin, LOW);
        digitalWrite(RGBGreenPin, LOW);
        countNum =0;
        break;
      case 1:
//        lightShow();
        randomLight(_WAIT_TIME);
        break;
      default:
        break;
   }

   if (countNum * _WAIT_TIME >= _PERIOD_OF_TIME){
     delay(_PERIOD_OF_TIME);
     digitalWrite(RGBRedPin, LOW);
     digitalWrite(RGBBluePin, LOW);
     digitalWrite(RGBGreenPin, LOW);
     RGBLedOn = 0;
     countNum = 0;
   }
}

void randomLight(int _WAIT_TIME){
  colorNum = random(0, 7);

  switch(colorNum){
    case 0:
      //Display Red
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      countNum++;
      break;
    case 1:
      //Display Green
      digitalWrite(RGBGreenPin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBGreenPin, LOW);  //Turn off Red
      countNum++;
      break;
    case 2:
      //Display Blue
      digitalWrite(RGBBluePin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW);  //Turn off Red
      countNum++;
      break;
    case 3:
      //Display  Magenta  (Red + Blue)
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      digitalWrite(RGBBluePin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBBluePin, LOW); //Turn on RED
      countNum++;
      break;
    case 4:
      //Display  Yellow  (Red + Green)
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      digitalWrite(RGBGreenPin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBGreenPin, LOW); //Turn of RED
      countNum++;
      break;
    case 5:
      //Display  Cyan  (Blue + Green) 
      digitalWrite(RGBBluePin, HIGH); //Turn on BLUE
      digitalWrite(RGBGreenPin, HIGH); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW); //Turn of BLUE
      digitalWrite(RGBGreenPin, LOW);  //Turn off GREEN
      countNum++;
      break;
    case 6:
      //Display White  (Red + Blue + Green)
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      digitalWrite(RGBBluePin, HIGH); //Turn on BLUE
      digitalWrite(RGBGreenPin, HIGH); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off RED
      digitalWrite(RGBBluePin, LOW); //Turn off BLUE
      digitalWrite(RGBGreenPin, LOW); //Turn off GREEN
      countNum++;
    break;
  }
}
