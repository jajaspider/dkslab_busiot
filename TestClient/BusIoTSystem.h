#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>
#include <ctype.h>

#define BUF_SIZE 1024
#define BUF_LEN 1024
#define PORT 29903
#define IPADDR "113.198.236.96"
#define MAXTIMINGS 85
#define MAX_STR_LEN 4000

struct Settings{
  char setting_name[20];
  int setting_data;
} ;

struct Settings settings[20];

char current_day[20];
char log_time[50];
char current_time[50];
char logdata[100];
int gps_x=0;
int gps_y=0;
int gps_time=0;
int temperature=0;
int humidity=0;
int passengercount=0;
int buttoncheck=0;
int setting_count=0;

char* trim(char *s);
char* ltrim(char *s);
char* rtrim(char* s);
int random_generation(char *str,int min,int max);
void log_management(char *log_data);
int load_setting();
int random_count();
