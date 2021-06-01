#include <SoftwareSerial.h>

SoftwareSerial myBT(10, 11);

int r, g, b                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                         ;
int PIN_R = 5;
int PIN_G = 6;
int PIN_B = 7;

void setup() 
{
  myBT.begin(38400);
  Serial.begin(9600);

  pinMode(PIN_R, OUTPUT);
  pinMode(PIN_G, OUTPUT);
  pinMode(PIN_B, OUTPUT);
} 

void loop() 
{
  if (myBT.available() > 0)
  {
    Serial.println("Im here");++
    char code = myBT.read();
    if (code == 'R')
    {
      r = myBT.read();
      if (r == -1)
      {
        r = 255;
      }
      code = myBT.read();
      if (code == 'G')
      {
        g = myBT.read();
        if (g == -1)
        {
          g = 255;
        }
        code = myBT.read();  
        if (code == 'B')
        {
          b = myBT.read();  
          if (b == -1)
          {
            b = 255;
          }

          r = 255 - r;
          g = 255 - g;
          b = 255 - b;

          analogWrite(PIN_R, r);
          analogWrite(PIN_G, g);
          analogWrite(PIN_B, b);
        }
      }
    }
  }
}