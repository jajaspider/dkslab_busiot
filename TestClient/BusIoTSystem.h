#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/time.h>
#include <time.h>
#include <ctype.h>

#define BUF_SIZE 1024
#define BUF_LEN 1024
#define PORT 29903
#define IPADDR "113.198.235.247"
#define MAXTIMINGS 85
#define MAX_STR_LEN 4000

struct Settings{
  char setting_name[20];
  int setting_data;
  int min;
  int max;
} ;

struct timeval val;
struct Settings settings[100];

int setting_count=0;
char* millisecond;

char current_day[20];
char log_time[50];
char current_time[50];
char logdata[1024];

char* trim(char *s);
char* ltrim(char *s);
char* rtrim(char* s);
char* substring(char *input, int i_begin, int i_end);
int random_generation(char *str,int min,int max);
void log_management(char *log_data);
int load_setting();
int random_count();
