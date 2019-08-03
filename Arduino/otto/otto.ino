//----------------------------------------------------------------
//-- CC BY SA (http://ottodiy.com)
//-- 16 January 2017 - Modified by MHs, Ultra Sound fixed
//-- double check your US (Ultra sound) module some have TRIG and ECHO swapped!
//-----------------------------------------------------------------
//-- Otto will avoid obstacles with this code!
//-----------------------------------------------------------------
#include <Servo.h> 
#include <Wire.h>
#include <Oscillator.h>
#include <US.h>
#include <Otto.h>
#include <SoftwareSerial.h>

#define DEBUG true // turn debug message on or off in serial

Otto Otto;  //This is Otto!
SoftwareSerial softSerial(6,7); // RX, TX

// WiFi Definitions
const String ssid = "MyOttoWiFi";
const String password = "otto";

//---------------------------------------------------------
//-- First step: Make sure the pins for servos are in the right position
/*
         --------------- 
        |     O   O     |
        |---------------|
YR 3==> |               | <== YL 2 yaw left
         --------------- 
            ||     ||
RR 5==>   -----   ------  <== RL 4 roll left
         |-----   ------|
*/
  #define PIN_YL 2 //servo[2]
  #define PIN_YR 3 //servo[3]
  #define PIN_RL 4 //servo[4]
  #define PIN_RR 5 //servo[5]

  #define ECHOPIN 9        // Pin to receive echo pulse
  #define TRIGPIN 8        // Pin to send trigger pulse

///////////////////////////////////////////////////////////////////
//-- Global Variables -------------------------------------------//
///////////////////////////////////////////////////////////////////
//-- Movement parameters
int T=1000;              //Initial duration of movement
int moveId=0;            //Number of movement
int moveSize=15;         //Asociated with the height of some movements
//---------------------------------------------------------
bool obstacleDetected = false;
///////////////////////////////////////////////////////////////////
//-- Setup ------------------------------------------------------//
///////////////////////////////////////////////////////////////////
void setup(){
  // Setup WiFi
  uint32_t baud = 9600;
  Serial.begin(baud);
//  while (!Serial); // wait for serial port to connect. Needed for native USB port only
//  delay(2000);
  softSerial.begin(baud);

  Serial.flush();
  delay(2000);
  
  //Set the servo pins
  Otto.init(PIN_YL,PIN_YR,PIN_RL,PIN_RR,true, -1, 13, 8, 9);
  Otto.home();
  delay(50);
  Otto.sing(S_happy); // a happy Otto :)

//  pinMode(ECHOPIN, INPUT);
//  pinMode(TRIGPIN, OUTPUT);

//  // Set ESP8266 as client and connect to Wi-Fi
//  cmdExecute("AT+RST\r\n", 1000, DEBUG); // Reset ESP8266
//  cmdExecute("AT+CWMODE=1\r\n", 1000, DEBUG); // configure as sta
//  cmdExecute("AT+CWJAP=\"Georgian\",\"\"\r\n", 10000, DEBUG);
//  cmdExecute("AT+CIFSR\r\n", 5000, DEBUG); // get ip address // 192.168.4.1
//  cmdExecute("AT+CIPMUX=1\r\n", 1000, DEBUG); // set the multiple mode, it needs to be set before next line
//  cmdExecute("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80

  // Set ESP8266 as AP
  cmdExecute("AT+RST\r\n", 2000, DEBUG); // Reset ESP8266
  cmdExecute("AT+CWMODE=3\r\n", 2000, DEBUG); // configure as access point
  cmdExecute("AT+CWJAP=\"Georgian\",\"\"\r\n", 10000, DEBUG);
  cmdExecute("AT+CWSAP=\"OttoWi-Fi\",\"Ej3Cj06Ru8\",4,0", 5000, DEBUG);
  cmdExecute("AT+CIFSR\r\n", 2000, DEBUG); // get ip address // 192.168.4.1
  cmdExecute("AT+CIPMUX=1\r\n", 2000, DEBUG); // set the multiple mode, it needs to be set before next line
  cmdExecute("AT+CIPSERVER=1,80\r\n", 2000, DEBUG); // turn on server on port 80
  Serial.println("Server Ready");
}
///////////////////////////////////////////////////////////////////
//-- Principal Loop ---------------------------------------------//
///////////////////////////////////////////////////////////////////
//WE CAN PLAY WITH THESE NUMBERS
void loop() {
//  if(obstacleDetected){ 
//    Otto.walk(3,1300,-1); 
//    Otto.turn(4,1000,-1);                 
//    delay(50); 
//    obstacleDetector(); 
//  } else { 
//    Otto.walk(1,1000,1); 
//    obstacleDetector(); 
//  }
  if(softSerial.available()){ // check if the esp is sending a message
    if(softSerial.find("+IPD,")){
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)

      /* get the connection id so we can then disconnect
       *  subtract 48 because the read() function returns 
       *  the ASCII decimal value and 0 (the first decimal number) starts at 48
      */
      int connectionId = softSerial.read() - 48;
      
     softSerial.find("pin="); // advance cursor to "pin="

     int pinNumber = (softSerial.read()-48)*10; // get first number. If the pin 13 then the 1st number is 1.
     int secondNumber = (softSerial.read()-48);
     if(secondNumber >= 0 && secondNumber <= 9){
      pinNumber += secondNumber;
     }
//     digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin
     switch(pinNumber){
      case 9:
      Otto.walk(3,1000,1); 
      break;
      case 10:
      Otto.turn(4,1000,-1);
      break;
      case 11:
      Otto.moonwalker(3, 1000, 25, 1);
      break;
     }

//     lcd.clear();
//     lcd.setCursor(0,0);
//     lcd.print("IP Address");
//     lcd.setCursor(0,1);
//     lcd.print();

     // build string that is send back to device that is requesting pin toggle
     String content = "Pin ";
     content += pinNumber;
     content += " is ";

     if(digitalRead(pinNumber)){
      content+= "ON";
     } else {
      content += "OFF";
     }
     
     sendHTTPResponse(connectionId, content);
     
     // make close command
     String closeCommand = "AT+CIPCLOSE="; 
     closeCommand+=connectionId; // append connection id
     closeCommand+="\r\n";

     cmdExecute(closeCommand,500,DEBUG); // close connection
    }
  }
}  
//////////////////////////////////////////////////////////////////////////////////
//-- Function to read distance sensor & to actualize obstacleDetected variable //
/////////////////////////////////////////////////////////////////////////////////
void obstacleDetector(){
// Start Ranging
  digitalWrite(TRIGPIN, LOW);
  delayMicroseconds(2);
  digitalWrite(TRIGPIN, HIGH);
  delayMicroseconds(10);
  digitalWrite(TRIGPIN, LOW);
// Compute distance
  float distance = pulseIn(ECHOPIN, HIGH);
  distance= distance/68;
  Serial.print(distance);
  Serial.println("cm");
 if(distance<15){
          obstacleDetected = true;
          Serial.println ("Obstacle Detected! Avoid collision");
        }else{
          obstacleDetected = false;
          Serial.println ("No Obstacle detected! - Keep on walking");
        }
  
}

