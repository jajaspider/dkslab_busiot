#include "BusIoTSystem.h"

int random_generation(char *str,int min,int max){
        int i;
        srand((unsigned int)time(NULL));
        i=rand()%(max-min)+min;
        char print_str[50];
        sprintf(print_str,"[BusIoTSystem] %s generation : %d",str,i);
        printf("%s\n",print_str);

        sprintf(logdata,"%s 값 랜덤생성",str);
        log_management(logdata);
        sprintf(logdata,"생성된 데이터 : %d",i);
        log_management(logdata);

        return i;
}

int random_count(){
        int i;
        srand(time(NULL));
        i=rand()%10;
        printf("[BusIoTSystem] ramdom generate number : %d\n",i);
        return i;
}

void log_management(char *log_data){
        FILE *f;
        char filename[20];
        sprintf(filename,"%s_log",current_day);
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

int load_setting(){
        FILE *f;
        char read_data[20];
        char temp_str[50];
        char *temp_str1;
        char *temp_str2;
        char *temp_str3;
        char *temp_str4;
        char *temp_str5;

        //파일이 있을 때
        if(access("settings.txt",0)==0) {
                f = fopen("settings.txt","r");
        }
        //파일이 없을 때
        else if(access("settings.txt",0)==-1) {
                log_management("settings.txt 파일을 찾을수없습니다.");
                return 1;
        }
        int i=0;
        while(!feof(f)) {
                fgets(temp_str,sizeof(temp_str),f);

                temp_str1=strtok(temp_str,"=");
                strcpy(settings[i].setting_name,temp_str1);

                temp_str2=strtok(NULL,"=");
                temp_str2=trim(temp_str2);

                temp_str3=strtok(temp_str2," ");
                temp_str4=strtok(NULL," ");
                temp_str5=strtok(NULL," ");

                settings[i].setting_data=atoi(temp_str3);
                settings[i].min=atoi(temp_str4);
                settings[i].max=atoi(temp_str5);

                printf("[BusIoTSystem] Setting Data : %s = %d ,min = %d, max = %d\n",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                sprintf(logdata,"%s 세팅값 : %d ,min = %d, max = %d",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                log_management(logdata);
                i+=1;
                setting_count+=1;
        }
        fclose(f);
        return 2;
}

char* trim(char *s) {
        return rtrim(ltrim(s));
}

// 문자열 우측 공백문자 삭제 함수
char* rtrim(char* s) {
        char t[MAX_STR_LEN];
        char *end;
        strcpy(t, s);
        end = t + strlen(t) - 1;
        while (end != t && isspace(*end))
                end--;
        *(end + 1) = '\0';
        s = t;

        return s;
}

// 문자열 좌측 공백문자 삭제 함수
char* ltrim(char *s) {
        char* begin;
        begin = s;

        while (*begin != '\0') {
                if (isspace(*begin))
                        begin++;
                else {
                        s = begin;
                        break;
                }
        }
        return s;
}

int main(int argc,char *argv[])
{
        int client_fd,len;
        struct sockaddr_in client_addr;
        char recv_data[BUF_SIZE];
        char buffer[BUF_LEN];
        char setting_string[50];
        char temp_string[10];
        char temp_string1[10];
        time_t timer;
        struct tm *t;
        int setting_flag;

        //배열 초기화
        memset(buffer,0x00,sizeof(buffer));
        memset(setting_string,0x00,sizeof(setting_string));

        //현재 시간 데이터 받아오기
        timer = time(NULL);
        t = localtime(&timer);
        sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
        sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

        log_management("시스템 시작");

        log_management("시스템 세팅값 불러오는 중");
        setting_flag=load_setting();
        if(setting_flag==1) {
                log_management("시스템 세팅값 불러오기 실패");
                return 0;
        }
        else if(setting_flag==2) {
                log_management("시스템 세팅값 불러오기 완료");
        }
        //세팅값에따른 바이트길이세팅
        //sprintf(setting_string,"%%0%dx%%0%dx%%0%dx%%0%dx%%0%dx%%0%dx%%0%dx\n",gps_x,gps_y,gps_time,temperature,humidity,passengercount,buttoncheck);


        int i=0;
        while(1) {
                client_fd = socket(PF_INET,SOCK_STREAM,0);
                client_addr.sin_addr.s_addr = inet_addr(IPADDR);
                client_addr.sin_family = AF_INET;
                client_addr.sin_port = htons(PORT);

                timer = time(NULL);
                t = localtime(&timer);
                sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
                sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
                sprintf(current_time,"%02d%02d%02d",t->tm_hour,t->tm_min,t->tm_sec);



                if(connect(client_fd,(struct sockaddr *)&client_addr,sizeof(client_addr))== -1)
                {
                        printf("[BusIoTSystem] Socket Can't connect\n");
                        log_management("소켓연결 에러");
                        close(client_fd);
                        sleep(5);
                }
                else{
                        printf("[BusIoTSystem] Socket connection Success\n");
                        log_management("접속 성공");

                        //탑승객 수 랜덤증감
                        if(random_count()>=5) {
                                i+=1;
                        }
                        else{
                                i-=1;
                        }
                        if(i<0)
                                i=0;
                        /*
                           //모든 데이터들 버퍼에 추가
                           sprintf(buffer,setting_string,random_generation("GPS_X",0,100000),random_generation_1("GPS_Y",0,100000),current_time,random_generation("Temperature",10,40),random_generation("Humidity",20,60),i,0);
                         */

                        //임시 세팅값 변경중
                        // sprintf(temp_string,"%%0%dx",settings[0].setting_data);
                        // sprintf(temp_string1,temp_string,current_time);
                        sprintf(temp_string,"%%0%dx%%0%dx%%0%dx",settings[0].setting_data,settings[1].setting_data,settings[2].setting_data)
                        sprintf(temp_string1,temp_string,t->tm_hour,t->tm_min,t->tm_sec);
                        printf("[DEBUG] current_time : %s\n", current_time);

                        strcat(buffer,temp_string1);
                        int j;
                        for(j=3; j<setting_count; j+=1) {
                                sprintf(temp_string,"%%0%dx",settings[j].setting_data);
                                sprintf(temp_string1,temp_string,random_generation(settings[j].setting_name,settings[j].min,settings[j].max));
                                strcat(buffer,temp_string1);
                        }

                        //전송
                        write(client_fd,buffer,strlen(buffer));
                        printf("[BusIoTSystem] Send Data %s\n",buffer);
                        sprintf(logdata,"전송된 데이터 : %s",buffer);
                        log_management(logdata);
                        //전송후 클라이언트 연결 끊음
                        close(client_fd);
                        printf("[BusIoTSystem] Close Connection\n");
                        sprintf(logdata,"접속 종료");
                        log_management(logdata);
                        //버퍼 초기화
                        memset(buffer,0x00,sizeof(buffer));
                        sleep(1);
                }
        }
        return 0;
}
