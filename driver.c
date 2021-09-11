// driver.c

#include <time.h>
#include <stdio.h>

typedef struct data_struct {
  time_t time; // Time stamp
  char type; // Message type (I/W/E/F)
  char * string; // Message string
} data_t;

int addmsg (const char type, const char * msg);
void clearlog();
char * getlog();
int savelog(char * filename);

int main(int argc, char** argv) {
  printf("Hello, World!\n");

  return 0;
}

// The function addmsg creates the data structure data_t by adding the time stamp to the supplied parameters message type
// and message string, and inserts a copy of the data structure at the end of the list. It also verifies that the message type is a
// valid message type and issues an error if it is invalid.
int addmsg (const char type, const char * msg) {

}

/**
 * The savelog function saves the logged message to a disk file.
 * 
 */
int savelog(char * filename) {

}

/**
 * The
 * clearlog function releases all the storage that has been allocated for the logged message and empties the list of logged
 * messages
 */
char * getlog() {

}

/**
 * The getlog function allocates enough space for a string containing the entire log, copies the log into this string,
 * and returns a pointer to the string. It is the responsibility of the calling program to free this memory when necessary.
 */
void clearlog () {

}