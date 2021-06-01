#include <Servo.h>
#include <SoftwareSerial.h>

SoftwareSerial myBT(10, 11);

const byte control = 3;

Servo servo;

void setup()
{
    pinMode(control, OUTPUT);
    servo.attach(control);
    myBT.begin(38400);
    Serial.begin(9600);

    delay(2000);
}

void loop()
{
    servo.write(0);
    int angle = selectAngle();
    execute(angle);
}

int selectAngle()
{
    int angle = 0;
    bool stop = true;

    while (stop)
    {
        while (myBT.available())
        {
            angle *= 10;
            angle += (int)myBT.read() - 48;
            delay(100);
            if (!myBT.available())
            {
                stop = false;
            }
        }
    }
    return angle;
}

void execute(int angle)
{
    if (angle > 180)
    {
        angle = 180;
    }
    else
    {
        if (angle < 0)
        {
            angle = 0;
        }
    }

    servo.write(angle);
    delay(2000);
}   