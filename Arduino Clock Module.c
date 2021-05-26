/*
Arduino Clock Module | v0.11 | by Jan Sittinger | made in 2021 | handbent.com | @jano.wan @handbent

Pin 2:
|----------------------- 1x bpm

Pin 3:
|-----------|----------- 2x bpm

Pin 4:
|-----|-----|-----|----- 4x bpm

Pin 5:
|--|--|--|--|--|--|--|-- 8x bpm

*/

int clockPins[]{
    2,3,4,5
}; //clock outputs

int inputPins[]{
    6,7,8,9
}; //for future interaction, e.g. switches, buttons

int clockDivs[]{
    2,4,8,16 //selectable in the future
};

int bpm = 100; //beats per minute - is going to be adjustable in the future
int pulseLen = 10; //duration of a clock pulse - is also going to be adjustable

float spacing = 1000/(bpm/60);
int count = 0;

void setup(){
   
    for (int pins = 0; pins < 4; pins++){
        pinMode(clockPins[pins], OUTPUT);
    }

    for (int pins = 0; pins < 4; pins++){
        digitalWrite(clockPins[pins], LOW);
    }

    for (int pins = 0; pins < 4; pins++){
        pinMode(inputPins[pins], INPUT_PULLUP);
    }
}

void loop(){

    //pulsing all outputs on count = 0

    if (count == 0){
        for (int pins = 0; pins < 4; pins++){
            digitalWrite(clockPins[pins], HIGH);
        }
        delay(pulseLen);
        for (int pins = 0; pins < 4; pins++){
            digitalWrite(clockPins[pins], LOW);
        }                
        delay((spacing/clockDivs[2]) - pulseLen);
    }

    //pulsing pins 3,4,5 in the middle of the base clock

    if (count == 4){
        digitalWrite(clockPins[1], HIGH);
        digitalWrite(clockPins[2], HIGH);
        digitalWrite(clockPins[3], HIGH);
        delay(pulseLen);
        digitalWrite(clockPins[1], LOW);
        digitalWrite(clockPins[2], LOW);
        digitalWrite(clockPins[3], LOW);
        delay((spacing/clockDivs[2]) - pulseLen);
    }

    //pulsing pin 4 and 5 on all even divisions of the base clock

    if (count == 2 | count == 6){
        digitalWrite(clockPins[2], HIGH);
        digitalWrite(clockPins[3], HIGH);
        delay(pulseLen);
        digitalWrite(clockPins[2], LOW);
        digitalWrite(clockPins[3], LOW);
        delay((spacing/clockDivs[2]) - pulseLen);
    }

    //pulsing pin 5 on all odd divisions of the base clock

    if ((count % 2 != 0) && count != 0){
        digitalWrite(clockPins[3], HIGH);
        delay(pulseLen);
        digitalWrite(clockPins[3], LOW);
        delay((spacing/clockDivs[2]) - pulseLen);
    }

    if (count >= (clockDivs[2])-1){
            count = 0;
    } else{
        count++;
    }
}