void sendHTTPResponse(int connectionId, String content){
  //build HTTP response
  String httpResponse;
  String httpHeader;
  httpHeader = "HTTP/1.1 200 OK\r\nContent-Type: text/html; charset=UTF-8\r\n";
  httpHeader += "Content-Length: ";
  httpHeader += content.length();
  httpHeader += "\r\nConnnection: close\r\n\r\n";
  httpResponse = httpHeader + content + " "; // There is a bug in this code: content would not be send without the last space
  sendCIPData(connectionId, httpResponse);
}

void sendCIPData(int connectionId, String data){
  String cipSend = "AT+CIPSEND=";
  cipSend += connectionId;
  cipSend += ",";
  cipSend += data.length();
  cipSend += "\r\n";
  cmdExecute(cipSend,1000,DEBUG);
  cmdSendData(data,1000,DEBUG);
}

String cmdSendData(String _cmd, const int _timeout, boolean _debug){
  String response = "";

  int dataSize = _cmd.length();
  char data[dataSize];
  _cmd.toCharArray(data, dataSize);

  softSerial.write(data, dataSize); // send the read character to the esp8266
  if(_debug){
    Serial.println("\r\n====== HTTP Response From Arduino ======");
    Serial.write(data, dataSize);
    Serial.println("\r\n========================================");
  }

  long int _time = millis();

  while((_time+_timeout) > millis()){
    while(softSerial.available()){
      // The esp8266 has data so display its output to the serial window
      char c = softSerial.read();
      response += c;
    }
  }
  if(_debug){
    Serial.print(response);
  }
  return response;
}

String cmdExecute(String _cmd, const int _timeout, boolean _debug){
  String response = "";

  softSerial.println(_cmd); // send the read character to the esp8266
  
  long int time = millis();

  while((time + _timeout) > millis()){
    while(softSerial.available()){
      char ch = softSerial.read();
      response += ch;
    }
  }
  if(_debug){
    Serial.print(response);
  }
  return response;
}
