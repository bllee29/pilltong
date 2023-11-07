#include <iostream>
#include <wiringPi.h>

using namespace std;

#define LED1 17

extern "C"
{
    int blink(){
        if(wiringPiSetupGpio() < 0){
            cout << "Unable to setup wiring pi";
            return 1;
        }
        pinMode(LED1, OUTPUT);

        while(true){
            digitalWrite(LED1, HIGH);
            delay(500);
            digitalWrite(LED1, LOW);
            delay(500);
        }
    }
}