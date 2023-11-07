#include <stdio.h>
#include <wiringPi.h>

#define LED 17

int main(){
    const int led_pin = 0;

    wiringPiSetup();
    pinMode(LED, OUTPUT);
    while(1){
        digitalWrite(LED, HIGH);
        delay(500);
        digitalWrite(LED, LOW);
        delay(500);
    }
}