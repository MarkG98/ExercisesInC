/* Example from Head First C.

Downloaded from https://github.com/twcamper/head-first-c

Modified by Allen Downey.

1. Only articles from the first RSS feed is printed because once execle() is run,
   this processes PID is passed to that function and then the program ends after
   the script is run once and returns.

*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>

// errno is an external global variable that contains
// error information
extern int errno;

void wait_error(char *argv[])
{
    fprintf(stderr, "wait failed: %s\n", strerror(errno));
    perror(argv[0]);
    exit(1);
}

void error(char *msg)
{
    fprintf(stderr, "%s: %s\n", msg, strerror(errno));
    exit(1);
}

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <search phrase>\n", argv[0]);
        return 1;
    }
    const char *PYTHON = "/usr/bin/python2";
    const char *SCRIPT = "rssgossip.py";
    char *feeds[] = {
        "http://www.nytimes.com/services/xml/rss/nyt/Africa.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Americas.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/MiddleEast.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/Europe.xml",
        "http://www.nytimes.com/services/xml/rss/nyt/AsiaPacific.xml"
    };
    int num_feeds = 5;
    char *search_phrase = argv[1];
    char var[255];
    pid_t pid;
    int status;

    for (int i=0; i<num_feeds; i++) {
        sprintf(var, "RSS_FEED=%s", feeds[i]);
        char *vars[] = {var, NULL};

        pid = fork();

        if (pid == -1)
        {
            error("Can't fork process.");
        }

        if (!pid)
        {
            int res = execle(PYTHON, PYTHON, SCRIPT, search_phrase, NULL, vars);
            if (res == -1) {
                error("Can't run script.");
            }
        }
    }

    for (int i = 0; i < num_feeds; i++) {
        pid = wait(&status);

        if (pid == -1) {
            wait_error(argv);
        }

        // check the exit status of the child
        status = WEXITSTATUS(status);
    }

    return 0;
}
