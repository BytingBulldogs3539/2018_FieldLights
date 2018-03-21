#include <SoftwareSerial.h>
#include <Adafruit_NeoPixel.h>

//Scale

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
  setLeftColor(colorLeft);
  setRightColor(colorRight);
  setRightBrightness(255);
  setLeftBrightness(255);
  delay(500);
  start();
}

void loop() 
{
  if(digitalRead(rightButton)&&digitalRead(leftButton))
  {
    setLeftColor( pixelsLeft.Color(0, 255, 0));
    setRightColor( pixelsLeft.Color(0, 255, 0));
    delay(300);
    start();

  }
  else if (digitalRead(rightButton))
  {
    Serial.println("Right");
    setLeftBrightness(25);
    fadeRight();
  }
  else if (digitalRead(leftButton))
  {
    Serial.println("Left");
    setRightBrightness(25);
    fadeLeft();
  }
  
  else
  {
    Serial.println("neither");
    setRightBrightness(255);
    setLeftBrightness(255);
    setLeftColor(colorLeft);
    setRightColor(colorRight);
    leftFadeLoop=255;
    rightFadeLoop=255;
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
void start()
{
  delay(2000);

   
  pinMode(rightButton, INPUT);
  pinMode(leftButton, INPUT);
  //1==red
  randomSeed(analogRead(0));
  long Center = random(1,3);
  long scale = random(1,3);
  Serial.println(String(Center)+" "+String(scale));
  
  delay(25);
  if (Center==1)
  {
    mySerial.write("R");
    Serial.println("R");
  }
  else
  {
    mySerial.write("B");
    Serial.println("B");
  }
  if(scale==1)
  {
    colorRight=pixelsLeft.Color(255,0,0);
    colorLeft=pixelsLeft.Color(0,0,255);
  }
  else
  {
    colorLeft=pixelsLeft.Color(255,0,0);
    colorRight=pixelsLeft.Color(0,0,255);
  }
}

