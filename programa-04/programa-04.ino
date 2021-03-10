#include <LiquidCrystal.h>
#include <Keypad.h>

// Keypad variables
const byte rowsCount = 4;
const byte colsCount = 4;

// Keypad map
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

// LCD object
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Motor Pins
const byte motorPin1 = 2;
const byte motorPin2 = 3;
const byte motorEn1 = 15;
const byte motorEn2 = 14;

void setup() {
    lcd.begin(16, 2);
    lcd.print("Program 04");
    
    // Init motor variables
    pinMode(motorPin1, OUTPUT);
    pinMode(motorPin2, OUTPUT);
    pinMode(motorEn1, OUTPUT);
    pinMode(motorEn2, OUTPUT);

    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    digitalWrite(motorEn1, HIGH);
    digitalWrite(motorEn2, LOW);

    delay(1000);
}

void loop() {
    int power = selectPower();
    bool direction = selectDirection();
    executeSequence(power, direction);
}

int selectPower() {
    int power = 0;

    lcd.clear();
    lcd.print("Select power");
    lcd.setCursor(0, 1);
    lcd.print("* Rem, D Send");

    char key;

    do {
        key = keypad.getKey();
        if (key >= '0' && key <= '9') {
            power *= 10;
            power += (key - 48);

            lcd.clear();
            lcd.print("Power");
            lcd.setCursor(0, 1);
            lcd.print(power);
        } else if (key == '*') {
            power /= 10;

            lcd.clear();
            lcd.print("Power");
            lcd.setCursor(0, 1);
            lcd.print(power);
        }
    } while (key != 'D');

    return power;
}

bool selectDirection() {
    lcd.clear();
    lcd.print("Select dir");
    lcd.setCursor(0, 1);
    lcd.print("0:<-, 1:->");

    char key;
    do {
        key = keypad.getKey();
        if (key && key != '0' && key != '1') {
            lcd.clear();
            lcd.print("Invalid");

            delay(1000);

            lcd.clear();
            lcd.print("Select dir");
            lcd.setCursor(0, 1);
            lcd.print("0:<-, 1:->");
        }
    } while (key != '0' && key != '1');

    return key == '1';
}

void executeSequence(int power, bool dir) {
    // Correct values
    if (power > 100) {
        power = 100;
    }

    analogWrite(motorPin1, 0);
    analogWrite(motorPin2, 0);
    delay(100);

    lcd.clear();
    lcd.print("Power: ");
    lcd.print(power);
    lcd.setCursor(0, 1);

    if (dir) {
        analogWrite(motorPin1, power*2.55);
        digitalWrite(motorEn1, HIGH);
        digitalWrite(motorEn2, LOW);
        lcd.print("->");
    } else {
        analogWrite(motorPin2, power*2.55);
        digitalWrite(motorEn2, HIGH);
        digitalWrite(motorEn1, LOW);
        lcd.print("<-");
    }

    delay(1000);
}


// Pin1 --- Pin2      Pin3
//           EN


// GND     IN1 --- PWM1
// GND --- IN2     PWM2























