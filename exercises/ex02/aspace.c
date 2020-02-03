/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

Questions

4. The heap on my system is growing up. The address of p2 is 0x213b0a0
   which is larger than 0x213b010.

5. I can confirm that the stack grows downward. The address of
   the local variable var2 in main is 0x7fff5532656c which is larger
   than the variable created next which is at 0x7fff55326544.

6. The two chunks of size 26 bytes are 48 bytes apart (the sum of their allocation sizes).

*/

#include <stdio.h>
#include <stdlib.h>

int var1;

// Function that prints local variable x
void print_local_variable()
{
  int x = 3;
  printf("Address of x is %p\n",&x);
}

int main ()
{
    int var2 = 5;
    void *p = malloc(128);
    void *p2 = malloc(128); // for question 4
    char *s = "Hello, World";

    void *p3 = malloc(26); // for question 6
    void *p4 = malloc(26); // for question 6

    printf ("Address of main is %p\n", main);
    printf ("Address of var1 is %p\n", &var1);
    printf ("Address of var2 is %p\n", &var2);
    printf ("p2 points to %p\n", p2);
    printf ("p points to %p\n", p);
    printf ("s points to %p\n", s);
    print_local_variable();
    printf ("p3 points to %p\n", p3);
    printf ("p4 points to %p\n", p4);

    return 0;
}
