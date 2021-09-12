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