#include <stdio.h>
#include <unistd.h>

#define MAX_CLIENT 100

int main()
{
   int count = 0;
   pid_t pid[MAX_CLIENT];
   printf( "자식 프로세스 생성");

   while(count<MAX_CLIENT){
     pid[count] = fork();
     switch(pid[count])
     {
        case -1:
        {
           printf( "자식 프로세스 생성 실패\n");
           return -1;
        }
        case 0:
        {
           printf("자식 프로세스 생성 성공.\n");
           while(1)
           {
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
