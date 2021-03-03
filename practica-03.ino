#include <LiquidCrystal.h>
#include <Keypad.h>
#include <Servo.h>

// Keypad variables
const byte rowsCount = 4;
const byte colsCount = 4;

// Keypad matrix
char keys[rowsCount][colsCount] = {
    { '1', '2', '3', 'A' }, 
    { '4', '5', '6', 'B' }, 
    { '7', '8', '9', 'C' }, 
    { '*', '0', '#', 'D' }
};

// Keypad pins
byte rowPins[rowsCount] = { 13, 12, 11, 10 };
byte colPins[colsCount] = { 9, 8, 7, 6 };

// Keypad object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rowsCount, colsCount);

// LCD variables
const byte RS = 53, EN = 51, D4 = 49, D5 = 47, D6 = 45, D7 = 43;

// Lcd object
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Servo variables
const byte servoPin = 3;

// Servo object
Servo servo;

void setup() {
    // Init LCD
    lcd.begin(16, 2);
    lcd.print("Program 03");

    // Init motor
    pinMode(servoPin, OUTPUT);
    servo.attach(servoPin);

    delay(1000);
}

void loop() {
    servo.write(0);
    int angle = selectAngle();
    executeSequence(angle);
}

int selectAngle() {
    int angle = 0;

    lcd.clear();
    lcd.print("Select angle");
    lcd.setCursor(0, 1);
    lcd.print("* Rem, D Send");

    char key;
    do {
        key = keypad.getKey();
        if (key >= '0' && key <= '9') {
            angle *= 10;
            angle += (key - 48);

            lcd.clear();
            lcd.print("Angle");
            lcd.setCursor(0, 1);
            lcd.print(angle);
        } else if (key == '*') {
            angle /= 10;

            lcd.clear();
            lcd.print("Angle");
            lcd.setCursor(0, 1);
            lcd.print(angle);
        }
    } while(key != 'D');

    return angle;
}

void executeSequence(int angle) {
    // Correct values
    if (angle > 180) {
        angle = 180;
    }

    lcd.clear();
    lcd.print("Moving to");
    lcd.setCursor(0, 1);
    lcd.print(angle);

    servo.write(angle);
    delay(2000);
}































