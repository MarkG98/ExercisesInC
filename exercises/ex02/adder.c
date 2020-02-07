#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 10
#define MAX_NUMBERS 6

/* Fills array with numbers inputted by user

   Function returns -1 (error) if:
      1. User enters a number that overflows the
         input buffer.
      2. User enters too many numbers for the
         passed array.
      3. atoi is unable to convert the input to an
         integer.

    If it does not error, it returns the number of
    numbers entered by the user.

    numbers: pointer to array variable.
*/
int get_numbers(int* numbers)
{
    char numBuff[BUFF_SIZE];
    int j = 0;

    printf("Welcome to the adding machine! Enter up to %i numbers each\nwith max "
           "length %i characters and hit Control-D when you are done to add them up!\n\n",MAX_NUMBERS,BUFF_SIZE-2);

    while(fgets(numBuff, sizeof(numBuff), stdin) != NULL)
    {

        size_t len = strlen(numBuff);

        if (numBuff[len - 1] != '\n')
        {
            puts("\nERROR: You entered a number larger than the size of the input buffer!\n");
            return -1;
        }
        if (j > MAX_NUMBERS - 1)
        {
            puts("\nERROR: You entered too many numbers!");
            return -1;
        }

        int numFromString = atoi(numBuff);
        if (numFromString == 0)
        {
            puts("\nERROR: Could not convert input from string to int");
            return -1;
        }

        numbers[j] = numFromString;
        j++;
    }
    return j;
}

/* Sums and returns integers stored in an array

   numbers: pointer to array containing numbers
   total_numbers: number of elements in array "numbers"
*/
int sum_array(int* numbers, int total_numbers)
{
    int sum = 0;
    for (int i = 0; i < total_numbers; i++)
    {
        sum += numbers[i];
    }
    return sum;
}


int main()
{
    int numbers[MAX_NUMBERS];
    int total_numbers = get_numbers(numbers);
    if (total_numbers == -1)
    {
      return 0; // if get_numbers returns an error, end program
    }
    printf("Sum: %i\n",sum_array(numbers, total_numbers));
}
