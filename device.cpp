#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

// BCM NUMBER
#define SERVO 13
#define LEDANALOG 18
#define ENDBUTTON 20
#define CAMBUTTON 21
#define TESTBUTTON 16

extern "C"
{
    int userInput() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        while (TRUE) {
            if (digitalRead(16)) {
                return 0;
            }
            if (digitalRead(20)) {
                return 1;
            }
            if (digitalRead(21)) {
                return 2;
            }
        }
    }

    int LEDON(int bright) {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LEDANALOG, PWM_OUTPUT);
        digitalWrite(LED1, bright);
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

    int turn() {
        //sg-90 360 degree servo motor
        wiringPiSetupGpio();
        pinMode(SERVO, OUTPUT);
        softPwmCreate(SERVO, 0, 200);

        // approximately 15 degree rotate
        softPwmWrite(SERVO, 13);    
        delay(170);

        // stop
        softPwmWrite(SERVO, 14);

        return 0;
    }           
    
    // functions for testing

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