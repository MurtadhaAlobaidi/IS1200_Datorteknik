#include <stdint.h>
#include <pic32mx.h>
#include "mipslab.h"
#include "time4io.h"

int getsw(void) {
    // 0000 => SW nere, 0101 => SW 3 och SW 1 är uppe
    int output = 0;
    //while(1) {
        // PORTD kolla in på 0xF00
        // SW4 = 1, = 1000. SW3 = 1, 0100. SW2 = 1, 0010. SW1 = 1, 0001. 
        output = (PORTD >> 8) & 0xF;

    //}
    return (output > 9) ? 9 : output;// Each bit is a SW
}

int getbtns(void) {
    int output = (PORTD >> 5) & 0x7;
    // HOLD a BTN = >1, RELEASE a btn = 0
    // btn4 = 8, btn3 = 4, btn2 = 2 (ouput)
    return output; //0x0001;
}
