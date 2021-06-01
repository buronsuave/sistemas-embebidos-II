#include <SoftwareSerial.h>

SoftwareSerial myBT(10, 11);

int Steps [ 4 ][ 4 ] = {
      {1, 1, 0, 0},
      {0, 1, 1, 0},
      {0, 0, 1, 1},
      {1, 0, 0, 1}
};


boolean direction = true;
int M1 = 0, M2 = 1, M3 = 2, M4 = 3;

boolean next = false;

void setup() 
{
  pinMode(M1, OUTPUT);
  pinMode(M2, OUTPUT);
  pinMode(M3, OUTPUT);
  pinMode(M4, OUTPUT);

  myBT.begin(38400);
  delay(4000);
}

void loop() 
{
    while (!next) 
    {
    if (myBT.available()) 
    {
      if(myBT.read() - 48 == 0)
      {
        direction = false;
      }
        else
      {
        direction = true;
      }
      if(!myBT.available())
      {
        next = true;
      }
    }
  }

  next = false;

  for (int i = 0; i < 2048; i++)
  {
    digitalWrite( M1, Steps[direction? i%4 : 4-(i%4)][ 0] );
    digitalWrite( M2, Steps[direction? i%4 : 4-(i%4)][ 1] );
    digitalWrite( M3, Steps[direction? i%4 : 4-(i%4)][ 2] );
    digitalWrite( M4, Steps[direction? i%4 : 4-(i%4)][ 3] );  
    delay(4);
  }
}