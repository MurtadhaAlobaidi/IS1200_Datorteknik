/*
 print-prime.c
 By David Broman.
 Last modified: 2015-09-15
 This file is in the public domain.
*/

#include <stdio.h>
#include <stdlib.h>

#define COLUMNS 6
//Antal Koloner
int numbersInRow = 0;

//att skriva primtalet som matris
void print_number(int num) {
  printf("%5d ", num);
  numbersInRow++; // räknare och plus ett
    if(numbersInRow == COLUMNS) { //När den är =6 då börjar nytt rad
    printf("\n");
    numbersInRow = 0;
  }
}

int is_prime(int n){
  int prime = 1; // assumes number is prime
  for(int i = 2; i < n; i++)
    if(n%i == 0) { // checks if number isn't prime
        prime = 0; // sets result to 0
      break; // leaves the loop since we know it's not prime already
    }
  return prime;
}
//print all prime numbers from 2 to n by calling functionsprint_number and is_prime.
void print_primes(int n){
  if(n >= 2) // checks if the number is 2 or higher
      print_number(2); // prints the first prime
  for(int i = 3; i < n; i++) {
    if(is_prime(i)) // prints the number if it's prime
        print_number(i);
  }
  printf("\n");
}

// 'argc' contains the number of program arguments, and
// 'argv' is an array of char pointers, where each
// char pointer points to a null-terminated string.
int main(int argc, char *argv[]){
  int number;
  if(argc == 2)
    print_primes(atoi(argv[1])); // atoi converts the argument to an int
  else
    printf("Please state an interger number.\n");
    scanf("%d", &number);
    print_primes(number);
  return 0;
}

