#include <ADXL335.h>

#include "notes.h"
#include <Wire.h>
#include "Adafruit_TCS34725.h"

#define PAUSE 0
#define QN 1000
#define DEN 750
#define EN 500
#define SN 250

//playlist for RGB color
int play1[] = {NOTE_D5};
int play1_time[] = {EN};//For RED
int play2[] = {NOTE_D1};
int play2_time[] = {EN};//FOR BLUE
int play3[] = {NOTE_E1};
int play3_time[] = {EN};//FOR GREEN
int play4[] = {NOTE_G1};
int play4_time[] = {EN};//FOR YELLOW


#define redpin 3
#define greenpin 5
#define bluepin 6
#define vibpin 11
#define buttonPin 2 
int buttonState=LOW;
// for a common anode LED, connect the common pin to +5V
// for common cathode, connect the common to ground


/*basic setup for color sensor*/
// set to false if using a common cathode LED
#define commonAnode true
// our RGB -> eye-recognized gamma color
byte gammatable[256];
Adafruit_TCS34725 tcs = Adafruit_TCS34725(TCS34725_INTEGRATIONTIME_50MS, TCS34725_GAIN_4X);




void setup(){
  Serial.begin(9600);
  Serial.println("Color View Test!");

  if (tcs.begin()) {
    Serial.println("Found sensor");
  } else {
    Serial.println("No TCS34725 found ... check your connections");
    while (1); // halt!
  }
  
  // use these three pins to drive an LED
  pinMode(redpin, OUTPUT);
  pinMode(greenpin, OUTPUT);
  pinMode(bluepin, OUTPUT);
  
  // thanks PhilB for this gamma table!
  // it helps convert RGB colors to what humans see
  for (int i=0; i<256; i++) {
    float x = i;
    x /= 255;
    x = pow(x, 2.5);
    x *= 255;
      
    if (commonAnode) {
      gammatable[i] = 255 - x;
    } else {
      gammatable[i] = x;      
    }
    //Serial.println(gammatable[i]);
  }
 
  pinMode(vibpin,OUTPUT);
  pinMode(buttonPin, INPUT);
  play_piece(8, play1, play1_time, sizeof(play1)/sizeof(play1[0]));
}

  
  

//maybe add the accelorameter section 
void loop() {
  
  uint16_t clear, red, green, blue;
  tcs.setInterrupt(false);      // turn on LED
  delay(200);  // takes 50ms to read 
  tcs.getRawData(&red, &green, &blue, &clear);
  tcs.setInterrupt(true);  // turn off LED
  
  Serial.print("C:\t"); Serial.print(clear);
  Serial.print("\tR:\t"); Serial.print(red);
  Serial.print("\tG:\t"); Serial.print(green);
  Serial.print("\tB:\t"); Serial.print(blue);
  
  //----------code for hexcalculation--------------//
  uint32_t sum = clear;
  float r, g, b;
  r = red; r /= sum;
  g = green; g /= sum;
  b = blue; b /= sum;
  r *= 256; g *= 256; b *= 256;
  //Serial.print((int)r ); Serial.print(" "); Serial.print((int)g);Serial.print(" ");  Serial.println((int)b );
  analogWrite(redpin, gammatable[(int)r]);
  analogWrite(greenpin, gammatable[(int)g]);
  analogWrite(bluepin, gammatable[(int)b]);
  Serial.print("\t");
  Serial.print((int)r, HEX); Serial.print((int)g, HEX); Serial.print((int)b, HEX);
  Serial.println();
//----------------------------------------------------//




//-----judge if color match-------//
if ((abs(red-145)<20)&&(abs(green-110)<20)&&(abs(blue-80)<20))
{
  //play red sound 
  play_piece(8, play1, play1_time, sizeof(play1)/sizeof(play1[0]));
  Serial.println("Red");
  delay(100);}

else if ((abs(red-0)<20)&&(abs(green-250)<20)&&(abs(blue-0)<20))
{
   //play green sound 
  play_piece(8, play3, play3_time, sizeof(play3)/sizeof(play3[0]));
  Serial.println("Green");
   delay(100);
  }

else if ((abs(red-0)<20)&&(abs(green-0)<20)&&(abs(blue-250)<20))
{
   //play blue sound 
  play_piece(8, play2, play2_time, sizeof(play2)/sizeof(play2[0]));
  Serial.println("Blue");
   delay(100);
  }

else
{
 //vibrator starts Max 255 Min 0
 digitalWrite(vibpin,10);
 delay(50);
 digitalWrite(vibpin,0);
 }
  
  
}



void play_piece(int pin, int *melody, int *duration, int length) {
  for (int i = 0; i < length; ++i) {
    tone(pin, melody[i], duration[i]);
    delay(duration[i]);}}
