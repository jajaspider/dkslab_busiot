#include "BusIoTSystem.h"

char* trim(char *s) {
        return rtrim(ltrim(s));
}

//비트열 unsigned char 변환 함수
// void ch_test(int Byte_size, int temp) {
//   int i,sum=0,count = 3;
//   int size = Byte_size*8;
//   int *change_U_char = (int*)malloc(sizeof(char)*Byte_size);
//         printf("temp :%d\n", temp);
//         printf("size :%d\n", size);
//         printf("change_U_char :%d\n", sizeof(change_U_char));
//         for(i=1; i<= Byte_size*8; i++) {
//                 if((temp>>(size-i))&1) {
//                         change_U_char[i-1] = 1;
//                 }
//                 else{
//                         change_U_char[i-1] = 0;
//                 }
//                 printf("change_U_char2 : %d\n",change_U_char[i-1]);
//         }
// printf("\n");
//         for (i = 0; i < Byte_size*8; i++) {
//           sum+=(change_U_char[i]*(pow(2,count)));
//           count--;
//           if(count<0){
//             over_byte_value[obv_size]=(unsigned char)sum;
//             sum=0;
//             obv_size++;
//             count = 3;
//           }
//         }
//         for (i = 0; i < obv_size; i++) {
//           printf("%c\n",over_byte_value[obv_size]);
//         }
// }

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

//문자열 자르기 함수
char* substring(char *input, int i_begin, int i_end)
{
        int cnt = 0;
        int size = (i_end - i_begin)+2;
        char *str = (char*)malloc(size);

        memset(str, 0, size);
        for(int i = i_begin; i <= i_end; i++)
        {
                str[cnt] = input[i];
                cnt++;
        }
        return str;
}

