#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>   /* For random(), RAND_MAX */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameHeader.h"  /* Declatations for these labs */

uint8_t btn,end;
int wait = 100; // spels hastighet
int score=0;
// begin the code:

void beginWithString()
{
 stringInit(); //stringwork.c // To set the page address, set colums and set start page.
 welcome(); // stringwork.c // To write the welcome page.
}


void beginTheGame()//intilize every thing
{
   gameInit(); //To Write on horizental mode // set the address page and to start from the left colums
   GetFood();  // prepretions.c // To put the food in the random places and turn on the food.
 }

void mainfunction()
{
  while( 1 )//to continue until gameOver
  {
    delay( wait ); //frem 
    snakeUpdate(); //snake.c // To clare the old snake and uppdate the game
    delay( wait );
    display_image();//functions.c //To send the data to display and tell the display 
                    //everytime which will turn on and update the game  


    end = checkEndGame();
    if (end >= 1)
    {
      int scr = score;
      end = 0;
      stringInit(); //stringword.c //To set the page address, set columns and set the start page
      printGameOver(); //stringword.c //To print last page with gameover, score etc.
      break;
    }
  }
}

void ContinuePlaying()
{
  btn = getbtns();
  while (btn != 4)
  {
    if (getbtns() == 8) //To change the btns (2(btn2), 4(btn3), 8(btn4))
    {
      btn = 4;
      break;
    }
  }
}

void run()
{
  display_init();//functions and it is from the labs(from basic I/O Shield)

  while (1)
  {
    snakeInit();// snake.c // The function discribe how the snake can move and the size
    beginWithString(); // game.c
    delay( 2000 ); // time for start page
    beginTheGame(); // game.c
    mainfunction(); // game.c
    ContinuePlaying(); // game.c // To continue the game press btn4
    clearDisplay(); // functions.c // Clear all information 
  }

}
