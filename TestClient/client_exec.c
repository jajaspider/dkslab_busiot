#include <stdio.h>
#include <unistd.h>

#define MAX_CLIENT 100

void log_management(char *log_data){
        FILE *f;
        char filename[13];
        sprintf(filename,"%s.log",current_day);
        //파일이 있을 때
        if(access(filename,0)==0) {
                f = fopen(filename,"a");
        }
        //파일이 없을 때
        else if(access(filename,0)==-1) {
                f = fopen(filename,"w");
        }
        fprintf(f, "[%s]%s\n",log_time,log_data);
        fclose(f);
}

int main()
{
        time_t timer;
        struct tm *t;

        timer = time(NULL);
        t = localtime(&timer);
        sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
        sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

        log_management("client_exec : 프로세스 생성 시작");
        int count = 0;
        pid_t pid[MAX_CLIENT];
        printf( "자식 프로세스 생성");

        while(count<MAX_CLIENT) {
                pid[count] = fork();
                switch(pid[count])
                {
                case -1:
                {
                        log_management("client_exec : 자식 프로세스 생성 실패");
                        printf( "자식 프로세스 생성 실패\n");
                        return -1;
                }
                case 0:
                {
                        log_management("client_exec : 자식 프로세스 생성");
                        printf("자식 프로세스 생성 성공.\n");
                        while(1)
                        {
                                log_management("client_exec : BusIoTSystem 실행");
                                system("./BusIoTSystem");
                        }
                }
                default:
                {

                }
                }
                count+=1;
        }
}
