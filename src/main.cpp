#include "mbed.h"

DigitalOut led_red(p6);
DigitalOut led_gren(p7);
DigitalOut led_yellow(p8);
InterruptIn Button(p5);

char trigger;
int t = 0;//elapsed time
int tBt = 0;//time Button pressed

void int_button1() {trigger |= 0x01;}
void int_button2() {trigger = 0;}

// estado 0 = red
// estado 1 = gren
// estado 2 = yellow
// estado 3 = alert
// estado 4 = off


int main() {
    
    //estado inicial
    int state = 0;
    int ant_state = 0;
    int blink = 0;
    led_red = !led_red;
    //estado inicial
    
    Button.rise(&int_button1);
    Button.fall(&int_button2);
    
    while (1) {
        
        printf("t: %d tBt: %d\n blink: %d\n", t, tBt, blink);
        
        switch(state){
            case 0:
            if(t == 10000){
                state = 1;
                led_red = !led_red;
                led_gren = !led_gren;
                t = 0;
            }else if(tBt > 10000 && trigger == 0){
                state = 4;
                led_red = !led_red;
                tBt = 0;
            }else if(tBt >= 3000 && tBt <= 10000 && trigger == 0){
                ant_state = state;
                state = 3;
                led_red = !led_red;
                tBt = 0;
            }
            
            break;
            
            case 1:
            if(t == 20000){
                state = 2;
                led_gren = !led_gren;
                led_yellow = !led_yellow;
                t = 0;
            }else if(tBt > 10000 && trigger == 0){
                state = 4;
                led_gren = !led_gren;
                tBt = 0;
            }else if(tBt >= 3000 && tBt <= 10000 && trigger == 0){
               ant_state = state;
                state = 3;
                led_gren = !led_gren;
                tBt = 0;
            }
            
            break;
            
            case 2:
            if(t == 4000){
                state = 0;
                led_yellow = !led_yellow;
                led_red = !led_red;
                t = 0;
            }else if(tBt > 10000 && trigger == 0){
                state = 4;
                led_yellow = !led_yellow;
                tBt = 0;
            }else if(tBt >= 3000 && tBt <= 10000 && trigger == 0){
                ant_state = state;
                state = 3;
               led_yellow = !led_yellow;
                tBt = 0;
            }
            break;
            
            case 3:
            blink = 1;
            if(tBt >= 3000 && tBt <= 10000 && trigger == 0){
                state = ant_state;
                tBt = 0;
                t = 0;
                blink = 0;
                if(led_yellow == 1){
                    led_yellow = !led_yellow;
                }
                if(state == 0){
                    led_red = !led_red;
                }else if(state == 1){
                    led_gren = !led_gren;
                }else if(state == 2){
                    led_yellow = !led_yellow;
                }
                
            }else if(tBt > 10000 && trigger == 0){
                state = 4;
                tBt = 0;
                blink = 0;
            }
            break;
            
            case 4:
            if(tBt > 10000 && trigger == 0){
                state = 0;
                led_red = !led_red;
                tBt = 0;
                t = 0;
            }
            break;
        }
        
        if(blink == 1){
            led_yellow = !led_yellow;
            wait_ms(500);
        }
        
        wait_ms(500);
        t = t+500;
        
        if (trigger & 0x01){
            tBt = tBt+500;
        }
        
    }
    
}