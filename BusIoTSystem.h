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

char current_day[20];
char log_time[50];
char current_time[50];
char logdata[100];
int gps_x;
int gps_y;
int gps_time;
int temperature;
int humidity;
int passengercount;
int buttoncheck;

char* trim(char *s);
char* ltrim(char *s);
char* rtrim(char* s);
int random_generation(char *str,int min,int max);
int gps_x_random_generation(int min,int max);
int gps_y_random_generation(int min,int max);
int temperature_random_generation(int min,int max);
int humidity_random_generation(int min,int max);
void log_management(char *log_data);
int setting_data();
int random_count();
