#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

#define LED1 17
#define ANALOG 18

extern "C"
{   
    int userInput(){
        digi
        
    }
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
        return 0;
    }

    int LEDOFF() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LED1, OUTPUT);
        digitalWrite(LED1, LOW);
        return 0;
    }

    int pwmlight(void){
        int sel = 1;
        wiringPiSetupGpio();

        pinMode(ANALOG, PWM_OUTPUT);

        while(sel != 0) {
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
        while(sel != 0) {
            cin >> sel;
            softPwmWrite(ANALOG, 13);    // approximately 15 degree rotate
            delay(170);
            softPwmWrite(ANALOG, 14);    // stop
        }
        return 0;
    }
}