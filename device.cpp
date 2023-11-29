#include <iostream>
#include <wiringPi.h>
#include <softPwm.h>

using namespace std;

// BCM NUMBER
#define SERVO 13
#define BUZZER 25
#define LED1 17
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
    void setup() {
        if (wiringPiSetupGpio() < 0) {
            cout << "Unable to setup wiringPi";
            return;
        }
        pinMode(ENDBUTTON, INPUT);
        pinMode(CAMBUTTON, INPUT);
        pinMode(TESTBUTTON, INPUT);

        pinMode(LED1, OUTPUT);
        pinMode(LEDANALOG, OUTPUT);
        pinMode(SERVO, OUTPUT);
        pinMode(BUZZER, OUTPUT);

        softPwmCreate(SERVO, 0, 200);
    }

    void LEDON(int bright) {
        pinMode(LEDANALOG, PWM_OUTPUT);
        pwmWrite(LEDANALOG, bright);
    }

    void LEDOFF() {
        pinMode(LEDANALOG, OUTPUT);
        digitalWrite(LEDANALOG, LOW);
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
    
    bool button1(int& val, int& old_val) {
        val = digitalRead(TESTBUTTON);
        if ((val == HIGH) && (old_val == LOW)) {
            return true;
        }
        old_val = val;
    }

    bool button2(int& val, int& old_val) {
        val = digitalRead(ENDBUTTON);
        if ((val == HIGH) && (old_val == LOW)) {
            return true;
        }
        old_val = val;
    }

    bool button3(int& val, int& old_val) {
        val = digitalRead(CAMBUTTON);
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
        setup();
        // loop
        while (1) {
            if(button1(val1, old_val1)){
                return 0;
            };
            if(button2(val2, old_val2)){
                return 1;
            };
            if(button3(val3, old_val3)){
                return 2;
            };
        }
    }       
}