/* mipslabfunc.c
   This file written 2015 by F Lundevall
   Some parts are original code written by Axel Isaksson

   For copyright and licensing, see file COPYING */

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameHeader.h"  /* Declatations for these labs */


uint8_t speed = 1;
uint8_t array[512] = {
		// the first line
		0, 254, 254, 254, 254, 254, 254, 254,     /* 0st-7th    column*/
		254, 254, 254, 254, 254, 254, 254, 254,     // 8th-15th   column
		254, 254, 254, 254, 254, 254, 254, 254,     // 16th-23th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 24th-31th  column

		254, 254, 254, 254, 254, 254, 254, 254,     // 32th-39th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 40th-47th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 48th-55th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 56th-63th  column

		254, 254, 254, 254, 254, 254, 254, 254,     // 64th-71th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 72th-79th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 80th-87th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 88th-95th  column

		254, 254, 254, 254, 254, 254, 254, 254,     // 96th-103th  column
		254, 254, 254, 254, 254, 254, 254, 254,     // 104th-111th column
		254, 254, 254, 254, 254, 254, 254, 254,     // 112th-119th column
		254, 254, 254, 254, 254, 254, 254, 0,     // 120th-127th column


		// the second line
		0, 255, 255, 255, 255, 255, 255, 255,     /* 0st-7th    column*/
		255, 255, 255, 255, 255, 255, 255, 255,     // 8th-15th   column
		255, 255, 255, 255, 255, 255, 255, 255,     // 16th-23th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 24th-31th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 32th-39th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 40th-47th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 48th-55th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 56th-63th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 64th-71th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 72th-79th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 80th-87th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 88th-95th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 96th-103th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 104th-111th column
		255, 255, 255, 255, 255, 255, 255, 255,     // 112th-119th column
		255, 255, 255, 255, 255, 255, 255, 0,     // 120th-127th column

		// the third line
		0, 255, 255, 255, 255, 255, 255, 255,     /* 0st-7th    column*/
		255, 255, 255, 255, 255, 255, 255, 255,     // 8th-15th   column
		255, 255, 255, 255, 255, 255, 255, 255,     // 16th-23th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 24th-31th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 32th-39th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 40th-47th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 48th-55th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 56th-63th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 64th-71th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 72th-79th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 80th-87th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 88th-95th  column

		255, 255, 255, 255, 255, 255, 255, 255,     // 96th-103th  column
		255, 255, 255, 255, 255, 255, 255, 255,     // 104th-111th column
		255, 255, 255, 255, 255, 255, 255, 255,     // 112th-119th column
		255, 255, 255, 255, 255, 255, 255, 0,     // 120th-127th column


		// the fourth and last line
		0, 127, 127, 127, 127, 127, 127, 127,     /* 0st-7th    column*/
		127, 127, 127, 127, 127, 127, 127, 127,     // 8th-15th   column
		127, 127, 127, 127, 127, 127, 127, 127,     // 16th-23th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 24th-31th  column

		127, 127, 127, 127, 127, 127, 127, 127,     // 32th-39th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 40th-47th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 48th-55th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 56th-63th  column

		127, 127, 127, 127, 127, 127, 127, 127,     // 64th-71th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 72th-79th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 80th-87th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 88th-95th  column

		127, 127, 127, 127, 127, 127, 127, 127,     // 96th-103th  column
		127, 127, 127, 127, 127, 127, 127, 127,     // 104th-111th column
		127, 127, 127, 127, 127, 127, 127, 127,     // 112th-119th column
		127, 127, 127, 127, 127, 127, 127, 0,     // 120th-127th column
};

//void welcome();


/* Declare a helper function which is local to this file */
static void num32asc( char * s, int );

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)

#define DISPLAY_ACTIVATE_RESET (PORTGCLR = 0x200)
#define DISPLAY_DO_NOT_RESET (PORTGSET = 0x200)

#define DISPLAY_ACTIVATE_VDD (PORTFCLR = 0x40)
#define DISPLAY_ACTIVATE_VBAT (PORTFCLR = 0x20)

#define DISPLAY_TURN_OFF_VDD (PORTFSET = 0x40)
#define DISPLAY_TURN_OFF_VBAT (PORTFSET = 0x20)



uint8_t spi_send_recv(uint8_t data) {
	while(!(SPI2STAT & 0x08));
	SPI2BUF = data;
	while(!(SPI2STAT & 1));
	return SPI2BUF;
}

/* quicksleep:
   A simple function to create a small delay.
   Very inefficient use of computing resources,
   but very handy in some special cases. */
void quicksleep(int cyc) {
	int i;
	for(i = cyc; i > 0; i--);
}

void user_isr( void )
{
  return;
}

/**
** almost copy and paste from basic I/O Shield
*/
void display_init(void)
{
	/* We're going to be sending commands, so clear the Data/Cmd bit
  */
  DISPLAY_CHANGE_TO_COMMAND_MODE;
	quicksleep(10);
	/* Start by turning VDD on and wait a while for the power to come up.
	*/
	DISPLAY_ACTIVATE_VDD;
	quicksleep(1000000);


	/* Display off command
  */
  spi_send_recv(0xAE);

  /* Bring Reset low and then high
  */
	DISPLAY_ACTIVATE_RESET;
	quicksleep(10);
	DISPLAY_DO_NOT_RESET;
	quicksleep(10);

  /* Send the Set Charge Pump and Set Pre-Charge Period commands
  */
  spi_send_recv(0x8D);
  spi_send_recv(0x14);

  spi_send_recv(0xD9);
  spi_send_recv(0xF1);


  /* Turn on VCC and wait for a little bit
  */
	DISPLAY_ACTIVATE_VBAT;
	quicksleep(10000000);
  //PORTClearBits(prtVbatCtrl, bitVbatCtrl);


  /* Send the commands to invert the display. This puts the display origin
  ** in the upper left corner.
  */
  spi_send_recv(0xA1);          //remap columns
  spi_send_recv(0xC8);          //remap the rows

  /* Send the commands to select sequential COM configuration. This makes the
  ** display memory non-interleaved.
  */
  spi_send_recv(0xDA);        //set COM configuration command
  spi_send_recv(0x20);        //sequential COM, left/right remap enabled

  /* Send Display On command
  */
  spi_send_recv(0xAF);


}

