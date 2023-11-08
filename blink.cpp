#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

#define LED1 17
#define MOTOR 18

extern "C"
{
    int blink() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LED1, OUTPUT);

        while (true) {
            digitalWrite(LED1, HIGH);
            delay(10000);
            digitalWrite(LED1, LOW);
            delay(500);
        }
    }

    int LEDON() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LED1, OUTPUT);
        digitalWrite(LED1, HIGH);
    }

    int LEDOFF() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LED1, OUTPUT);
        digitalWrite(LED1, LOW);
    }        

    int servo() {
        int sel = 1;
        wiringPiSetupGpio();
        pinMode(MOTOR, OUTPUT);
        softPwmCreate(MOTOR, 0, 200);
        while(sel != 0) {
            cin << sel
            softPwmWrite(MOTOR, 13);    // approximately 15 degree rotate
            delay(170);
            softPwmWrite(MOTOR, 14);    // stop
        }
        return 0;
    }
}