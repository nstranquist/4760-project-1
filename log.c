#include <log.h>

// Create Log list structure
typedef struct list_struct {
  data_t item;
  struct list_struct *next;
} log_t;

static log_t *headptr = NULL;
static log_t *tailptr = NULL;

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

  printf("Message received: %s\n", msg);

  // Get formatted time
  time_t tm = time(NULL);
  char * time_str = gettime(tm);
  printf("Time string: %s", time_str);

  int msg_length = strlen(msg) + strleng(time_str) + 1;

  // Populate data structure
  new_data->time = tm;
  new_data->type = type;
  new_data->string = malloc(msg_length);

  strcpy(new_data->string, msg);

  // Add timestamp to message and type and message string parameters

  // Add message to end of list
  log_t * new_node = malloc(sizeof(log_t));
  new_node->item = *new_data;
  new_node->next = NULL;
  
  if (headptr == NULL)
    headptr = new_node;
  else {
    tailptr->next = new_node;
  }
  tailptr = new_node;

  printdata(*new_data);

  if (new_data->string == NULL) {
    perror("Error: new_data->string is NULL (cannot be allocated with msg length)");
    free(new_data);
    return -1;
  }

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
  headptr = NULL;
  tailptr = NULL;


  // Empty the list of logs and free the allocated memory
  
}

// Utility function for printing the data structure to console
void printdata(data_t data) {
  printf("Type: %c\n", data.type);
  printf("Time: ");
  printtime(data.time);
  printf("Message: %s\n", data.string);
}

// Utility to print all logs in the list
void printlist() {
  printf("\nPrinting all Messages:\n");
  log_t * current = headptr;

  while(current != NULL) {
    printdata(current->item);
    current = current->next;
    printf("\n");
  }
}

// Print the time from time_t formatted in readable hh:mm:ss format
void printtime(time_t tm) {
  time(&tm);

  struct tm *tp = localtime(&tm);

  printf("%.2d:%.2d:%.2d\n", tp->tm_hour, tp->tm_min, tp->tm_sec);
}

// Return char string formatted in hh:mm:ss to add to messages
char * gettime(time_t tm) {
  time(&tm);
  struct tm *tp = localtime(&tm);

  char * buf[9];
  sprintf(*buf, "%.2d:%.2d:%.2d", tp->tm_hour, tp->tm_min, tp->tm_sec);
  printf("%s\n", *buf);

  return *buf;
}