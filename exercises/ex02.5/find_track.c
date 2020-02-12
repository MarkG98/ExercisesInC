/* Example code for Exercises in C.

Modified version of an example from Chapter 2.5 of Head First C.

*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <regex.h>

#define NUM_TRACKS 5
#define ERROR_BUFF 100

char tracks[][80] = {
    "So What",
    "Freddie Freeloader",
    "Blue in Green",
    "All Blues",
    "Flamenco Sketches"
};

// Buffer for error string
char error_buff[ERROR_BUFF];

// Finds all tracks that contain the given string.
//
// Prints track number and title.
void find_track(char search_for[])
{
    int i;
    for (i=0; i<NUM_TRACKS; i++) {
        if (strstr(tracks[i], search_for)) {
            printf("Track %i: '%s'\n", i, tracks[i]);
        }
    }
}

// Finds all tracks that match the given pattern.
//
// Prints track number and title.
void find_track_regex(char pattern[])
{

    for (int i=0; i<NUM_TRACKS; i++)
    {
      // To store status of regcomp() and regexec()
      int status;

      // stores results of patter argument
      regex_t re;

      // Compile pattern
      if (regcomp(&re, pattern, REG_EXTENDED|REG_NOSUB) != 0)
      {
        // If compilation errors load error message into error_buff,
        // print it, and then exit(1)
        regerror(status, &re, error_buff, ERROR_BUFF);
        printf("%s\n",error_buff);
        exit(1);
      }

      // Parse text according to regex
      status = regexec(&re, tracks[i], (size_t) 0, NULL, 0);

      // Free memory allocated by regcomp() associated with re
      regfree(&re);

      // Catch error
      if (status != 0)
      {
        // Load error message into error_buff
        regerror(status, &re, error_buff, ERROR_BUFF);

        // If error message is not "No match" print and exit(1)
        if (strcmp(error_buff,"No match"))
        {
          printf("%s\n",error_buff);
          exit(1);
        }
      }
      else
      {
        // If there is a match print the track and its number
        printf("Track %i: '%s'\n", i, tracks[i]);
      }
    }
}

// Truncates the string at the first newline, if there is one.
void rstrip(char s[])
{
    char *ptr = strchr(s, '\n');
    if (ptr) {
        *ptr = '\0';
    }
}

int main (int argc, char *argv[])
{
    char search_for[80];

    /* take input from the user and search */
    printf("Search for: ");
    fgets(search_for, 80, stdin);
    rstrip(search_for);

    //find_track(search_for);
    find_track_regex(search_for);

    return 0;
}
