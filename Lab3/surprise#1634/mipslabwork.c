/* mipslabwork.c

   This file written 2015 by F Lundevall
   Updated 2017-04-21 by F Lundevall

   This file should be changed by YOU! So you must
   add comment(s) here with your name(s) and date(s):

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "mipslab.h"  /* Declatations for these labs */

int prime = 1234567;
int mytime = 0x5957;
//volatile int(för att pekaren PE/TE kan plötsligt ändra sitt värde vilket gör att compilatorn kmr vilja optimisera variabeln till sitt gamla värde vilket vi inte vill).
//PE Port E are set as outputs (med att göra PE är 0)Port E so that bits 7 through 0
//TE Register TRISE has address 0xbf886100 (outputs)
volatile int* PE = (volatile int*) 0xbf886110;
volatile int* TE = (volatile int*) 0xbf886100;

char textstring[] = "text, more text, and even more text!";

int timeoutcount = 0; // Declare timeoutcount
/* Interrupt Service Routine */
void user_isr( void ){

    /*surprise start*/
    if(IFS(0) & 0x80000) {
        IFSCLR(0) = 0x80000;
        *((volatile int *)0xbf886110) += 1; // D. PORTE Increment by 1 bit.
    }
    /*surprise End*/
    
     if(IFS(0) & 0x100){ // check if interrupt register flag is enabled
     timeoutcount++; // Increment timeoutcount
     IFSCLR(0) = 0x100; //Reset the timeout flag
  }
   
    
  if(timeoutcount == 10){
    time2string( textstring, mytime );
    display_string( 3, textstring );
    display_update();
    tick( &mytime );
    timeoutcount = 0;
  }
IFSCLR(0) = 0x100;    // Clear flag
}

/* Lab-specific initialization goes here */
void labinit( void )
{
    PR2 = 31249;  //Set period to 1/10 of a second (31250) 80M/10 =PS*(PR2+1)               //PS(prescelar)=256
    T2CON = 0x0;                    //Clearing clock
    T2CONSET = 0x70;              //Set prescale to 256                                                   //processor capacity
                                //16 bit timers – These can count between 0-65536
    TMR2 = 0;                       //Reset timer //den gör timer till 0
    T2CONSET = (1 << 15);            // turn timer on

    TRISDSET = (0xFF << 5);       //Set port D for input
    *TE &= ~(0xFF);               //Set port E for output
    *PE &= ~(0xFF);               //Reset the LED bits

    IPC(2) = IPC(2) | 0x10;
    // Enable interrupt for timer2
    IEC(0) = IEC(0) | 0x100;

    IECCLR(0) = 0x00080000; // disable INT4
    IFSCLR(0) = 0x00080000; // clear the interrupt flag
    IECSET(0)= 0x00080000; // enable INT4
  
    IPC(4) = IPC(4) | 0x100;
    
    enable_interrupt();
    return;
}

/* This function is called repetitively from the main program */
void labwork( void ) {
  prime = nextprime( prime );
  display_string( 0, itoaconv( prime ) );
  display_update();
}
