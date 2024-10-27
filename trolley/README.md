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
scanf was chosen because it offers the following advantages:
- It automatically parses input in a specified format. In this case, we can read integers and not have to worry about atoi or strtol.
- It returns EOF when EOF is reached, meaning we can easily handle it.
- It ignores whitespace(space, tab and enter) which we need since the specification asks for it.
- It does not need any buffers to be manually allocated or freed by us.

Next, the integers we read. Notice that the specification mentions that the input can be anywhere from -10^18 to 10^18.
Given that, we need to find the size of integer we should allocate to cover the whole input range.
The range [-10^18, 10^18], contains:
* 10^18 negatives
* 10^18 positives
* 0
That means our numbers have 2\*10^18 + 1 discrete states.
To store and distinguish between that many numbers we need an integer of size:
D = log2(2\*10^18 + 1) ≈ 60.8 bits
Therefore we need a 64-bit integer type to hold this large a number.

Now, to specifically allocate 64-bit signed-integers I use the int64\_t type. The reason for that is because we cannot rely on a long long to be 64-bit, since it's system specific.
Therefore we use an integer with a set size that is guaranteed by the C standard to be the size we need.

```c
// Initialize 2 stack variables which we will be using throughout our whole
// lifecycle, instead of reallocating on every repetition
int64_t left;
int64_t right;
```

Note that we allocate 2 variables for all of the program's lifetime. This is technically speaking better than allocating a new set of variables on every  
iteration of the loop, but then again moving the stack pointer isn't that hard for today's machines.

For the scanning, we also cannot use a format specifier like `%lld` because nothing guarantees that int64\_t is gonna be a long long. Thus we need to use the following:
```c
"%" SCNd64
```
which is the C standard compliant way of printing the intxx\_t types.

That is how the specific commands for reading input where chosen.

### Input Handling
Now to process the input:
- if EOF is reached when we are asking for the left input, we need to terminate gracefully.

```c
// if left is EOF terminate successfully
if (scanf("%" SCNd64, &left) != 1)
  break;
```
the above code, exits the program's main loop while the message printing and returning 0 is handled by the main function:

```c
// print the message shown in the test cases
printf("Terminating.\n");

// successful execution
return 0;
```

- if EOF is reached or no match can be made while we are asking for the right input, we exit unsuccessfully printing the message from the provided examples:

```c
if (scanf("%" SCNd64, &right) != 1) {
    // if not right cost is provided, we exit unsuccessfully
    printf("No right cost provided\n");
    return 1;
}
```
*NOTE: I use != 1 instead of != EOF in order to also make sure at least one item is matched. This ensures that if we get a matching failure
(which would happen in the user entered "hello" instead of a valid decimal integer) the program also exits.
Technically speaking that would also not be needed according to instructor feedback, but seeing that != EOF and == 1 generate the same amount of instructions, I say we can handle the case normally.*

~~- if any of the provided numbers are outside the program's specified input range, we exit unsuccessfully.
To do that we use the 'out\_of\_bounds' function which is implemented as follows:~~
- The above is actually not needed according to piazza feedback from our instructor.
However, I would argue that under normal execution circumstances, it is required we make sure that we get valid input.
In favor of speed however, if we are guaranteed to get valid input we can ignore the branching to separate functions and the jumps in the main function.

```c
// 10^18 is just hardcoded because I wouldn't wanna repeat this long thing like
// 4 times
#define MAX_NUM 1000000000000000000

// check if number x is within the range of valid inputs
static bool out_of_bounds(int64_t x) { return x > MAX_NUM || x < -MAX_NUM; }
```

Futhermore, we use the following function to let the user know they made a mistake:

```c
static void notify_for_oob(int64_t x) {
  fprintf(stderr,
          "specified value %" PRId64 " is outside the range [-10^18, 10^18]\n", x);
}
```

All of that is put together in the main loop using the following code:


```c
// if left is out of bounds, terminate with status code 1 and let the user know 
if (out_of_bounds(left)) {
    notify_for_oob(left);
    return 1;
}
```
Note that I didn't really like the idea of abstracting these 2 functions out. The reason for that is because this is too small a program with a small number of use cases for said functions.
Usually I implement utility functions when I get to using the same logic more than 2 times. But because I am not sure how this will be graded, I decided to just abstract them away just in case.

PS: the static modifier makes a function local to the current translation unit. Its usage is intentional.

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
