
// Pick analog outputs, for the UNO these three work well
// use ~560  ohm resistor between Red & Blue, ~1K for green (its brighter)
#define redpin 3
#define greenpin 5
#define bluepin 11
#define vibpin 9
#define led 13
#include "notes.h"
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground
#define PAUSE 0
#define QN 1000
#define DEN 750
#define EN 500
#define SN 250

int play1[] = {NOTE_D7};
int play1_time[] = {EN};//For RED
int play2[] = {NOTE_C7};
int play2_time[] = {EN};//FOR BLUE
int play3[] = {NOTE_D8};
int play3_time[] = {EN};//FOR GREEN
int play4[] = {NOTE_G1};

int rstate=0;
int gstate=0;
int bstate=0;
int vibstate=0;

void setup() {
  Serial.begin(9600);
  pinMode(led,OUTPUT);
  // use these three pins to drive an LED
  pinMode(redpin, INPUT);
  pinMode(greenpin, INPUT);
  pinMode(bluepin, INPUT);
  pinMode(8,OUTPUT);}
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
 


void loop() {
  rstate = digitalRead(redpin);
  gstate = digitalRead(greenpin);
  bstate = digitalRead(bluepin);
  vibstate = digitalRead(vibpin);

  // check if the pushbutton is pressed. If it is, the buttonState is HIGH:
  if (rstate == LOW) {
    // turn LED on:
    Serial.println("red");
    digitalWrite(vibpin,127); //64,127,191,255
    delay(20);
    }
 

  else if (gstate == LOW) {
    // turn LED on:
    digitalWrite(led, HIGH);
    Serial.println("green");
    digitalWrite(vibpin,191); //64,127,191,255
    delay(20);
  } 
  
   else if (bstate == LOW) {
    // turn LED on:
    digitalWrite(led, HIGH);
    Serial.println("blue");
    digitalWrite(vibpin,64); //64,127,191,255
    delay(20);
  } 

   else if (vibstate == LOW) {
    // turn sound on:
    digitalWrite(led, HIGH);
    Serial.println("sound");
    play_piece(8, play1, play1_time, sizeof(play1)/sizeof(play1[0]));
    delay(50);
  } 
  
  else {
    // turn LED off:
    digitalWrite(led, LOW);
    delay(50);
  }

  
  
} 



void play_piece(int pin, int *melody, int *duration, int length) {
  for (int i = 0; i < length; ++i) {
    tone(pin, melody[i], duration[i]);
    delay(duration[i]);}}
/*
int inPin = 2;         // the number of the input pin
int outPin = 13;       // the number of the output pin

int state = HIGH;      // the current state of the output pin
int reading;           // the current reading from the input pin
int previous = LOW;    // the previous reading from the input pin

// the follow variables are long's because the time, measured in miliseconds,
// will quickly become a bigger number than can be stored in an int.
long time = 0;         // the last time the output pin was toggled
long debounce = 200;   // the debounce time, increase if the output flickers

void setup()
{
  pinMode(inPin, INPUT);
  pinMode(outPin, OUTPUT);
}

void loop()
{
  reading = digitalRead(inPin);

  // if the input just went from LOW and HIGH and we've waited long enough
  // to ignore any noise on the circuit, toggle the output pin and remember
  // the time
  if (reading == HIGH && previous == LOW && millis() - time > debounce) {
    if (state == HIGH)
      state = LOW;
    else
      state = HIGH;

    time = millis();    
  }

  digitalWrite(outPin, state);

  previous = reading;
}*/
