#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct data_struct {
  time_t time; // Time stamp
  char type; // Message type (I/W/E/F)
  char * string; // Message string
} data_t;

int addmsg (const char type, const char * msg);
void clearlog();
char * getlog();
int savelog(char * filename);

void printdata(data_t data);
void printlist();
void printtime(time_t time);
char * gettime(time_t time);