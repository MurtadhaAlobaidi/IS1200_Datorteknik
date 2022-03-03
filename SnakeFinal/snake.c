

#include <stdint.h>   /* Declarations of uint_32 and the like */
#include <stdlib.h>   /* For random(), RAND_MAX */
#include <pic32mx.h>  /* Declarations of system-specific addresses etc */
#include "gameHeader.h"  /* Declatations for these labs */

//uint8_t xUR, yUR, xDR, yDR, xUL, yUL, xDL, yDL;
int xSpeed, ySpeed;
int total, scale, score;
uint8_t min = 5;     //1
uint8_t xMax = 120;  //127
uint8_t yMax = 25;    // 31

struct Point {
  uint8_t x;
  uint8_t y;

  uint8_t x2;
  uint8_t y2;

  uint8_t x3;
  uint8_t y3;

  uint8_t x4; //= x+1;
  uint8_t y4; // = y+1;
};



struct Point currentXY;  // currentLocation
struct Point previousXY;
struct Point tail[511];
struct Point prevTail[511];

void check();
void snakeDisplay();
void eat();
void moveTail();
void increaseScore();

void snakeInit(void)//to intilize a place for the snake
{
  setPoint(&previousXY,0,0);//& to take the address of previous
  setPoint(&currentXY, 63,15); // Y-led är 31bit och X-led är 127bit (128x32 pixel) //Where will the snake begin

  xSpeed = 1; //1 åt höger och -1 åt vänster
  ySpeed = 0; //1 nedåt och -1 åt uppåt
  scale = 1; // Numbers of steps
  score = 0;
  total = 0; // Snake length
  int i;
  struct Point temp;

  for (i = 0; i < 511; i++) //511 max score that snake can be
  {
    tail[i] = temp;//put tail in all the screen
    prevTail[i] = temp;
  }

}



void tailWork(uint8_t value)//total for scores
{
  int i;
  struct Point temp;
  for (i = 0; i < total; i++)
  {
    temp = tail[i];

    if (value == 0)
    {
    draw(&temp,0,0);
    }
    else if (value == 1)
    {
    draw(&temp,1,1);
    }

  }
}


void drawSnake(){
  tailWork(0);
}

void clearSnake() {
  tailWork(1);
}

void direction(int xSp, int ySp)
{
  xSpeed = xSp;
  ySpeed = ySp;
}



int checkEatHelper(uint8_t xx, uint8_t yy, uint8_t xf, uint8_t yf)
{
  if ((xx == xf && yy == yf )) { //Snake head(2 pixel) == Snake food(4 pixel)
    return 5;
  }
 else if ((xx == xf+1 && yy == yf) ) {
    return 5;
  }
  else if ((xx == xf && yy == yf + 1)) {
    return 5;
  }
  else if ( (xx == xf +1 && yy == yf + 1)){
    return 5;
  }
  else {
    return 0;
  }
}


struct Point food;
int checkEat()
{
  uint8_t xf = food.x;
  uint8_t yf = food.y;

  
  uint8_t xUL = currentXY.x;
  uint8_t yUL = currentXY.y;
  uint8_t xDL = currentXY.x2;
  uint8_t yDL = currentXY.y2;

  int r1 = checkEatHelper(xUL, yUL, xf, yf);//two points
  int r2 = checkEatHelper(xDL, yDL, xf, yf);

  if (r1 == 5 || r2 == 5)
  {
    return 5; 
  }
  else
    return 0;
}


int eatTail() // To check if the snake has eat itselv or not
{
  int i;
  struct Point temp;
  uint8_t xx = currentXY.x;
  uint8_t yy = currentXY.y;
  uint8_t xx2 = currentXY.x2;
  uint8_t yy2 = currentXY.y2;

  for (i = 0; i < total; i++) { 
    temp = tail[i];

    if (xx == temp.x && (yy == temp.y || yy == temp.y+1)) {
      return -100;
      break;
    }
    else if (xx2 == temp.x && (yy2 == temp.y || yy2 == temp.y+1)) {
      return -100;
      break;
    }

  }

  return 100;
}

int constrain(uint8_t xx, int min, int max) {
  if(xx > min && xx < (max-scale))
  {
    return 1;  // return  100
  }
  else
  {
    return 0;  // return  -1
  }
}

void check() {
    if (checkSafe() == 0 || eatTail() == -100)//Snake is dead
    {
        endGame(); //stringword.c // To end the game 
    }
    else if(checkEat() == 5){ //compare
        eat();
        delay(100);
    }
}

int checkSafe() // To show if the snake has crash with the "ram"
{
  int xx = constrain(currentXY.x, 0, 127);
  int yy = constrain(currentXY.y, 0, 31);

  if (xx != 1 || yy != 1)
  {
    return 0;//Snake dead
  }
  else
    return 100; //return Snake alive
}

void moveOn()
{
  moveTail();//move the tail to right // game.c, To move the snake 

  setPoint(&previousXY, currentXY.x, currentXY.y); //prepretions.c
  uint8_t xx = currentXY.x + (xSpeed * scale);
  uint8_t yy = currentXY.y + (ySpeed * scale);

  setPoint(&currentXY ,xx, yy);
  check();

  snakeDisplay();
}



/*almost the main function*/
void snakeUpdate()//move on the snake
{
  checkSwitches();//if we do not press any btn clear //function.c
  clearSnake();//it will clear the old position for the old snake
  draw(&currentXY,1,1);//clear the snake to show how the snake is move
  check(); //snake.c // To check if the snake will grow upp or die 
  moveOn(); //snake.c // to move the snake again
}

void moveTail()
{

  int i;
  struct Point temp;

  for (i = total-1; i > 0; i--)   // shift the snake to right
  {
    prevTail[i] = tail[i];// To decide what the pre is
    temp = prevTail[i-1];
    tail[i] = temp;
  }
  if (total >= 1) {
    prevTail[0] = tail[0];
    setPoint(&temp, previousXY.x, previousXY.y);
    tail[0] = temp;
  }

}

void eat()
{ 
  increaseScore();
  total = total + 1;
  clearFood(); //prepretions.c 
  delay(100);
  GetFood(); //prepretions.c
}

void increaseScore()
{
  score++;
}

void snakeDisplay()
{
  checkSwitches();
  drawSnake();//rita Til
  drawPoint(&currentXY); //rita snake huvudet
}
