/* Questions

   3. Overall, I think I took a good approach to developing this program. Something that worked really well
      was that I developed my implementation in incremental steps and tested as I went. I first printed out
      the arguemnts/flags that the program recieved from my input, then delt with the file entry, and then
      it all together. It also helped that I split it into multiple functions for easy organization and sense
      of control flow. Something I would probably do differntly next time is I would spend more time reading
      the library documentation a bit more carefully. There were definitly some hurdles that I could have avoided
      had I read the documentation of getopt_long a bit more thoroughly.

   4. First of all, there are legal/liscense related things in the professional solutions which I don't have in
      mine for obvious reasons. Also it looks as if they used malloc to handle the buffer, for which I just
      used a fixed buffer size and the functionality of fgets to handle overflow. They also implemented the
      functionality of the "-i" flag.
*/

#include <stdio.h>
#include <getopt.h>
#include <stdlib.h>

#define BUFFER_SIZE 1024

// Input buffer
char input_buffer[BUFFER_SIZE];

/* Prints out information regarding pogram use.

   Called using the --help flag

*/
void print_help()
{
    printf("Usage: tee [OPTION]... [FILE]...\n"
    "Copy standard input to each FILE, and also to standard output.\n\n"

    "   -a, --append              append to the given FILEs, do not overwrite\n"
    "         --help     display this help and exit\n"
    "         --version  output version information and exit\n");
}

/* Prints out information regarding program version.

   Called with the --version flag

*/
void print_version()
{
    printf("Version 0.0.1 -- Written by Mark Goldwater\n");
}

/* Takes in a file name and write/append argument to write to file.

   Takes standard input buffer and either appends to
   a file, or writes to a new file.

   optarg: name of file
   op: either "a" or "w"
*/
void load_file(char* optarg, char* op)
{
    FILE *out_file = fopen(optarg, op);
    while(fgets(input_buffer, BUFFER_SIZE, stdin) != NULL)
    {
      fprintf(out_file, "%s", input_buffer);
      printf("%s",input_buffer);
    }
    fclose(out_file);
}

int main(int argc, char* argv[])
{
    // Booleans triggered by user-input flags
    int do_help = 0;
    int do_version = 0;
    int do_file = 0;

    char ch;        // Variable to iterate through flags
    char* myfile;   // Stores file name
    char* op = "w"; // Stores file use mode ("a" or "w" for this program)

    // Struct for long user-inputed flags
    struct option longopts[] = {
        { "help", no_argument, & do_help, 1 },
        { "version", no_argument, & do_version, 1},
        { "append", required_argument, NULL, 'a'},
        { 0, 0, 0, 0 }
    };

    // Process flags and arguments, and set boolean variables
    while((ch = getopt_long(argc, argv, "a:", longopts, NULL)) != EOF)
    {
      switch(ch) {
        case 'a': ;
            do_file = 1;
            op = "a";
            myfile = optarg;
            break;
        case 0:
            // getopt_long() set a variable, just keep going
            break;
        case '?':
        default:
            //fprintf(stderr, "%s: option `-%c' is invalid: ignored\n", argv[0], optopt);
            return 1;
      }
    }

    // Update input variables
    argc -= optind;
    argv += optind;

    // Execute program
    if (do_help)
    {
      print_help();
    }
    else if (do_version)
    {
      print_version();
    }
    else if (do_file)
    {
      load_file(myfile, op);
    }
    else
    {
      myfile = argv[0];
      load_file(myfile, op);
    }
}
