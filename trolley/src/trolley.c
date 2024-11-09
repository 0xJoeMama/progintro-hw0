#include <inttypes.h>
#include <stdio.h>

// using a macro as an inline function to avoid repeating code
#define tr_read_and_handle_input(number, eof_msg, eof_ret)                     \
  {                                                                            \
    /* read a 64 bit integer from stdin into the local number variable */      \
    switch (scanf("%" SCNd64, &number)) {                                      \
    case EOF:                                                                  \
      /* if eof is reached, print the message given to us and exit with the    \
       * respective return code*/                                              \
      puts(eof_msg);                                                           \
      return eof_ret;                                                          \
    case 0:                                                                    \
      /* if 0 is returned it means a matching failure has occured so we can    \
       * print a message to the user letting them know they made a mistake     \
       * then exit with failure */                                             \
                                                                               \
      /* we need to flush since we want our messages to show up in the correct \
       order */                                                                \
      fflush(stdout);                                                          \
      fprintf(stderr, "\nnot a valid number: ");                               \
      /* stdin is line buffered, so we read until the next newline or EOF is   \
       reached and print the characters read*/                                 \
      int c;                                                                   \
      while ((c = fgetc(stdin)) != '\n' && c != EOF)                           \
        fputc(c, stderr);                                                      \
                                                                               \
      /* finally print a newline and exit with failure*/                       \
      fputc('\n', stderr);                                                     \
      return 1;                                                                \
    }                                                                          \
  }

int main(void) {
  // initialize 2 stack variables which we will be using throughout our whole
  // lifecycle, instead of reallocating on every repetition
  int64_t left;
  int64_t right;

  // loop as long as we are given data
  for (;;) {
    // ask user for left input
    printf("Enter the cost of going left: ");
    tr_read_and_handle_input(left, "Terminating.", 0);

    // ask user for right input
    printf("Enter the cost of going right: ");
    tr_read_and_handle_input(right, "No right cost provided.", 1);

    // if right is greater than or equal to left, we go left
    if (left <= right) {
      puts("Go left");
    } else { // otherwise we go right
      puts("Go right");
    }
  }

  return -1; // unreachable since we can only exit on EOF or an error
}
