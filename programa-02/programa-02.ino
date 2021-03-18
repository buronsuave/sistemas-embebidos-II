#include <LiquidCrystal.h>
#include <Keypad.h>

// Keypad varibales
const byte rowsCount = 4;
const byte colsCount = 4;

char keys[rowsCount][colsCount] = {
    { '1', '2', '3', 'A' }, 
    { '4', '5', '6', 'B' }, 
    { '7', '8', '9', 'C' }, 
    { '*', '0', '#', 'D' }
};

byte rowPins[rowsCount] = { 14, 15, 16, 17 };
byte colPins[colsCount] = { 18, 19, 20, 21 };

Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, rowsCount, colsCount);

// LCD variables
const byte RS = 1, EN = 2, D4 = 4, D5 = 5, D6 = 6, D7 = 7;
LiquidCrystal lcd(RS, EN, D4, D5, D6, D7);

// Stepper variables
const byte stepperCount = 4;
const byte INA = 8, INB = 9, INC = 10, IND = 11;
const byte stepperPins[stepperCount] = { INA, INB, INC, IND };
const int stepperDelay = 20;

// Stepper matrixes
const byte halfMatrix[8][4] = {
    { 1, 0, 0, 0 }, 
    { 1, 1, 0, 0 }, 
    { 0, 1, 0, 0 }, 
    { 0, 1, 1, 0 }, 
    { 0, 0, 1, 0 },
    { 0, 0, 1, 1 }, 
    { 0, 0, 0, 1 }, 
    { 1, 0, 0, 1 }
};

const byte fullMatrix[4][4] = {
    { 1, 0, 0, 0 }, 
    { 0, 1, 0, 0 },
    { 0, 0, 1, 0 }, 
    { 0, 0, 0, 1 }
};

const byte normalMatrix[4][4] = {
    { 1, 1, 0, 0 }, 
    { 0, 1, 1, 0 },
    { 0, 0, 1, 1 }, 
    { 1, 0, 0, 1 }
};

// Program
void setup() {
    lcd.begin(16, 2);
    for (int i = 0; i < stepperCount; i++) {
        pinMode(stepperPins[i] , OUTPUT);
    }
}

void loop() {
    bool dir = selectDirection();
    executeSequence(dir);
}

bool selectDirection() {
    lcd.clear();
    lcd.print("Select direction");
    lcd.setCursor(0, 1);
    lcd.print("<-: 0, ->:1");

    char key;
    do {
        key = keypad.getKey();
    } while (key != '0' && key != '1');

    return (key == '1');
}

void executeSequence(bool dir) {
    bool flag = true;

    lcd.clear();
    lcd.print("Select matrix");
    lcd.setCursor(0, 1);
    lcd.print("0: H, 1: F, 2: N");

    char key;
    do {
        key = keypad.getKey();
        switch(key) {
            // Half matrix
            case '0' : {
                flag = false;
                for (int i = 0; i < 512; i++) {
                    for (int j = 0; j < 8; j++) {
                        for (int k = 0; k < stepperCount; k++) {
                            digitalWrite(stepperPins[k], halfMatrix[dir? j:7-j][k]);
                        }
                        delay(stepperDelay);
                    } 
                }
                break;
            }

            // Full matrix
            case '1' : {
                flag = false;
                for (int i = 0; i < 512; i++) {
                    for (int j = 0; j < 4; j++) {
                        for (int k = 0; k < stepperCount; k++) {
                            digitalWrite(stepperPins[k], fullMatrix[dir? j:3-j][k]);
                        }
                        delay(stepperDelay);
                    } 
                }
                break;
            }

             // Normal matrix
            case '2' : {
                flag = false;
                for (int i = 0; i < 512; i++) {
                    for (int j = 0; j < 4; j++) {
                        for (int k = 0; k < stepperCount; k++) {
                            digitalWrite(stepperPins[k], normalMatrix[dir? j:3-j][k]);
                        }
                        delay(stepperDelay);
                    } 
                }
                break;
            }

            default: {
                break;
            }

        }
    } while (flag && key != '0' && key != '1' && key != '2');
}