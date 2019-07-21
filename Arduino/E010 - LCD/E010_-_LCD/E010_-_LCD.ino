/*
        Title: 321Maker Experiment #011 - LCD
        Description: This program will display 321Maker on the serial LCD.
        Tutorial:  http://321maker.com/e/011-lcd
        Revision Date: October 12, 2016
        Licence: http://321maker.mit-license.org/
        Requirements:  Arduino with 321Maker Shield, 1602 Serial LCD 
        Serial LCD library: https://bitbucket.org/fmalpartida/new-liquidcrystal/downloads/NewliquidCrystal_1.3.4.zip      
*/
//Load libraries
#include <Wire.h>
#include <LCD.h>
#include <LiquidCrystal_I2C.h>

 //Define address for the Serial LCD display.
#define I2C_ADDR  0x27  //If 0x3f doesn't work change this to 0x27
#define BACKLIGHT_PIN  3

//Initialise the Serial LCD.
LiquidCrystal_I2C lcd(I2C_ADDR, 2,1,0,4,5,6,7); //These pin numbers are hard coded in on the serial backpack board.

// Humidity settings
#include "DHT.h"
int DHT11Pin = 4;        //The DHT11 sensor  is connected to pin 4 of the Arduino. 
int waitTime = 5000;     //The amount of time to wait between sensor reads.
DHT dht(DHT11Pin, DHT11);//Initialize the sensor. 

int lightPin = A1; //The light sensor is plugged into pin A1 of the Arduino.

static int counter = 0;
int sw1Pin = 2;
int rightCount = 0;
int leftCount = 0;
int cursCount = 0;

void setup()
{
  pinMode(sw1Pin, INPUT);

  dht.begin();  //Start the sensor.
  
  lcd.begin (16,2);     //Initalize the LCD.
  lcd.setBacklightPin(3,POSITIVE);//Setup the backlight.
  lcd.setBacklight(HIGH); //Switch on the backlight.
  lcd.clear();
  lcd.setCursor(0,0);   //goto first column  and first line (0,0)
  lcd.print("321");     //Print at cursor Location
  lcd.setCursor(0,1);   //goto first column and second line 
  lcd.print("Maker");   //Print at cursor Location 
  delay(1000);   
}
 
void loop(){
  /* Level 2 Program Modification */
//  level2();

  /* Level 3 Advanced Application
   *  Write a program that will display your name, then the user presses sw1 (d2) your favorite hobby or interest will be displayed.
   *  Then if they push sw1 (d2) again, the display will show what you want for lunch. Finally if sw1 (d2) is pushed again then the
   *  display reset and display your name again.
   *  
   *  Write a program that prints your name and have it shift your name back and forth across the LCD
  */
//  level3_1();
  level3_2("Diego");

  /* Level 4 Project Challenge
   *  Write a program that will display temperature, humidity, and light values on the LCD screen.
  */
//  level4();
}

void level4(){
  delay(waitTime);
  float humidity = dht.readHumidity();
  float celsius = dht.readTemperature();
  int data = analogRead(lightPin);
  
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("T: ");
  lcd.print(celsius);
  lcd.print("C ");
  lcd.setCursor(0, 1);
  lcd.print("H: ");
  lcd.print(humidity);
  lcd.print("% ");
  lcd.print("L: ");
  lcd.print(data);
}

void level3_2(String str){
  char ch[str.length() + 1];
  str.toCharArray(ch, str.length() + 1);
  lcd.clear();
  for(int i = 0; i < sizeof(ch) - 1; i++){
    if(rightCount + sizeof(ch) > 32){
      rightCount = 0;
      if(cursCount < 1){
        cursCount++;
      } else {
        cursCount = 0;
      }
    }
    if(i + rightCount < 16 && cursCount == 0){
      lcd.setCursor(i + rightCount, 0);
      lcd.print(ch[i]);
    } else if(i + rightCount < 32 && cursCount == 0){
      lcd.setCursor(i + rightCount - 16, 1);
      lcd.print(ch[i]);
    } else if(i + rightCount < 16 && cursCount == 1){
      lcd.setCursor(16 - 1 - i - rightCount, 1);
      lcd.print(ch[sizeof(ch) - 2 - i]);
    } else if(i + rightCount >= 16 && sizeof(ch) + rightCount <= 32 && cursCount == 1){
      lcd.setCursor(32 - 1 - i - rightCount, 0);
      lcd.print(ch[sizeof(ch) - 2 - i]);
    }
  }
  
  rightCount++;
  delay(500);
}

void level3_1(){
  if(digitalRead(sw1Pin) == LOW){
    delay(500);
    if(counter < 2){
      counter++;
    } else {
      counter = 0;
    }
  }
  
  if(counter == 0){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Terry Gu");
    delay(1000);
  } else if (counter == 1) {
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Painting");
    delay(1000);
  } else if (counter == 2){
    lcd.clear();
    lcd.setCursor(0,0);
    lcd.print("Pasta");
    delay(1000);
  }
}

void level2(){
  lcd.clear();
  lcd.setCursor(0, 0);
  lcd.print("Terry Gu");
  lcd.setCursor(0, 1);
  lcd.print("3");
  delay(1000);
  lcd.print("2");
  delay(1000);
  lcd.print("1");
  delay(1000);
  lcd.print("Maker");
}
