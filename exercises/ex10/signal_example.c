/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: MIT License

Based on an example from
https://raw.githubusercontent.com/twcamper/head-first-c/master/10/math-master.c

Based on an example in Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <time.h>
#include <string.h>
#include <errno.h>
#include <signal.h>

int score = 0;
int keep_running = 1;

/* Set up a signal handler.

   sig: signal number
   handler: signal handler function
*/
int catch_signal(int sig, void (*handler) (int)) {
    struct sigaction action;
    action.sa_handler = handler;
    sigemptyset(&action.sa_mask);
    action.sa_flags = 0;
    return sigaction(sig, &action, NULL);
}

/* Signal handler: End the game.
 */
void end_game(int sig)
{
    printf("\nFinal score: %i\n", score);
    exit(EXIT_SUCCESS);
}

/* Signal handler: Notify the user and raise SIGINT.
*/
void times_up(int sig) {
    keep_running = 0;
}

int main(void) {
    int a, b, answer;
    char txt[4];

    // when the alarm goes off, call times_up
    catch_signal(SIGALRM, times_up);

    // if we get interrupted, end the game
    catch_signal(SIGINT, end_game);

    // seed the random number generator
    srandom((unsigned int) time(NULL));

    while(1) {
        // pose the question
        a = rand() % 11;
        b = rand() % 11;
        printf("\nWhat is %d times %d? ", a, b);

        // set (or reset) the alarm
        alarm(5);

        // If alarm goes off lower 'keep_going' flag which will end the game
        // after this question. if you responsd in time continue the program
        // and start the new loop which will reset alarm(5)
        while(1)
        {
	         char *ret = fgets(txt, 4, stdin);
           if(ret)
           {
              break;
           }
        }
        answer = atoi(txt);

        // check the answer
        if (answer == a * b) {
            printf("\nRight!\n");
            score++;
        } else {
            printf("\nWrong!\n");
        }
        printf("Score: %i\n", score);

        // End the game if 'keep_running' flag is lowered
        if(!keep_running)
        {
            end_game(0);
        }

    }
    return 0;
}
