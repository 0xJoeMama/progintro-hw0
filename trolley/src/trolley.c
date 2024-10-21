#include <inttypes.h>
#include <stdbool.h>
#include <stdio.h>

// 10^18 is just hardcoded because I wouldn't wanna repeat this long thing like
// 4 times
#define MAX_NUM 1000000000000000000

// check if number x is within the range of valid inputs
static bool out_of_bounds(int64_t x) { return x > MAX_NUM || x < -MAX_NUM; }

static void notify_for_oob(int64_t x) {
  fprintf(stderr,
          "specified value %" PRId64 " is outside the range [-10^18, 10^18]\n", x);
}

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
    if (scanf("%" SCNd64, &left) == EOF)
      break;

    // if left is out of bounds, terminate with status code 1 and let the user
    // know
    if (out_of_bounds(left)) {
      notify_for_oob(left);
      return 1;
    }

    // User input for right
    printf("Enter the cost of going right: ");
    if (scanf("%" SCNd64, &right) == EOF) {
      // if not right cost is provided, we exit unsuccessfully
      printf("No right cost provided\n");
      return 1;
    }

    // if right is out of bounds, terminate with status code 1 and let the user
    // know
    if (out_of_bounds(right)) {
      notify_for_oob(right);
      return 1;
    }

    // if right is greater than or equal to left, we go left.
    // otherwise we go right
    if (left <= right) {
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