int random_generation(char *str,int min,int max){
        int i;
        srand((unsigned int)time(NULL));
        i=rand()%(max-min)+min;
        //char print_str[100];
        //sprintf(print_str,"[BusIoTSystem] %s generation : %d",str,i);
        //printf("%s\n",print_str);

        sprintf(logdata,"BusIoTSystem : %s 값 랜덤생성",str);
        log_management(logdata);
        sprintf(logdata,"BusIoTSystem : 생성된 데이터 : %d",i);
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

int load_setting(){
        FILE *f;
        char temp_str[1024];
        char *temp_str1;
        char *temp_str2;
        char *temp_str3;
        char *temp_str4;
        char *temp_str5;

        //파일이 있을 때
        if(access("settings.txt",0)==0) {
                f = fopen("settings.txt","rb");
        }
        //파일이 없을 때
        else if(access("settings.txt",0)==-1) {
                log_management("BusIoTSystem : settings.txt 파일을 찾을수없습니다.");
                return 1;
        }
        int i=0;
        while(!feof(f)) {
                fgets(temp_str,sizeof(temp_str),f);
                //fscanf(f,"%s",&temp_str);
                temp_str[strlen(temp_str)-1]='\0';

                //printf("[DEBUG]%s\n",temp_str);
                temp_str1=strtok(temp_str,"=");
                temp_str1=trim(temp_str1);
                strcpy(settings[i].setting_name,temp_str1);

                //세팅파일 형식에따라  strtok 추가
                temp_str2=strtok(NULL,"=");
                temp_str2=trim(temp_str2);
                temp_str3=strtok(temp_str2," ");
                temp_str4=strtok(NULL," ");
                //시간 시 분 초 데이터
                if(!strcmp(temp_str4,"timeauto1")) {
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9999;
                        settings[i].max = 9999;
                        printf("[BusIoTSystem] Setting Data : %s = %d\n",settings[i].setting_name,settings[i].setting_data);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte, autotime1 setting",settings[i].setting_name,settings[i].setting_data);
                        log_management(logdata);
                }
                //시간 시 분 초 밀리초 데이터
                else if(!strcmp(temp_str4,"timeauto2")) {
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9998;
                        settings[i].max = 9998;
                        printf("[BusIoTSystem] Setting Data : %s = %d\n",settings[i].setting_name,settings[i].setting_data);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte, autotime2 setting",settings[i].setting_name,settings[i].setting_data);
                        log_management(logdata);
                }
                //STX 데이터
                else if(!strcmp(temp_str4,"STX")) {
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9997;
                        settings[i].max = 9997;
                        printf("[BusIoTSystem] Setting Data : %s = %d\n",settings[i].setting_name,settings[i].setting_data);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte, STX setting",settings[i].setting_name,settings[i].setting_data);
                        log_management(logdata);
                }
                //ETX 데이터
                else if(!strcmp(temp_str4,"ETX")) {
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9996;
                        settings[i].max = 9996;
                        printf("[BusIoTSystem] Setting Data : %s = %d\n",settings[i].setting_name,settings[i].setting_data);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte, ETX setting",settings[i].setting_name,settings[i].setting_data);
                        log_management(logdata);
                }
                //ESC 데이터
                else if(!strcmp(temp_str4,"ESC")) {
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9995;
                        settings[i].max = 9995;
                        printf("[BusIoTSystem] Setting Data : %s = %d\n",settings[i].setting_name,settings[i].setting_data);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte, ESC setting",settings[i].setting_name,settings[i].setting_data);
                        log_management(logdata);
                }
                else{
                        temp_str5=strtok(NULL," ");
                        //세팅 구조체에 세팅값 저장
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min=atoi(temp_str4);
                        settings[i].max=atoi(temp_str5);
                        printf("[BusIoTSystem] Setting Data : %s = %d ,min = %d, max = %d\n",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d byte,min = %d, max = %d",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                        log_management(logdata);
                }
                i+=1;
                setting_count+=1;
        }
        fclose(f);
        return 2;
}

void auto_increament(int data,int data_length){
        //int quotient[data_length];
        int real_data[data_length];
        int j;
        for(j=0;j<data_length;j+=1){
          real_data[j]=0;
        }

        int i=1;

        real_data[data_length-1] = data%256;
        if(data>256) {
                int temp_quotient=data/256;
                if(temp_quotient<256) {
                        real_data[data_length-2] = temp_quotient;
                }
                else {
                        int temp=temp_quotient/256;
                        if(temp<256) {
                                real_data[data_length-2] = temp_quotient%256;
                                real_data[data_length-3] = temp;
                        }
                        else{
                                int temp1=temp/256;
                                if(temp1<256) {
                                        real_data[data_length-3] = temp%256;
                                        real_data[data_length-4] = temp1;
                                }
                        }
                }
        }
        for(i=0; i<data_length; i+=1) {

                if((unsigned char)real_data[i]==0x02) {
                        g_sendBuff[data_count++] = 0x10;
                        g_sendBuff[data_count++] = 0x16;
                }
                else if((unsigned char)real_data[i]==0x03) {
                        g_sendBuff[data_count++] = 0x10;
                        g_sendBuff[data_count++] = 0x17;
                }
                else if((unsigned char)real_data[i]==0x10) {
                        g_sendBuff[data_count++] = 0x10;
                        g_sendBuff[data_count++] = 0x10;
                }
                else{
                        g_sendBuff[data_count++] = (unsigned char)real_data[i];
                }
        }
}

void ClearSendBuff () {
        memset(g_sendBuff, '\0', BUF_SIZE);
        data_count = 0;
}

int main(int argc,char *argv[])
{
        int client_fd,len;
        struct sockaddr_in client_addr;
        unsigned char buffer[BUF_LEN];
        unsigned char temp_string[20];
        unsigned char temp_string1[50];
        unsigned char *real_temp;
        time_t timer;
        struct tm *t;
        int setting_flag;

        //배열 초기화
        memset(buffer,0x00,sizeof(buffer));

        //현재 시간 데이터 받아오기
        timer = time(NULL);
        t = localtime(&timer);
        sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
        sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);

        log_management("BusIoTSystem : 시스템 시작");

        log_management("BusIoTSystem : 시스템 세팅값 불러오는 중");
        setting_flag=load_setting();
        if(setting_flag==1) {
                log_management("BusIoTSystem : 시스템 세팅값 불러오기 실패");
                return 0;
        }
        else if(setting_flag==2) {
                log_management("BusIoTSystem : 시스템 세팅값 불러오기 완료");
        }

        int i=0;
        while(1) {
                char print_str[100];


                client_fd = socket(PF_INET,SOCK_STREAM,0);
                client_addr.sin_addr.s_addr = inet_addr(IPADDR);
                client_addr.sin_family = AF_INET;
                client_addr.sin_port = htons(PORT);

                timer = time(NULL);
                gettimeofday(&val,NULL);
                t = localtime(&val.tv_sec);

                sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
                sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
                sprintf(current_time,"%02d%02d%02d",t->tm_hour,t->tm_min,t->tm_sec);



                if(connect(client_fd,(struct sockaddr *)&client_addr,sizeof(client_addr))== -1)
                {
                        printf("[BusIoTSystem] Socket Can't connect\n");
                        log_management("BusIoTSystem : 소켓연결 에러");
                        close(client_fd);
                        sleep(5);
                }
                else{
                        printf("[BusIoTSystem] Socket connection Success\n");
                        log_management("BusIoTSystem : 접속 성공");

                        //탑승객 수 랜덤증감
                        if(random_count()>=5) {
                                i+=1;
                        }
                        else{
                                i-=1;
                        }
                        if(i<0)
                                i=0;

                        int j;
                        for(j=0; j<setting_count; j+=1) {
                                timer = time(NULL);
                                gettimeofday(&val,NULL);
                                //시간 시 분초 데이터
                                if(settings[j].min==9999&&settings[j].max==9999) {
                                        sprintf(current_day,"%d%02d%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday);
                                        sprintf(log_time,"%d-%02d-%02d %02d:%02d:%02d",t->tm_year+1900,t->tm_mon+1,t->tm_mday,t->tm_hour,t->tm_min,t->tm_sec);
                                        sprintf(current_time,"%02d%02d%02d",t->tm_hour,t->tm_min,t->tm_sec);
                                        // sprintf(temp_string,"%%0%dx%%0%dx%%0%dx",(settings[j].setting_data)/3,(settings[j].setting_data)/3,(settings[j].setting_data)/3);
                                        // sprintf(temp_string1,(unsigned char)temp_string,t->tm_hour,t->tm_min,t->tm_sec);
                                        // temp_string1[0] = (unsigned char)t->tm_hour;
                                        // temp_string1[1] = (unsigned char)t->tm_min;
                                        // temp_string1[2] = (unsigned char)t->tm_sec;
                                        // temp_string1[3] = (unsigned char)t->tm_sec;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_hour;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_min;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_sec;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_sec;
                                        // strcat(buffer,temp_string1);
                                        // memset(temp_string1,0x00,sizeof(temp_string1));
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %d%d%d",settings[i].setting_name,t->tm_hour,t->tm_min,t->tm_sec);
                                        printf("%s\n",print_str);

                                }
                                // STX 변환규칙
                                else if(settings[j].min==9997&&settings[j].max==9997) {
                                        // sprintf(temp_string1,(unsigned char)2);
                                        // temp_string1[0] = (unsigned char)2;
                                        // strcat(buffer,temp_string1);
                                        // memset(temp_string1,0x00,sizeof(temp_string1));
                                        g_sendBuff[data_count++] = (unsigned char)2;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %c",settings[j].setting_name,(unsigned char)2);
                                        printf("%s\n",print_str);
                                }
                                // ETX 변환규칙
                                else if(settings[j].min==9996&&settings[j].max==9996) {
                                        // sprintf(temp_string1,(unsigned char)3);
                                        // temp_string1[0] = (unsigned char)3;
                                        // strcat(buffer,temp_string1);
                                        memset(temp_string1,0x00,sizeof(temp_string1));
                                        g_sendBuff[data_count++] = (unsigned char)3;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %c",settings[j].setting_name,(unsigned char)3);
                                        printf("%s\n",print_str);
                                }
                                // ESC 변환규칙
                                else if(settings[j].min==9995&&settings[j].max==9995) {
                                        // sprintf(temp_string1,(unsigned char)10);
                                        // temp_string1[0] = (unsigned char)10;
                                        // strcat(buffer,temp_string1);
                                        // memset(temp_string1,0x00,sizeof(temp_string1));
                                        g_sendBuff[data_count++] = (unsigned char)10;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %c",settings[j].setting_name,(unsigned char)10);
                                        printf("%s\n",print_str);
                                }
                                else{
                                        // sprintf(temp_string,"%%0%dx",settings[j].setting_data);
                                        // sprintf(temp_string1,(unsigned char)temp_string,random_generation(settings[j].setting_name,settings[j].min,settings[j].max));
                                        // real_temp = (unsigned char)random_generation(settings[j].setting_name,settings[j].min,settings[j].max);
                                        // strcat(buffer,real_temp);
                                        // memset(temp_string1,0x00,sizeof(temp_string1));
                                        auto_increament(random_generation(settings[j].setting_name,settings[j].min,settings[j].max),settings[j].setting_data);
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %d",settings[j].setting_name,random_generation(settings[j].setting_name,settings[j].min,settings[j].max));
                                        printf("%s\n",print_str);
                                }
                        }

                        //전송1
                        // write(client_fd,buffer,strlen(buffer));
                        // printf("[BusIoTSystem] Send Data : %s\n",buffer);
                        // sprintf(logdata,"BusIoTSystem : 전송된 데이터 : %s",buffer);
                        // log_management(logdata);
                        // printf("[BusIoTSystem] 데이터 총 길이 : %d\n",strlen(buffer));
                        // sprintf(logdata,"[BusIoTSystem] 데이터 총 길이 : %d",strlen(buffer));
                        // log_management(logdata);

                        // 전송2
                        send(client_fd, g_sendBuff, data_count, 0);
                        ClearSendBuff();
                        //printf("[BusIoTSystem] Send Data : %s\n",g_sendBuff);
                        //sprintf(logdata,"BusIoTSystem : 전송된 데이터 : %s",g_sendBuff);
                        printf("[BusIoTSystem] Send Data : ");
                        int max_leng;
                        for(max_leng=0;max_leng<data_count;max_leng+=1){
                          printf("0x%x ",g_sendBuff[max_leng]);
                        }
                        printf("\n");
                        log_management(logdata);
                        printf("[BusIoTSystem] 데이터 총 길이 : %d\n",strlen(g_sendBuff));
                        sprintf(logdata,"[BusIoTSystem] 데이터 총 길이 : %d",strlen(g_sendBuff));
                        log_management(logdata);

                        //전송후 클라이언트 연결 끊음
                        close(client_fd);
                        printf("[BusIoTSystem] Close Connection\n");
                        sprintf(logdata,"BusIoTSystem : 접속 종료");
                        log_management(logdata);
                        //버퍼 초기화
                        memset(buffer,0x00,sizeof(buffer));
                        sleep(1);
                }
        }
        return 0;
}
