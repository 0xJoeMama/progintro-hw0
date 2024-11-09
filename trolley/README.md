# trolley Problem

We basically need to read 2 numbers from stdin and compare them.
It is important we keep in mind the specifications given to us, specifically when the program should error-out and when it should terminate gracefully.

## Build Instructions

To build this project, you need to make GNU Make, a C compiler(gcc by default) and an implementation of libc installed on your system.

To build using Make and gcc you can run:
```sh
$ make
```

To specify an alternative compiler, you can use:
```sh
$ make CC=yourcompiler
```

You can also change the compilation flags, using the CFLAGS Make variable:
```sh
$ make CFLAGS=-Ofast -Wall -pedantic -std=C99 -Wextra -Werror
```

After a successful execution of Make, a file called 'trolley' will be available in the directory you run make from.

NOTE: a .build directory will be created to store object files. Beware that if you need to rebuild, it is advised you use the following:

```sh
$ make clean
```

## The Solution

### The Main Loop
The program needs to repeatedly execute until the user terminates it with EOF. Therefore we need a main loop the program is gonna run on.
Therefore the following came to be:

```c
// loop as long as we are given data
for (;;) {
  // ...
}
```

### The Input
We now need to get user input from stdin.
`scanf` was chosen because it offers the following advantages:
- It automatically parses input in a specified format. In this case, we can read integers and not have to worry about atoi or strtol.
- It returns EOF when EOF is reached, meaning we can easily handle it.
- It ignores whitespace(space, tab and enter) which we need since the specification asks for it.
- It does not need any buffers to be manually allocated or freed by us.

Next, the integers we read. Notice that the specification mentions that the input can be anywhere from $-10^18$ to $10^18$.
Given that, we need to find the size of integer we should allocate to cover the whole input range.
The range $[-10^18, 10^18]$, contains:
* 10^18 negatives
* 10^18 positives
* 0
That means our numbers have $2\*10^18 + 1$ discrete states.
To store and distinguish between that many numbers we need an integer of size:
$D = log2(2\*10^18 + 1) \approx 60.8 bits$
Therefore we need a 64-bit integer type to hold this large a number.

Now, to specifically allocate 64-bit signed-integers I use the `int64_t` type. The reason for that is because we cannot rely on a `long long` to be 64-bit, since it's system specific.
Therefore we use an integer with a set size that is guaranteed by the C standard to be the size we need.

```c
// Initialize 2 stack variables which we will be using throughout our whole
// lifecycle, instead of reallocating on every repetition
int64_t left;
int64_t right;
```

Note that we allocate 2 variables for all of the program's lifetime. This is technically speaking better than allocating a new set of variables on every  
iteration of the loop, but then again moving the stack pointer isn't that hard for today's machines and the compiler might be able to make that optimization on its own.

For the scanning, we also cannot use a format specifier like `%lld` because nothing guarantees that `int64_t` is gonna be a long long. Thus we need to use the following:
```c
"%" SCNd64
```
which is the C standard compliant way of printing the `intxx_t` types.

That is how the specific commands for reading input where chosen.

### Input Handling
Now to process the input and act accordingly, I make use of a custom macro called `read_input`.
This macro takes in a local variable which will be the one that will be read from `stdin`, a message to print and a return value to exit with from the main function when EOF is reached.
This was originally inlined into the main function, however it lead to repetitive code so I thought it would be a better idea to abstract it away into a macro.
I chose not to use a function as that would lead to a slight performance problem which would be caused by the stack manipulation needed to enter and exit a function.
Since our solutions are graded for performance it's a better idea to do it this way.

```c
// using a macro as an inline function to avoid repeating code
#define tr_read_and_handle_input(number, message, eof_ret)                     \
  {                                                                            \
    switch (scanf("%" SCNd64, &number)) {                                      \
    case -1:                                                                   \
      printf(message "\n");                                                    \
      return eof_ret;                                                          \
    case 0:                                                                    \
      fprintf(stderr, "not a number: ");                                       \
      int c;                                                                   \
      while ((c = fgetc(stdin)) != '\n' && c != EOF)                           \
        fputc(c, stderr);                                                      \
                                                                               \
      fputc('\n', stderr);                                                     \
      return 1;                                                                \
    }                                                                          \
  }
```
As seen above, this reads a 64-bit integer from `stdin`, using the `scanf` function.
Using a switch statement, we can then handle invalid cases separately. According to the man page for scanf:
* if scanf returns `EOF`, it means end of file has been reached without a match occuring. Thus we need to print the message given to us by the specification("Terminating." and "No right cost provided.") and exit with the correct exit code (0 for left EOF, 1 for right).
* if scanf returns 0, it means a matching failure has happened. This means the user provided something that could not be parsed as an integer. So we let the user know using the `stderr` stream and a message showing the invalid input.
* otherwise scanf has returned at least 1 which means we have valid input

### The Logic
Finally the actual logic:

```c
// if right is greater than or equal to left, we go left.
// otherwise we go right
if (left <= right) {
    printf("Go left\n");
} else {
    printf("Go right\n");
}
```

If left is less than right, go left.
If left is equal to right, then according to the specification, we go left.
Otherwise, we go right.
Pretty simple.

## Benchmarking
Using a tool called [hyperfine](https://github.com/sharkdp/hyperfine) I am able to benchmark the program.
Over 1000 iterations of execution, using the [trolley.txt](./trolley.txt) file provided to us as test input,
I was able to get the following results:
```sh
Benchmark 1: ./trolley < ./trolley.txt
  Time (mean ± σ):       7.5 ms ±   1.1 ms    [User: 6.3 ms, System: 0.5 ms]
  Range (min … max):     6.3 ms …  17.6 ms    1000 runs
```

Our average time is 7.5ms plus or minus 1.1ms which for a program that uses stdin/stdout extensively is actually really good.
Note: This was run on DI's Linux computers, which I have noticed have quite unstable program runtimes. As a matter of fact, I've seen execution times from 15ms to 6ms.
This is probably something that was to do with the large(TM) amount of background vscode-server processes running on the equipment(about 5 per computer at the time of testing).
It is also the case that computers with more active users also have a slower runtime, which also makes sense.

This does make me quite curious as to how our programs are gonna be benchmarked.  
To me it seems like it can be affected by the background processes quite a lot, which considering the testing is gonna be in such an unstable environment leads me to question the accuracy of the results.
