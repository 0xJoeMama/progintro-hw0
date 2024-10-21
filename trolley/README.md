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
That means our numbers have 2*10^18 + 1 discrete states.
To store and distinguish between that many numbers we need an integer of size:
D = log2(2*10^18 + 1) ≈ 60.8 bits
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
if (scanf("%" SCNd64, &left) == EOF)
  break;
```
the above code, exits the program's main loop while the message printing and returning 0 is handled by the main function:

```c
// print the message shown in the test cases
printf("Terminating.\n");

// successful execution
return 0;
```

- if EOF is reached while we are asking for the right input, we exit unsuccessfully printing the message from the provided examples:

```c
if (scanf("%" SCNd64, &right) == EOF) {
    // if not right cost is provided, we exit unsuccessfully
    printf("No right cost provided\n");
    return 1;
}
```

- if any of the provided numbers are outside the program's specified input range, we exit unsuccessfully.
To do that we use the 'out\_of\_bounds' function which is implemented as follows:

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
In the end the program is working. The real question is: does it match the performance criteria provided?
Now, we need to generate inputs. For 10000 executions we need 20000 numbers. I ain't writing that by hand.
We can use a shell command instead. A benchmark is included in the default build process.

```sh
$ make bench
  # ...
  Enter the cost of going left: Enter the cost of going right: Go left                                                                                                                                                                         
  Enter the cost of going left: Enter the cost of going right: Go left                                                                                                                                                                         
  Enter the cost of going left: Enter the cost of going right: Go right                                                                                                                                                                        
  Enter the cost of going left: Terminating.                                                                                                                                                                                                   
                                                                                                                                                                                                                                               
  real    0m0.110s                                                                                                                                                                                                                             
  user    0m0.027s                                                                                                                                                                                                                             
  sys     0m0.000s         
```
Even with the inaccurate benchmark, we are still way below the threshold of a second.
