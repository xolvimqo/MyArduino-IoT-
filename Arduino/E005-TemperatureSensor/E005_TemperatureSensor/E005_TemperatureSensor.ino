/*
 * Yu-Ming(Terry) Gu
        Title: 321Maker Experiment #005 - Temperature Sensor
        Description: This program will read the data from the temperature sensor. Convert the data to a temperature and display the temperature to the serial monitor in both Celsius and Fahrenheight
        Tutorial:  http://321maker.com/e/temperature-sensor
        Revision Date: March 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
        Instructions: Click Tools, Serial Montior (Ctrl + Shift + M) to view the output.
*/

int buzzerPin = 5;
int redLEDPin = 12;
int blueLEDPin = 13;
int tempPin = A2;     //The temperature sensor is plugged into pin A2 of the Arduino.
int data;             //This will store the data from the sensor.
int waitTime = 3000;  //Wait
boolean currentTempHigh = 0;
void setup(void) {    //The Setup function runs once.
  Serial.begin(9600); //This will enable the Arduino to send data to the Serial monitor.
  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

void loop(void) { //The loop function runs forever.
  data = analogRead(tempPin);        //Read from the temperature sensor
  Serial.print("Sensor reading = "); //Serial.print displays to the Serial Monitor.
  Serial.println(data);                //This is the raw analog reading

  // Calculate and display temperature.
  float temperatureC = (5.0 * data * 100.0) / 1024;
  Serial.print(temperatureC);
  Serial.write(0xC2);
  Serial.write(0xB0); 
  Serial.println("C");

  // Convert temperature to Fahrenheight and display.
  float temperatureF = (temperatureC * 9.0 / 5.0) + 32.0;
  Serial.print(temperatureF); 
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.println("F");

  /* Level 2 Program Modification
   *  Modify the program to show the current temperature and
   *  how far away the current temperature is away from boiling water.
   */
//  level2(temperatureC);

  /* Level 3 Advanced Application
   *  Write a program that will display the current temperature
   *  using Celsius, Kelvin and Newton scales.
   */
//  level3(temperatureC);

  /* Level 4 Project Challenge */
  /* Level 4-1 Temperature Alarm
   *  Write a program that will sound buzzer (D5) if the temperature is above
   *  25C.
   */
//  level4_1(temperatureC);

  /* Level 4-2 HVAC Challenge
   *  Write a program that will turn on the red LED (D12) when the temperature
   *  is below 25C to indicate that the furnace is on, and turn on the blue
   *  LED (D13) when the temperature is above 25C to indicate that air 
   *  conditioner is on.
   */
   level4_2(temperatureC);
  delay(waitTime); //Wait waitTime before running again.
}

void level2(float _tempC){
  Serial.print("The current temperature is ");
  Serial.print(_tempC);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.print("C and it is ");
  Serial.print(100.0 - _tempC);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.println("C away from boiling water.");
}

void level3(float _tempC){
  Serial.println("The current temperature is");
  Serial.print(_tempC);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.println("C");
  Serial.print(_tempC + 273.15);
  Serial.println("K");
  Serial.print(_tempC * 0.33);
  Serial.write(0xC2);
  Serial.write(0xB0);
  Serial.println("N");
}

void level4_1(float _tempC){
  if(_tempC > 25){
    currentTempHigh = 1;
    Serial.print("The current temperature is higher than 25");
    Serial.write(0xC2);
    Serial.write(0xB0);
    Serial.println("C");
  } else {
    currentTempHigh = 0;
  }

  switch(currentTempHigh){
    case 1:
    analogWrite(buzzerPin, HIGH);
    break;
    case 0:
    analogWrite(buzzerPin, LOW);
    break;
  }
}

void level4_2(float _tempC){
  if(_tempC < 25){
    digitalWrite(redLEDPin, HIGH);
    digitalWrite(blueLEDPin, LOW);
  } else {
    digitalWrite(blueLEDPin, HIGH);
    digitalWrite(redLEDPin, LOW);
  }
}
