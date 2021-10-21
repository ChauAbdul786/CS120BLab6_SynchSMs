/*	Author: Abdullah Chaudhry
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #6  Exercise #3
 *	Exercise Description: Output for PORTB is initially 7. Pressing or holding PA0 will increment B every 100ms. Pressing or holding
                          PA1 will decrement B every 100ms. Pressing both PA0 and PA1 will reset B to 7. B has a range of 0 - 9.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *
 *  Demo Link: https://drive.google.com/file/d/1AmKogTQtLYRt-bJ-6TgtAbTVz1pRQQ4B/view?usp=sharing
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, state} State; 
unsigned char tmpA;
unsigned char tmpB;

void Tick(){
    switch(State){ //State Transitions
        case Start:
            State = state;
            tmpB = 0x07;
            break;

        case state:
            if((tmpA & 0x03) == 0x03){
                //Do nothing
            }else if((tmpA & 0x03) == 0x02){
                if(tmpB < 9){
                    tmpB++;
                }
            }else if((tmpA & 0x03) == 0x01){
                if(tmpB > 0){
                    tmpB--;
                }
            }else if((tmpA & 0x03) == 0x00){
                tmpB = 0;
            }
            break;

        default:
            State = state;
            break;
    }
    //No State Actions
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;
    DDRB = 0xFF; PORTB = 0x07;

    /* Insert your solution below */
    TimerSet(100);
    TimerOn();

    while (1) {
        tmpA = PINA;
        Tick();
        PORTB = tmpB;
        while(!TimerFlag) {}; //Wait 1 second
        TimerFlag = 0;
    }
    return 1;
}
