/* Terry Gu
 * IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
 * An IR detector/demodulator must be connected to the input RECV_PIN.
 * Version 0.1 July, 2009
 * Copyright 2009 Ken Shirriff
 * http://arcfn.com
 */
#include <IRremote.h>

int buzzerPin = 5;
int RECV_PIN = 6;
int redLEDPin = 12;
int blueLEDPin = 13;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  // In case the interrupt driver crashes on setup, give a clue
  // to the user what's going on.
  Serial.println("Enabling IRin");
  irrecv.enableIRIn(); // Start the receiver
  Serial.println("Enabled IRin");

  pinMode(buzzerPin, OUTPUT);
  pinMode(redLEDPin, OUTPUT);
  pinMode(blueLEDPin, OUTPUT);
}

// level
#define UP 16746615
#define DOWN 16750695
#define RIGHT 16738455
#define LEFT 16722135
#define POWER 16711935

void loop() {
  level3();
}

void level3(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    if(results.value == UP){
      digitalWrite(blueLEDPin, HIGH);
    } else if (results.value == DOWN){
      digitalWrite(redLEDPin, HIGH);
    } else if (results.value == RIGHT){
      digitalWrite(blueLEDPin, LOW);
    } else if (results.value == LEFT){
      digitalWrite(redLEDPin, LOW);
    } else if (results.value == POWER){
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
      delay(500);
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
      delay(500);
    }
  }
  delay(100);
}

void level4(){
  if (irrecv.decode(&results)) {
    Serial.println(results.value, HEX);
    Serial.println(results.value);
    irrecv.resume(); // Receive the next value
    if(results.value == UP){
      digitalWrite(blueLEDPin, HIGH);
    } else if (results.value == DOWN){
      digitalWrite(redLEDPin, HIGH);
    } else if (results.value == RIGHT){
      digitalWrite(blueLEDPin, LOW);
    } else if (results.value == LEFT){
      digitalWrite(redLEDPin, LOW);
    } else if (results.value == POWER){
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
      delay(500);
      tone(buzzerPin, 1000);
      delay(500);
      noTone(buzzerPin);
      delay(500);
    }
  }
  delay(100);
}
