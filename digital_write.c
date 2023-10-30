#include <stdio.h>
#include <wiringPi.h>

int main(){
    const int led_pin = 0;

    wiringPiSetup();
    
    pinMode(led_pin, OUTPUT);

    digitalWrite(led_pin, HIGH);
}