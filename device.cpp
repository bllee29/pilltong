#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

// BCM NUMBER

#define BUZZER 22
// BCM 18 - pin 12, 18 share same pwm
#define SERVO 18
// 2 pwm leds
#define LED1 13
#define LED3 12
// 1 digital led
#define STATE_LED 25
#define END_BUTTON 20
#define CAM_BUTTON 21
#define TEST_BUTTON 16

// #define c3 7692 // 130 Hz
// #define d3 6802 // 147 Hz
// #define e3 6060 // 165 Hz
// #define f3 5714 // 175 Hz
// #define g3 5102 // 196 Hz
// #define a3 4545 // 220 Hz
// #define b3 4048 // 247 Hz
// #define c4 3830 // 261 Hz
// #define d4 3400 // 294 Hz
// #define e4 3038 // 329 Hz
// #define f4 2864 // 349 Hz
// #define g4 2550 // 392 Hz
// #define a4 2272 // 440 Hz
// #define b4 2028 // 493 Hz
// #define c5 1912 // 523 Hz

const int melody[] = { 261, 294, 329, 349, 392, 440, 493, 523 };

const long duration = 200000;
const long pause = 10;


extern "C"
{
    void setup() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiringPi";
            return;
        }

        pinMode(END_BUTTON, INPUT);
        pinMode(CAM_BUTTON, INPUT);
        pinMode(TEST_BUTTON, INPUT);

        pinMode(STATE_LED, OUTPUT);
        pinMode(SERVO, OUTPUT);
        pinMode(BUZZER, OUTPUT);

        pinMode(LED1, PWM_OUTPUT);
        pinMode(LED3, PWM_OUTPUT);
        softPwmCreate(SERVO, 0, 200);

    }

    void STATE(int state) {
        digitalWrite(STATE_LED, state);
    }

    void LEDON(int pin, int bright) {
        if(pin == 1){
            pwmWrite(LED1, bright);
        }
        else{
            pwmWrite(LED1, bright);
            pwmWrite(LED3, bright);        
        }
    }

    void LEDOFF(int num) {
        if (num == 0) {
            digitalWrite(STATE_LED, LOW);
        }
        else if (num == 1) {
            pwmWrite(LED1, LOW);
        }
        else if (num == 2) {
            pwmWrite(LED3, LOW);
        }
        else {
            digitalWrite(STATE_LED, LOW);
            pwmWrite(LED1, LOW);
            pwmWrite(LED3, LOW);
        }
    }

    //sg-90 360 degree servo motor
    void turn() {
        // approximately 15 degree rotate
        softPwmWrite(SERVO, 13);
        delay(200);

        // stop
        softPwmWrite(SERVO, 14);
    }

    int buzzer() {
        long elapsed_time = 0;
        int tone_ = melody[0];
        for (int i = 0; i < 16; ++i) {
            tone_ = melody[i];
            while (1) {
                tone_ = (tone_ + 1) % 16;
                digitalWrite(BUZZER, HIGH);
                delayMicroseconds(tone_ / 2);
                digitalWrite(BUZZER, LOW);
                delayMicroseconds(tone_ / 2);
            }
        }
        return 0;
    }

    bool button1(int& val, int& old_val) {
        val = digitalRead(TEST_BUTTON);
        if ((val == HIGH) && (old_val == LOW)) {
            return true;
        }
        old_val = val;
        return false;
    }

    bool button2(int& val, int& old_val) {
        val = digitalRead(END_BUTTON);
        if ((val == HIGH) && (old_val == LOW)) {
            return true;
        }
        old_val = val;
        return false;
    }

    bool button3(int& val, int& old_val) {
        val = digitalRead(CAM_BUTTON);
        if ((val == HIGH) && (old_val == LOW)) {
            return true;
        }
        old_val = val;
        return false;
    }

    // main
    // cant use global variable in extern dynamic alloc problem
    int main() {
        int val1(LOW), val2(LOW), val3(LOW);
        int old_val1(LOW), old_val2(LOW), old_val3(LOW);
        unsigned long time = millis();
        int state = 0;
        while (1) {
            // blink while waiting input
            if (millis() - time > 1000) {
                STATE(state);
                state = 1 - state;
                time = millis();
            }
            if (button1(val1, old_val1)) {
                return 0;
            };
            if (button2(val2, old_val2)) {
                return 1;
            };
            if (button3(val3, old_val3)) {
                return 2;
            };
        }
    }
}