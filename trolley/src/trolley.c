#include <inttypes.h>
#include <stdio.h>

// 10^18 is just hardcoded because I wouldn't wanna repeat this long thing like
// 4 times
int main(void) {
  // Initialize 2 stack variables which we will be using throughout our whole
  // lifecycle, instead of reallocating on every repetition
  int64_t left;
  int64_t right;

  // loop as long as we are given data
  for (;;) {
    // User input for left
    printf("Enter the cost of going left: ");

    // if left is EOF terminate successfully
    if (scanf("%" SCNd64, &left) != 1) 
      break;

    // User input for right
    printf("Enter the cost of going right: ");
    if (scanf("%" SCNd64, &right) != 1) {
      puts("No right cost provided.");
      return 1;
    }

    // if right is greater than or equal to left, we go left.
    // otherwise we go right
    if (left <= right) {
      puts("Go left");
    } else {
      puts("Go right");
    }
  }

  // print the message shown in the test cases
  puts("Terminating.");

  // successful execution
  return 0;
}
