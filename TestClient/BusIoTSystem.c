#include "BusIoTSystem.h"

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
        srand(gettimeofday(&val,NULL));
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

char *substr(char *pnInput,int nStart,int nLen ){
        int nLoop;
        int nLength;
        char *pszOutPut;

        if( pnInput == NULL ) {
                return NULL;
        }
        pszOutPut = (char *)malloc( sizeof(char) * nLen + 1 );
        nLength = strlen( pnInput );
        if( nLength > nStart + nLen ) {
                nLength = nStart + nLen;
        }
        for( nLoop = nStart; nLoop < nLength; nLoop++ ) {
                pszOutPut[nLoop-nStart] = pnInput[nLoop];
        }
        pszOutPut[nLoop - nStart] = '\0';
        return pszOutPut;
}

void ascii_generation(char *str,char *min,char *max,int data_length){
        srand(gettimeofday(&val,NULL));
        int i;
        char print_str[100];
        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : ",str);
        printf("%s",print_str);
        for(i=0; i<data_length; i+=1) {
                char *temp1;
                char *temp2;
                temp1 = substr(min,i,1);
                temp2 = substr(max,i,1);
                int temp_1 = atoi(temp1);
                int temp_2 = atoi(temp2);
                int temp_3 = rand()%(temp_2-temp_1)+temp_1;
                if(temp_3==0) {
                        g_sendBuff[data_count++] = 0x30;
                        printf("30");
                }
                if(temp_3==1) {
                        g_sendBuff[data_count++] = 0x31;
                        printf("31");
                }
                if(temp_3==2) {
                        g_sendBuff[data_count++] = 0x32;
                        printf("32");
                }
                if(temp_3==3) {
                        g_sendBuff[data_count++] = 0x33;
                        printf("33");
                }
                if(temp_3==4) {
                        g_sendBuff[data_count++] = 0x34;
                        printf("34");
                }
                if(temp_3==5) {
                        g_sendBuff[data_count++] = 0x35;
                        printf("35");
                }
                if(temp_3==6) {
                        g_sendBuff[data_count++] = 0x36;
                        printf("36");
                }
                if(temp_3==7) {
                        g_sendBuff[data_count++] = 0x37;
                        printf("37");
                }
                if(temp_3==8) {
                        g_sendBuff[data_count++] = 0x38;
                        printf("38");
                }
                if(temp_3==9) {
                        g_sendBuff[data_count++] = 0x39;
                        printf("39");
                }
                printf(" ");
        }
        printf("\n");
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
        char *temp_str6;
        char *flag_substr;

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
                flag_substr = substr(temp_str4,0,5);
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
                // ascii 값
                else if(!strcmp(flag_substr,"ascii")) {
                        temp_str5=strtok(NULL," ");
                        temp_str6=strtok(NULL," ");
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min = 9994;
                        settings[i].max = 9994;
                        settings[i].ascii_min=temp_str5;
                        settings[i].ascii_max=temp_str6;
                        printf("[BusIoTSystem] Setting Data ASCII : %s = %d ,min = %s, max = %s\n",settings[i].setting_name,settings[i].setting_data,settings[i].ascii_min,settings[i].ascii_max);
                        sprintf(logdata,"BusIoTSystem : %s ASCII 세팅값 : %d byte,min = %d, max = %d",settings[i].setting_name,settings[i].setting_data,settings[i].ascii_min,settings[i].ascii_max);
                        log_management(logdata);
                }
                else{
                        temp_str5=strtok(NULL," ");
                        //세팅 구조체에 세팅값 저장
                        settings[i].setting_data=atoi(temp_str3);
                        settings[i].min=atoi(temp_str4);
                        settings[i].max=atoi(temp_str5);
                        printf("[BusIoTSystem] Setting Data : %s = %d ,min = %d, max = %d\n",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                        sprintf(logdata,"BusIoTSystem : %s 세팅값 : %d min = %d, max = %d",settings[i].setting_name,settings[i].setting_data,settings[i].min,settings[i].max);
                        log_management(logdata);
                }
                i+=1;
                setting_count+=1;
        }
        fclose(f);
        return 2;
}

void auto_byte_generation(char *log_data, int data,int data_length){
        //int quotient[data_length];
        int real_data[data_length];
        int j;
        for(j=0; j<data_length; j+=1) {
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
                        read_data_count++;
                }
                else if((unsigned char)real_data[i]==0x03) {
                        g_sendBuff[data_count++] = 0x10;
                        g_sendBuff[data_count++] = 0x17;
                        read_data_count++;
                }
                else if((unsigned char)real_data[i]==0x10) {
                        g_sendBuff[data_count++] = 0x10;
                        g_sendBuff[data_count++] = 0x10;
                        read_data_count++;
                }
                else{
                        g_sendBuff[data_count++] = (unsigned char)real_data[i];
                        read_data_count++;
                }
        }
        char print_str[100];
        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : ",log_data);
        int temp_for;
        printf("%s",print_str);
        for(temp_for=0; temp_for<data_length; temp_for+=1) {
                printf("%02x ",real_data[temp_for]);
        }
        printf("\n");
}

void ClearSendBuff () {
        memset(g_sendBuff, '\0', BUF_SIZE);
        data_count = 0;
        read_data_count =0;
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
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_hour;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_min;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_sec;
                                        g_sendBuff[data_count++] = (unsigned char)t->tm_sec;
                                        read_data_count=read_data_count+4;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %02x %02x %02x %02x",settings[j].setting_name,t->tm_hour,t->tm_min,t->tm_sec,t->tm_sec);
                                        printf("%s\n",print_str);

                                }
                                // STX 변환규칙
                                else if(settings[j].min==9997&&settings[j].max==9997) {
                                        g_sendBuff[data_count++] = (unsigned char)2;
                                        read_data_count++;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %d",settings[j].setting_name,2);
                                        printf("%s\n",print_str);
                                }
                                // ETX 변환규칙
                                else if(settings[j].min==9996&&settings[j].max==9996) {
                                        g_sendBuff[data_count++] = (unsigned char)3;
                                        read_data_count++;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %d",settings[j].setting_name,3);
                                        printf("%s\n",print_str);
                                }
                                // ESC 변환규칙
                                else if(settings[j].min==9995&&settings[j].max==9995) {
                                        g_sendBuff[data_count++] = (unsigned char)10;
                                        read_data_count++;
                                        sprintf(print_str,"[BusIoTSystem] %s 값 추가 : %d",settings[j].setting_name,10);
                                        printf("%s\n",print_str);
                                }
                                // ascii 추가
                                else if(settings[j].min==9994&&settings[j].max==9994) {
                                        ascii_generation(settings[j].setting_name,settings[j].ascii_min,settings[j].ascii_max,settings[j].setting_data);
                                }
                                else{
                                        auto_byte_generation(settings[j].setting_name,random_generation(settings[j].setting_name,settings[j].min,settings[j].max),settings[j].setting_data);
                                }
                        }

                        // 데이터 전송
                        send(client_fd, g_sendBuff, data_count, 0);
                        printf("[BusIoTSystem] Send Data : ");
                        int max_leng;
                        for(max_leng=0; max_leng<data_count; max_leng+=1) {
                                printf("%02x ",g_sendBuff[max_leng]);
                        }

                        printf("\n");
                        log_management(logdata);
                        printf("[BusIoTSystem] 데이터 총 길이 : %d\n",read_data_count);
                        sprintf(logdata,"[BusIoTSystem] 데이터 총 길이 : %d",read_data_count);
                        log_management(logdata);
                        ClearSendBuff();
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
