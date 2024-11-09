#include <inttypes.h>
#include <stdio.h>

int main(void) {
  // initialize 2 stack variables which we will be using throughout our whole
  // lifecycle, instead of reallocating on every repetition
  int64_t left;
  int64_t right;

  // loop as long as we are given data
  for (;;) {
    // ask user for left input
    printf("Enter the cost of going left: ");
    // if EOF is reached or a matching failure occurs when reading left exit
    // with success
    if (scanf("%" SCNd64, &left) != 1)
      break;

    // ask user for right input
    printf("Enter the cost of going right: ");

    // if EOF is reached or a matching failure occurs when reading right exit with failure
    if (scanf("%" SCNd64, &right) != 1) {
      puts("No right cost provided.");
      return 1;
    }

    // if right is greater than or equal to left, we go left
    if (left <= right) {
      puts("Go left");
    } else { // otherwise we go right
      puts("Go right");
    }
  }

  puts("Terminating.");
  return 0;
}
