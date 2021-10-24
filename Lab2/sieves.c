#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLUMNS 6
int numbersInRow = 0;

void print_number(int num) {
  printf("%5d ", num);
  numbersInRow++; // increases the count
  if(numbersInRow == COLUMNS) {
    printf("\n");
    numbersInRow = 0;
  }
}

void print_sieves(int n) {
  char possiblePrime[n-2]; // declares a "boolean" array assuming all numbers to be prime (2 är första nummer i premtal)
  for(int i = 2; i < n; i++) { //(n-2) den tar bort första nummer och nummert som vi få.
    possiblePrime[i-2] = 1;
  }
    
  for(int i = 2; i <= sqrt(n); i++) { // loops through all possible primes
    if(possiblePrime[i-2]) { // checks if current number is prime
      for(int j = i*i; j <= n; j += i) { // marks all multiples of i as not primes
        possiblePrime[j-2] = 0; // om indext stora än vektor storlek den kommer axtra cellen att nollas då den visar den inte i rad 30
      }
    }
  }
  for(int i = 2; i <= n; i++) { // goes through all possible primes
    if(possiblePrime[i-2]) { // prints number if it's prime
        print_number(i);
    }
  }
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
    int number;
  if(argc == 2)
    print_sieves(atoi(argv[1])); // atoi converts the argument to an int
  else
    printf("Please state an interger number.\n");
    scanf("%d", &number);
    print_sieves(number);
  return 0;
}
