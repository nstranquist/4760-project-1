// driver.c

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>
#include <log.h>


// Global variables
data_t * recent_message;
char * filename = "messages.log";

// How to specify a main function to run? In a static archive library?

int main(int argc, char** argv) {
  int option;
  int print_messages = 0;
  int random_seconds = 0;

  // Get the command line arguments
  // optstring is simply  a list of characters, 
  // each representing a single character option.
  while((option = getopt(argc, argv, ":ht:")) != -1) {
    printf("Option: %c\n", option);
    switch(option) {
      case 'h':
        printf("h: print Help usage message and terminate\n");
        // Print help message and terminate
        return 0;
        break;
      case 't':
        printf("t: time in seconds\n");
        printf("%s\n", optarg);
        int secondsInput = atoi(optarg);
        // validate optarg to be a number
        if(!secondsInput && optarg != "0") {
          printf("Invalid time\n");
          // thow error
        }
        // Messages are printed every 'sec' seconds
        // Use random number generator to generate number between 0 and 2*seconds (from argument)
        int sec;
        int lower = 0;
        int upper = 2 * secondsInput;

        printf("Seconds provided to generate range: [%d - %2.d]\n", lower, upper);

        // Generate random number between 0 and 2
        int random =  rand() % (upper - lower + 1) + lower;
        printf("Random number generated: %d\n", random);

        random_seconds = random;
        print_messages = 1;

        break;
      default:
        printf("?: Unknown option\n");
        break;
    }
  }

  if (optind < argc) {
    printf("filename is %s\n", argv[optind]);
    // then let user know that only the first non-option argument will be used as the filename
    filename = argv[optind];
  }
  else {
    printf("No filename provided. Using default name: %s\n", filename);
  }

  if(print_messages == 1) {
    FILE * fp = fopen(filename, "r");

    if(fp == NULL) {
      perror("Error opening the file.");
      return -1;
    }

    char * line = NULL;
    size_t len = 0;
    ssize_t read;

    // read file line by line
    while ((read = getline(&line, &len, fp)) != -1) {
      printf("%s", line);
      sleep(random_seconds);
    }

    printf("All messages from the file have been read.\n");

    fclose(fp);

    // exit after reading all lines
    return 0;
  }

  // Demonstrate functionality in driver.
  printf("Adding a new message\n");

  char type = 'E';
  char * msg = "This is a test message";
  addmsg(type, msg);

  printf("Saving log to disk.\n");
  // savelog(filename);
  savelog(filename);

  char next_type = 'W';
  char * next_msg = "This is another test message";

  addmsg(next_type, next_msg);
  printf("finished adding second message\n");

  savelog(filename);

  printf("Printing all messages in list\n");

  printlist();

  printf("Getting messages log.\n");
  char * full_log = getlog();

  printf("Full log: %s\n", full_log);

  printf("\nClearing message log.\n");

  clearlog();

  printlist();

  return 0;
}
