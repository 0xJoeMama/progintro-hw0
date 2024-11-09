#include <inttypes.h>
#include <stdio.h>

#define TEN2EIGHTEENTH 1000000000000000000

static int tr_is_valid_input(int64_t in) {
  if (in > TEN2EIGHTEENTH || in < -TEN2EIGHTEENTH) {
    fprintf(
        stderr,
        "specified integer is outside the allowed range([-10^ 18, 10^18])\n");
    return 0;
  }

  return 1;
}

// if 0 is returned it means a matching failure has occured so we can
// print a message to the user letting them know they made a mistake
// then exit with failure
static void tr_print_invalid_int(void) {
  // we need to flush since we want our messages to show up in the correct order
  fflush(stdout);
  fprintf(stderr, "\nnot a valid number: ");

  // stdin is line buffered, so we read until the next newline or EOF is reached
  // and print the characters read
  int c;
  while ((c = fgetc(stdin)) != '\n' && c != EOF)
    fputc(c, stderr);

  // finally print a newline
  fputc('\n', stderr);
}

typedef enum {
  RR_FAIL_HARD = 1,
  RR_FAIL_SOFT = 0,
  RR_SUCC = -1,
} ReadResult;

static ReadResult tr_read_input(int64_t *target, const char *fail_msg) {
  switch (scanf("%" SCNd64, target)) {
  case EOF:
    // if we reached eof we fail soft and print the message
    puts(fail_msg);
    return RR_FAIL_SOFT;
  case 0:
    // if we weren't given a valid int print the invalid state to stderr
    tr_print_invalid_int();
    return RR_FAIL_HARD;
  }

  // if the read value is out of bounds, fail hard
  if (!tr_is_valid_input(*target))
    return RR_FAIL_HARD;

  return RR_SUCC;
}

int main(void) {
  // initialize 2 stack variables which we will be using throughout our whole
  // lifecycle, instead of reallocating on every repetition
  int64_t left;
  int64_t right;
  ReadResult res;

  // loop as long as we are given data
  for (;;) {
    // ask user for left input
    printf("Enter the cost of going left: ");
    if ((res = tr_read_input(&left, "Terminating.")) != RR_SUCC)
      return res;

    // User input for right
    printf("Enter the cost of going right: ");
    if ((res = tr_read_input(&right, "No right cost provided.")) != RR_SUCC)
      return RR_FAIL_HARD;

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
