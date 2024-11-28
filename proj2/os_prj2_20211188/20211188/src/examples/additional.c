

#include <stdio.h>
#include <syscall.h>
#include <stdlib.h>


int main(int argc, char *argv[]) {
  if(argc != 5) {
      printf("error: doesnt match!!");
      return EXIT_FAILURE;
  }
  
  int num1 = atoi(argv[1]);
  int num2 = atoi(argv[2]);
  int num3 = atoi(argv[3]);
  int num4 = atoi(argv[4]);

  int fib_result = FIBONACCI(num1);
  int max_result = MAX_OF_FOUR_INT(num1, num2, num3, num4);

  printf("Fibonacci of %d: %d\n", num1, fib_result);
  printf("Max of the four integers: %d\n", max_result);

  return EXIT_SUCCESS;
}