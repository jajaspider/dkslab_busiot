#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <time.h>

#define BUF_SIZE 1024
#define BUF_LEN 1024
#define PORT 29903
#define IPADDR "113.198.236.96"
#define busnumber "70자6665"
#define MAXTIMINGS 85
int dht11_dat[5] = {0,};

int gps_random_generation(int min,int max){
        int i;
        srand(time(NULL));
        i=rand()%(max-min)+min;
        printf("[BusIoTSystem]GPS generation : %d\n",i);
        return i;
}

int random_count(){
        int i;
        srand(time(NULL));
        i=rand()%10;
        printf("[BusIoTSystem]ramdom generate number : %d\n",i);
        return i;
}

int temperature_random_generation(int min,int max){
        int i;
        srand(time(NULL));
        i=rand()%(max-min)+min;
        printf("[BusIoTSystem]temperature generation : %d\n",i);
        return i;
}

int humidity_random_generation(int min,int max){
        int i;
        srand(time(NULL));
        i=rand()%(max-min)+min;
        printf("[BusIoTSystem]Humidity generation : %d\n",i);
        return i;
}

int main(int argc,char *argv[])
{
        int client_fd,len;
        struct sockaddr_in client_addr;
        char recv_data[BUF_SIZE];
        char buffer[BUF_LEN];
        time_t timer;
        struct tm *t;

        memset(buffer,0x00,sizeof(buffer));
        client_fd = socket(PF_INET,SOCK_STREAM,0);
        client_addr.sin_addr.s_addr = inet_addr(IPADDR);
        client_addr.sin_family = AF_INET;
        client_addr.sin_port = htons(PORT);
        /*if(connect(client_fd,(struct sockaddr *)&client_addr,sizeof(client_addr))== -1)
        {
                printf("[BusIoTSystem]Socket Can't connect\n");
                close(client_fd);
                return -1;
        }*/
        //temp
        int i=0;
        while(1) {
                timer = time(NULL);
                t = localtime(&timer);
                //탑승객wwwwww
                if(random_count()>=5) {
                        i+=1;
                }
                else{
                        i-=1;
                }
                if(i<0)
                        i=0;
                char temp_string[BUF_LEN];
                char temp_str[6]="%06x";
                char temp_str1[6]="%02x";
                sprintf(temp_string,"%s%s%s%s%s%s%s%s\n",temp_str,temp_str,temp_str1,temp_str1,temp_str1,temp_str1,temp_str1,temp_str1);
                printf("string %s",temp_string);
                //sprintf(buffer,"%06x%06x%02x%02x%02x%02x%02x%02x",gps_random_generation(0,200000),gps_random_generation(0,100000),t->tm_hour,t->tm_min,t->tm_sec,temperature_random_generation(10,40),humidity_random_generation(20,60),i);
                sprintf(buffer,temp_string,gps_random_generation(0,200000),gps_random_generation(0,100000),t->tm_hour,t->tm_min,t->tm_sec,temperature_random_generation(10,40),humidity_random_generation(20,60),i);
                printf("[BusIoTSystem]Send Data %s\n",buffer);
                //send(client_fd,"c",strlen(buffer),0);
                //int temp = 14;
                write(client_fd,buffer,strlen(buffer));
                //write(client_fd,'a',4);
                //buffer[0] = '\0';
                //memset(buffer,0x00,sizeof(buffer));
                //recv(client_fd,recv_data,sizeof(recv_data),0);
                //printf("recv data : %s\n",recv_data);

                sleep(1);
        }
        //    close(client_fd);
        return 0;
}
