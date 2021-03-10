// Libraries
#include <LiquidCrystal.h>
#include <Keypad.h>

// Keypad dimensions
const byte rowsCount = 4;
const byte colsCount = 4;

// Matrix definition
char keys[rowsCount][colsCount] = {
    { '1', '2', '3', 'A' }, 
    { '4', '5', '6', 'B' }, 
    { '7', '8', '9', 'C' }, 
    { '*', '0', '#', 'D' }
};

// Keypad pins
byte rowPins[rowsCount] = { 13, 12, 11, 10 };
byte colPins[colsCount] = { 9, 8, 7, 6 };

// Create Keypad Object
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rowsCount, colsCount);

// LCD values
const byte RS = 53, EN = 51, D4 = 49, D5 = 47, D6 = 45 , D7 = 43;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Motor values
const byte motorPin = 3;
double motorPWM;




// Setup
void setup() {
    lcd.begin(16, 2);
    lcd.print("Program 01");
    pinMode(motorPin, OUTPUT);
    analogWrite(motorPin, 0);

    delay(1000);
}

// Loop
void loop() {
    motorPWM = 0;
    analogWrite(motorPin, motorPWM);
    int seconds = selectTime(); 
    executeSequence(seconds);
}

int selectTime() {
    int seconds = 0;

    lcd.clear();
    lcd.print("Select seconds");
    lcd.setCursor(0, 1);
    lcd.print("* Rem, D Send");

    char key;

    do {
        key = keypad.getKey();
        if (key >= '0' && key <= '9') {
            seconds *= 10;
            seconds += (key - 48);

            lcd.clear();
            lcd.print("Seconds");
            lcd.setCursor(0, 1);
            lcd.print(seconds);
        }
        else if (key == '*') {
            seconds /= 10;

            lcd.clear();
            lcd.print("Seconds");
            lcd.setCursor(0, 1);
            lcd.print(seconds);
        }

    } while (key != 'D');

    return seconds;
}

void executeSequence(int seconds) {
    // Correct values
    if (seconds < 10) {
        seconds = 10;
    } 
    else if (seconds > 120) {
        seconds = 120;
    }

    int interval = seconds*10;
    for (int i = 0; i <= 100; i++) {
        analogWrite(motorPin, motorPWM);
        lcd.clear();
        lcd.print("Speed value");
        lcd.setCursor(0, 1);
        lcd.print(i);
        lcd.print("%");

        delay(interval);
        if (i != 100) {
            motorPWM += 2.55;
        }
    }
}





























