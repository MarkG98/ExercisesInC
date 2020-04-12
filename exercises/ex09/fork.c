/* Example code for Exercises in C.

Copyright 2016 Allen B. Downey
License: MIT License https://opensource.org/licenses/MIT

Global, heap, and stack experiments:

I set a global, heap, and stack integer to 0 in the parent, changed all three to 3 in the
child_code function, and then printed them out again in the parent after all of the
child processes had returned. This last print showed them all to be zero still, so I would
conclude that the parent and child processes do not share these segments of memory.

Static and code experiemnts:

In order to test the static and code segments, I allocated a static string and checked its address in both the
parent and child, and checked the address of the main function in both the parent and child. The addresses for
the static string were different, but those for the main function were the same. So, in this instance, the parent
and child shared the code segment of memeory but not the static segment of memory.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/time.h>
#include <sys/types.h>
#include <wait.h>


// errno is an external global variable that contains
// error information
extern int errno;

// Create global variable
int num_global = 0;

// get_seconds returns the number of seconds since the
// beginning of the day, with microsecond precision
double get_seconds() {
    struct timeval tv[1];

    gettimeofday(tv, NULL);
    return tv->tv_sec + tv->tv_usec / 1e6;
}


void child_code(int i, int *num_heap, int num_stack, char *s, int (*main)(int, char**))
{
    sleep(i);
    printf("Hello from child %d.\n", i);

    // Child changes global variable
    num_global = 3;
    printf("\nChild changed num_global to num_global = %d\n", num_global);

    // Child changes global variable
    *num_heap = 3;
    printf("Child changed num_heap to num_heap = %d\n", *num_heap);

    // Child changes stack variable
    num_stack = 3;
    printf("Child changed num_stack to num_stack = %d\n", num_stack);

    // Print address of static variable
    printf("Child says address of s is %p\n", &s);

    // Print address of main from child
    printf("Child says address of main is %p\n\n", main);
}

// main takes two parameters: argc is the number of command-line
// arguments; argv is an array of strings containing the command
// line arguments
int main(int argc, char *argv[])
{
    int status;
    pid_t pid;
    double start, stop;
    int i, num_children;

    // the first command-line argument is the name of the executable.
    // if there is a second, it is the number of children to create.
    if (argc == 2) {
        num_children = atoi(argv[1]);
    } else {
        num_children = 1;
    }

    // Parent prints global variable
    printf("\nParent says num_global = %d\n", num_global);

    // Parent allocated memory for an integer
    int *num_heap = malloc(sizeof(int));
    *num_heap = 0;
    printf("Parent says num_heap = %d\n", *num_heap);

    // Parent creates stack variable
    int num_stack = 0;
    printf("Parent says num_stack = %d\n", num_stack);

    // Parent creates static string
    char *s = "Hello, Son.";
    printf("Parent says address of s is %p\n", &s);

    printf("Parent says address of main is %p\n\n", main);

    // get the start time
    start = get_seconds();

    for (i=0; i<num_children; i++) {

        // create a child process
        printf("Creating child %d.\n", i);
        pid = fork();

        /* check for an error */
        if (pid == -1) {
            fprintf(stderr, "fork failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        /* see if we're the parent or the child */
        if (pid == 0) {
            child_code(i, num_heap, num_stack, s, main);
            exit(i);
        }
    }

    /* parent continues */
    printf("Hello from the parent.\n");

    for (i=0; i<num_children; i++) {
        pid = wait(&status);

        if (pid == -1) {
            fprintf(stderr, "wait failed: %s\n", strerror(errno));
            perror(argv[0]);
            exit(1);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
        printf("Child %d exited with error code %d.\n", pid, status);
    }
    // compute the elapsed time
    stop = get_seconds();
    printf("Elapsed time = %f seconds.\n", stop - start);

    // Parent prints global variable again
    printf("\nParent says num_global = %d\n", num_global);

    // Parent prints heap variable again
    printf("Parent says num_heap = %d\n", *num_heap);

    // Parent prints stack variable again
    printf("Parent says num_stack = %d\n", num_stack);



    exit(0);
}
