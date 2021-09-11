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
  char * filename = NULL;
  // Log info
  printf("# of arguments provided: %d\n", argc);

  // Get the command line arguments
  // optstring is simply  a list of characters, 
  // each representing a single character option.
  while((option = getopt(argc, argv, ":ht:")) != -1) {
    printf("Option: %c\n", option);
    switch(option) {
      case ':':
        printf("unkown option :\n");
        break;
      case '?':
        printf("unknown option ?\n");
        break;
      case 'h':
        printf("h: print Help usage message and terminate\n");
        // Print help message and terminate
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

  printf("Adding a new message\n");

  char type = 'E';
  const char * msg = "This is a test message";
  // addmsg(type, msg);

  return 0;
}
