/*
 *      Terry Gu
        Title: 321Maker Experiment #007 - RGB Fade
        Description: This program will fade the Red, Green, Blue(RGB) LED on the 321Maker shield.
        Tutorial:  http://321maker.com/tutorials/rgb-fade
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
int fadeDelay = 5;    //This is the number of milliseconds that it will take between steps during fading.
int data = 0;
int value = 0;
int counter = 0;

void setup() { //The Setup function runs once.
  Serial.begin(9600); // This will enable the Arduino to send data to the Serial monitor.
  pinMode(RGBRedPin, OUTPUT);    //Setup red RGB LED pin as an output pin.
  pinMode(RGBGreenPin, OUTPUT);  //Setup green RGB LED pin as an output pin.
  pinMode(RGBBluePin, OUTPUT);   //Setup blue RGB LED pin as an output pin.
  pinMode(button1Pin, INPUT);
  pinMode(button2Pin, INPUT);
}

void loop() { //The loop function runs forever.
//  level1();

  /* Level2
   * Fade the red channel of the RGB LED in and out when the user pushes SW1 (D2)
   * Fade the blue channel of the RGB LED in and out when the user pushes SW2(D3).
  */
//  level2();
  
  /* Level3
   * Map the brightness of the green channel of the RGB led to the rotation sensor A0.
   */
//  level3();

  /* Level4
   *  Write a program that allows the user to set the brightness of each of the RGB channels by using the rotation dial to control brightness and a push button to select the channel. For example, the operation of this program could be as follows.
   * User turns the dial to set the brightness of the red LED.
   * The User pushes the “mode” button SW1 (D2)
   * User turns the dial to set the brightness of the green LED.
   * The User pushes the “mode” button SW1 (D2)
   * User turns the dial to set the brightness of the blue LED.
   * If the user pushed the “mode” button again, then the it will loop back to the red channel again.
   */
   level4();
}

void level4(){
  data = analogRead(rotationPin);
  value = map(data, 0, 1023, 0, 255);
//  Serial.print("Value = ");
//  Serial.println(value);

  if(digitalRead(button1Pin) == LOW){
    delay(500);
    if(counter < 2){
      ++counter;
    } else {
      counter = 0;
    }
    Serial.println(counter);
  }

  if(counter == 0){
    analogWrite(RGBRedPin, value);
    delay(fadeDelay);
  }
  if(counter == 1){
    analogWrite(RGBGreenPin, value);
    delay(fadeDelay);
  }
  if(counter == 2){
    analogWrite(RGBBluePin, value);
    delay(fadeDelay);
  }
}

void level3(){
  data = analogRead(rotationPin);
  value = map(data, 0, 1023, 0, 255);
  Serial.print("Value = ");
  Serial.println(value);
  analogWrite(RGBGreenPin, value);
  delay(fadeDelay);
}

void level2(){
  if(digitalRead(button1Pin) == LOW){
    for (int x = 0; x <= 255; x++) { //Fade in red.
      analogWrite(RGBRedPin, x);
      delay(fadeDelay);
    }

    for (int x = 255; x >= 0; x--) { //Fade out red.
      analogWrite(RGBRedPin, x);
      delay(fadeDelay);
    }
  }

  if(digitalRead(button2Pin) == LOW){
     for (int x = 0; x <= 255; x++) { //Fade in blue.
      analogWrite(RGBBluePin, x);
      delay(fadeDelay);
    }
  
    for (int x = 255; x >= 0; x--) { //Fade out blue.
      analogWrite(RGBBluePin, x);
      delay(fadeDelay);
    }
  }
}

void level1(){
  for (int x = 0; x <= 255; x++) { //Fade in red.
    analogWrite(RGBRedPin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out red.
    analogWrite(RGBRedPin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in green.
    analogWrite(RGBGreenPin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out green.
    analogWrite(RGBGreenPin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in blue.
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out blue.
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in red and blue.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out red and blue.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in red and green.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBGreenPin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out red and green.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBGreenPin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in green and blue.
    analogWrite(RGBGreenPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out green and blue.
    analogWrite(RGBGreenPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 0; x <= 255; x++) { //Fade in red, green and blue.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBGreenPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }

  for (int x = 255; x >= 0; x--) { //Fade out red, green and blue.
    analogWrite(RGBRedPin, x);
    analogWrite(RGBGreenPin, x);
    analogWrite(RGBBluePin, x);
    delay(fadeDelay);
  }
}
