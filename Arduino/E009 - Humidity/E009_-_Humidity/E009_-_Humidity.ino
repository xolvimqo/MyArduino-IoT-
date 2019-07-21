/*
 * Terry Gu
        Title: 321Maker Experiment #009 - Humidity
        Description: This program will monitior the humidity and temperature from the DHT11 sensor and display it in the serial monitor.
        Tutorial:  http://321maker.com/e/humidity
        Revision Date: January 15, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield
        DHT sensor library: https://github.com/adafruit/DHT-sensor-library/archive/master.zip
*/

// LCD settings
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

// Define address for the Serial LCD display
#define I2C_ADDR 0x27
#define BACKLIGHT_PIN 3

// Initialise the Serial LCD.
LiquidCrystal_I2C lcd(I2C_ADDR, 2,1,0,4,5,6,7);

// Humidity settings
#include "DHT.h"
int DHT11Pin = 4;        //The DHT11 sensor  is connected to pin 4 of the Arduino. 
int waitTime = 5000;     //The amount of time to wait between sensor reads.
DHT dht(DHT11Pin, DHT11);//Initialize the sensor. 

int redLEDPin = 12;
int blueLEDPin = 13;
int greenRGBPin = 9;
int blueRGBPin = 11;
int buzzerPin = 5;
int rotationPin = A0;

void setup(){
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
  pinMode(greenRGBPin, OUTPUT);
  pinMode(blueRGBPin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);
  
  dht.begin();  //Start the sensor.

  lcd.begin (16,2);     //Initalize the LCD.
  lcd.setBacklightPin(3,POSITIVE);//Setup the backlight.
  lcd.setBacklight(HIGH); //Switch on the backlight.
}

void loop()
{
  delay(waitTime);
  float humidity = dht.readHumidity();  //Read the humidity value from the sensor.
  float celsius = dht.readTemperature(); //Read the temperature (c) value from the sensor. 
  float fahrenheit = dht.readTemperature(true); //Read the temperature (f) value from the sensor.
  float heatIndexF = dht.computeHeatIndex(fahrenheit, humidity); //Calculate the heat index (f).
  float heatIndexC = dht.computeHeatIndex(celsius, humidity, false); //Calculate the heat index (c).

  Serial.print("Humidity   (%): "); 
  Serial.println(humidity );        //Display the humidity precentage.
  Serial.print("Temperature(c): ");
  Serial.println(celsius);          //Display the temperature in celsius.
  Serial.print("Heat index (c): ");
  Serial.println(heatIndexC);       //Display the heat index in celsius.
  Serial.print("Temperature(f): ");
  Serial.println(fahrenheit);       //Display the temperature in fahrenheit.
  Serial.print("Heat index (f): ");
  Serial.println(heatIndexF);       //Display the heat index in fahrenheit.

  /* Level 2 Program Modification */
  Serial.print("Dewpoint:");
  Serial.println(dewPoint(celsius, humidity));

  /* Level 3 Advanced Application
   *  Have the Red LED (D12) turn on when the temperature is 25C or and the Blue LED (D13) when the temperature is below 25C
   *  Have the Green LED on the RGB (D9) turn on when the humidity is below 50% and Blue LED on the RGB (D11) when it's above 50%.
  */
//  level3(humidity, celsius);

  /* Level 4 Project Challenge 
   *  Create a humidity alarm such that when the humidity is above a threshold set by the rotation sensor (A0).
   *  Then the buzzer will chirp.
  */
  level4(humidity);
}

void level4(double humidity){
  int rotaData = analogRead(rotationPin);
  int threshold = map(rotaData, 0, 1023, 0, 100);

  lcd.clear();
  lcd.setCursor(0,0);   //goto first column  and first line (0,0)
  lcd.print("Thresho Humidity");     //Print at cursor Location
  lcd.setCursor(0,1);   //goto first column and second line 
  lcd.print(threshold);
  lcd.print(" % ");   //Print at cursor Location 
  lcd.print(humidity);
  lcd.print(" %");
  delay(100);
  
  if(humidity > threshold){
    tone(buzzerPin, 2000, 100);
  }
}

void level3(double humidity, double celsius){
  if(celsius >24){
    digitalWrite(blueLEDPin, LOW);
    digitalWrite(redLEDPin, HIGH);
  } else{
    digitalWrite(redLEDPin, LOW);
    digitalWrite(blueLEDPin, HIGH);
  }

  if(humidity < 50){
    digitalWrite(blueRGBPin, LOW);
    digitalWrite(greenRGBPin, HIGH);
  } else{
    digitalWrite(greenRGBPin, LOW);
    digitalWrite(blueRGBPin, HIGH);
  }
  
  lcd.clear();
  lcd.setCursor(0,0);   //goto first column  and first line (0,0)
  lcd.print("Celsius Humidity");     //Print at cursor Location
  lcd.setCursor(0,1);   //goto first column and second line 
  lcd.print(celsius);
  lcd.print(" C ");   //Print at cursor Location 
  lcd.print(humidity);
  lcd.print(" %");
  delay(1000);
}

double dewPoint(double celsius, double humidity){
  double a = 17.271;
  double b = 237.7;
  double temp = (a * celsius) / (b + celsius) + log(humidity * 0.01);
  double dP = (b * temp) / (a - temp);
  return dP;
}
