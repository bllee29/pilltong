#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

// BCM NUMBER
#define LED1 17
#define ANALOG 18
#define ENDBUTTON 20
#define CAMBUTTON 21
#define TESTBUTTON 16

extern "C"
{    
    int buttonTest() {
        wiringPiSetupGpio();
        pinMode(17, OUTPUT);
        pinMode(20, INPUT);
        pinMode(21, INPUT);
        pinMode(16, INPUT);

        while (true) {
            if (digitalRead(20) || digitalRead(21) || digitalRead(16)) {
                digitalWrite(17, HIGH);
            }
            else {
                digitalWrite(17, LOW);
            }

        }
    }

    int pwmlight() {
        int sel = 1;
        wiringPiSetupGpio();

        pinMode(ANALOG, PWM_OUTPUT);

        while (sel != 0) {
            cin >> sel;
            pwmWrite(ANALOG, sel);
        }
        return 0;
    }

    int servo() {
        int sel = 1;
        wiringPiSetupGpio();
        pinMode(ANALOG, OUTPUT);
        softPwmCreate(ANALOG, 0, 200);
        while (sel != 0) {
            cin >> sel;
            softPwmWrite(ANALOG, 13);    // approximately 15 degree rotate
            delay(170);
            softPwmWrite(ANALOG, 14);    // stop
        }
        return 0;
    }
}