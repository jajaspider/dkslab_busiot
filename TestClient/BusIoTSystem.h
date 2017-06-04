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
#include <stdint.h>
#include <math.h>

#define BUF_SIZE 1330693
#define BUF_LEN 1330693
#define PORT 45000
#define IPADDR "113.198.235.247"
#define MAXTIMINGS 85
#define MAX_STR_LEN 4000

#define BYTE						unsigned char

struct Settings{
  char setting_name[30];
  int setting_data;
  int min;
  int max;
  char *ascii_min;
  char *ascii_max;
} ;

struct timeval val;
struct Settings settings[200];

int obv_size = 0;
int setting_count=0;
int data_count=0;
int read_data_count=0;
char* millisecond;

char current_day[20];
char log_time[50];
char current_time[50];
char logdata[1024];

unsigned char over_byte_value[50];

unsigned char g_sendBuff[BUF_SIZE];

unsigned char g_recvBuff[BUF_SIZE];


char* trim(char *s);
char* ltrim(char *s);
char* rtrim(char* s);
char* substring(char *input, int i_begin, int i_end);
char *substr( char *pnInput, int nStart, int nLen );
int random_generation(char *str,int min,int max);
void ascii_generation(char *str,char *min,char *max,int data_length);
void log_management(char *log_data);
int load_setting();
int random_count();
