#include <stdio.h>

char* text1 = "This is a string.";
char* text2 = "Yet another thing.";

int list1[20]; //20 since an int is 4 bytes in size, 80/4 = 20
int list2[20];
int count = 0;

void copycodes(char* text, int* list, int* count) {
    while(*text != 0) {
        *list = *text; //sw    $t0,0($a1)
        text++; //addi    $a0,$a0,1  //text++ för att adera bytes till postion
        list++; //addi    $a1,$a1,4

        (*count)++; //(*count)++ för att adera alla och öka summan av allt
    }
}

void work() {
    copycodes(text1, list1, &count);// executes copycodes with text1 and list1
    copycodes(text2, list2, &count);// executes copycodes with text2 and list2
}

void printlist(const int* lst){
  printf("ASCII codes and corresponding characters.\n");
  while(*lst != 0){
    printf("0x%03X '%c' ", *lst, (char)*lst);
    lst++;
  }
  printf("\n");
}

void endian_proof(const char* c){
  printf("\nEndian experiment: 0x%02x,0x%02x,0x%02x,0x%02x\n",
         (int)*c,(int)*(c+1), (int)*(c+2), (int)*(c+3));

}

int main(void){
  work();

  printf("\nlist1: ");
  printlist(list1);
  printf("\nlist2: ");
  printlist(list2);
  printf("\nCount = %d\n", count);

  endian_proof((char*) &count); //The Intel x86 and AMD64 series of processors use the little-endian
}

//(MSB)//0xA004564 är litte endian(LSB) //Naturligt i beräkning(matmatik oprationen fungerar mestadels från minst till viktigaste sivran så det är mycket lättare att använda litle endian
//(LSB)//0xA4345000 är big endian//(MSB)
