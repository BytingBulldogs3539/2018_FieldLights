#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

//Switch

#define RIGHTSTRIP 2   // the digitial pin that the rights neopixels are pluged into.
#define LEFTSTRIP 4    // the digitial pin that the left neopixels are pluged into.

#define rightButton 6
#define leftButton  5


#define NUMPIXELSLEFT      75 // number of neopixels in the left strip.
#define NUMPIXELSRIGHT     75 // number of neopixels in right strip.

Adafruit_NeoPixel pixelsLeft = Adafruit_NeoPixel(NUMPIXELSLEFT, LEFTSTRIP, NEO_GRB + NEO_KHZ800);
Adafruit_NeoPixel pixelsRight = Adafruit_NeoPixel(NUMPIXELSRIGHT, RIGHTSTRIP, NEO_GRB + NEO_KHZ800);

int leftFadeLoop=255;
int rightFadeLoop=255;

boolean leftFadeLoopAdd=true;
boolean rightFadeLoopAdd = true;


uint32_t colorRight = pixelsLeft.Color(255, 0, 255);
uint32_t colorLeft = pixelsLeft.Color(255, 0, 255);

SoftwareSerial mySerial(10, 11);


void setup() 
{
  mySerial.begin(4800);
  Serial.begin(9600);
  pixelsLeft.begin();
  pixelsRight.begin();
    
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
}

void loop() 
{
  if (mySerial.available()) 
  {
    char returned = mySerial.read();
    if (returned=='R')
    {
      colorRight = pixelsLeft.Color(255, 0, 0);
      
      colorLeft = pixelsLeft.Color(0, 0, 255);
    }
    else
    {
      colorRight = pixelsLeft.Color(0, 0, 255);
      colorLeft = pixelsLeft.Color(255, 0, 0);

    }
    Serial.println(returned);
  }
  if (digitalRead(rightButton))
  {
    setLeftBrightness(25);
    fadeRight();
  }
  else if (digitalRead(leftButton))
  {
    setRightBrightness(25);
    fadeLeft();
  }
  else
  {
    setRightBrightness(255);
    setLeftBrightness(255);
    setLeftColor(colorLeft);
    setRightColor(colorRight);
  }
  
}

void fadeLeft()
{
    Serial.println(leftFadeLoop);
  if (leftFadeLoop>=255)
    {
      leftFadeLoopAdd=false;
    }
    if (leftFadeLoop<=0)
    {
      leftFadeLoopAdd=true;
    }
    if(leftFadeLoopAdd)
    {
      leftFadeLoop+=5;
    }
    else
    {
      leftFadeLoop-=5;
    }
    setLeftColor(colorLeft);
    setRightColor(colorRight);
    setLeftBrightness(leftFadeLoop);
}
void fadeRight()
{
  if (rightFadeLoop>=255)
    {
      rightFadeLoopAdd=false;
    }
    if (rightFadeLoop<=0)
    {
      rightFadeLoopAdd=true;
    }
    if(rightFadeLoopAdd)
    {
      rightFadeLoop+=5;
    }
    else
    {
      rightFadeLoop-=5;
    }
    setLeftColor(colorLeft);
    setRightColor(colorRight);
    setRightBrightness(rightFadeLoop);
}
void setRightBrightness(int brightness)
{
  pixelsRight.setBrightness(brightness);
  pixelsRight.show();
}
void setLeftBrightness(int brightness)
{
  pixelsLeft.setBrightness(brightness);
  pixelsLeft.show();
}
void setRightColor(uint32_t cRight)

{
  for(int i=0;i<NUMPIXELSRIGHT;i++)
    {
      pixelsRight.setPixelColor(i, cRight);
    }
    pixelsRight.show(); 
}
void setLeftColor(uint32_t cLeft)
{
  for(int i=0;i<NUMPIXELSLEFT;i++)
    {
      pixelsLeft.setPixelColor(i, cLeft);
    }
    pixelsLeft.show(); 
}


