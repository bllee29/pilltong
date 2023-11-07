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
            delay(500);
            digitalWrite(LED1, LOW);
            delay(500);
        }
    }

    int servo() {
        wiringPiSetupGpio();
        pinMode(MOTOR, OUTPUT);
        softPwmCreate(MOTOR, 0, 200);
        for (;;) {
            softPwmWrite(MOTOR, 10);
            delay(500);
            softPwmWrite(MOTOR, 15);
            delay(500);
            softPwmWrite(MOTOR, 20);
            delay(500);
        }
        return 0;
    }
}