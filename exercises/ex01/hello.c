/*
  Author: Mark Goldwater

  Code for the optimization section of ex01 in ExercisesInC.

  Questions:
  1. Can you find the code that corresponds to this line?

     subq	$16, %rsp
     movl	$5, -4(%rbp)

  2. What happens if you turn on optimizatio using the flag -02?

     The number of assembly instructions is greatly reduced, and the
     lines where x is assigned are no longer there.

  3. Modify the printf statement to print x, then compile it with and
     without optimization. What effect does it have when you print x?

     Without optimization x is assigned and printed. With optimization, There
     are less assemly instructions and __printf_chk is called rather
     than printf. Also, it seems as the value of x is not stored, but just
     printed.

  4. And then print the value of y (but not x). Compile with and without
     optimization. What happens to x and y?

     It looks as if without optimization, x and y are assigned and then
     y is printed. However, with optimization, it seems like the value
     is just calculated and then printed.

     Overall, when we set the compiler to optimize the code, it does not store
     values in locations which represent variables if the variables are not used
     later, rather it just uses the values where they are needed in the code.
*/

#include <stdio.h>

int main() {
    int x = 5;
    int y = x + 1;
    printf("%i\n", y);
    return 0;
}
