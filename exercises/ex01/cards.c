/* Author: Mark Goldwater

   Functionalized code from head first C which
   is able to count cards based on user input.
*/

#include <stdio.h>
#include <stdlib.h>

/* Takes the current count and new card value to update count.

   If card is between 2 and 7 up count by 1.
   If card is 10, reduce count by 1.
   The current count is then printed to the terminal.

   count: current value of count
   val: value of most recent card
*/
int update_count(int count, int val)
{
    if ((val > 2) && (val < 7)) {
        count++;
    } else if (val == 10) {
        count--;
    }
    printf("Current count: %i\n", count);
    return count;
}

/* Prompts the user for input and puts the reply in the given buffer.

   User input is truncated to the first two characters.

   prompt: string prompt to display
   card_name: buffer where result is stored
*/
void get_card_name(char *prompt, char *card_name)
{
    puts(prompt);
    scanf("%2s", card_name);
}


int main()
{
    char card_name[3];
    char *prompt = "Enter the card name: ";
    int count = 0;
    int val = 0;
    do {
          get_card_name(prompt, card_name);

          switch(card_name[0]) {
          case 'K':
          case 'Q':
          case 'J':
              val = 10;
              break;
          case 'A':
              val = 11;
              break;
          case 'X':
              continue;
          default:
              val = atoi(card_name);
              if ((val < 1) || (val > 10)) {
                  puts("I don't understand that value!");
                  continue;
              }
          }

          count = update_count(count, val);

    } while (card_name[0] != 'X');
    return 0;
}
