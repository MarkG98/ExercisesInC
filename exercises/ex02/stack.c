/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

Questions:

1. What this program is intended to do is print and return a pointer to an array
   filled with 42 from the function foo(), print and create another array with bar()
   where each element is its index, and then print the values of the array
   returned by foo().

2. The warning I try to compile this file is "function returns address of local
   variable [-Wreturn-local-addr]", and it points to "return array in foo()".
   This means that the array variable, a pointer to which is being returned, is
   local to foo(). I am probably being warned of this because once this function
   returns, this variable, and all other local variables, are destroyed.

3. When I run the program, I get a Segmentation fault. This is because after foo()
   return a pointer to array, and bar() is run, the program tries to print the
   elements of array in main. However, after foo() returns, the array variable is
   destroyed, so trying to do this in main is reading from an incorrect memory
   location leading to a Segmentation fault.

4. Now nothing prints and I still get a Segmentation fault.

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    for (i=0; i<SIZE; i++) {
        array[i] = i;
    }
}

int main()
{
    int i;
    int *array = foo();
    bar();

    for (i=0; i<SIZE; i++) {
        printf("%d\n", array[i]);
    }

    return 0;
}
