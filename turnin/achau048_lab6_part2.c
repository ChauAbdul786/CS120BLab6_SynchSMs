/*	Author: Abdullah Chaudhry
 *  Partner(s) Name: 
 *	Lab Section: 21
 *	Assignment: Lab #6  Exercise #2
 *	Exercise Description: Three blinking lights on PB2 - PB0 blink in ascending order (PB0, PB1, PB2, PB0, PB1, ...), changing lights every 300 ms. 
                          Pressing a button connected to PA0 will pause the sequence on whatever light is currently lit. Pressing the button again
                          will reset the sequence.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#include "timer.h"
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

enum States {Start, pb1On, pb2On, pb3On, button, ledWait} state;

void Tick(){
    switch(state){ //State Transitions
        case Start:
            state = pb1On;
            break;

        case pb1On:
            if(PINA == 0xFE){
                state = button;
            }else{
                state = pb2On;
            }
            break;

        case pb2On:
            if(PINA == 0xFE){
                state = button;
            }else{
                state = pb3On;
            }            
            break;

        case pb3On:
            if(PINA == 0xFE){
                state = button;
            }else{
                state = pb1On;
            }
            break;

        case button:
            if(PINA == 0xFE){
                state = button;
            }else{
                state = ledWait;
            }
            break;

        case ledWait:
            if(PINA == 0xFE){
                state = pb1On;
            }else{
                state = ledWait;
            }
            break;

        default:
            state = pb1On;
            break;
    }

    switch(state){ //State Actions
        case Start:
            break;

        case pb1On:
            PORTB &= 0xF8; //BBBB B000
            PORTB |= 0x01; //BBBB B001
            break;

        case pb2On:
            PORTB &= 0xF8; //BBBB B000
            PORTB |= 0x02; //BBBB BB10
            break;

        case pb3On:
            PORTB &= 0xF8; //BBBB B000
            PORTB |= 0x04; //BBBB B100
            break;

        case button:
            break;

        case ledWait:
            break;

        default:
            PORTB &= 0xF8; //BBBB B000
            PORTB |= 0x01; //BBBB B001
            break;
    }
}

int main(void) {
    /* Insert DDR and PORT initializations */
    DDRA = 0x00; PINA = 0xFF;
    DDRB = 0xFF; PORTB = 0x00;

    /* Insert your solution below */
    TimerSet(300);
    TimerOn();

    while (1) {
        Tick();
        while(!TimerFlag) {}; //Wait 1 second
        TimerFlag = 0;
    }
    return 1;
}
