#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFF_SIZE 10
#define MAX_NUMBERS 6

int get_numbers(int* numbers)
{
    char numBuff[BUFF_SIZE];
    int j = 0;
    int len;
    int numFromString;

    printf("Welcome to the adding machine! Enter up to %i numbers\neach with max. length %i and hit Control-D\nwhen you are done to add them up!\n\n",MAX_NUMBERS,BUFF_SIZE-2);
    while(fgets(numBuff, sizeof(numBuff), stdin) != NULL)
    {

        len = strlen(numBuff);

        if (numBuff[len-1] != '\n')
        {
            puts("ERROR: You entered a number larger than the size of the input buffer!\n");
            return -1;
        }
        else if (j > MAX_NUMBERS - 1)
        {
            puts("ERROR: You entered too many numbers!");
            return -1;
        }

        numFromString = atoi(numBuff);
        if (numFromString == 0)
        {
            puts("ERROR: Could convert input from string to int");
            return -1;
        }

        numbers[j] = numFromString;
        j++;
    }
    return j;
}

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
      return 0;
    }

    printf("Sum: %i\n",sum_array(numbers, total_numbers));
}
