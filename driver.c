// driver.c

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <getopt.h>

typedef struct data_struct {
  time_t time; // Time stamp
  char type; // Message type (I/W/E/F)
  char * string; // Message string
} data_t;

int addmsg (const char type, const char * msg);
void clearlog();
char * getlog();
int savelog(char * filename);

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
    // then let user know that only the first non-option argument will be used as the filename
    filename = argv[optind];
  } 

  printf("Adding a new message\n");

  char type = 'E';
  const char * msg = "This is a test message";
  // addmsg(type, msg);

  return 0;
}

/**
 * - creates the data structure data_t by adding the timestamp to the supplied parameters message type and message string,
 * - and inserts a copy of the data structure at the end of the list.
 * - It also verifies that the message type is a valid message type
 * - and issues an error if it is invalid.
 */
int addmsg (const char type, const char * msg) {
  // Check if type is valid
  if(type != 'I' && type != 'W' && type != 'E' && type != 'F') {
    perror("Error: Message Type is invalid.");
    return -1;
  }

  if(type == 'F') {
    printf("Fatal Error. Printing message to file and exiting the program"); // filename
    return -1;
  }
  
  data_t * new_data = malloc(sizeof(data_t));

  if (new_data == NULL) {
    perror("Error: New messag could not be created");
    return -1;
  }

  new_data->time = time(NULL);
  new_data->type = type;
  new_data->string = malloc(strlen(msg) + 1);

  if (new_data->string == NULL) {
    perror("Error: new_data->string is NULL (cannot be allocated with msg length)");
    free(new_data);
    return -1;
  }

  strcpy(new_data->string, msg);
  return 0;
}

/**
 * The savelog function saves the logged message to a disk file.
 */
int savelog(char * filename) {
  FILE * fp = fopen(filename, "w");

  if(fp == NULL) {
    perror("Error: File could not be opened");
    return -1;
  }

  char * log = getlog();

  fprintf(fp, "%s", log);

  fclose(fp);

  return 0;
}

/**
 * The getlog function allocates enough space for a string containing the entire log, copies the log into this string,
 * and returns a pointer to the string. It is the responsibility of the calling program to free this memory when necessary.
 */
char * getlog() {
  return "Wow";
}

/**
 * The
 * clearlog function releases all the storage that has been allocated for the logged message and empties the list of logged
 * messages
 */
void clearlog () {

}