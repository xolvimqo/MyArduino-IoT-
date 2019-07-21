/*    
 *      Terry Gu
        Title: 321Maker Experiment #003 - Rotation Sensor
        Description: This program will read the data from the rotation sensor and display the result to the serial monitor.
        Tutorial:  http://321maker.com/e/rotation-sensor
        Revision Date: March 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
        Instructions: Click Tools, Serial Montior (Ctrl + Shift + M) to view the output.
*/
int rotationPin = A0; //The rotation sensor is plugged into pin A0 of the Arduino.
int buzzerPin = 5;
int data = 0;           //Used to store data from sensor.
int RGBRedPin = 9;
int RGBGreenPin = 10;
int RGBBluePin = 11;
int redLedPin = 12;
int blueLedPin = 13;
int waitTime = 2000;
int colorNum = 0;
int dataVolume = 0;
boolean isOver512 = 0;
int brightness = 0;

void setup() { //The Setup function runs once.
  Serial.begin(9600); //This will enable the Arduino to send data to the Serial monitor.
  pinMode(RGBRedPin, OUTPUT);
  pinMode(RGBGreenPin, OUTPUT);
  pinMode(RGBBluePin, OUTPUT);
  pinMode(redLedPin, OUTPUT);
  pinMode(blueLedPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  randomSeed(analogRead(0));
}

void loop() { //The loop function runs forever.
//data = analogRead(rotationPin);  //Read the value from the light sensor and store it in the lightData variable.
//Serial.print("Rotation value ="); 
//Serial.println(data);  //Print the data to the serial port.
//delay(5000);           //Wait 5 second (5000mS) before running again. 

  /* Level 2 Program Modification */
//  data = analogRead(rotationPin);  //Read the value from the light sensor and store it in the lightData variable.
//  Serial.print("Volume ="); 
//  Serial.println(data/4);  //Print the data to the serial port.
//  delay(5000);           //Wait 5 second (5000mS) before running again. 

  /* Level 3 Advanced Application */
//  data = analogRead(rotationPin)/4;
//  waitTime = data*10;
//  if (dataVolume != data){
//    Serial.print("Wait Time = ");
//    Serial.println(waitTime);
//    dataVolume == data;
//  }
//  randomLight(waitTime);

  /* Level 4 Project Challenge */
  /* Level 4_1 Heating and Cooling Challenge
   *  Write a program that will read the rotation sensor and
   *  it will control the such that if the value of the dial is 
   *  below 512 the blue LED (D13) will turn on, or else if the
   *  value is 512 or greater the red Led (D12) will turn on.
   */
    data = analogRead(rotationPin);
    if (dataVolume != data){
      Serial.print("Value = ");
      Serial.println(data);
      dataVolume == data;
    }
    if(data >= 512){
     isOver512 = 1;
    } else {
     isOver512 = 0;
    }

   switchRBLed(isOver512);

   /* Level 4_2 Light Show Challenge
    *  Write a program that vary the brightness of the RGB led (D9-D11), 
    *  based on the value of the rotation sensor.
    */
    data = analogRead(rotationPin);
    waitTime = data * 10;
    brightness = data / 4;
    brightnessLight(waitTime, brightness);

    /* Level 4_3 */
    analogWrite(buzzerPin, data);
}

void switchRBLed(boolean _isOver512){
  switch(_isOver512){
    case 0:
      digitalWrite(blueLedPin, HIGH);
      digitalWrite(redLedPin, LOW);
      break;
    case 1:
      digitalWrite(redLedPin, HIGH);
      digitalWrite(blueLedPin, LOW);
      break;
    default:
      digitalWrite(redLedPin, LOW);
      digitalWrite(blueLedPin, LOW);
      break;
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
      break;
    case 1:
      //Display Green
      digitalWrite(RGBGreenPin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBGreenPin, LOW);  //Turn off Red
      break;
    case 2:
      //Display Blue
      digitalWrite(RGBBluePin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW);  //Turn off Red
      break;
    case 3:
      //Display  Magenta  (Red + Blue)
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      digitalWrite(RGBBluePin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBBluePin, LOW); //Turn on RED
      break;
    case 4:
      //Display  Yellow  (Red + Green)
      digitalWrite(RGBRedPin, HIGH); //Turn on RED
      digitalWrite(RGBGreenPin, HIGH); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBGreenPin, LOW); //Turn of RED
      break;
    case 5:
      //Display  Cyan  (Blue + Green) 
      digitalWrite(RGBBluePin, HIGH); //Turn on BLUE
      digitalWrite(RGBGreenPin, HIGH); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW); //Turn of BLUE
      digitalWrite(RGBGreenPin, LOW);  //Turn off GREEN
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
    break;
  }
}

void brightnessLight(int _WAIT_TIME, int _BRIGHTNESS){
  colorNum = random(0, 7);

  switch(colorNum){
    case 0:
      //Display Red
      analogWrite(RGBRedPin, _BRIGHTNESS); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      break;
    case 1:
      //Display Green
      analogWrite(RGBGreenPin, _BRIGHTNESS); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBGreenPin, LOW);  //Turn off Red
      break;
    case 2:
      //Display Blue
      analogWrite(RGBBluePin, _BRIGHTNESS); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW);  //Turn off Red
      break;
    case 3:
      //Display  Magenta  (Red + Blue)
      analogWrite(RGBRedPin, _BRIGHTNESS); //Turn on RED
      analogWrite(RGBBluePin, _BRIGHTNESS); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBBluePin, LOW); //Turn on RED
      break;
    case 4:
      //Display  Yellow  (Red + Green)
      analogWrite(RGBRedPin, _BRIGHTNESS); //Turn on RED
      analogWrite(RGBGreenPin, _BRIGHTNESS); //Turn on RED
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off Red
      digitalWrite(RGBGreenPin, LOW); //Turn of RED
      break;
    case 5:
      //Display  Cyan  (Blue + Green) 
      analogWrite(RGBBluePin, _BRIGHTNESS); //Turn on BLUE
      analogWrite(RGBGreenPin, _BRIGHTNESS); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBBluePin, LOW); //Turn of BLUE
      digitalWrite(RGBGreenPin, LOW);  //Turn off GREEN
      break;
    case 6:
      //Display White  (Red + Blue + Green)
      analogWrite(RGBRedPin, _BRIGHTNESS); //Turn on RED
      analogWrite(RGBBluePin, _BRIGHTNESS); //Turn on BLUE
      analogWrite(RGBGreenPin, _BRIGHTNESS); //Turn on GREEN
      delay(_WAIT_TIME);               //Wait for 2 seconds
      digitalWrite(RGBRedPin, LOW);  //Turn off RED
      digitalWrite(RGBBluePin, LOW); //Turn off BLUE
      digitalWrite(RGBGreenPin, LOW); //Turn off GREEN
    break;
  }
}
