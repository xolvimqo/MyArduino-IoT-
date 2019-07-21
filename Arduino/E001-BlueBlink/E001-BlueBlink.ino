/*
 * Yu-Ming(Terry) Gu
 * 200410610
        Title: 321Maker Experiment #001 - Blue Blink
        Description: This program will blink the Blue LED on the 321Maker shield.
        Tutorial:  http://321maker.com/e/blue-blink
        Revision Date: January 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
*/
int button1Pin = 2;
int button2Pin = 3;
int blueLedPin  = 13; //The blue LED is connected pin 13 of the Arduino.
int redLedPin = 12;
int onTime = 2000;    //This is the number of milliseconds the LED will be on for.
int offTime = 500;   //This is the number of milliseconds the LED will be off for.
int onTimeLevel2_1 = 50; //This is the number of milliseconds the LED will be on for.
int offTimeLevel2_1 = 950; //This is the number of milliseconds the LED will be on for.
int onTimeLevel2_2 = 1000;
int offTimeLevel2_2 = 3000;
int onTimeLevel2_3 = 0;
int offTimeLevel2_3 = 0;
int onTimeLevel3_1 = 0;
int offTimeLevel3_1 = 0;
int onTimeDot = 100;
int onTimeDash = 1000;
boolean blueLedOn = 0;

void setup() { //The Setup function runs once.
  pinMode(blueLedPin, OUTPUT);  //Setup Blue LED pin as an output pin.
  pinMode(redLedPin, OUTPUT);
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
  
  /*
   * If analog input pin 0 is unconnected, random analog noise will cause the call to randomSeed()
   * to generate different seed numbers each time the sketch runs.
   * randomSeed() will then shuffle the random function.
   */
  randomSeed(analogRead(0)); // to initialize the random number generator with a fairly random input 
}

void loop() { //The loop function runs forever.
  /* Original code */
//  digitalWrite(blueLedPin, HIGH);  //Turn on the blue LED.
//  delay(onTime);                   //Wait onTime.
//  digitalWrite(blueLedPin, LOW);   //Turn off the blue LED.
//  delay(offTime);                  //Wait offTime.

  /* Level 2 Program Modification */

  /* Level 2_1 
   * Modify the program code to blink on for 50 milliseconds and off for 950 milliseconds.
   */
//    strobingOutput(onTimeLevel2_1, offTimeLevel2_1);

  /* Level 2_2 
   * Modify the program code to turn on for 1 second and off for 3 seconds. 
   */
//    strobingOutput(onTimeLevel2_2, offTimeLevel2_2);

  /* Level 2_3
   * Modify the program code to blink faster at a rate of 10 times per second.
   * (onTime + offTime)*10 = 1000 milliseconds
   * onTime + offTime = 100 milliseconds
   * 1 <= onTime = 100 - offTime <= 99
   */
//   level2_3();

  /* Level 3 Advanced Application */

  /* Level 3_1
   *  Modify the program to make the LED flash slow three times (1000 mS delay), 
   *  then quickly three times. (100 mS delay)
   */
//   level3_1();

  /* Level 3_2
   *  Modify the program to flash your initials using Morse code (See chart below). 
   *  A "dot" would have the LED on for 100 mS and for a dash the LED would be on for 1000 mS.
   */
   level3_2();

  /* Level 4 Project Challenge */

  /* Level 4_1
   *  Write a program that starts strobing the SW1 button is pressed and 
   *  stops strobing when the SW2 button is pressed.
   */
//   level4_1(onTime, offTime);

  /* Level 4_2
   *  Write a program that alternates between the blue LED1 and red LED2, 
   *  to simulate an emergency vehicle.
   */
//   level4_2(100, 100);
}

void level2_3(){
  // set onTimeLevel2_3 from 1 to 99
   onTimeLevel2_3 = random(1, 100);
   offTimeLevel2_3 = 100 - onTimeLevel2_3;
   strobingOutput(onTimeLevel2_3, offTimeLevel2_3);
}

void level3_1(){
  for (int i = 0; i < 3; i++) {
    onTimeLevel3_1 = random(1, 1000);
    offTimeLevel3_1 = 1000 - onTimeLevel3_1;
    strobingOutput(onTimeLevel3_1, offTimeLevel3_1);
   }
   
   for (int i = 0; i < 3; i++) {
    onTimeLevel3_1 = random(1, 100);
    offTimeLevel3_1 = 100 - onTimeLevel3_1;
    strobingOutput(onTimeLevel3_1, offTimeLevel3_1);
   }
}

void level3_2(){
  /* Y dash dot dash dash */ 
  strobingOutput(onTimeDash, offTime);
  
  strobingOutput(onTimeDot, offTime);

  strobingOutput(onTimeDash, offTime);

  strobingOutput(onTimeDash, 3*offTime);

  /* G dash dash dot */
  strobingOutput(onTimeDash, offTime);

  strobingOutput(onTimeDash, offTime);

  strobingOutput(onTimeDot, 3*offTime);
}

void level4_1(int on_Time, int off_Time){
  if(digitalRead(button1Pin) == LOW){
    blueLedOn = 1;
   } else if(digitalRead(button2Pin) == LOW){
    blueLedOn = 0;
   }
   
   switch(blueLedOn){
    case 0:
      digitalWrite(blueLedPin, LOW);
      break;
    case 1:
      strobingOutput(on_Time, off_Time);
      break;
    default:
      break;
   }
}

void level4_2(int on_Time, int off_Time){
   if(digitalRead(button1Pin) == LOW){
    blueLedOn = 1;  // set blueLedOn true if button1Pin is pressed
   } else if(digitalRead(button2Pin) == LOW){
    blueLedOn = 0;
   }
   
   switch(blueLedOn){
    case 0:
      digitalWrite(blueLedPin, LOW);
      break;
    case 1:
      digitalWrite(blueLedPin, HIGH);  //Turn on the blue LED.
      delay(on_Time);                   //Wait onTime.
      digitalWrite(blueLedPin, LOW);   //Turn off the blue LED.
      delay(off_Time);                  //Wait offTime.
  
      digitalWrite(redLedPin, HIGH);  //Turn on the red LED.
      delay(on_Time);                   //Wait onTime.
      digitalWrite(redLedPin, LOW);   //Turn off the red LED.
      delay(off_Time);                  //Wait offTime.
      break;
    default:
      break;
   }
}

void strobingOutput(int on_Time, int off_Time){
  digitalWrite(blueLedPin, HIGH);  //Turn on the blue LED.
  delay(on_Time);                   //Wait onTime.
  digitalWrite(blueLedPin, LOW);   //Turn off the blue LED.
  delay(off_Time);                  //Wait offTime.
}
