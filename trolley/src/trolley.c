#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

// 10^18 is just hardcoded because I wouldn't wanna repeat this long thing like
// 4 times
#define MAX_NUM 1000000000000000000

int main(void) {
  // Initialize 2 stack variables which we will be using throughout our whole
  // lifecycle, instead of reallocating on every repetition
  int64_t left = 0;
  int64_t right = 0;

  // loop as long as we are given data
  for (;;) {
    // User input for left
    printf("Enter the cost of going left: ");

    // if left is EOF terminate successfully
    if (scanf("%" PRId64, &left) == EOF)
      break;

    // if left is out of bounds, terminate with status code 1
    if (left > MAX_NUM || left < -MAX_NUM)
      return 1;

    // User input for right
    printf("Enter the cost of going right: ");
    if (scanf("%" PRId64, &right) == EOF) {
      // if not right cost is provided, we exit unsuccessfully
      printf("No right cost provided\n");
      return 1;
    }

    // if right is out of bounds, terminate with status code 0
    if (right > MAX_NUM || right < -MAX_NUM)
      return 1;

    // if right is greater than or equal to left, we go left.
    // otherwise we go right
    if (right >= left) {
      printf("Go left\n");
    } else {
      printf("Go right\n");
    }
  }

  // print the message shown in the test cases
  printf("Terminating.\n");

  // successful execution
  return 0;
}
