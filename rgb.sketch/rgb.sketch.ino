/*
Adafruit Arduino - Lesson 3. RGB LED
*/

int redPin = 11;
int greenPin = 10;
int bluePin = 9;

//uncomment this line if using a Common Anode LED
//#define COMMON_ANODE

void setup()
{
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);  
}

void loop()
{
  for (int i = 0; i<2;++i)
  {
    setColor(255, 0, 0);  // red
    delay(100);
    setColor(0, 0, 0);  // red
    delay(200);
  }
  for (int i = 0; i<2;++i)
  {
    setColor(0, 255, 0);
    delay(100);
    setColor(0, 0, 0);
    delay(200);
  }
}

void setColor(int red, int green, int blue)
{
  #ifdef COMMON_ANODE
    red = 255 - red;
    green = 255 - green;
    blue = 255 - blue;
  #endif
  analogWrite(redPin, red);
  analogWrite(greenPin, green);
  analogWrite(bluePin, blue);  
}
