#define DEBUG true // turn debug message on or off in serial

#include<Servo.h>
#include<Wire.h>
#include<LCD.h>
#include<LiquidCrystal_I2C.h>
#define BACKLIGHT_PIN 3
#define I2C_ADDR  0x27  //If 0x3f doesn't work change this to 0x27

Servo myservo; // create servo object to control a servo

// WiFi Definitions
const char* ssid = "xolvimqoESP8266";
const char* password = "xolvimqo8266";
const char* value = "";

int servoPin = 7;
int redRGBPin = 9;
int greenRGBPin = 10;
int blueRGBPin = 11;

int serAng;

LiquidCrystal_I2C lcd(I2C_ADDR, 2,1,0,4,5,6,7);

void setup() {
  // set up servo
  myservo.attach(7);
  // set up LCD
  lcd.begin(16,2);
  lcd.setBacklightPin(3,POSITIVE);
  lcd.setBacklight(HIGH);
  lcd.clear();
  lcd.setCursor(0,0);
  lcd.print("321");
  lcd.setCursor(0,1);
  lcd.print("Maker");
  delay(1000);
  // pin mode setting
  pinMode(redRGBPin, OUTPUT);
  digitalWrite(redRGBPin, LOW);
  pinMode(greenRGBPin, OUTPUT);
  digitalWrite(greenRGBPin, LOW);
  pinMode(blueRGBPin, OUTPUT);
  digitalWrite(blueRGBPin, LOW);

  // attaches the servo on pin 7 to the servo object
  myservo.attach(servoPin);
  
  // put your setup code here, to run once:
  while (!Serial); // wait for serial port to connect. Needed for Leonardo only
  delay(2000);
  Serial.begin(9600);
  Serial1.begin(115200);

  delay(2000);

  cmdExecute("AT+RST\r\n", 1000, DEBUG); // Reset ESP8266
  cmdExecute("A&W\r\n", 1000, DEBUG); // Reset ESP8266
  cmdExecute("AT+CWMODE=1\r\n", 1000, DEBUG); // configure as sta
  cmdExecute("AT+CWJAP=\"Georgian\",\"\"\r\n", 10000, DEBUG);
  cmdExecute("AT+CIFSR\r\n", 1000, DEBUG); // get ip address // 192.168.4.1
  cmdExecute("AT+CIPMUX=1\r\n", 1000, DEBUG); // set the multiple mode, it needs to be set before next line
  cmdExecute("AT+CIPSERVER=1,80\r\n", 1000, DEBUG); // turn on server on port 80

  Serial.println("Server Ready");
}

void loop() {  
  // Servo
  myservo.write(90);
  delay(15);
  // put your main code here, to run repeatedly:
  if(Serial1.available()){ // check if the esp is sending a message
    if(Serial1.find("+IPD,")){
      delay(1000); // wait for the serial buffer to fill up (read all the serial data)

      /* get the connection id so we can then disconnect
       *  subtract 48 because the read() function returns 
       *  the ASCII decimal value and 0 (the first decimal number) starts at 48
      */
      int connectionId = Serial1.read() - 48;
      
     Serial1.find("pin="); // advance cursor to "pin="

     int pinNumber = (Serial1.read()-48)*10; // get first number. If the pin 13 then the 1st number is 1.
     int secondNumber = (Serial1.read()-48);
     if(secondNumber >= 0 && secondNumber <= 9){
      pinNumber += secondNumber;
     }
     digitalWrite(pinNumber, !digitalRead(pinNumber)); // toggle pin

     switch(pinNumber){
      case 9:
      myservo.write(45);
      break;
      case 10:
      myservo.write(90);
      break;
      case 11:
      myservo.write(135);
      break;
     }

     lcd.clear();
     lcd.setCursor(0,0);
     lcd.print("Servo");
     lcd.setCursor(0,1);
     lcd.print(myservo.read());

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

  Serial1.write(data, dataSize); // send the read character to the esp8266
  if(_debug){
    Serial.println("\r\n====== HTTP Response From Arduino ======");
    Serial.write(data, dataSize);
    Serial.println("\r\n========================================");
  }

  long int _time = millis();

  while((_time+_timeout) > millis()){
    while(Serial1.available()){
      // The esp8266 has data so display its output to the serial window
      char c = Serial1.read();
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

  Serial1.println(_cmd); // send the read character to the esp8266
  
  long int time = millis();

  while((time + _timeout) > millis()){
    while(Serial1.available()){
      char ch = Serial1.read();
      response += ch;
    }
  }
  if(_debug){
    Serial.print(response);
  }
  return response;
}
