#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

// BCM NUMBER
#define SERVO 13
#define BUZZER 25
#define LEDANALOG 18
#define ENDBUTTON 20
#define CAMBUTTON 21
#define TESTBUTTON 16

#define c3 7692 // 130 Hz
#define d3 6802 // 147 Hz
#define e3 6060 // 165 Hz
#define f3 5714 // 175 Hz
#define g3 5102 // 196 Hz
#define a3 4545 // 220 Hz
#define b3 4048 // 247 Hz
#define c4 3830 // 261 Hz
#define d4 3400 // 294 Hz
#define e4 3038 // 329 Hz
#define f4 2864 // 349 Hz
#define g4 2550 // 392 Hz
#define a4 2272 // 440 Hz
#define b4 2028 // 493 Hz
#define c5 1912 // 523 Hz

const int melody[] = {261, 294, 329, 349, 392, 440, 493, 523};

const long duration = 200000;
const long pause = 10;


extern "C"
{
    int userInput() {
        int state[3];
        int old_state[3];
        
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        
        pinMode(ENDBUTTON, INPUT);
        pinMode(CAMBUTTON, INPUT);
        pinMode(TESTBUTTON, INPUT);

        while (TRUE) {
            state[0] = digitalRead(16);
            state[1] = digitalRead(20);
            state[2] = digitalRead(21);
            if ((state[0] == HIGH) && (old_state[0] == LOW)) {
                return 0;
            }
            else if ((state[1] == HIGH) && (old_state[1] == LOW)) {
                return 1;
            }
            else if ((state[2] == HIGH) && (old_state[2] == LOW)) {
                return 2;
            }
            old_state[0] = state[0];
            old_state[1] = state[1];
            old_state[2] = state[2];
        }
    }

    int LEDON(int bright) {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LEDANALOG, PWM_OUTPUT);
        pwmWrite(LEDANALOG, bright);
        return 0;
    }


    int LEDOFF() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LEDANALOG, OUTPUT);
        digitalWrite(LEDANALOG, LOW);
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

    int buzzer() {
        wiringPiSetupGpio();

        pinMode(BUZZER, OUTPUT);
        long elapsed_time = 0;
        int tone_ = c4;
        for(int i = 0; i < 16; ++i){
            tone_ = melody[i];
            while(1){
                tone_ = (tone_+1) % 16;
                digitalWrite(BUZZER,HIGH);
                delayMicroseconds(tone_ / 2);
                digitalWrite(BUZZER,LOW);
                delayMicroseconds(tone_ / 2);
            }
        }     
        return 0;
    }

    int pwmlight() {
        int sel = 1;
        wiringPiSetupGpio();

        pinMode(LEDANALOG, PWM_OUTPUT);

        while (sel != 0) {
            cin >> sel;
            pwmWrite(LEDANALOG, sel);
        }
        return 0;
    }
    


    int servo() {
        int sel = 1;
        wiringPiSetupGpio();
        pinMode(LEDANALOG, OUTPUT);
        softPwmCreate(LEDANALOG, 0, 200);
        while (sel != 0) {
            cin >> sel;
            softPwmWrite(LEDANALOG, 13);    // approximately 15 degree rotate
            delay(170);
            softPwmWrite(LEDANALOG, 14);    // stop
        }
        return 0;
    }            
}