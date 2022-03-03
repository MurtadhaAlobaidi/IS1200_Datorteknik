

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>   /* For random(), RAND_MAX */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameHeader.h"  /* Declatations for these labs */

#define DISPLAY_CHANGE_TO_COMMAND_MODE (PORTFCLR = 0x10)// the command mode works when pins 0to7 is low
#define DISPLAY_CHANGE_TO_DATA_MODE (PORTFSET = 0x10)//the data mode works when pins 0to7 is high

char textstring0[] = "Play Snake";
char textstring1[] = "READY!";

int end = 0;
int score;
void endGame()
{
	end++;
}


int checkEndGame()
{
	return end;
}


//TODO
void display_string(int line, char *s, int location)
{
	int i;
	if(line < 0 || line >= 4)
		return;
	if(!s)//we cant print
		return;

	for(i = location; i < 16; i++)  // i = 0
		if(*s) {
			textbuffer[line][i] = *s;
			s++;
		} else
			textbuffer[line][i] = ' ';
}



void display_update(void) {//after we wrote on Ram, we want it to appear on the screen so we use Update
	int i, j, k;
	int c;
	for(i = 0; i < 4; i++) {
		DISPLAY_CHANGE_TO_COMMAND_MODE;
		spi_send_recv(0x22);
		spi_send_recv(i);

		spi_send_recv(0x0);
		spi_send_recv(0x10);

		DISPLAY_CHANGE_TO_DATA_MODE;

		for(j = 0; j < 16; j++) {
			c = textbuffer[i][j];
			if(c & 0x80)
				continue;

			for(k = 0; k < 8; k++)
				spi_send_recv(font[c*8 + k]);
		}
	}
}

void clearStrings()
{
	display_string( 0, " ",            0 );              // clear the line
  display_string( 1, " ",            0 );              // clear the line
	display_string( 2, " ",            0 );              // clear the linem
	display_string( 3, " ",            0 );              // clear the line
}



void printGameOver( void )
{
  delay( 500 );
	int scr = score;
	char* score = itoaconv(scr);

	clearStrings();

  display_string( 0, "GameOver", 3 );
  display_string( 1, "Score:", 3 );
  display_string( 1, score, 10 );
  display_string( 2, "Play Again?",3 );
  display_string( 3, "Press  BTN4 ",3 );

  display_update();
}


void welcome( void )
{
  clearStrings(); //To clear display after "gameOver" and "Play Snake"
  display_string( 0, textstring0, 4);
  display_string( 2, textstring1, 6);
  display_update();//after every change we clear every thing old and write the new information
}


void stringInit()
{

    DISPLAY_CHANGE_TO_COMMAND_MODE;

    // Set the page address
    
    spi_send_recv(0x20);    //Set memory addressing mode
    spi_send_recv(0x02);    //choose page addressing mode which is 10b in the least significant


    // Set Columns
    
    spi_send_recv(0x0);    // Set Lower Column from column 0
    spi_send_recv(0x10);    // Set Higher Column


    // Set page start
    
    spi_send_recv(0xb0);    //Set page start from page o

    DISPLAY_CHANGE_TO_DATA_MODE;

}

void gameInit(){

    DISPLAY_CHANGE_TO_COMMAND_MODE;

    // Set the page address
    
    spi_send_recv(0x20);    //Set memory addressing mode
    spi_send_recv(0x0);    //choose horizontal addressing mode

    // Start from the left column
    spi_send_recv(0x00);    //set lower nibble of column
    spi_send_recv(0x10);    //set higher nibble of column

    spi_send_recv(0x21);    //Set column address as it exist in manul
    spi_send_recv(0x00);    //column start address and we start from coloumn 0
    spi_send_recv(0x7F);		//column end address and we finish at the last column as it exist in manuell 0111 1111=127

    spi_send_recv(0x22);    //Set page address
    spi_send_recv(0x00);    //page start address and we start from the first page
    spi_send_recv(0x7);     //page end address and we finish at the page 7

    DISPLAY_CHANGE_TO_DATA_MODE;
}
