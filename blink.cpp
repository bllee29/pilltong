#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

#define LED1 17
#define MOTOR 12

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
        char sel;

        if (wiringPiSetup() == -1)
            return 1;

        softPwmCreate(MOTOR, 0, 200);

        while (1)
        {
            fputs("select c, r, l, q: ", stdout);
            scanf("%c", &sel);
            getchar();
            if (sel == 'c') softPwmWrite(MOTOR, 15);   // 0 degree
            else if (sel == 'r') softPwmWrite(MOTOR, 24); // 90 degree
            else if (sel == 'l') softPwmWrite(MOTOR, 5); // -90 degree
            else if (sel == 'q') return 0;
        }

        return 0;
    }
}