void display_image()
{

		DISPLAY_CHANGE_TO_DATA_MODE;

		/* send the data to display
		*/
		int j;
		for(j = 0; j < 512; j++){
			spi_send_recv(~array[j]);
		}

}


int getsw(void) {
  return ((PORTD & 0xf00) >> 8);
}

int getbtns(void) {
  int btn4 = ((PORTD & 0x80) >> 4); 
  return btn4;
}

void checkSwitches(void)
{
    int sw = getsw();

    if (sw == 1) {  // SW1=0001 
        direction(speed,0);     // right(); 
    }
   else if (sw == 4) {  // SW3=0100 
        direction(0,-1*speed);     // up();
    }
    else if (sw ==8 ) {  // SW4 =1000
        direction(0,speed);   //  down();
    }
    else if (sw == 2) {  // sw2  = 0010
        direction(-1*speed,0);  //left();
    }
}


void lightUp(int x, int y, int setValueTo)//x and y
{

    int rows  = 32; // 
    int col = 128;   // 
    int bitsInOneArray = 8;  //there are 8 (8 pixel) nibble in one page

    int page = (y / bitsInOneArray);//to know in which page is the point (31/8=3,9=3)
    int block = (page * col) + x;   //---> one array, to know exactly which column in the array(3*128+127=511)
    uint8_t temp = array[block];// array to the block means one column

    int bit = y % bitsInOneArray; //(31 % 8= 7)

		int shiftedNumber = 1 << bit; //0-128 (1000 0000 binär)

		if (setValueTo == 1) {  //1 
			temp = temp | shiftedNumber;
		}
		else if(setValueTo == 0) { //0
			temp = temp & (~shiftedNumber);//temp is column
		}
    array[block] = temp;
}

// Function to turn on/off the border
void clearDisplay()
{
	int x, y;
	for(x = 0; x < 128; x++)
	{
		for (y = 0; y < 32; y++) 
		{
			if (y == 0 || y == 31 || x == 0 || x == 127) //for the border
			{
				lightUp(x,y,0); // the border is lighted. // function.c
			}
			else
				lightUp(x,y,1); // the border is unlighted.
		}
	}
}

/*
 * itoa
 *
 * Simple conversion routine
 * Converts binary to decimal numbers
 * Returns pointer to (static) char array
 *
 * The integer argument is converted to a string
 * of digits representing the integer in decimal format.
 * The integer is considered signed, and a minus-sign
 * precedes the string of digits if the number is
 * negative.
 *
 * This routine will return a varying number of digits, from
 * one digit (for integers in the range 0 through 9) and up to
 * 10 digits and a leading minus-sign (for the largest negative
 * 32-bit integers).
 *
 * If the integer has the special value
 * 100000...0 (that's 31 zeros), the number cannot be
 * negated. We check for this, and treat this as a special case.
 * If the integer has any other value, the sign is saved separately.
 *
 * If the integer is negative, it is then converted to
 * its positive counterpart. We then use the positive
 * absolute value for conversion.
 *
 * Conversion produces the least-significant digits first,
 * which is the reverse of the order in which we wish to
 * print the digits. We therefore store all digits in a buffer,
 * in ASCII form.
 *
 * To avoid a separate step for reversing the contents of the buffer,
 * the buffer is initialized with an end-of-string marker at the
 * very end of the buffer. The digits produced by conversion are then
 * stored right-to-left in the buffer: starting with the position
 * immediately before the end-of-string marker and proceeding towards
 * the beginning of the buffer.
 *
 * For this to work, the buffer size must of course be big enough
 * to hold the decimal representation of the largest possible integer,
 * and the minus sign, and the trailing end-of-string marker.
 * The value 24 for ITOA_BUFSIZ was selected to allow conversion of
 * 64-bit quantities; however, the size of an int on your current compiler
 * may not allow this straight away.
 */
#define ITOA_BUFSIZ ( 24 )
char * itoaconv( int num )
{
  register int i, sign;
  static char itoa_buffer[ ITOA_BUFSIZ ];
  static const char maxneg[] = "-2147483648";

  itoa_buffer[ ITOA_BUFSIZ - 1 ] = 0;   /* Insert the end-of-string marker. */
  sign = num;                           /* Save sign. */
  if( num < 0 && num - 1 > 0 )          /* Check for most negative integer */
  {
    for( i = 0; i < sizeof( maxneg ); i += 1 )
    itoa_buffer[ i + 1 ] = maxneg[ i ];
    i = 0;
  }
  else
  {
    if( num < 0 ) num = -num;           /* Make number positive. */
    i = ITOA_BUFSIZ - 2;                /* Location for first ASCII digit. */
    do {
      itoa_buffer[ i ] = num % 10 + '0';/* Insert next digit. */
      num = num / 10;                   /* Remove digit from number. */
      i -= 1;                           /* Move index to next empty position. */
    } while( num > 0 );
    if( sign < 0 )
    {
      itoa_buffer[ i ] = '-';
      i -= 1;
    }
  }
  /* Since the loop always sets the index i to the next empty position,
   * we must add 1 in order to return a pointer to the first occupied position. */
  return( &itoa_buffer[ i + 1 ] );
}
